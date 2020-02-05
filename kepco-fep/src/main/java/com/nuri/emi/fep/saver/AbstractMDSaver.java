package com.nuri.emi.fep.saver;

import java.util.List;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

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
	DeviceInfoDAO devieInfoDAO;

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

	public abstract void saveLpData(List<LPData> lpDatas);
	
	public abstract void saveBillingImportData(List<MeterBillingImport> billingDatas);
		
	public abstract void saveBillingExportData(List<MeterBillingExport> billingDatas);
	

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
			if (!"".equals(meterModel) && meterModel != null) {
				if (meterModel.substring(0, 2).equals("ET")) {
					meter.setType_code(MeterType.METERTYPE.EType.getCode());
				} else if (meterModel.substring(0, 2).equals("GT")) {
					meter.setType_code(MeterType.METERTYPE.GType.getCode());
				} else if (meterModel.substring(0, 2).equals("AE")) {
					meter.setType_code(MeterType.METERTYPE.AEType.getCode());
				}
				DeviceModel deviceModel = deviceModelDAO.selectModelByName(meterModel);
				meter.setModel_id(deviceModel.getModel_id());
			}
			
			// vendor
			if (!"".equals(meterType) && meterType != null) {
				VendorInfo vendor = vendorInfoDAO.selectVendorByName(meterType);
				meter.setVendor_id(vendor.getVendor_id());
			}

			meter.setMeter_serial(this.mdData.getMeterID());
			meter.setEnergy_type_code(MeterType.TYPE.EnergyMeter.getCode());
			
			// device id
			DeviceInfo deviceInfo = new DeviceInfo();
			deviceInfo.setDevice_oid(mdData.getDeviceOid());
			devieInfoDAO.select(deviceInfo);
			
			if(deviceInfo != null) {
				meter.setDevice_id(deviceInfo.getDevice_id());
			}							
			this.setMeter(meter);					
			
			logger.debug("isNewMeter : {}", isNewMeter);
			
			if(isNewMeter) {
				// insert
				result = meterInfoDAO.insert(meter);
			} else {
				// update
				result = meterInfoDAO.update(meter);
			}

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

			deviceStatus = deviceStatusDAO.select(param);

			logger.debug("DEVICETYPE.METER.getCode() " + DEVICETYPE.METER.getCode());
			
			if (deviceStatus == null) { // insert
				
				deviceStatus = new DeviceStatus();
				deviceStatus.setDevice_id(meterInfo.getMeter_id());
				deviceStatus.setDevice_code(DEVICETYPE.METER.getCode()); // meter
				deviceStatus.setDevice_stat(DEVICESTATUS.NORMAL.getCode()); // normal
				deviceStatusDAO.insert(deviceStatus);
				
			} else { // update

				deviceStatus = new DeviceStatus();
				deviceStatus.setDevice_id(meterInfo.getMeter_id());
				deviceStatus.setDevice_code(DEVICETYPE.METER.getCode()); // meter
				deviceStatus.setDevice_stat(DEVICESTATUS.NORMAL.getCode()); // normal
				deviceStatusDAO.update(deviceStatus);
			}
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}