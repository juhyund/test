package com.nuri.kepco.fep.saver;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.nuri.kepco.fep.datatype.LPData;
import com.nuri.kepco.fep.datatype.MDData;
import com.nuri.kepco.fep.mddata.AbstractMDSaver;
import com.nuri.kepco.fep.mddata.IMeasurementData;
import com.nuri.kepco.fep.parser.KepcoMDDataParser;
import com.nuri.kepco.model.MeterBilling;
import com.nuri.kepco.model.MeterInfo;
import com.nuri.kepco.model.MeterValue;
import com.nuri.kepco.model.dao.MeterBillingDAO;
import com.nuri.kepco.model.dao.MeterValueDAO;

@Service
public class KepcoMDDataSaver extends AbstractMDSaver {
	
	private static final Logger LOG = LoggerFactory.getLogger(KepcoMDDataSaver.class);
	
	@Autowired
	MeterValueDAO meterValueDAO;
	
	@Autowired
	MeterBillingDAO meterBillingDAO;
		
	@Override
	public boolean save(IMeasurementData md) throws Exception {
		
		KepcoMDDataParser parser = (KepcoMDDataParser)md.getMeterDataParser();		
		List<MDData> mdList = parser.getMDList();		
		String deviceSerial = md.getDeviceId();
		
		LOG.debug("## deviceSerial Saver : {}" , deviceSerial);
		
		// checkDevice
		checkDevice(deviceSerial, md.getModemTime());
		
		if(getDeviceInfo() != null) {
				
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
				checkMeter(mdData);
				
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
				}
			}
		}
		
		return false;
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
			
			Double initVal = null;
			initVal = initChannelValue.get(lpData.getChannel());
			LOG.debug("channel : " + lpData.getChannel());
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
					
					LOG.debug("METER_ID : {}", meterInfo.getMeter_id());
					meterBilling.setMeter_id(meterInfo.getMeter_id());
					
					LOG.debug("meter time : {}" , mdData.getMeterTime());
										
					String billingDate = getBillingDate(mdData.getMeterTime(), meterInfo.getBilling_dt());
					
					if(meterBilling.getBilling_dt() == null || !"".equals(billingDate)) {
						meterBilling.setBilling_dt(billingDate); // 정기검침일자
					}
					
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
					
					LOG.debug("meter billing day : {}", meterInfo.getBilling_dt());
					LOG.debug("METER_ID : {}" , meterInfo.getMeter_id());
					LOG.debug("MODEM TIME : {}" , mdData.getModemTime());
					LOG.debug("BILLING DATE : {} " , mdData.getBillingDate());
					
					meterBilling.setMeter_id(meterInfo.getMeter_id());					
					meterBilling.setBilling_dt(billingDate); // 정기검침일자
					
					result += meterBillingDAO.insertExport(meterBilling);
					
				} catch (Exception e) {
					LOG.error("error", e);
				}
			}
		}
		return result;
	}
	
}