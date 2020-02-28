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
import com.nuri.kepco.mongo.model.ConnectivityStatisticsMonitor;
import com.nuri.kepco.mongo.model.CpuUsageMonitor;
import com.nuri.kepco.mongo.model.RamUsageMonitor;
import com.nuri.kepco.mongo.model.dao.ConnectivityMonitorDAO;
import com.nuri.kepco.mongo.model.dao.ConnectivityStatisticsMonitorDAO;
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
	
	@Autowired
	ConnectivityStatisticsMonitorDAO connectivityStatisticsMonitorDAO;
	
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
					int result2 = saveConnectivityStatisticsMonitor(connectiviMonitorList);
					LOG.debug("save Connectivity Monitor : total {} / result {} / statistics {}", connectiviMonitorList.size(), result, result2);
				}
			}
			
		}		
		return false;
	}
	
	/**
	 * saveCPUUsage
	 * @param connectivityList
	 * @return
	 */
	private int saveCPUUsage(List<CpuUsageMonitor> cpuUsageList) {
		
		int result = 0;
		
		try {
			
			String deviceId = getDeviceInfo().getDevice_id();
			String deviceSerial = getDeviceInfo().getDevice_serial();
			String branchId = getDeviceInfo().getBranch_id();
			String branchNm = getDeviceInfo().getBranch_nm();
			String deviceStatus = getDeviceInfo().getDevice_status();
			String deviceStatusNm = getDeviceInfo().getDevice_status_nm();
			
			for(CpuUsageMonitor cpu : cpuUsageList) {				
				cpu.setDeviceId(deviceId);
				cpu.setDeviceSerial(deviceSerial);
				cpu.setBranchId(branchId);
				cpu.setBranchNm(branchNm);
				cpu.setDeviceStatus(deviceStatus);
				cpu.setDeviceStatusNm(deviceStatusNm);
			}
			
			cpuUsageMonitorDAO.add(cpuUsageList);
			result = cpuUsageList.size();
			
		} catch (Exception e) {
			LOG.error("error", e);
			result = -1;
		}
		
		return result;
	}

	/**
	 * saveRAMUsage
	 * @param connectivityList
	 * @return
	 */
	private int saveRAMUsage(List<RamUsageMonitor> ramUsageList) {
		
		int result = 0;
		try {
			
			String deviceId = getDeviceInfo().getDevice_id();
			String deviceSerial = getDeviceInfo().getDevice_serial();
			String branchId = getDeviceInfo().getBranch_id();
			String branchNm = getDeviceInfo().getBranch_nm();
			String deviceStatus = getDeviceInfo().getDevice_status();
			String deviceStatusNm = getDeviceInfo().getDevice_status_nm();
			
			for(RamUsageMonitor ram : ramUsageList) {				
				ram.setDeviceId(deviceId);
				ram.setDeviceSerial(deviceSerial);
				ram.setBranchId(branchId);
				ram.setBranchNm(branchNm);
				ram.setDeviceStatus(deviceStatus);
				ram.setDeviceStatusNm(deviceStatusNm);
			}
			
			ramUsageMonitorDAO.add(ramUsageList);
			result = ramUsageList.size();
			
		} catch (Exception e) {
			LOG.error("error", e);
			result = -1;
		}
		return result;
	}	
	
	/**
	 * saveConnectivityMonitor
	 * @param connectivityList
	 * @return
	 */
	private int saveConnectivityMonitor(Map<Integer, ConnectivityMonitor> connectivityList) {
		
		List<ConnectivityMonitor> list = new ArrayList<ConnectivityMonitor>();
		int result = 0;
		
		try {
			
			String deviceId = getDeviceInfo().getDevice_id();
			String deviceSerial = getDeviceInfo().getDevice_serial();
			String branchId = getDeviceInfo().getBranch_id();
			String branchNm = getDeviceInfo().getBranch_nm();
			String deviceStatus = getDeviceInfo().getDevice_status();
			String deviceStatusNm = getDeviceInfo().getDevice_status_nm();
			
			for(Integer key: connectivityList.keySet()) {
				
				ConnectivityMonitor connectivityMonitor = connectivityList.get(key);
				connectivityMonitor.setDeviceId(deviceId);
				connectivityMonitor.setDeviceSerial(deviceSerial);
				connectivityMonitor.setBranchId(branchId);
				connectivityMonitor.setBranchNm(branchNm);
				connectivityMonitor.setDeviceStatus(deviceStatus);
				connectivityMonitor.setDeviceStatusNm(deviceStatusNm);
				
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
	
	/**
	 * saveConnectivityMonitor
	 * @param connectivityList
	 * @return
	 */
	private int saveConnectivityStatisticsMonitor(Map<Integer, ConnectivityMonitor> connectivityList) {
		
		List<ConnectivityStatisticsMonitor> list = new ArrayList<ConnectivityStatisticsMonitor>();
		int result = 0;
		
		try {
			
			String deviceId = getDeviceInfo().getDevice_id();
			String deviceSerial = getDeviceInfo().getDevice_serial();
			String branchId = getDeviceInfo().getBranch_id();
			String branchNm = getDeviceInfo().getBranch_nm();
			String deviceStatus = getDeviceInfo().getDevice_status();
			String deviceStatusNm = getDeviceInfo().getDevice_status_nm();
			
			for(Integer key: connectivityList.keySet()) {
				
				ConnectivityMonitor connectivityMonitor = connectivityList.get(key);
				
				// param - device id가 동일한 Statistics를 가지로 온다.
				ConnectivityStatisticsMonitor param = new ConnectivityStatisticsMonitor();
				param.setDeviceId(deviceId);
				 
				List<ConnectivityStatisticsMonitor> slist = connectivityStatisticsMonitorDAO.getConnectivityStatisticsMonitor(param);				
				ConnectivityStatisticsMonitor statistics = null;
				
				LOG.debug("slist : {}", slist);
				
				if(slist.size() > 0) {					 
					statistics = slist.get(0);
					
				} else {
					statistics = new ConnectivityStatisticsMonitor();
				}
				
				statistics.setDeviceId(deviceId);
				statistics.setDeviceSerial(deviceSerial);
				statistics.setBranchId(branchId);
				statistics.setBranchNm(branchNm);
				statistics.setDeviceStatus(deviceStatus);
				statistics.setDeviceStatusNm(deviceStatusNm);
				statistics.setRsrp(connectivityMonitor.getRsrp());
				statistics.setRsrq(connectivityMonitor.getRsrq());
				statistics.setIpAddress(connectivityMonitor.getIpAddress());
				statistics.setCellId(connectivityMonitor.getCellId());
				statistics.setSmnc(connectivityMonitor.getSmnc());
				statistics.setSmcc(connectivityMonitor.getSmcc());
				statistics.setSsnr(connectivityMonitor.getSsnr());
				LOG.debug("slist : {}", slist);
				// save
				connectivityStatisticsMonitorDAO.save(statistics);
				result++;
			}
			
		} catch (Exception e) {
			LOG.error("error", e);
			result = -1;
		}
		
		return result;
	}

}
