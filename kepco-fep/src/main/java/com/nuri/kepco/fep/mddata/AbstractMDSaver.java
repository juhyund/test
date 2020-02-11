package com.nuri.kepco.fep.mddata;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.nuri.kepco.fep.datatype.MDData;
import com.nuri.kepco.fep.datatype.MeterType;
import com.nuri.kepco.fep.datatype.MeterType.COMMTYPE;
import com.nuri.kepco.fep.datatype.MeterType.DEVICEFLAG;
import com.nuri.kepco.fep.datatype.MeterType.DEVICESTATUS;
import com.nuri.kepco.fep.datatype.MeterType.DEVICETYPE;
import com.nuri.kepco.model.DeviceInfo;
import com.nuri.kepco.model.DeviceModel;
import com.nuri.kepco.model.DeviceStatus;
import com.nuri.kepco.model.MeterInfo;
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

	public abstract boolean save(IMeasurementData md) throws Exception;
	
	String modemTime;

	protected void checkMeter(MDData mdData) {

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
			meter.setEnergy_type_code(MeterType.TYPE.EnergyMeter.getCode());			
			meter.setDevice_id(deviceInfo.getDevice_id());
			
			if (mdData.getBillingDate() != null) {
				meter.setBilling_dt(mdData.getBillingDate());
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
			
			
			logger.debug("mdData.getMeterTime() : {}", mdData.getMeterTime());
			logger.debug("isNewMeter : {}", isNewMeter);

			if (isNewMeter) {
				// insert
				result = meterInfoDAO.insert(meter);
			} else {
				// update
				result = meterInfoDAO.update(meter);
			}

			logger.debug(meter.getMeter_id());
			
			updateDeviceStatus(meter, mdData);

			mdData.setMeterInfo(meter);

		} catch (Exception e) {
			logger.error(e.getMessage());
		}
	}

	protected void checkDevice(String deviceSerial, String modemTime) {

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

			if (isNewDevice) {
				deviceInfoDAO.insert(deviceInfo);
				updateDeviceStatus(deviceInfo);
			} else {
				deviceInfoDAO.update(deviceInfo);
				updateDeviceStatus(deviceInfo);
			}

			this.deviceInfo = deviceInfo;

		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	protected void updateDeviceStatus(MeterInfo meterInfo, MDData mdData) {

		DeviceStatus param = new DeviceStatus();
		param.setDevice_id(meterInfo.getMeter_id());

		DeviceStatus deviceStatus = null;

		try {

			deviceStatus = deviceStatusDAO.selectOne(param);

			if (deviceStatus == null) { // insert

				deviceStatus = new DeviceStatus();
				deviceStatus.setDevice_id(meterInfo.getMeter_id());
				deviceStatus.setDevice_flag(DEVICEFLAG.METER.getCode()); // meter
				deviceStatus.setDevice_status(DEVICESTATUS.NORMAL.getCode()); // normal
				deviceStatus.setLast_comm_dt(mdData.getMeterTime()); // meter time
				deviceStatusDAO.insert(deviceStatus);

			} else { // update

				deviceStatus = new DeviceStatus();
				deviceStatus.setDevice_id(meterInfo.getMeter_id());
				deviceStatus.setDevice_flag(DEVICEFLAG.METER.getCode()); // meter
				deviceStatus.setDevice_status(DEVICESTATUS.NORMAL.getCode()); // normal
				deviceStatus.setLast_comm_dt(mdData.getMeterTime()); // meter time
				deviceStatusDAO.update(deviceStatus);
			}

		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	/**
	 * updateDeviceStatus
	 * 
	 * @param deviceInfo
	 */
	protected void updateDeviceStatus(DeviceInfo deviceInfo) {

		DeviceStatus param = new DeviceStatus();
		param.setDevice_id(deviceInfo.getDevice_id());

		DeviceStatus deviceStatus = null;

		try {

			deviceStatus = deviceStatusDAO.selectOne(param);

			if (deviceStatus == null) { // insert

				deviceStatus = new DeviceStatus();
				deviceStatus.setDevice_id(deviceInfo.getDevice_id());
				deviceStatus.setDevice_flag(DEVICEFLAG.DEVICE.getCode()); // device
				deviceStatus.setDevice_status(DEVICESTATUS.NORMAL.getCode()); // normal
				deviceStatus.setLast_comm_dt(modemTime); // modem time
				deviceStatusDAO.insert(deviceStatus);

			} else { // update

				deviceStatus = new DeviceStatus();
				deviceStatus.setDevice_id(deviceInfo.getDevice_id());
				deviceStatus.setDevice_flag(DEVICEFLAG.DEVICE.getCode()); // device
				deviceStatus.setDevice_status(DEVICESTATUS.NORMAL.getCode()); // normal
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

}