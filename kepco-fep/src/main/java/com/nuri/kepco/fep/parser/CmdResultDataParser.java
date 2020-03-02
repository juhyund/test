package com.nuri.kepco.fep.parser;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.eclipse.leshan.core.node.LwM2mPath;
import org.eclipse.leshan.json.JsonArrayEntry;
import org.eclipse.leshan.json.JsonRootObject;
import org.eclipse.leshan.json.LwM2mJson;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.aimir.util.TimeUtil;
import com.nuri.kepco.fep.datatype.ConnectivityMonitorEntry;
import com.nuri.kepco.fep.datatype.ConnectivityMonitorEntry.CONNECTIVITYMONITOR;
import com.nuri.kepco.fep.datatype.MeterEntry.METERENTRY;
import com.nuri.kepco.fep.datatype.ResultMessage;
import com.nuri.kepco.fep.mddata.DataParser;
import com.nuri.kepco.model.MeterInfo;
import com.nuri.kepco.mongo.model.CmdResultData;
import com.nuri.kepco.mongo.model.ConnectivityMonitor;
import com.nuri.kepco.mongo.model.CpuUsageMonitor;
import com.nuri.kepco.mongo.model.RamUsageMonitor;

public class CmdResultDataParser extends DataParser {

	private static final Logger LOG = LoggerFactory.getLogger(CmdResultDataParser.class);
	
	private List<CmdResultData> cmdResultDataList = null;
	
	private String modemTime;
	private String deviceId;
	
	@Override
	public void parser(ResultMessage resultMessage, String deviceId, String modemTime) throws Exception {
		
		this.cmdResultDataList = new ArrayList<CmdResultData>();		
		// modem
		this.modemTime = (modemTime == null)? TimeUtil.getCurrentTimeMilli() : modemTime;
		this.deviceId = deviceId;
		
		LOG.debug("modemTime : [{}]", this.modemTime);
		
		try {
			CmdResultData cmdResultData = new CmdResultData();
			
			cmdResultData.setDeviceId(deviceId);
			cmdResultData.setTid(resultMessage.getTid());
			cmdResultData.setMid(resultMessage.getMid());
			cmdResultData.setMethod(resultMessage.getMethod());
			cmdResultData.setResource(resultMessage.getResource());
			cmdResultData.setFormat(resultMessage.getFormat());
			cmdResultData.setToken(resultMessage.getToken());
			cmdResultData.setPayload(resultMessage.getPayload());
			cmdResultData.setResultTime(this.modemTime); // 응답받은시간
			cmdResultData.setSaveTime(TimeUtil.getCurrentTimeMilli()); // 저장시간
			cmdResultData.setRequestTime(resultMessage.getRequestTime()); // 요청시간
			cmdResultData.setResult(resultMessage.getResult()); // 응답결과
			
			cmdResultDataList.add(cmdResultData);
			
		} catch (Exception e) {
			LOG.error("error", e);
		}
	}

	public List<CmdResultData> getCmdResultDataList() {
		return cmdResultDataList;
	}

	@Override
	public void parser(String data, String deviceId, String modemTime) throws Exception {
		// TODO Auto-generated method stub
	}
	
}
