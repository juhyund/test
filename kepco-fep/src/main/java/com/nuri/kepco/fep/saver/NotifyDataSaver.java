package com.nuri.kepco.fep.saver;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.nuri.kepco.fep.mddata.AbstractMDSaver;
import com.nuri.kepco.fep.mddata.IMeasurementData;
import com.nuri.kepco.fep.parser.KepcoDLMSParser;
import com.nuri.kepco.fep.parser.NotifyDataParser;
import com.nuri.kepco.mongo.model.ConnectivityMonitor;
import com.nuri.kepco.mongo.model.CpuUsageMonitor;
import com.nuri.kepco.mongo.model.RamUsageMonitor;
import com.nuri.kepco.mongo.model.dao.ConnectivityMonitorDAO;
import com.nuri.kepco.mongo.model.dao.CpuUsageMonitorDAO;
import com.nuri.kepco.mongo.model.dao.RamUsageMonitorDAO;

@Service
public class NotifyDataSaver extends AbstractMDSaver {
	
	private static final Logger LOG = LoggerFactory.getLogger(KepcoDLMSParser.class);
	
	@Autowired
	CpuUsageMonitorDAO cpuUsageMonitorDAO;
	
	@Autowired
	RamUsageMonitorDAO ramUsageMonitorDAO;
	
	@Autowired
	ConnectivityMonitorDAO connectivityMonitorDAO;
	
	@Override
	public boolean save(IMeasurementData md) throws Exception {
		
		NotifyDataParser parser = (NotifyDataParser)md.getMeterDataParser();		
		List<CpuUsageMonitor> cpuUsageList = parser.getCPUUsageList();
		List<RamUsageMonitor> ramUsageList = parser.getRAMUsageList();
		Map<Integer, ConnectivityMonitor> connectiviMonitorList = parser.getConnectivityList();
		
		String deviceSerial = md.getDeviceId();
		
		// checkDevice
		checkDevice(deviceSerial, md.getModemTime());
		
		if(getDeviceInfo() != null) {			
			
			// save CPU Usage (mongodb)
			if(cpuUsageList != null) {
				if(cpuUsageList.size() > 0) {					
					int result = saveCPUUsage(cpuUsageList);
					LOG.debug("save CPU Usage : total {} / result {}", cpuUsageList.size(), result);
				}
			}
			
			// save RAM Usage (mongodb)			
			if(ramUsageList != null) {
				if(ramUsageList.size() > 0) {					
					int result = saveRAMUsage(ramUsageList);
					LOG.debug("save RAM Usage : total {} / result {}", ramUsageList.size(), result);
				}
			}
			
			// save Connectivity Monitor Usage (mongodb)		
			if(connectiviMonitorList != null) {
				if(connectiviMonitorList.size() > 0) {					
					int result = saveConnectivityMonitor(connectiviMonitorList);
					LOG.debug("save Connectivity Monitor : total {} / result {}", connectiviMonitorList.size(), result);
				}
			}
			
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
	
	
	private int saveConnectivityMonitor(Map<Integer, ConnectivityMonitor> connectivityList) {
		
		List<ConnectivityMonitor> list = new ArrayList<ConnectivityMonitor>();
		int result = 0;
		
		try {
			
			String deviceId = getDeviceInfo().getDevice_id();
			String deviceSerial = getDeviceInfo().getDevice_serial();
			
			for(Integer key: connectivityList.keySet()) {
				
				ConnectivityMonitor connectivityMonitor = connectivityList.get(key);
				connectivityMonitor.setDeviceId(deviceId);
				connectivityMonitor.setDeviceSerial(deviceSerial);
				
				list.add(connectivityMonitor);
			}
			
			connectivityMonitorDAO.add(list);
			result = list.size();
			
		} catch (Exception e) {
			LOG.error("error", e);
			result = -1;
		}
		
		return result;
	}	

}
