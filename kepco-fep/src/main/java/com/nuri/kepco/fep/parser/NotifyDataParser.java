package com.nuri.kepco.fep.parser;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import org.eclipse.leshan.core.node.LwM2mPath;
import org.eclipse.leshan.json.JsonArrayEntry;
import org.eclipse.leshan.json.JsonRootObject;
import org.eclipse.leshan.json.LwM2mJson;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Service;

import com.nuri.kepco.fep.mddata.DataParser;
import com.nuri.kepco.mongo.model.CpuUsageMonitor;
import com.nuri.kepco.mongo.model.RamUsageMonitor;

public class NotifyDataParser extends DataParser {

	private static final Logger LOG = LoggerFactory.getLogger(NotifyDataParser.class);
	
	private static final Integer AMI_COMMON_CONTROL_OBJECTID = 26241;
	private static final Integer AMI_CPU_RESOURCEID = 10;
	private static final Integer AMI_RAM_RESOURCEID = 11;
	
	List<CpuUsageMonitor> cpuUsageList = null;
	List<RamUsageMonitor> ramUsageList = null;
	
	@Override
	public void parser(String data) throws Exception {
		
		cpuUsageList = new ArrayList<CpuUsageMonitor>();
		ramUsageList = new ArrayList<RamUsageMonitor>();
		
		try {
			JsonRootObject jsonObject = LwM2mJson.fromJsonLwM2m(data);			
			String bn = jsonObject.getBaseName();
			
			for (JsonArrayEntry e : jsonObject.getResourceList()) {
				
				String resourcePath = bn + "/" + e.getName();
				
				LwM2mPath path = new LwM2mPath(resourcePath);
				
				if(AMI_COMMON_CONTROL_OBJECTID.equals(path.getObjectId())) {
					
					if(AMI_CPU_RESOURCEID.equals(path.getResourceId())) {
						
						CpuUsageMonitor cpu = new CpuUsageMonitor();
						cpu.setCpuUsage(e.getFloatValue().intValue());
						cpu.setUsageTime(new Date());
						
						cpuUsageList.add(cpu);
					}
					
					if(AMI_RAM_RESOURCEID.equals(path.getResourceId())) {
						
						RamUsageMonitor ram = new RamUsageMonitor();
						ram.setRamUsage(e.getFloatValue().intValue());
						ram.setUsageTime(new Date());
						
						ramUsageList.add(ram);
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
}
