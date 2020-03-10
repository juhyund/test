package com.nuri.kepco.service.impl;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
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
import com.nuri.kepco.util.DateUtil;
import com.nuri.kepco.util.ExcelRef;
import com.nuri.kepco.util.ExcelUtil;

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
	
	@Value("${file.download.dir:/files}")
	String fileDownloadDir;

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

		return ConversionUtil.getJSONArrayByModel(list,nmsInfo.getStart());
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
		
		return ConversionUtil.getJSONArrayByModel(list, (int) connectivityStatistics.getOffset());
	}

	@Override
	public long getCount(Map<String, Object> param) throws Exception {
		ConnectivityStatisticsMonitor connectivityStatistics = new ConnectivityStatisticsMonitor();
		ConversionUtil.getModelByMap(connectivityStatistics, param);

		return this.connectivityStatisticsMonitorDAO.getCount(connectivityStatistics);
	}

	@Override
	public Map<String, String> excelMeterList(Map<String, Object> param) throws Exception {
		Map<String, String> output = new HashMap<String, String>();
		ConnectivityStatisticsMonitor connectivityStatistics = new ConnectivityStatisticsMonitor();
		ConversionUtil.getModelByMap(connectivityStatistics, param);
		
		String template_filepath = "/template/template_excel.xlsx";
		String filename = "device_list_" + DateUtil.getNowDateTime() + ".xlsx";
		String filepath = fileDownloadDir + "/deviceList/" + DateUtil.GetYear() + "/" + DateUtil.GetMonth();
		
		List<ConnectivityStatisticsMonitor> result = this.connectivityStatisticsMonitorDAO.getConnectivityStatisticsMonitor(connectivityStatistics);
		
		ExcelRef excelRef = new ExcelRef();

		excelRef.setTitle("제어이력 다운로드");
		excelRef.setHeaders(new String[] {"모뎀번호", "본부", "지사", "모뎀상태", "CPU(%)","Memory(%)", "RSRP(dBm)", "RSRQ(dB)", "SNR(dB)", "최종 통신일자", "등록일자"});
		excelRef.setCells("deviceSerial,parentBranchNm,branchNm,deviceStatusNm,cpuUsage,ramUsage,rsrp,rsrq,ssnr,usageTime,saveTime");
		ExcelUtil.makeExcelTemplate(template_filepath, filepath, filename, result, excelRef);
		
		output.put("filepath", filepath);
		output.put("filename", filename);
			
		return output;
	}
}
