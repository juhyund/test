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

import com.nuri.kepco.model.DeviceInfo;
import com.nuri.kepco.model.DevicePowerLog;
import com.nuri.kepco.model.dao.DevicePowerLogDAO;
import com.nuri.kepco.service.DevicePowerLogService;
import com.nuri.kepco.util.ConversionUtil;
import com.nuri.kepco.util.DateUtil;
import com.nuri.kepco.util.ExcelRef;
import com.nuri.kepco.util.ExcelUtil;

@Service
@Transactional
public class DevicePowerLogServiceImpl implements DevicePowerLogService {

	@Autowired
	DevicePowerLogDAO devicePowerLogDAO;

	@Value("${file.download.dir:/files}")
	String fileDownloadDir;
	
	@Override
	public JSONObject selectOne(Map<String, Object> param) throws Exception {
		DevicePowerLog devicePowerLog = new DevicePowerLog();
		ConversionUtil.getModelByMap(devicePowerLog, param);
		devicePowerLog = this.devicePowerLogDAO.selectOne(devicePowerLog);

		return ConversionUtil.getJSONObjectByModel(devicePowerLog);
	}

	@Override
	public JSONArray selectList(Map<String, Object> param) throws Exception {
		DevicePowerLog devicePowerLog = new DevicePowerLog();
		ConversionUtil.getModelByMap(devicePowerLog, param);
		List<DevicePowerLog> list = this.devicePowerLogDAO.selectList(devicePowerLog);
		
		return ConversionUtil.getJSONArrayByModel(list, devicePowerLog.getStart());
	}

	@Override
	public int selectCount(Map<String, Object> param) throws Exception {
		DevicePowerLog devicePowerLog = new DevicePowerLog();
		ConversionUtil.getModelByMap(devicePowerLog, param);

		return this.devicePowerLogDAO.selectCount(devicePowerLog);
	}

	@Override
	public int insert(Map<String, Object> param) throws Exception {
		DevicePowerLog devicePowerLog = new DevicePowerLog();
		ConversionUtil.getModelByMap(devicePowerLog, param);

		return this.devicePowerLogDAO.insert(devicePowerLog);
	}

	@Override
	public int update(Map<String, Object> param) throws Exception {
		DevicePowerLog devicePowerLog = new DevicePowerLog();
		ConversionUtil.getModelByMap(devicePowerLog, param, false);

		return this.devicePowerLogDAO.update(devicePowerLog);
	}

	@Override
	public Map<String, String> excelDevicePowerLogList(Map<String, Object> param) throws Exception {
		Map<String, String> output = new HashMap<String, String>();
		DevicePowerLog devicePowerLog = new DevicePowerLog();
		ConversionUtil.getModelByMap(devicePowerLog, param);		
		
		String template_filepath = "/template/template_excel.xlsx";
		String filename = "device_power_log_list_" + DateUtil.getNowDateTime() + ".xlsx";			
		String filepath = fileDownloadDir + "/devicepowerloglist/" + DateUtil.GetYear() + "/" + DateUtil.GetMonth();

		List<DevicePowerLog> result = this.devicePowerLogDAO.selectList(devicePowerLog);
		
		
		ExcelRef excelRef = new ExcelRef();
		excelRef.setTitle("정전/복전 다운로드");
		excelRef.setHeaders(new String[] {"모뎀번호","본부","지사","복전 시간","정전 시간","정전 상태","서버 등록 일시"});
		excelRef.setCells("device_serial,parent_branch_nm,branch_nm,power_on_time,power_off_time,power_status,reg_dt");
		
		ExcelUtil.makeExcelTemplate(template_filepath, filepath, filename, result, excelRef);
		
		output.put("filepath", filepath);
		output.put("filename", filename);
		
		return output;
	}

}

