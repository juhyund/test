package com.nuri.kepco.fep.saver;

import java.util.List;
import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.aimir.util.TimeUtil;
import com.nuri.kepco.fep.datatype.Device.DEVICE;
import com.nuri.kepco.fep.datatype.FIRMWARE.FIRMWARECODE;
import com.nuri.kepco.fep.datatype.FIRMWARE.FIRMWAREUPDATE;
import com.nuri.kepco.fep.mddata.AbstractMDSaver;
import com.nuri.kepco.fep.mddata.IMeasurementData;
import com.nuri.kepco.fep.parser.ObjectLinkDataParser;
import com.nuri.kepco.model.DeviceFw;
import com.nuri.kepco.model.DeviceFwHistory;
import com.nuri.kepco.model.DeviceInfo;
import com.nuri.kepco.model.DeviceModel;
import com.nuri.kepco.model.DeviceResource;
import com.nuri.kepco.model.MeterInfo;
import com.nuri.kepco.model.dao.DeviceFwDAO;
import com.nuri.kepco.model.dao.DeviceFwHistoryDAO;
import com.nuri.kepco.model.dao.DeviceInfoDAO;
import com.nuri.kepco.model.dao.DeviceResourceDAO;
import com.nuri.kepco.model.dao.MeterInfoDAO;

@Service
public class ObjectLinkDataSaver extends AbstractMDSaver {

	private static final Logger LOG = LoggerFactory.getLogger(ObjectLinkDataSaver.class);

	@Autowired
	DeviceResourceDAO deviceResourceDAO;

	@Autowired
	MeterInfoDAO meterInfoDAO;

	@Autowired
	DeviceInfoDAO deviceInfoDAO;

	@Autowired
	DeviceFwDAO deviceFwDAO;

	@Autowired
	DeviceFwHistoryDAO deviceFwHistoryDAO;

	@Override
	public boolean save(IMeasurementData md) throws Exception {

		ObjectLinkDataParser parser = (ObjectLinkDataParser) md.getMeterDataParser();
		String deviceSerial = md.getDeviceId();

		// checkDevice
		DeviceInfo deviceInfo = checkDevice(deviceSerial, md.getModemTime());
		LOG.debug("Device [{}] branchId : {}", deviceSerial, deviceInfo.getBranch_id());

		int result = saveDeviceResource(parser, deviceInfo);
		LOG.debug("Device [{}] resource update : {}", deviceSerial, result);

		int result2 = saveMeterInfo(parser, deviceInfo);
		LOG.debug("Device [{}] meter update : {}", deviceSerial, result2);
		
		//int result3 = saveFirmwareInfo(parser);
		//LOG.debug("Device [{}] firmware update : {}", deviceSerial, result3);
		
		int result4 = saveDeviceInfo(parser, deviceInfo);
		LOG.debug("Device [{}] device fw/sw version update : {}", deviceSerial, result4);
		
		return true;
	}

	/**
	 * device resource ????????? ????????????.
	 * 
	 * @return
	 */
	private int saveDeviceResource(ObjectLinkDataParser parser, DeviceInfo deviceInfo) {
		
		int result = 0;
		List<DeviceResource> deviceResourceList = parser.getDeviceResourceList();

		if (deviceInfo != null) {
			for (DeviceResource deviceResource : deviceResourceList) {
				deviceResource.setDevice_id(deviceInfo.getDevice_id());
			}

			LOG.debug("DEVICE : {}", deviceResourceList);

			result = deviceResourceDAO.insertAll(deviceResourceList);
		}

		return result;
	}

	/**
	 * meterentry ????????? ?????? ?????? ????????? ???????????? ??????.
	 * 
	 * @return
	 */
	private int saveMeterInfo(ObjectLinkDataParser parser, DeviceInfo deviceInfo) {

		int result = 0;
		Map<Integer, MeterInfo> meterInfoList = parser.getMeterInfoList();

		if (deviceInfo != null) {

			if (meterInfoList != null) {
				for (Integer key : meterInfoList.keySet()) {

					MeterInfo meterInfo = meterInfoList.get(key);
					meterInfo.setDevice_id(deviceInfo.getDevice_id());
					meterInfo.setBranch_id(deviceInfo.getBranch_id());
					result = checkMeter(meterInfo);
				}
			}
		}

		return result;
	}

	/**
	 * firmware update ????????? ?????? ?????? ?????? ??? ????????? ????????? ???????????? ??????. Firmware update ????????? 1 ?????????
	 * ???????????? ????????? ????????????.
	 * 
	 * @return
	 */
	private int saveFirmwareInfo(ObjectLinkDataParser parser, DeviceInfo deviceInfo) {

		int result = 0;
		
		Map<Integer, Object> firmwareInfo = parser.getFirmwareInfo();

		try {

			if (firmwareInfo != null && deviceInfo != null) {

				// firmware version
				String fw_version = (String) firmwareInfo.get(FIRMWAREUPDATE.PACKAGEVERSION.getCode());
				String fw_pkg_uri = (String) firmwareInfo.get(FIRMWAREUPDATE.PACKAGEURI.getCode());

				/**
				 * update result 0: ?????????. ???????????? ??????????????? ???????????? ????????????/???????????? ????????? ????????????. 1: ???????????? ?????? 2: ?????????
				 * ????????? ?????? 3. ???????????? ???????????? ??? RAM ?????? 4: ???????????? ???????????? ??? ????????? ?????? 5: ???????????? ??? ??? ???????????? ?????? ????????? ??????
				 * ?????? 6: ????????? ????????? ?????? 7: ????????? URI 8: ????????? ???????????? ?????? 9: ????????? ????????????
				 */
				int updateResult = (int) firmwareInfo.get(FIRMWAREUPDATE.UPDATERESULT.getCode());

				// packageUri
				if (updateResult != 0 && !"".equals(fw_version)) { // ???????????? ????????????

					DeviceFw deviceFw = null;
					DeviceFwHistory deviceFwHistory = new DeviceFwHistory();

					if (!"".equals(fw_pkg_uri) && fw_pkg_uri != null) {
						// firmware ?????? ??????
						deviceFw = deviceFwDAO.selectOneByPackageUri(fw_pkg_uri);
					}

					if (deviceFw != null) {

						deviceFwHistory.setDevice_id(deviceInfo.getDevice_id());
						deviceFwHistory.setFw_id(deviceFw.getFw_id());
						deviceFwHistory.setResult_dt(TimeUtil.getCurrentTimeMilli()); // ????????????
						deviceFwHistory.setFw_issue_status(FIRMWARECODE.getType(updateResult).getValue()); // ????????????

						// update??? ???????????? ??????????????? ?????? fw_version != ????????? fw_version ???????????? ??????
						if (updateResult == 1 && !deviceInfo.getFw_version().equals(fw_version)) {

							deviceFwHistory.setFw_success_dt(TimeUtil.getCurrentTimeMilli()); // ????????????

							// modem fw version update
							deviceInfo.setFw_version(fw_version);

							try {
								deviceInfoDAO.update(deviceInfo);
							} catch (Exception e) {
								LOG.error("error : ", e);
							}
						}

						// fw ????????? ????????????.
						deviceFwHistoryDAO.insert(deviceFwHistory);
					}
				}
			} // end if

		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return result;
	}

	/**
	 * saveDeviceInfo
	 * 
	 * @return
	 */
	private int saveDeviceInfo(ObjectLinkDataParser parser, DeviceInfo deviceInfo) {

		int result = 0;
		Map<Integer, Object> deviceInfoMap = parser.getDeviceInfoMap();

		try {

			if (deviceInfoMap != null && deviceInfo != null) {
				
				LOG.debug("deviceInfoMap : {}", deviceInfoMap);

				// firmware version
				String fw_version = (String) deviceInfoMap.get(DEVICE.FWVERSION.getCode());
				LOG.debug("fw_version : {}", fw_version);

				Map<Integer, String> sw_version = (Map<Integer, String>) deviceInfoMap.get(DEVICE.SWVERSION.getCode());
				for(Integer key : sw_version.keySet()) {
					LOG.debug("KEY : {}", key);
				}
				
				// device model
				String modelNumber = (String) deviceInfoMap.get(DEVICE.MODELNUMBER.getCode());
				int model_seq = getModelSeqByName(modelNumber);
				
				// modem fw version update
				deviceInfo.setFw_version(fw_version);
				deviceInfo.setSw_version1((String)sw_version.get(1));
				deviceInfo.setSw_version2((String)sw_version.get(2));
				deviceInfo.setModel_seq(model_seq);

				try {
					deviceInfoDAO.update(deviceInfo);
				} catch (Exception e) {
					LOG.error("error : ", e);
				}

			} // end if

		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return result;
	}
}
