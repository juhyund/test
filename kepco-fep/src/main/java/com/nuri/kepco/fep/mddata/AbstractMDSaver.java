package com.nuri.kepco.fep.mddata;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;

import com.aimir.util.TimeUtil;
import com.nuri.kepco.fep.datatype.MDData;
import com.nuri.kepco.fep.datatype.MeterType;
import com.nuri.kepco.fep.datatype.MeterType.COMMTYPE;
import com.nuri.kepco.fep.datatype.MeterType.DEVICEFLAG;
import com.nuri.kepco.fep.datatype.MeterType.DEVICESTATUS;
import com.nuri.kepco.fep.datatype.MeterType.DEVICETYPE;
import com.nuri.kepco.fep.parser.DLMSVARIABLE;
import com.nuri.kepco.model.DeviceInfo;
import com.nuri.kepco.model.DeviceModel;
import com.nuri.kepco.model.DeviceStatus;
import com.nuri.kepco.model.MeterInfo;
import com.nuri.kepco.model.VendorInfo;
import com.nuri.kepco.model.dao.DeviceInfoDAO;
import com.nuri.kepco.model.dao.DeviceModelDAO;
import com.nuri.kepco.model.dao.DeviceStatusDAO;
import com.nuri.kepco.model.dao.MeterInfoDAO;
import com.nuri.kepco.model.dao.VendorInfoDAO;

@Service
public abstract class AbstractMDSaver {

	Logger logger = LoggerFactory.getLogger(AbstractMDSaver.class);

	@Autowired
	MeterInfoDAO meterInfoDAO;

	@Autowired
	DeviceModelDAO deviceModelDAO;

	@Autowired
	VendorInfoDAO vendorInfoDAO;

	@Autowired
	DeviceStatusDAO deviceStatusDAO;

	@Autowired
	DeviceInfoDAO deviceInfoDAO;

	private DeviceInfo deviceInfo;
	
	@Value("${device.model.name}")
	private String defaultModelName;
	
	@Value("${unknown.model.name:UNKNOWN}")
	private String unknownModelName;
	
	@Value("${default.branch.id:9999}")
	private String defaultBranchId;

	public abstract boolean save(IMeasurementData md) throws Exception;


	String modemTime; // 서버가 모뎀으로부터 수신한 시간

	protected int checkMeter(MDData mdData) {

		int result = 0;
		boolean isNewMeter = false;

		try {
			String meterSerial = mdData.getMeterID();
			MeterInfo meter = meterInfoDAO.selectByMeterSerial(meterSerial);

			if (meter == null) {
				meter = new MeterInfo();
				isNewMeter = true;
			}
			String meterType = mdData.getMeterType();
			String meterPhase = mdData.getMeterPhase();
			
			// meter type
			if (!"".equals(meterType) && meterType != null) {
				meter.setMeter_type(meterType);
			} else {
				meter.setMeter_type(MeterType.METERTYPE.UNKNOWN.getCode());
			}

			meter.setMeter_phase(meterPhase);
			meter.setMeter_serial(mdData.getMeterID());
			meter.setMeterModel(); // serial vendorCd, modelCd 
			meter.setEnergy_type_code(MeterType.TYPE.EnergyMeter.getCode());
			meter.setDevice_id(deviceInfo.getDevice_id());

			// 정기검침일 (MeterEntry)
			if (mdData.getBillingDay() != null) {
				meter.setBilling_dt(mdData.getBillingDay()); 
			}

			if (mdData.getCosemDeviceName() != null) {
				meter.setCosem_device_name(mdData.getCosemDeviceName());
			}
			if (mdData.getAcon() != null) {
				meter.setAcon(mdData.getAcon());
			}
			if (mdData.getRcon() != null) {
				meter.setRcon(mdData.getRcon());
			}
			if (mdData.getPcon() != null) {
				meter.setPcon(mdData.getPcon());
			}
			if (mdData.getItime() != null) {
				meter.setItime(mdData.getItime());
			}
			if (mdData.getMtime() != null) {
				meter.setMtime(mdData.getMtime());
			}
			if (mdData.getLpPeriod() != null) {
				meter.setLp_period(mdData.getLpPeriod());
			}
			if (mdData.getNetMetering() != null) {
				meter.setNet_metering(mdData.getNetMetering());
			}
			
			if(mdData.getAvgPowerPeriod() != null) {
				meter.setAvg_power_period(mdData.getAvgPowerPeriod());
			}

			logger.debug("mdData.getMeterTime() : {}", mdData.getMeterTime());
			logger.debug("isNewMeter : {}", isNewMeter);
			logger.debug("meter.getVendorCd() : {}", meter.getVendorCd());
			
			// vendor info
			int vendorSeq = getVendorSeqByCode(meter.getVendorCd());
			if(vendorSeq > 0) {			
				meter.setVendor_seq(vendorSeq);
			}
			
			// model info
			int model_seq = getModelSeqByVendorCode(meter.getVendorCd());			
			if(model_seq > 0) {
				meter.setModel_seq(model_seq);
			} else {
				// 없다면 default
				meter.setModel_seq(getModelSeqByName(unknownModelName)); 
			}

			if (isNewMeter) {				
				// default branch id
				meter.setBranch_id(defaultBranchId);
				
				// insert
				result = meterInfoDAO.insert(meter);
			} else {
				
				if(meter.getBranch_id() == null) {
					// default branch id
					meter.setBranch_id(defaultBranchId);
				}
				// update
				result = meterInfoDAO.update(meter);
			}

			logger.debug(meter.getMeter_id());

			updateDeviceStatus(meter, mdData.getMeterTime());

			mdData.setMeterInfo(meter);

		} catch (Exception e) {
			logger.error(e.getMessage());
		}
		
		return result;
	}
	
	protected int checkMeter(MeterInfo meterInfo) {
		
		int result = 0;
		
		try {
			
			meterInfo.setMeterModel(); // modelcd, vendorcd
			meterInfo.setMeter_type(DLMSVARIABLE.METERTYPE.getMeterType(meterInfo.getModelCd()).getName());
			meterInfo.setMeter_phase(DLMSVARIABLE.METERPHASE.getMeterPhase(meterInfo.getModelCd()).getName());
			meterInfo.setEnergy_type_code(MeterType.TYPE.EnergyMeter.getCode());
			
			// vendor info
			int vendorSeq = getVendorSeqByCode(meterInfo.getVendorCd());
			if(vendorSeq > 0) {
				meterInfo.setVendor_seq(vendorSeq);
			}		
			
			// model info
			int model_seq = getModelSeqByVendorCode(meterInfo.getVendorCd());			
			if(model_seq > 0) {
				meterInfo.setModel_seq(model_seq);
			} else {
				// 없다면 default
				meterInfo.setModel_seq(getModelSeqByName(unknownModelName)); 
			}
			
			MeterInfo meter = meterInfoDAO.selectByMeterSerial(meterInfo.getMeter_serial());
			if (meter == null) {				
				// default branch id 세팅
				deviceInfo.setBranch_id(defaultBranchId);
				meterInfo.setBranch_id(defaultBranchId);
				result += meterInfoDAO.insert(meterInfo);				
			} else {
				
				// default branch id 세팅
				if(meter.getBranch_id() == null) {
					meterInfo.setBranch_id(defaultBranchId); //
				}
				
				meterInfo.setMeter_id(meter.getMeter_id()); // meter id
				result += meterInfoDAO.update(meterInfo);
			}
			
			updateDeviceStatus(meter, null);
		
		} catch (Exception e) {
			logger.error("error", e);
		}
		
		return result;
	}
	
	private int getVendorSeqByCode(String vendorCode) {
		
		VendorInfo vendorInfo = null;
		try {
			vendorInfo = vendorInfoDAO.selectVendorByCode(vendorCode);
			
			if(vendorInfo != null) {
				return vendorInfo.getVendor_seq();
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return -1;
	}
	
	private Integer getModelSeqByVendorCode(String vendorCode) {
		
		DeviceModel deviceInfo = null;
		try {
			deviceInfo = deviceModelDAO.selectModelByVendorCode(vendorCode);			
			if(deviceInfo != null) {
				return deviceInfo.getModel_seq();
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return -1;
	}
	
	private Integer getModelSeqByName(String modelName) {
		
		DeviceModel deviceInfo = null;
		try {
			deviceInfo = deviceModelDAO.selectModelByName(modelName);			
			if(deviceInfo != null) {
				return deviceInfo.getModel_seq();
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return -1;
	}

	protected int checkDevice(String deviceSerial, String modemTime, String mobileNo) {

		int result = 0;
		boolean isNewDevice = false;
		this.modemTime = modemTime;

		try {
			// device id
			DeviceInfo deviceInfo = null;
			deviceInfo = deviceInfoDAO.selectByDeviceSerial(deviceSerial);

			if (deviceInfo == null) {
				deviceInfo = new DeviceInfo();
				isNewDevice = true;
			}

			deviceInfo.setDevice_serial(deviceSerial);
			deviceInfo.setDevice_type(DEVICETYPE.DEVICE.getCode()); // DEVICE
			deviceInfo.setAllow_yn("1");
			deviceInfo.setComm_type(COMMTYPE.LTE.getCode()); // LTE
			
			if(mobileNo != null) deviceInfo.setMobile_no(mobileNo);

			if (isNewDevice) {			
				
				// model을 default로 저장
				String model_nm = defaultModelName;
				DeviceModel deviceModel = deviceModelDAO.selectModelByName(model_nm);
				
				if(deviceModel != null) {
					deviceInfo.setModel_seq(deviceModel.getModel_seq());
				}				
				
				deviceInfo.setBranch_id(defaultBranchId);
				result = deviceInfoDAO.insert(deviceInfo);
				
			} else {
				
				if(deviceInfo.getBranch_id() == null) {
					deviceInfo.setBranch_id(defaultBranchId);	
				}
				
				result = deviceInfoDAO.update(deviceInfo);
			}
			
			updateDeviceStatus(deviceInfo, DEVICESTATUS.NORMAL);
			this.deviceInfo = deviceInfo;

		} catch (Exception e) {
			logger.error("error", e);
		}
		
		return result;
	}
	
	/**
	 * checkDevice
	 * @param deviceSerial
	 * @param modemTime
	 * @param ip
	 * @param port
	 * @param init_reg_dt
	 * @param deviceStatus
	 * @return
	 */
	protected int checkDevice(String deviceSerial, String modemTime, String ip, String port, String init_reg_dt, DEVICESTATUS deviceStatus) {

		int result = 0;
		boolean isNewDevice = false;
		this.modemTime = modemTime;

		try {
			// device id
			DeviceInfo deviceInfo = null;
			deviceInfo = deviceInfoDAO.selectByDeviceSerial(deviceSerial);

			if (deviceInfo == null) {
				deviceInfo = new DeviceInfo();
				isNewDevice = true;
			}

			deviceInfo.setDevice_serial(deviceSerial);
			deviceInfo.setDevice_type(DEVICETYPE.DEVICE.getCode()); // DEVICE
			deviceInfo.setAllow_yn("1");
			deviceInfo.setComm_type(COMMTYPE.LTE.getCode()); // LTE
			
			if(ip != null) {
				deviceInfo.setIp(ip);
			}
			
			if(port != null) {
				deviceInfo.setPort(port);
			}
			
			if (isNewDevice) {	
				
				// model을 default로 저장
				String model_nm = defaultModelName;
				DeviceModel deviceModel = deviceModelDAO.selectModelByName(model_nm);
				
				if(deviceModel != null) {
					deviceInfo.setModel_seq(deviceModel.getModel_seq());
				}		
				
				deviceInfo.setInit_reg_dt(init_reg_dt);
				
				deviceInfo.setBranch_id(defaultBranchId);
				result = deviceInfoDAO.insert(deviceInfo);
				
			} else {
				
				if(deviceInfo.getBranch_id() == null) {
					deviceInfo.setBranch_id(defaultBranchId);	
				}
				
				result = deviceInfoDAO.update(deviceInfo);
			}
			updateDeviceStatus(deviceInfo, deviceStatus);
			this.deviceInfo = deviceInfo;

		} catch (Exception e) {
			logger.error("error", e);
		}
		
		return result;
	}
	
	
	protected int checkDevice(String deviceSerial, String modemTime) {

		return checkDevice(deviceSerial, modemTime, null);
	}
	
	/**
	 * updateDeviceStatus - meter 상태정보 업데이트
	 * @param meterInfo
	 * @param mdData
	 */
	protected void updateDeviceStatus(MeterInfo meterInfo, String meterTime) {

		DeviceStatus param = new DeviceStatus();
		param.setDevice_id(meterInfo.getMeter_id());

		DeviceStatus deviceStatus = null;
		
		if(meterTime == null) {
			// 현재시간
			meterTime = TimeUtil.getCurrentTimeMilli();
		}

		try {

			deviceStatus = deviceStatusDAO.selectOne(param);
			
			// todo last_comm_dt 통신시간 체크

			if (deviceStatus == null) { // insert

				deviceStatus = new DeviceStatus();
				deviceStatus.setDevice_id(meterInfo.getMeter_id());
				deviceStatus.setDevice_flag(DEVICEFLAG.METER.getCode()); // meter
				deviceStatus.setDevice_status(DEVICESTATUS.NORMAL.getCode()); // normal
				deviceStatus.setLast_comm_dt(meterTime); // meter time
				deviceStatusDAO.insert(deviceStatus);

			} else { // update

				deviceStatus = new DeviceStatus();
				deviceStatus.setDevice_id(meterInfo.getMeter_id());
				deviceStatus.setDevice_flag(DEVICEFLAG.METER.getCode()); // meter
				deviceStatus.setDevice_status(DEVICESTATUS.NORMAL.getCode()); // normal
				deviceStatus.setLast_comm_dt(meterTime); // meter time
				deviceStatusDAO.update(deviceStatus);
			}

		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	/**
	 * updateDeviceStatus - 단말 상태 정보 업데이트
	 * 
	 * @param deviceInfo
	 */
	protected void updateDeviceStatus(DeviceInfo deviceInfo, DEVICESTATUS deviceStatusCode) {

		DeviceStatus param = new DeviceStatus();
		param.setDevice_id(deviceInfo.getDevice_id());

		DeviceStatus deviceStatus = null;
		
		if(modemTime == null) {
			// 현재시간
			modemTime = TimeUtil.getCurrentTimeMilli();
		}
		
		if(deviceStatusCode == null) {
			deviceStatusCode = DEVICESTATUS.NORMAL;
		}

		try {

			deviceStatus = deviceStatusDAO.selectOne(param);

			if (deviceStatus == null) { // insert

				deviceStatus = new DeviceStatus();
				deviceStatus.setDevice_id(deviceInfo.getDevice_id());
				deviceStatus.setDevice_flag(DEVICEFLAG.DEVICE.getCode()); // device
				deviceStatus.setDevice_status(deviceStatusCode.getCode()); // normal
				deviceStatus.setLast_comm_dt(modemTime); // modem time
				deviceStatusDAO.insert(deviceStatus);

			} else { // update

				deviceStatus = new DeviceStatus();
				deviceStatus.setDevice_id(deviceInfo.getDevice_id());
				deviceStatus.setDevice_flag(DEVICEFLAG.DEVICE.getCode()); // device
				deviceStatus.setDevice_status(deviceStatusCode.getCode()); // normal
				deviceStatus.setLast_comm_dt(modemTime); // modem time
				deviceStatusDAO.update(deviceStatus);
			}

		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public DeviceInfo getDeviceInfo() {
		return deviceInfo;
	}

	/**
	 * 정기검침일
	 * 
	 * @param mrd
	 * @return
	 */
	public String getBillingDate(String meterTime, String billingDay) {
		
		if("".equals(billingDay) || billingDay == null) {
			billingDay = "01";
		}
		
		if(billingDay.length() == 1) {
			billingDay = "0" + billingDay;
		}
		
		logger.debug("billingDay : {}", billingDay);
		return meterTime.substring(0, 6) + billingDay + "0000"; // length - 12
	}
}
