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

//	private List<DeviceResource> deviceResourceList = null;
//
//	private Map<Integer, MeterInfo> meterInfoList = null;
//
//	private Map<Integer, Object> firmwareInfo = null;
//
//	private Map<Integer, Object> deviceInfoMap = null;

	@Override
	public boolean save(IMeasurementData md) throws Exception {

		ObjectLinkDataParser parser = (ObjectLinkDataParser) md.getMeterDataParser();
		String deviceSerial = md.getDeviceId();

		// checkDevice
		DeviceInfo deviceInfo = checkDevice(deviceSerial, md.getModemTime());

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
	 * device resource 정보를 저장한다.
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
	 * meterentry 객체로 부터 미터 정보를 업데이트 한다.
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

					result = checkMeter(meterInfo);
				}
			}
		}

		return result;
	}

	/**
	 * firmware update 객체로 부터 단말 정보 및 펌웨어 상태를 업데이트 한다. Firmware update 상태가 1 이라면
	 * 성공일시 칼럼도 저장한다.
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
				 * update result 0: 초기값. 업데이트 프로세스가 시작되면 다운로드/업데이트 단계로 변환된다. 1: 업데이트 성공 2: 플래시
				 * 메모리 부족 3. 다운로드 프로세스 중 RAM 부족 4: 다운로드 프로세스 중 연결이 끊김 5: 다운로드 된 새 패키지에 대한 무결성 검사
				 * 실패 6: 미지원 패키지 유형 7: 잘못된 URI 8: 펌웨어 업데이트 실패 9: 미지원 프로토콜
				 */
				int updateResult = (int) firmwareInfo.get(FIRMWAREUPDATE.UPDATERESULT.getCode());

				// packageUri
				if (updateResult != 0 && !"".equals(fw_version)) { // 초기값이 아니라면

					DeviceFw deviceFw = null;
					DeviceFwHistory deviceFwHistory = new DeviceFwHistory();

					if (!"".equals(fw_pkg_uri) && fw_pkg_uri != null) {
						// firmware 정보 찾자
						deviceFw = deviceFwDAO.selectOneByPackageUri(fw_pkg_uri);
					}

					if (deviceFw != null) {

						deviceFwHistory.setDevice_id(deviceInfo.getDevice_id());
						deviceFwHistory.setFw_id(deviceFw.getFw_id());
						deviceFwHistory.setResult_dt(TimeUtil.getCurrentTimeMilli()); // 응답일시
						deviceFwHistory.setFw_issue_status(FIRMWARECODE.getType(updateResult).getValue()); // 응답코드

						// update가 성공했고 디바이스의 현재 fw_version != 갱신된 fw_version 업데이트 성공
						if (updateResult == 1 && !deviceInfo.getFw_version().equals(fw_version)) {

							deviceFwHistory.setFw_success_dt(TimeUtil.getCurrentTimeMilli()); // 성공일시

							// modem fw version update
							deviceInfo.setFw_version(fw_version);

							try {
								deviceInfoDAO.update(deviceInfo);
							} catch (Exception e) {
								LOG.error("error : ", e);
							}
						}

						// fw 이력을 저장한다.
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

				// modem fw version update
				deviceInfo.setFw_version(fw_version);
				deviceInfo.setSw_version1((String)sw_version.get(1));
				deviceInfo.setSw_version2((String)sw_version.get(2));

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
