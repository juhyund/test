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

			String meterModel = mdData.getMeterModel();
			String meterType = mdData.getMeterType();
			
			// meter model
			if (!"".equals(meterType) && meterType != null) {
				if("ET".equals(meterType)) {
					meter.setMeter_type(MeterType.METERTYPE.EType.getCode());
				} else if("GT".equals(meterType)) {
					meter.setMeter_type(MeterType.METERTYPE.GType.getCode());
				} else if("AE".equals(meterType)) {
					meter.setMeter_type(MeterType.METERTYPE.AEType.getCode());
				}		
			}
			
			// device model
			DeviceModel deviceModel = deviceModelDAO.selectModelByName(meterModel);
			if(deviceModel != null) {
				meter.setModel_seq(deviceModel.getModel_seq());
			}		
			
			meter.setMeter_serial(mdData.getMeterID());
			meter.setEnergy_type_code(MeterType.TYPE.EnergyMeter.getCode());
		
			meter.setDevice_id(deviceInfo.getDevice_id());			
			
			logger.debug("isNewMeter : {}", isNewMeter);
			
			if(isNewMeter) {
				// insert
				result = meterInfoDAO.insert(meter);
			} else {
				// update
				result = meterInfoDAO.update(meter);
			}
			
			mdData.setMeterInfo(meter);
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	protected void checkDevice(String deviceSerial) {

		int result = 0;
		boolean isNewDevice = false;

		try {
			
			logger.debug("deviceInfoDAO : {}", deviceInfoDAO);
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
			
			if(isNewDevice) {
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

	protected void updateDeviceStatus(MeterInfo meterInfo) {

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
				deviceStatusDAO.insert(deviceStatus);
				
			} else { // update

				deviceStatus = new DeviceStatus();
				deviceStatus.setDevice_id(meterInfo.getMeter_id());
				deviceStatus.setDevice_flag(DEVICEFLAG.METER.getCode()); // meter
				deviceStatus.setDevice_status(DEVICESTATUS.NORMAL.getCode()); // normal
				deviceStatusDAO.update(deviceStatus);
			}
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	/**
	 * updateDeviceStatus
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
				deviceStatusDAO.insert(deviceStatus);
				
			} else { // update

				deviceStatus = new DeviceStatus();
				deviceStatus.setDevice_id(deviceInfo.getDevice_id());
				deviceStatus.setDevice_flag(DEVICEFLAG.DEVICE.getCode()); // device
				deviceStatus.setDevice_status(DEVICESTATUS.NORMAL.getCode()); // normal
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