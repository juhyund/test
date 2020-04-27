package com.nuri.kepco.fep.saver;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.eclipse.leshan.core.node.LwM2mPath;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.aimir.util.TimeUtil;
import com.nuri.kepco.fep.datatype.LPData;
import com.nuri.kepco.fep.datatype.MDData;
import com.nuri.kepco.fep.datatype.MeterAccessResult;
import com.nuri.kepco.fep.mddata.AbstractMDSaver;
import com.nuri.kepco.fep.mddata.IMeasurementData;
import com.nuri.kepco.fep.parser.DLMSVARIABLE;
import com.nuri.kepco.fep.parser.DLMSVARIABLE.OBIS;
import com.nuri.kepco.fep.parser.KepcoMDDataParser;
import com.nuri.kepco.model.DeviceInfo;
import com.nuri.kepco.model.DevicePowerLog;
import com.nuri.kepco.model.MeterBilling;
import com.nuri.kepco.model.MeterData;
import com.nuri.kepco.model.MeterInfo;
import com.nuri.kepco.model.MeterValue;
import com.nuri.kepco.model.OperationLog;
import com.nuri.kepco.model.dao.DeviceInfoDAO;
import com.nuri.kepco.model.dao.DevicePowerLogDAO;
import com.nuri.kepco.model.dao.MeterBillingDAO;
import com.nuri.kepco.model.dao.MeterDataDAO;
import com.nuri.kepco.model.dao.MeterInfoDAO;
import com.nuri.kepco.model.dao.MeterValueDAO;
import com.nuri.kepco.model.dao.OperationLogDAO;

@Service
public class KepcoMDDataSaver extends AbstractMDSaver {
	
	private static final Logger LOG = LoggerFactory.getLogger(KepcoMDDataSaver.class);
	
	@Autowired
	MeterValueDAO meterValueDAO;
	
	@Autowired
	MeterBillingDAO meterBillingDAO;
	
	@Autowired
	MeterInfoDAO meterInfoDAO;
	
	@Autowired
	DeviceInfoDAO deviceInfoDAO;
	
	@Autowired
	OperationLogDAO operationLogDAO;
	
	@Autowired
	DevicePowerLogDAO devicePowerLogDAO;
	
	@Autowired
	MeterDataDAO meterDataDAO;
		
	@Override
	public boolean save(IMeasurementData md) throws Exception {
		
		KepcoMDDataParser parser = (KepcoMDDataParser)md.getMeterDataParser();
		
		if(parser.getMeterAccessResult() != null) { // meterAccessResult
			
			meterAccessResultSaver(parser, md);
			
		} else if(parser.getMDList().size() > 0) { // 검침정보 
			
			mdDataSaver(parser, md);
			
		} else if(parser.getDevicePowerLog() != null) { // devicePowerOnOff
			
			mdDevicePowerLogSaver(parser, md);
			
		}
		 
		return true;
	}
	
	/**
	 * meterAccessResultSaver
	 * @param parser
	 * @param md
	 */
	private void meterAccessResultSaver(KepcoMDDataParser parser, IMeasurementData md) {
		
		MeterAccessResult meterAccessResult = parser.getMeterAccessResult();
		Map<Integer, String> meterStatus = (Map<Integer, String>)meterAccessResult.getMeterStatus();
		
		// OperationLog에 결과를 저장한다.
		try {
			
			// device info
			String device_serial = md.getDeviceId();
			DeviceInfo deviceInfo = deviceInfoDAO.selectByDeviceSerial(device_serial);
			
			String payload = "";
			payload += "OBIS [" + meterAccessResult.getOBIS() + "]\n";
			payload += "APDU [" + meterAccessResult.getAPDU() + "]\n";
			payload += meterAccessResult.getResultMsg();
			
			for(Integer key : meterStatus.keySet()) {			

				// meter info param				
				MeterInfo param = new MeterInfo();				
				param.setMeter_serial(String.valueOf(key));
				param.setDevice_serial(device_serial);
				
				LOG.debug("key : {}" , key);
				LOG.debug(meterStatus.get(key));
				
				
				// meter info
				MeterInfo meterInfo = meterInfoDAO.getMeterInfoBySerial(param);				
				payload += "=============================\n";						
				payload += "Meter Serial [" + meterInfo.getMeter_serial() + "] STATUS [" + meterStatus.get(key) + "]\n";
				payload += "=============================\n";
			}
			
			OperationLog operationLog = new OperationLog();
			operationLog.setDevice_id(deviceInfo.getDevice_id());
			operationLog.setRequest_dt(md.getModemTime());
			operationLog.setObject_id(31012); // METER ACCESS
			operationLog.setFormat("JSON");
			operationLog.setPayload(payload);
			operationLog.setResult(1);		
			operationLog.setResult_dt(md.getModemTime());
			
			int result = operationLogDAO.insert(operationLog);
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	/**
	 * mdDataSaver
	 * @param parser
	 * @param md
	 */
	private void mdDataSaver(KepcoMDDataParser parser, IMeasurementData md) {
		List<MDData> mdList = parser.getMDList();		
		String deviceSerial = md.getDeviceId();
		
		LOG.debug("## deviceSerial Saver : {}" , deviceSerial);
		
		// checkDevice
		DeviceInfo deviceInfo = checkDevice(deviceSerial, md.getModemTime(), parser.getMobileNo());
		
		if(deviceInfo != null) {
				
			for (MDData mdData : mdList) {
 
				if(mdData.getMeterTime() == null) {
					if(mdData.getLpDatas() != null) {
						// lp의 미터시간은 lpDatas의 마지막 read_dt
						if(mdData.getLpDatas().size() > 0) {
							LPData lp = mdData.getLpDatas().get(mdData.getLpDatas().size() - 1);							
							mdData.setMeterTime(lp.getRead_dt() + "00");
						}
					}
				}
				
				// 0. check meter
				checkMeter(mdData, deviceInfo);
				
				// 1. update dynamic Schedule
				saveDynamicData(mdData, deviceInfo);
				
				LOG.debug("meter time : {}" , mdData.getMeterTime());
				
				if(mdData.getMeterInfo() != null) {	
					
					// 1. save lp					
					int result = saveLpData(mdData);
					LOG.debug("## SAVE LP - deviceSerial : [{}], meterId : [{}], result : [{}]", deviceSerial, mdData.getMeterInfo().getMeter_serial(), result);
					
					// 2. save meterBillingImport					
					int result2 = saveMeterBillingImport(mdData);
					LOG.debug("## SAVE meterBillingImport - deviceSerial : [{}], meterId : [{}], result : [{}]", deviceSerial, mdData.getMeterInfo().getMeter_serial(), result2);
					
					// 3. save meterBillingExport					
					int result3 = saveMeterBillingExport(mdData);
					LOG.debug("## SAVE meterBillingExport - deviceSerial : [{}], meterId : [{}], result : [{}]", deviceSerial, mdData.getMeterInfo().getMeter_serial(), result3);
					
					// 4. save meterEtypeBillingExport					
					int result4 = saveEtypeMeterBillingImport(mdData);
					LOG.debug("## SAVE meterEtypeBillingExport - deviceSerial : [{}], meterId : [{}], result : [{}]", deviceSerial, mdData.getMeterInfo().getMeter_serial(), result4);
				}
			}
		}
	}
	
	public int saveDynamicData(MDData mdData, DeviceInfo deviceInfo) {
		
		int result = 0;		
		
		Map<String, Object> map = mdData.getDynamicDatas();
		for(String key : map.keySet()) {
			
			try {
				
				MeterData meterData = new MeterData();
				MeterInfo meterInfo = mdData.getMeterInfo();	
				
				if(meterInfo != null) {
					
					LOG.debug("key : {}", key);
					
					String obis_code = key.substring(0, 12);
					String class_id = key.substring(12, 16);
					String attribute_no = key.substring(16, 18);
				
					meterData.setRead_dt(mdData.getModemTime());
					meterData.setMeter_id(meterInfo.getMeter_id());
					meterData.setObis_code(obis_code);
					meterData.setClass_id(class_id);
					meterData.setAttribute_no(attribute_no);
					meterData.setItime(mdData.getModemTime());
					meterData.setMtime(mdData.getMeterTime());
					meterData.setPayload(String.valueOf(map.get(key)));
					meterDataDAO.insert(meterData);
				}
				
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				LOG.error("e", e);
			}
			
		}
		
		return result;
	}
	
	/**
	 * saveLpData
	 * @param mdData
	 * @return
	 */
	public int saveLpData(MDData mdData) {
		
		List<MeterValue> meterValues = new ArrayList<MeterValue>();
		List<LPData> lpDatas = mdData.getLpDatas();
		
		MeterInfo meterInfo = mdData.getMeterInfo();
		
		Map<String, Double> initChannelValue = new HashMap<String, Double>();
		
		for (LPData lpData : lpDatas) {
			
			MeterValue lp = new MeterValue();
			Double sect_meter_value = 0.0;
			
			lp.setMeter_id(meterInfo.getMeter_id());
			lp.setRead_dt(lpData.getRead_dt());
			lp.setChannel(lpData.getChannel());
			lp.setMeter_value(lpData.getValue());
			
			if(mdData.getMeterTime() != null && !"".equals(mdData.getMeterTime())) {
				lp.setMtime(mdData.getMeterTime()); // meter time
			}
			if(mdData.getModemTime() != null && !"".equals(mdData.getModemTime())) {
				lp.setItime(mdData.getModemTime());
			}
			
			Double initVal = null;
			initVal = initChannelValue.get(lpData.getChannel());
			
			// 구간값
			if(initVal == null) {	
				
				MeterValue lastVal = meterValueDAO.selectLastValue(lp);
				
				if(lastVal != null) {
					sect_meter_value = lp.getMeter_value() - lastVal.getMeter_value(); // 구간값 : 현재 - 이전						
				}			
							
			} else {					
				sect_meter_value = lp.getMeter_value() - initVal; // 구간값 : 현재 - 이전
			}
			
			initChannelValue.put(lp.getChannel(), lp.getMeter_value()); // 현재값으로 update			
			lp.setSect_meter_value(sect_meter_value);
			
			meterValues.add(lp);
		}
		
		if(meterValues.size() > 0) {
			LOG.debug("meterValues : {}", meterValues);
			return this.meterValueDAO.insertAll(meterValues);
		} else {
			return 0;
		}
	}
	
	/**
	 * 순방향 정기검침
	 * @param mdData
	 * @return
	 */
	public int saveMeterBillingImport(MDData mdData) {
		
		int result = 0;		
		List<MeterBilling> meterBillings = mdData.getBillingImportData();
		
		if(meterBillings != null) {
			
			MeterInfo meterInfo = mdData.getMeterInfo();
			
			for (MeterBilling meterBilling : meterBillings) {
				
				try {
					
					String billingDate = mdData.getBillingDate();
					
					if(billingDate == null) {
						billingDate = getBillingDate(mdData.getModemTime(), meterInfo.getBilling_dt());
					}
					
					LOG.debug("[saveMeterBillingImport] meter billing day : {}", meterInfo.getBilling_dt());
					LOG.debug("[saveMeterBillingImport] METER_ID : {}" , meterInfo.getMeter_id());
					LOG.debug("[saveMeterBillingImport] MODEM TIME : {}" , mdData.getModemTime());
					LOG.debug("[saveMeterBillingImport] BILLING DATE : {} " , mdData.getBillingDate());
					
					meterBilling.setMeter_id(meterInfo.getMeter_id());					
					meterBilling.setBilling_dt(billingDate); // 정기검침일자
					
					if(mdData.getMeterTime() != null && !"".equals(mdData.getMeterTime())) {
						meterBilling.setMtime(mdData.getMeterTime()); // meter time
					}
					if(mdData.getModemTime() != null && !"".equals(mdData.getModemTime())) {
						meterBilling.setItime(mdData.getModemTime());
					}
					
					LOG.debug("meterBilling : {}", meterBilling);
					
					result += meterBillingDAO.insertImport(meterBilling);
					
				} catch (Exception e) {
					LOG.error("error", e);
				}
			}			
		}
		
		return result;
	}
	
	/**
	 * 역방향 정기검침
	 * @param mdData
	 * @return
	 */
	public int saveMeterBillingExport(MDData mdData) {
		
		int result = 0;		
		List<MeterBilling> meterBillings = mdData.getBillingExportData();
		
		if(meterBillings != null) {
			MeterInfo meterInfo = mdData.getMeterInfo();
			
			for (MeterBilling meterBilling : meterBillings) {
				
				try {					
					String billingDate = mdData.getBillingDate();
					
					if(billingDate == null) {
						billingDate = getBillingDate(mdData.getModemTime(), meterInfo.getBilling_dt());
					}
					
					LOG.debug("[saveMeterBillingExport] meter billing day : {}", meterInfo.getBilling_dt());
					LOG.debug("[saveMeterBillingExport] METER_ID : {}" , meterInfo.getMeter_id());
					LOG.debug("[saveMeterBillingExport] MODEM TIME : {}" , mdData.getModemTime());
					LOG.debug("[saveMeterBillingExport] BILLING DATE : {} " , mdData.getBillingDate());
					
					meterBilling.setMeter_id(meterInfo.getMeter_id());					
					meterBilling.setBilling_dt(billingDate); // 정기검침일자
					
					if(mdData.getMeterTime() != null && !"".equals(mdData.getMeterTime())) {
						meterBilling.setMtime(mdData.getMeterTime()); // meter time
					}
					if(mdData.getModemTime() != null && !"".equals(mdData.getModemTime())) {
						meterBilling.setItime(mdData.getModemTime());
					}
					
					result += meterBillingDAO.insertExport(meterBilling);
					
				} catch (Exception e) {
					LOG.error("error", e);
				}
			}
		}
		return result;
	}
	
	
	/**
	 * 순방향 정기검침 (ETYPE)
	 * @param mdData
	 * @return
	 */
	public int saveEtypeMeterBillingImport(MDData mdData) {
		
		int result = 0;		
		List<MeterBilling> meterBillings = mdData.getETypeBillingImportData();
		
		if(meterBillings != null) {
			
			MeterInfo meterInfo = mdData.getMeterInfo();
			
			for (MeterBilling meterBilling : meterBillings) {
				
				try {				
					
					meterBilling.setMeter_id(meterInfo.getMeter_id());			
					if(mdData.getMeterTime() != null && !"".equals(mdData.getMeterTime())) {
						meterBilling.setMtime(mdData.getMeterTime()); // meter time
					}
					if(mdData.getModemTime() != null && !"".equals(mdData.getModemTime())) {
						meterBilling.setItime(mdData.getModemTime());
					}
					result += meterBillingDAO.insertImport(meterBilling);
					
				} catch (Exception e) {
					LOG.error("error", e);
				}
			}			
		}
		
		return result;
	}
	
	public int mdDevicePowerLogSaver(KepcoMDDataParser parser, IMeasurementData md) {
		
		int result = 0;
		
		DevicePowerLog devicePowerLog = parser.getDevicePowerLog();
		
		try {
			
			// TODO : 발생 일시 중복 시 저장하지 않아야 함.
			
			DeviceInfo deviceInfo = deviceInfoDAO.selectByDeviceSerial(devicePowerLog.getDevice_serial());
			devicePowerLog.setDevice_id(deviceInfo.getDevice_id());			
			// 현재년도
			String year = TimeUtil.getCurrentDay().substring(0, 4);
			int check = 0;
			
			if(!year.equals(devicePowerLog.getPower_off_time().substring(0, 4))) {
				check++;
			}
			
			if(!year.equals(devicePowerLog.getPower_on_time().substring(0, 4))) {
				check++;
			}
			
			if(check > 1) {
				
				LOG.debug("POWER ON TIME : {} / POWER OFF TIME : {}",devicePowerLog.getPower_on_time(), devicePowerLog.getPower_off_time());
				LOG.debug("현재시간 불일치로 저장하지 않음");
				
			} else {
				result = devicePowerLogDAO.insert(devicePowerLog);
			}
			
		} catch (Exception e) {
			LOG.error("error", e);
		}
		
		return result;
	}
	
}
