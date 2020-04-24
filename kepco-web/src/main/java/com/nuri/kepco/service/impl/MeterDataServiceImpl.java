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

import com.nuri.kepco.model.MeterData;
import com.nuri.kepco.model.dao.MeterDataDAO;
import com.nuri.kepco.service.MeterDataService;
import com.nuri.kepco.util.ConversionUtil;
import com.nuri.kepco.util.DateUtil;
import com.nuri.kepco.util.ExcelRef;
import com.nuri.kepco.util.ExcelUtil;


@Service
@Transactional
public class MeterDataServiceImpl implements MeterDataService {

	@Value("${file.download.dir:/files}")
	String fileDownloadDir;
	
	@Autowired
	MeterDataDAO meterDataDAO;


	@Override
	public int selectCount(Map<String, Object> param) throws Exception {
		MeterData meterData = new MeterData();
		ConversionUtil.getModelByMap(meterData, param);

		return this.meterDataDAO.selectCount(meterData);
	}

	@Override
	public JSONArray selectList(Map<String, Object> param) throws Exception {
		MeterData meterData = new MeterData();
		ConversionUtil.getModelByMap(meterData, param);
		List<MeterData> list = this.meterDataDAO.selectList(meterData);

		return ConversionUtil.getJSONArrayByModel(list,meterData.getStart());
	}
	
	@Override
	public JSONArray selectDetail(Map<String, Object> param) throws Exception {
		MeterData meterData = new MeterData();
		ConversionUtil.getModelByMap(meterData, param);
		List<MeterData> list = this.meterDataDAO.selectDetail(meterData);

		return ConversionUtil.getJSONArrayByModel(list,meterData.getStart());
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
	public Map<String, String> excelMeterData(Map<String, Object> param) throws Exception {
		Map<String, String> output = new HashMap<String, String>();
		MeterData meterData = new MeterData();
		ConversionUtil.getModelByMap(meterData, param);		
		
		String template_filepath = "/template/template_excel.xlsx";
		String filename = "meter_data_" + DateUtil.getNowDateTime() + ".xlsx";			
		String filepath = fileDownloadDir + "/meterData/" + DateUtil.GetYear() + "/" + DateUtil.GetMonth();
		
		List<MeterData> result = this.meterDataDAO.selectList(meterData);
		
		
		ExcelRef excelRef = new ExcelRef();
		excelRef.setTitle("기타검침정보 다운로드");
		excelRef.setHeaders(new String[] {"검침일자", "계기번호", "본부", "지사", "계기타입","모뎀번호","검침항목","등록시간"});
		excelRef.setCells("read_dt,meter_serial,parent_branch_nm,branch_nm,meter_type,device_serial,obis_code_descr,reg_dt");
		
		ExcelUtil.makeExcelTemplate(template_filepath, filepath, filename, result, excelRef);
		
		output.put("filepath", filepath);
		output.put("filename", filename);
		
		return output;
	}


}
