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
import com.nuri.kepco.model.DeviceInfo;
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
		DeviceInfo deviceInfo = checkDevice(deviceSerial, md.getModemTime());
		
		if(deviceInfo != null) {			
			
			// save CPU Usage (mongodb)
			if(cpuUsageList != null) {
				if(cpuUsageList.size() > 0) {					
					int result = saveCPUUsage(cpuUsageList, deviceInfo);
					int result2 = saveCpuStatisticsMonitor(cpuUsageList, deviceInfo);
					LOG.debug("save CPU Usage : deviceSerial {} / total {} / result {} / statistics {}", deviceSerial, cpuUsageList.size(), result, result2);
				}
			}
			
			// save RAM Usage (mongodb)			
			if(ramUsageList != null) {
				if(ramUsageList.size() > 0) {					
					int result = saveRAMUsage(ramUsageList, deviceInfo);
					int result2 = saveRamStatisticsMonitor(ramUsageList, deviceInfo);
					LOG.debug("save RAM Usage : deviceSerial {} / total {} / result {}/ statistics {}", deviceSerial, ramUsageList.size(), result, result2);
				}
			}
			
			// save Connectivity Monitor Usage (mongodb)		
			if(connectiviMonitorList != null) {
				if(connectiviMonitorList.size() > 0) {					
					int result = saveConnectivityMonitor(connectiviMonitorList, deviceInfo);
					int result2 = saveConnectivityStatisticsMonitor(connectiviMonitorList, deviceInfo);
					LOG.debug("save Connectivity Monitor :deviceSerial {} /total {} / result {} / statistics {}", deviceSerial, connectiviMonitorList.size(), result, result2);
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
	private int saveCPUUsage(List<CpuUsageMonitor> cpuUsageList, DeviceInfo deviceInfo) {
		
		int result = 0;
		
		try {
			
			String deviceId = deviceInfo.getDevice_id();
			String deviceSerial = deviceInfo.getDevice_serial();
			String branchId = deviceInfo.getBranch_id();
			String branchNm = deviceInfo.getBranch_nm();			
			String deviceStatus = deviceInfo.getDevice_status();
			String deviceStatusNm = deviceInfo.getDevice_status_local_nm();
			
			// ?????? branch
			String parentBranchNm = deviceInfo.getParent_branch_nm();
			String parentBranchId = deviceInfo.getBranch_parent_id();
			
			for(CpuUsageMonitor cpu : cpuUsageList) {				
				cpu.setDeviceId(deviceId);
				cpu.setDeviceSerial(deviceSerial);
				cpu.setBranchId(branchId);
				cpu.setBranchNm(branchNm);
				cpu.setDeviceStatus(deviceStatus);
				cpu.setDeviceStatusNm(deviceStatusNm);
				
				cpu.setParentBranchId(parentBranchId);
				cpu.setParentBranchNm(parentBranchNm);
			}
			
			LOG.debug("cpuUsageList : {}", cpuUsageList);
			
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
	private int saveRAMUsage(List<RamUsageMonitor> ramUsageList, DeviceInfo deviceInfo) {
		
		int result = 0;
		try {
			
			String deviceId = deviceInfo.getDevice_id();
			String deviceSerial = deviceInfo.getDevice_serial();
			String branchId = deviceInfo.getBranch_id();
			String branchNm = deviceInfo.getBranch_nm();
			String deviceStatus = deviceInfo.getDevice_status();
			String deviceStatusNm = deviceInfo.getDevice_status_local_nm();
			
			// ?????? branch
			String parentBranchNm = deviceInfo.getParent_branch_nm();
			String parentBranchId = deviceInfo.getBranch_parent_id();
			
			for(RamUsageMonitor ram : ramUsageList) {				
				ram.setDeviceId(deviceId);
				ram.setDeviceSerial(deviceSerial);
				ram.setBranchId(branchId);
				ram.setBranchNm(branchNm);
				ram.setDeviceStatus(deviceStatus);
				ram.setDeviceStatusNm(deviceStatusNm);
				
				ram.setParentBranchId(parentBranchId);
				ram.setParentBranchNm(parentBranchNm);
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
	private int saveConnectivityMonitor(Map<Integer, ConnectivityMonitor> connectivityList, DeviceInfo deviceInfo) {
		
		List<ConnectivityMonitor> list = new ArrayList<ConnectivityMonitor>();
		int result = 0;
		
		try {
			
			String deviceId = deviceInfo.getDevice_id();
			String deviceSerial = deviceInfo.getDevice_serial();
			String branchId = deviceInfo.getBranch_id();
			String branchNm = deviceInfo.getBranch_nm();
			String deviceStatus = deviceInfo.getDevice_status();
			String deviceStatusNm = deviceInfo.getDevice_status_local_nm();
			
			// ?????? branch
			String parentBranchNm = deviceInfo.getParent_branch_nm();
			String parentBranchId = deviceInfo.getBranch_parent_id();
			
			for(Integer key: connectivityList.keySet()) {
				
				ConnectivityMonitor connectivityMonitor = connectivityList.get(key);
				connectivityMonitor.setDeviceId(deviceId);
				connectivityMonitor.setDeviceSerial(deviceSerial);
				connectivityMonitor.setBranchId(branchId);
				connectivityMonitor.setBranchNm(branchNm);
				connectivityMonitor.setDeviceStatus(deviceStatus);
				connectivityMonitor.setDeviceStatusNm(deviceStatusNm);
				connectivityMonitor.setParentBranchId(parentBranchId);
				connectivityMonitor.setParentBranchNm(parentBranchNm);
				
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
	 * saveCpuStatisticsMonitor
	 * @param cpuUsageList
	 * @return
	 */
	private int saveConnectivityStatisticsMonitor(Map<Integer, ConnectivityMonitor> connectivityList, DeviceInfo deviceInfo) {
		
		int result = 0;
		
		try {
			
			String deviceId = deviceInfo.getDevice_id();
			String deviceSerial = deviceInfo.getDevice_serial();
			String branchId = deviceInfo.getBranch_id();
			String branchNm = deviceInfo.getBranch_nm();
			String deviceStatus = deviceInfo.getDevice_status();
			String deviceStatusNm = deviceInfo.getDevice_status_local_nm();
			
			// ?????? branch
			String parentBranchNm = deviceInfo.getParent_branch_nm();
			String parentBranchId = deviceInfo.getBranch_parent_id();
			
			for(Integer key: connectivityList.keySet()) {
				
				ConnectivityMonitor connectivityMonitor = connectivityList.get(key);
				
				// param - device id??? ????????? Statistics??? ????????? ??????.
				ConnectivityStatisticsMonitor param = new ConnectivityStatisticsMonitor();
				param.setDeviceId(deviceId);
				 
				List<ConnectivityStatisticsMonitor> _list = connectivityStatisticsMonitorDAO.getConnectivityStatisticsMonitor(param);				
				ConnectivityStatisticsMonitor statistics = null;
				
				if(_list.size() > 0) {					 
					statistics = _list.get(0);
					
				} else {
					statistics = new ConnectivityStatisticsMonitor();
				}
				
				statistics.setDeviceId(deviceId);
				statistics.setDeviceSerial(deviceSerial);
				statistics.setBranchId(branchId);
				statistics.setBranchNm(branchNm);
				statistics.setDeviceStatus(deviceStatus);
				statistics.setDeviceStatusNm(deviceStatusNm);
				statistics.setParentBranchId(parentBranchId);
				statistics.setParentBranchNm(parentBranchNm);
				
				if(connectivityMonitor.getRsrp() != null) { statistics.setRsrp(connectivityMonitor.getRsrp()); }
				if(connectivityMonitor.getRsrq() != null) { statistics.setRsrq(connectivityMonitor.getRsrq()); }
				if(connectivityMonitor.getIpAddress() != null) { statistics.setIpAddress(connectivityMonitor.getIpAddress()); }
				if(connectivityMonitor.getCellId() != null) { statistics.setCellId(connectivityMonitor.getCellId()); }
				if(connectivityMonitor.getSmnc() != null) { statistics.setSmnc(connectivityMonitor.getSmnc()); }
				if(connectivityMonitor.getSmcc() != null) { statistics.setSmcc(connectivityMonitor.getSmcc()); }
				if(connectivityMonitor.getSsnr() != null) { statistics.setSsnr(connectivityMonitor.getSsnr()); }
				if(connectivityMonitor.getUsageTime() != null) { statistics.setUsageTime(connectivityMonitor.getUsageTime());}
				if(connectivityMonitor.getSaveTime() != null) { statistics.setSaveTime(connectivityMonitor.getSaveTime());}
					
				LOG.debug("_list : {}", _list);
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
	
	/**
	 * saveCpuStatisticsMonitor
	 * @param cpuUsageList
	 * @return
	 */
	private int saveCpuStatisticsMonitor(List<CpuUsageMonitor> cpuUsageList, DeviceInfo deviceInfo) {
		
		int result = 0;
		
		try {
			
			String deviceId = deviceInfo.getDevice_id();
			String deviceSerial = deviceInfo.getDevice_serial();
			String branchId = deviceInfo.getBranch_id();
			String branchNm = deviceInfo.getBranch_nm();
			String deviceStatus = deviceInfo.getDevice_status();
			String deviceStatusNm = deviceInfo.getDevice_status_local_nm();
			
			// ?????? branch
			String parentBranchNm = deviceInfo.getParent_branch_nm();
			String parentBranchId = deviceInfo.getBranch_parent_id();
			
			for(CpuUsageMonitor cpu : cpuUsageList) {
				
				// param - device id??? ????????? Statistics??? ????????? ??????.
				ConnectivityStatisticsMonitor param = new ConnectivityStatisticsMonitor();
				param.setDeviceId(deviceId);
				 
				List<ConnectivityStatisticsMonitor> _list = connectivityStatisticsMonitorDAO.getConnectivityStatisticsMonitor(param);
				ConnectivityStatisticsMonitor statistics = null;
				
				if(_list.size() > 0) {					 
					statistics = _list.get(0);					
				} else {
					statistics = new ConnectivityStatisticsMonitor();
					
					statistics.setDeviceId(deviceId);
					statistics.setDeviceSerial(deviceSerial);
					statistics.setBranchId(branchId);
					statistics.setBranchNm(branchNm);
					statistics.setDeviceStatus(deviceStatus);
					statistics.setDeviceStatusNm(deviceStatusNm);
					statistics.setParentBranchId(parentBranchId);
					statistics.setParentBranchNm(parentBranchNm);
				}
				
				if(cpu.getCpuUsage() != null) { statistics.setCpuUsage(cpu.getCpuUsage());}
				if(cpu.getUsageTime() != null) { statistics.setUsageTime(cpu.getUsageTime());}
				if(cpu.getSaveTime() != null) { statistics.setSaveTime(cpu.getSaveTime());}
				
				connectivityStatisticsMonitorDAO.save(statistics);
				result++;
			}
				
			
		} catch (Exception e) {
			LOG.error("error", e);
			result = -1;
		}
		
		return result;
	}
	
	
	/**
	 * saveRamStatisticsMonitor
	 * @param ramUsageList
	 * @return
	 */
	private int saveRamStatisticsMonitor(List<RamUsageMonitor> ramUsageList, DeviceInfo deviceInfo) {
		
		int result = 0;
		
		try {
			
			String deviceId = deviceInfo.getDevice_id();
			String deviceSerial = deviceInfo.getDevice_serial();
			String branchId = deviceInfo.getBranch_id();
			String branchNm = deviceInfo.getBranch_nm();
			String deviceStatus = deviceInfo.getDevice_status();
			String deviceStatusNm = deviceInfo.getDevice_status_local_nm();
			
			// ?????? branch
			String parentBranchNm = deviceInfo.getParent_branch_nm();
			String parentBranchId = deviceInfo.getBranch_parent_id();
			
			for(RamUsageMonitor ram : ramUsageList) {
				
				// param - device id??? ????????? Statistics??? ????????? ??????.
				ConnectivityStatisticsMonitor param = new ConnectivityStatisticsMonitor();
				param.setDeviceId(deviceId);
				 
				List<ConnectivityStatisticsMonitor> _list = connectivityStatisticsMonitorDAO.getConnectivityStatisticsMonitor(param);
				ConnectivityStatisticsMonitor statistics = null;
				
				if(_list.size() > 0) {					 
					statistics = _list.get(0);					
				} else {
					statistics = new ConnectivityStatisticsMonitor();
					
					statistics.setDeviceId(deviceId);
					statistics.setDeviceSerial(deviceSerial);
					
					statistics.setParentBranchId(parentBranchId);
					statistics.setParentBranchNm(parentBranchNm);
					
					statistics.setBranchId(branchId);
					statistics.setBranchNm(branchNm);
					
					statistics.setDeviceStatus(deviceStatus);
					statistics.setDeviceStatusNm(deviceStatusNm);
				}
				
				LOG.debug("ram.getUsageTime() {}", ram.getUsageTime());
				
				if(ram.getRamUsage() != null) { statistics.setRamUsage(ram.getRamUsage());}
				if(ram.getUsageTime() != null) { statistics.setUsageTime(ram.getUsageTime());}
				if(ram.getSaveTime() != null) { statistics.setSaveTime(ram.getSaveTime());}
				
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
