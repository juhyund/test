package com.nuri.kepco.fep.saver;

import java.util.List;
import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.nuri.kepco.fep.mddata.AbstractMDSaver;
import com.nuri.kepco.fep.mddata.IMeasurementData;
import com.nuri.kepco.fep.parser.ObjectLinkDataParser;
import com.nuri.kepco.model.DeviceInfo;
import com.nuri.kepco.model.DeviceResource;
import com.nuri.kepco.model.MeterInfo;
import com.nuri.kepco.model.dao.DeviceResourceDAO;
import com.nuri.kepco.model.dao.MeterInfoDAO;

@Service
public class ObjectLinkDataSaver extends AbstractMDSaver {

	private static final Logger LOG = LoggerFactory.getLogger(ObjectLinkDataSaver.class);

	@Autowired
	DeviceResourceDAO deviceResourceDAO;

	@Autowired
	MeterInfoDAO meterInfoDAO;

	private List<DeviceResource> deviceResourceList = null;

	private Map<Integer, MeterInfo> meterInfoList = null;

	@Override
	public boolean save(IMeasurementData md) throws Exception {

		ObjectLinkDataParser parser = (ObjectLinkDataParser) md.getMeterDataParser();

		deviceResourceList = parser.getDeviceResourceList();
		meterInfoList = parser.getMeterInfoList();

		String deviceSerial = md.getDeviceId();

		// checkDevice
		checkDevice(deviceSerial, md.getModemTime());

		int result = saveDeviceResource();
		LOG.debug("Device [{}] resource update : {}", deviceSerial, result);

		int result2 = saveMeterInfo();
		LOG.debug("Device [{}] meter update : {}", deviceSerial, result2);

		return true;
	}

	/**
	 * device resource 정보를 저장한다.
	 * 
	 * @return
	 */
	private int saveDeviceResource() {

		int result = 0;

		// deviceInfo
		DeviceInfo deviceInfo = getDeviceInfo();

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
	private int saveMeterInfo() {

		int result = 0;

		// deviceInfo
		DeviceInfo deviceInfo = getDeviceInfo();

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

}