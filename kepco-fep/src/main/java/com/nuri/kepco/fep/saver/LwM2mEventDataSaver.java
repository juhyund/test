package com.nuri.kepco.fep.saver;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Service;

import com.nuri.kepco.fep.datatype.MeterType.DEVICESTATUS;
import com.nuri.kepco.fep.mddata.AbstractMDSaver;
import com.nuri.kepco.fep.mddata.IMeasurementData;
import com.nuri.kepco.fep.parser.LwM2mEventDataParser;
import com.nuri.kepco.model.DeviceInfo;
import com.nuri.kepco.mongo.model.LwM2mEventLog;

@Service
public class LwM2mEventDataSaver extends AbstractMDSaver {
	
	private static final Logger LOG = LoggerFactory.getLogger(LwM2mEventDataSaver.class);
	
	@Override
	public boolean save(IMeasurementData md) throws Exception {
		
		LwM2mEventDataParser parser = (LwM2mEventDataParser)md.getMeterDataParser();
		
		LwM2mEventLog lwm2mEventLog = parser.getLwm2mEventLog();
		
		String registrationDate = "";
		String deviceSerial = parser.getDeviceId();
		String modemTime = parser.getModemTime();
		String ip = parser.getIp().replace("/", "");
		Integer port = parser.getPort();
		
		String method = lwm2mEventLog.getMethod();
		
		LOG.debug("deviceSerial {} / method : {}", deviceSerial, method);
		
		DEVICESTATUS deviceStatus = null;
		
		if("REGISTRATION".equals(method)) { // 초기 등록			
			
			deviceStatus = DEVICESTATUS.NEWREGISTRATION;
			registrationDate = (String)parser.getPayloadMap().get("registrationDate");			
			
		} else if ("DEREGISTRATION".equals(method)) { // 해지
			
			deviceStatus = DEVICESTATUS.DEREGISTRATION;
		}
		
		// 단말정보 업데이트
		DeviceInfo deviceInfo = checkDevice(deviceSerial, modemTime, ip, String.valueOf(port), registrationDate, deviceStatus);
		
		if(deviceInfo != null) {
			return true;
		} else {
			return false;
		}
	}
}
