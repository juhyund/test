package com.nuri.kepco.fep.parser;

import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.google.gson.Gson;
import com.nuri.kepco.fep.datatype.ResultMessage;
import com.nuri.kepco.fep.mddata.DataParser;
import com.nuri.kepco.mongo.model.LwM2mEventLog;

public class LwM2mEventDataParser extends DataParser {

	private static final Logger LOG = LoggerFactory.getLogger(LwM2mEventDataParser.class);

	private String modemTime;
	private String deviceId;	
	private LwM2mEventLog lwm2mEventLog;
	private String ip;
	private Integer port;
	private Map payloadMap;
	
	@Override
	public void parser(String data, String deviceId, String modemTime) throws Exception {
		
		Gson gson = new Gson();
		
		LwM2mEventLog lwm2mEventLog = new LwM2mEventLog();
		lwm2mEventLog = gson.fromJson(data, LwM2mEventLog.class);
		
		Map map = gson.fromJson(lwm2mEventLog.getPayload(), Map.class);
		
		this.deviceId = deviceId;
		this.modemTime = modemTime;
		this.lwm2mEventLog = lwm2mEventLog;
		this.ip = lwm2mEventLog.getIp();
		this.port = lwm2mEventLog.getPort();
		this.payloadMap = map;
		
	}
	
	public LwM2mEventLog getLwm2mEventLog() {
		return lwm2mEventLog;
	}

	public String getModemTime() {
		return modemTime;
	}

	public String getDeviceId() {
		return deviceId;
	}
	
	public String getIp() {
		return ip;
	}

	public Integer getPort() {
		return port;
	}
	
	public Map getPayloadMap() {
		return payloadMap;
	}

	public void setPayloadMap(Map payloadMap) {
		this.payloadMap = payloadMap;
	}

	@Override
	public void parser(ResultMessage data, String deviceId, String modemTime) throws Exception {
		// TODO Auto-generated method stub
		
	}
	
}
