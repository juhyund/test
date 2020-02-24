package com.nuri.kepco.fep.saver;

import java.util.List;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.nuri.kepco.fep.mddata.AbstractMDSaver;
import com.nuri.kepco.fep.mddata.IMeasurementData;
import com.nuri.kepco.fep.parser.KepcoDLMSParser;
import com.nuri.kepco.fep.parser.NotifyDataParser;
import com.nuri.kepco.mongo.model.CpuUsageMonitor;
import com.nuri.kepco.mongo.model.RamUsageMonitor;
import com.nuri.kepco.mongo.model.dao.CpuUsageMonitorDAO;
import com.nuri.kepco.mongo.model.dao.RamUsageMonitorDAO;

@Service
public class NotifyDataSaver extends AbstractMDSaver {
	
	private static final Logger LOG = LoggerFactory.getLogger(KepcoDLMSParser.class);
	
	@Autowired
	CpuUsageMonitorDAO cpuUsageMonitorDAO;
	
	@Autowired
	RamUsageMonitorDAO ramUsageMonitorDAO;
	
	@Override
	public boolean save(IMeasurementData md) throws Exception {
		
		NotifyDataParser parser = (NotifyDataParser)md.getMeterDataParser();		
		List<CpuUsageMonitor> cpuUsageList = parser.getCPUUsageList();
		List<RamUsageMonitor> ramUsageList = parser.getRAMUsageList();
		
		String deviceSerial = md.getDeviceId();
		
		// checkDevice
		checkDevice(deviceSerial, md.getModemTime());
		
		if(getDeviceInfo() != null) {			
			// save CPU Usage (mongodb)
			saveCPUUsage(cpuUsageList);
			
			// save RAM Usage (mongodb)
			saveRAMUsage(ramUsageList);
		}		
		return false;
	}
	
	private int saveCPUUsage(List<CpuUsageMonitor> cpuUsageList) {
		
		int result = 0;
		
		try {
			
			String deviceId = getDeviceInfo().getDevice_id();
			String deviceSerial = getDeviceInfo().getDevice_serial();
			
			for(CpuUsageMonitor cpu : cpuUsageList) {				
				cpu.setDeviceId(deviceId);
				cpu.setDeviceSerial(deviceSerial);
			}
			
			cpuUsageMonitorDAO.add(cpuUsageList);
			result = cpuUsageList.size();
			
		} catch (Exception e) {
			LOG.error("error", e);
			result = -1;
		}
		
		return result;
	}

	
	private int saveRAMUsage(List<RamUsageMonitor> ramUsageList) {
		
		int result = 0;
		try {
			
			String deviceId = getDeviceInfo().getDevice_id();
			String deviceSerial = getDeviceInfo().getDevice_serial();
			
			for(RamUsageMonitor ram : ramUsageList) {				
				ram.setDeviceId(deviceId);
				ram.setDeviceSerial(deviceSerial);
			}
			
			ramUsageMonitorDAO.add(ramUsageList);
			result = ramUsageList.size();
			
		} catch (Exception e) {
			LOG.error("error", e);
			result = -1;
		}
		return result;
	}	

}