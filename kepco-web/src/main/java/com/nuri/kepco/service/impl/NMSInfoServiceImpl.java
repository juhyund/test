package com.nuri.kepco.service.impl;

import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.nuri.kepco.model.NMSInfo;
import com.nuri.kepco.model.dao.NMSInfoDAO;
import com.nuri.kepco.mongo.model.ConnectivityMonitor;
import com.nuri.kepco.mongo.model.ConnectivityStatisticsMonitor;
import com.nuri.kepco.mongo.model.CpuUsageMonitor;
import com.nuri.kepco.mongo.model.RamUsageMonitor;
import com.nuri.kepco.mongo.model.dao.ConnectivityMonitorDAO;
import com.nuri.kepco.mongo.model.dao.ConnectivityStatisticsMonitorDAO;
import com.nuri.kepco.mongo.model.dao.CpuUsageMonitorDAO;
import com.nuri.kepco.mongo.model.dao.RamUsageMonitorDAO;
import com.nuri.kepco.service.NMSInfoService;
import com.nuri.kepco.util.ConversionUtil;

@Service
@Transactional
public class NMSInfoServiceImpl implements NMSInfoService {

	@Autowired
	NMSInfoDAO nmsInfoDAO;
	
	@Autowired
	ConnectivityMonitorDAO connectivityMonitorDAO;
	
	@Autowired
	CpuUsageMonitorDAO cpuUsageMonitorDAO;
	
	@Autowired
	RamUsageMonitorDAO ramUsageMonitorDAO;
	
	@Autowired
	ConnectivityStatisticsMonitorDAO connectivityStatisticsMonitorDAO;

	@Override
	public int selectCount(Map<String, Object> param) throws Exception {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public JSONArray selectList(Map<String, Object> param) throws Exception {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public JSONObject selectOne(Map<String, Object> param) throws Exception {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int insert(Map<String, Object> param) throws Exception {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public int update(Map<String, Object> param) throws Exception {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public JSONObject selectByDeviceSerial(String device_serial) throws Exception {
		// TODO Auto-generated method stub
		return null;
	}
	
	@Override
	public List<ConnectivityMonitor> getConnectivityMonitor(Map<String, Object> param) throws Exception{
		ConnectivityMonitor connectivity = new ConnectivityMonitor();
		ConversionUtil.getModelByMap(connectivity, param);
		List<ConnectivityMonitor> list = this.connectivityMonitorDAO.getConnectivityMonitor(connectivity);
		
		return ConversionUtil.getJSONArrayByModel(list);
	}
	
	@Override
	public List<CpuUsageMonitor> getCpuUsageMonitor(Map<String, Object> param) throws Exception{
		CpuUsageMonitor cpuUsage = new CpuUsageMonitor();
		ConversionUtil.getModelByMap(cpuUsage, param);
		List<CpuUsageMonitor> list = this.cpuUsageMonitorDAO.getCpuUsageMonitor(cpuUsage);
		
		return ConversionUtil.getJSONArrayByModel(list);
	}
	
	@Override
	public List<RamUsageMonitor> getRamUsageMonitor(Map<String, Object> param) throws Exception{
		RamUsageMonitor ramUsage = new RamUsageMonitor();
		ConversionUtil.getModelByMap(ramUsage, param);
		List<RamUsageMonitor> list = this.ramUsageMonitorDAO.getRamUsageMonitor(ramUsage);
		
		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public JSONArray getNMSList(Map<String, Object> param) throws Exception {
		NMSInfo nmsInfo = new NMSInfo();
		ConversionUtil.getModelByMap(nmsInfo, param);
		List<NMSInfo> list = this.nmsInfoDAO.getNMSList(nmsInfo);

		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public int getNMSListCnt(Map<String, Object> param) throws Exception {
		NMSInfo nmsInfo = new NMSInfo();
		ConversionUtil.getModelByMap(nmsInfo, param);

		return this.nmsInfoDAO.getNMSListCnt(nmsInfo);
	}

	@Override
	public JSONObject getNMSDetail(String meter_serial) throws Exception {
		NMSInfo nmsInfo = nmsInfoDAO.getNMSDetail(meter_serial);
		return ConversionUtil.getJSONObjectByModel(nmsInfo);
	}

	@Override
	public JSONArray getConnectivityStatistics(Map<String, Object> param) throws Exception {
		ConnectivityStatisticsMonitor connectivityStatistics = new ConnectivityStatisticsMonitor();
		ConversionUtil.getModelByMap(connectivityStatistics, param);
		List<ConnectivityStatisticsMonitor> list = this.connectivityStatisticsMonitorDAO.getConnectivityStatisticsMonitor(connectivityStatistics);
		
		return ConversionUtil.getJSONArrayByModel(list);
	}
}
