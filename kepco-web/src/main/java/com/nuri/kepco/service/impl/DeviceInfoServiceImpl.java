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
import com.nuri.kepco.model.MeterBilling;
import com.nuri.kepco.model.dao.DeviceInfoDAO;
import com.nuri.kepco.service.DeviceInfoService;
import com.nuri.kepco.util.ConversionUtil;
import com.nuri.kepco.util.DateUtil;
import com.nuri.kepco.util.ExcelRef;
import com.nuri.kepco.util.ExcelUtil;

@Service
@Transactional
public class DeviceInfoServiceImpl implements DeviceInfoService {

	@Autowired
	DeviceInfoDAO deviceInfoDAO;
	
	@Value("${file.download.dir:/files}")
	String fileDownloadDir;
	

	@Override
	public JSONObject selectOne(Map<String, Object> param) throws Exception {
		DeviceInfo deviceInfo = new DeviceInfo();
		ConversionUtil.getModelByMap(deviceInfo, param);
		deviceInfo = this.deviceInfoDAO.selectOne(deviceInfo);

		return ConversionUtil.getJSONObjectByModel(deviceInfo);
	}

	@Override
	public JSONArray selectList(Map<String, Object> param) throws Exception {
		DeviceInfo deviceInfo = new DeviceInfo();
		ConversionUtil.getModelByMap(deviceInfo, param);
		List<DeviceInfo> list = this.deviceInfoDAO.selectList(deviceInfo);
		
		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public int selectCount(Map<String, Object> param) throws Exception {
		DeviceInfo deviceInfo = new DeviceInfo();
		ConversionUtil.getModelByMap(deviceInfo, param);

		return this.deviceInfoDAO.selectCount(deviceInfo);
	}

	@Override
	public int insert(Map<String, Object> param) throws Exception {
		DeviceInfo deviceInfo = new DeviceInfo();
		ConversionUtil.getModelByMap(deviceInfo, param);

		return this.deviceInfoDAO.insert(deviceInfo);
	}

	@Override
	public int update(Map<String, Object> param) throws Exception {
		DeviceInfo deviceInfo = new DeviceInfo();
		ConversionUtil.getModelByMap(deviceInfo, param, false);

		return this.deviceInfoDAO.update(deviceInfo);
	}

	@Override
	public JSONObject selectByDeviceSerial(String device_serial) throws Exception {
		DeviceInfo deviceInfo = this.deviceInfoDAO.selectByDeviceSerial(device_serial);

		return ConversionUtil.getJSONObjectByModel(deviceInfo);
	}

	@Override
	public JSONArray getDeviceList(Map<String, Object> param) throws Exception {
		DeviceInfo deviceInfo = new DeviceInfo();
		ConversionUtil.getModelByMap(deviceInfo, param);
		List<DeviceInfo> list = this.deviceInfoDAO.getDeviceList(deviceInfo);

		return ConversionUtil.getJSONArrayByModel(list, deviceInfo.getStart());
	}

	@Override
	public int getDeviceListCnt(Map<String, Object> param) throws Exception {
		DeviceInfo deviceInfo = new DeviceInfo();
		ConversionUtil.getModelByMap(deviceInfo, param);

		return this.deviceInfoDAO.getDeviceListCnt(deviceInfo);
	}

	@Override
	public JSONObject getDeviceInfo(String deviceId) throws Exception {
		DeviceInfo deviceInfo = this.deviceInfoDAO.getDeviceInfo(deviceId);

		return ConversionUtil.getJSONObjectByModel(deviceInfo);
	}

	@Override
	public JSONObject getCommunication() throws Exception {
		DeviceInfo deviceInfo = deviceInfoDAO.getCommunication();

		return ConversionUtil.getJSONObjectByModel(deviceInfo);
	}

	@Override
	public Map<String, String> excelDeviceList(Map<String, Object> param) throws Exception {
		Map<String, String> output = new HashMap<String, String>();
		DeviceInfo deviceInfo = new DeviceInfo();
		ConversionUtil.getModelByMap(deviceInfo, param);		
		
		String template_filepath = "/template/template_excel.xlsx";
		String filename = "device_list_" + DateUtil.getNowDateTime() + ".xlsx";			
		String filepath = fileDownloadDir + "/deviceList/" + DateUtil.GetYear() + "/" + DateUtil.GetMonth();

		List<DeviceInfo> result = this.deviceInfoDAO.getDeviceList(deviceInfo);
		
		
		ExcelRef excelRef = new ExcelRef();
		excelRef.setTitle("단말목록 다운로드");
		excelRef.setHeaders(new String[] {"단말번호","본부","지사","단말 모델","제조사","단말상태","최종통신일시","등록일자"});
		excelRef.setCells("device_serial,parent_branch_nm,branch_nm,model_nm,vendor_nm,code_local_nm,last_comm_dt,reg_dt");
		
		ExcelUtil.makeExcelTemplate(template_filepath, filepath, filename, result, excelRef);
		
		output.put("filepath", filepath);
		output.put("filename", filename);
		
		return output;
	}
}

