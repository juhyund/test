package com.nuri.kepco.fep.saver;

import java.util.List;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.nuri.kepco.fep.datatype.LPData;
import com.nuri.kepco.fep.datatype.MDData;
import com.nuri.kepco.fep.datatype.MeterType;
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

	MeterInfo meterInfo;

	MDData mdData;

	public void setMeter(MeterInfo meterInfo) {
		this.meterInfo = meterInfo;
	}

	public MeterInfo getMeter() {
		return this.meterInfo;
	}

	public MDData getMDData() {
		return mdData;
	}

	public void setMDData(MDData mdData) {
		this.mdData = mdData;
	}

	public abstract void save(MDData mddata);

	public abstract int saveLpData(List<LPData> lpDatas);
	
	protected void checkMeter(String meterSerial) {

		int result = 0;
		boolean isNewMeter = false;

		try {

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
				DeviceModel deviceModel = deviceModelDAO.selectModelByName(meterModel);
				meter.setModel_seq(deviceModel.getModel_seq());
			}
			
			meter.setMeter_serial(this.mdData.getMeterID());
			meter.setEnergy_type_code(MeterType.TYPE.EnergyMeter.getCode());
			
			// device id
			DeviceInfo deviceInfo = new DeviceInfo();			
			deviceInfoDAO.selectByDeviceSerial(this.mdData.getModemID()); // 변경될 수 있음.
			
			if(deviceInfo != null) {
				meter.setDevice_id(deviceInfo.getDevice_id());
			}							
			
			logger.debug("isNewMeter : {}", isNewMeter);
			
			if(isNewMeter) {
				// insert
				result = meterInfoDAO.insert(meter);
			} else {
				// update
				result = meterInfoDAO.update(meter);
			}
			
			this.setMeter(meter);
			
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

			logger.debug("DEVICETYPE.METER.getCode() " + DEVICETYPE.METER.getCode());
			
			if (deviceStatus == null) { // insert
				
				deviceStatus = new DeviceStatus();
				deviceStatus.setDevice_id(meterInfo.getMeter_id());
				deviceStatus.setDevice_flag("M"); // meter
				deviceStatus.setDevice_status(DEVICESTATUS.NORMAL.getCode()); // normal
				deviceStatusDAO.insert(deviceStatus);
				
			} else { // update

				deviceStatus = new DeviceStatus();
				deviceStatus.setDevice_id(meterInfo.getMeter_id());
				deviceStatus.setDevice_flag(DEVICETYPE.METER.getCode()); // meter
				deviceStatus.setDevice_status(DEVICESTATUS.NORMAL.getCode()); // normal
				deviceStatusDAO.update(deviceStatus);
			}
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}