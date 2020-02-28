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
import com.nuri.kepco.fep.mddata.DataParser;
import com.nuri.kepco.model.MeterInfo;
import com.nuri.kepco.mongo.model.ConnectivityMonitor;
import com.nuri.kepco.mongo.model.CpuUsageMonitor;
import com.nuri.kepco.mongo.model.RamUsageMonitor;

public class NotifyDataParser extends DataParser {

	private static final Logger LOG = LoggerFactory.getLogger(NotifyDataParser.class);
	
	private static final Integer AMI_COMMON_CONTROL_OBJECTID = 26241;
	private static final Integer AMI_CPU_RESOURCEID = 10;
	private static final Integer AMI_RAM_RESOURCEID = 11;
	
	private static final Integer CONNECTIVITY_MONITORING_OBJECTID = 4;
	
	private List<CpuUsageMonitor> cpuUsageList = null;
	private List<RamUsageMonitor> ramUsageList = null;
	private Map<Integer, ConnectivityMonitor> connectivityList = null;
	
	private String modemTime;
	private String deviceId;
	
	@Override
	public void parser(String data, String deviceId, String modemTime) throws Exception {
		
		this.cpuUsageList = new ArrayList<CpuUsageMonitor>();
		this.ramUsageList = new ArrayList<RamUsageMonitor>();
		
		// modem
		this.modemTime = (modemTime == null)? TimeUtil.getCurrentTimeMilli() : modemTime;
		this.deviceId = deviceId;
		
		try {
			
			JsonRootObject jsonObject = LwM2mJson.fromJsonLwM2m(data);			
			String bn = jsonObject.getBaseName();
			
			LwM2mPath basePath = new LwM2mPath(bn);
			
			// connectivity
			if(CONNECTIVITY_MONITORING_OBJECTID.equals(basePath.getObjectId())) {
				
				parseConnectivityMonitor(jsonObject);
				
			} else if(AMI_COMMON_CONTROL_OBJECTID.equals(basePath.getObjectId())) {
				
				for (JsonArrayEntry e : jsonObject.getResourceList()) {
					
					String resourcePath = bn + "/" + e.getName();
					
					LwM2mPath path = new LwM2mPath(resourcePath);
					
					// AMI_COMMON_CONTROL_OBJECTID
					if(AMI_COMMON_CONTROL_OBJECTID.equals(path.getObjectId())) {
						
						if(AMI_CPU_RESOURCEID.equals(path.getResourceId())) {
							
							CpuUsageMonitor cpu = new CpuUsageMonitor();
							cpu.setCpuUsage(e.getFloatValue().intValue());
							cpu.setUsageTime(modemTime);
							cpu.setSaveTime(TimeUtil.getCurrentTimeMilli());
							
							cpuUsageList.add(cpu);
						}
						
						if(AMI_RAM_RESOURCEID.equals(path.getResourceId())) {
							
							RamUsageMonitor ram = new RamUsageMonitor();
							ram.setRamUsage(e.getFloatValue().intValue());
							ram.setUsageTime(modemTime);
							ram.setSaveTime(TimeUtil.getCurrentTimeMilli());
							
							ramUsageList.add(ram);
						}
					}
				}
			}
			
		} catch (Exception e) {
			LOG.error("error", e);
		}
	}
	
	public List<CpuUsageMonitor> getCPUUsageList() {
		return cpuUsageList;
	}

	public List<RamUsageMonitor> getRAMUsageList() {
		return ramUsageList;
	}
	
	private void parseConnectivityMonitor(JsonRootObject jsonObject) {
		
		connectivityList = new HashMap<Integer, ConnectivityMonitor>();
		
		for (JsonArrayEntry e : jsonObject.getResourceList()) {			

			String resourcePath = CONNECTIVITY_MONITORING_OBJECTID + "/" + 0 + "/" + e.getName() ;
			
			LwM2mPath path = new LwM2mPath(resourcePath);
			ConnectivityMonitor connectivityMonitor = connectivityList.get(path.getObjectId());
			
			if (connectivityMonitor == null) {
				
				connectivityMonitor = new ConnectivityMonitor();
				connectivityList.put(path.getObjectId(), connectivityMonitor);
				
				if(modemTime == null) modemTime = TimeUtil.getCurrentTimeMilli(); 
				
				connectivityMonitor.setUsageTime(modemTime);
				connectivityMonitor.setSaveTime(TimeUtil.getCurrentTimeMilli());
			}
			
			if (CONNECTIVITYMONITOR.RSRP.getCode().equals(path.getResourceId())) {
				connectivityMonitor.setRsrp(e.getFloatValue().intValue());
			}
			
			if (CONNECTIVITYMONITOR.RSRQ.getCode().equals(path.getResourceId())) {
				connectivityMonitor.setRsrq(e.getFloatValue().intValue());				
			}
			
			if (CONNECTIVITYMONITOR.IPV6.getCode().equals(path.getResourceId())) {
				connectivityMonitor.setIpAddress(e.getStringValue());				
			}
			
			if (CONNECTIVITYMONITOR.CELLID.getCode().equals(path.getResourceId())) {
				connectivityMonitor.setCellId(e.getFloatValue().intValue());
			}
			
			if (CONNECTIVITYMONITOR.SMNC.getCode().equals(path.getResourceId())) {
				connectivityMonitor.setSmnc(e.getFloatValue().intValue());
			}
			
			if (CONNECTIVITYMONITOR.SMCC.getCode().equals(path.getResourceId())) {
				connectivityMonitor.setSmcc(e.getFloatValue().intValue());
			}
			
			if (CONNECTIVITYMONITOR.SSNR.getCode().equals(path.getResourceId())) {
				connectivityMonitor.setSsnr(e.getFloatValue().intValue());
			}
		}
		
		LOG.debug("connectivityList : {}", connectivityList.get(0));
	}
	
	public Map<Integer, ConnectivityMonitor> getConnectivityList() {
		return this.connectivityList;
	}
	
	
}
