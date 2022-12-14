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

import com.nuri.kepco.model.MeterValue;
import com.nuri.kepco.model.dao.MeterValueDAO;
import com.nuri.kepco.service.MeterValueService;
import com.nuri.kepco.util.ConversionUtil;
import com.nuri.kepco.util.DateUtil;
import com.nuri.kepco.util.ExcelRef;
import com.nuri.kepco.util.ExcelUtil;

@Service
@Transactional
public class MeterValueServiceImpl implements MeterValueService {

	@Value("${file.download.dir:/files}")
	String fileDownloadDir;
	
	@Autowired
	MeterValueDAO meterValueDAO;

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
	public JSONArray getMeterValue(Map<String, Object> param) throws Exception {
		MeterValue meterValue = new MeterValue();
		ConversionUtil.getModelByMap(meterValue, param);
		List<MeterValue> list = this.meterValueDAO.getMeterValue(meterValue);

		return ConversionUtil.getJSONArrayByModel(list,meterValue.getStart());
	}

	@Override
	public int getMeterValueCount(Map<String, Object> param) throws Exception {
		MeterValue meterValue = new MeterValue();
		ConversionUtil.getModelByMap(meterValue, param);

		return this.meterValueDAO.getMeterValueCount(meterValue);
	}

	@Override
	public JSONArray getMeterValueDetail(Map<String, Object> param) throws Exception {
		MeterValue meterValue = new MeterValue();
		ConversionUtil.getModelByMap(meterValue, param);
		
		List<Map<String, Object>> channels = this.meterValueDAO.selectMeterChannel(meterValue);
		meterValue.setChannelList(channels);
		
		List<Map<String, Object>> list = this.meterValueDAO.getMeterValueDetail(meterValue);
		return ConversionUtil.getJSONArrayByModel(list,meterValue.getStart());
	}

	@Override
	public JSONArray selectMeterInfo(Map<String, Object> param) throws Exception {
		MeterValue meterValue = new MeterValue();
		ConversionUtil.getModelByMap(meterValue, param);
		List<Map<String, Object>> list = this.meterValueDAO.selectMeterInfo(meterValue);

		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public JSONArray selectMeterChannel(Map<String, Object> param) throws Exception {
		MeterValue meterValue = new MeterValue();
		ConversionUtil.getModelByMap(meterValue, param);
		//meterValueDAO.sel
		List<Map<String, Object>>list =  this.meterValueDAO.selectMeterChannel(meterValue);
		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public Map<String, String> excelMeterValue(Map<String, Object> param) throws Exception {
		Map<String, String> output = new HashMap<String, String>();
		MeterValue meterValue = new MeterValue();
		ConversionUtil.getModelByMap(meterValue, param);
		
		String template_filepath = "/template/template_excel.xlsx";
		String filename = "meter_value_" + DateUtil.getNowDateTime() + ".xlsx";			
		String filepath = fileDownloadDir + "/meterValue/" + DateUtil.GetYear() + "/" + DateUtil.GetMonth();

		List<MeterValue> result = this.meterValueDAO.getMeterValue(meterValue);

		String[] header = {"????????????", "????????????", "??????", "??????", "????????????", "????????????", "??????????????? (kWh)","????????????"};
		String cells = "read_dt,meter_serial,parent_branch_nm,branch_nm,meter_type,device_serial,meter_value,reg_dt";
		
		ExcelRef excelRef = new ExcelRef();
		excelRef.setTitle("LP?????? ????????????");
		excelRef.setHeaders(header);
		excelRef.setCells(cells);
		
		ExcelUtil.makeExcelTemplate(template_filepath, filepath, filename, result, excelRef);
		
		output.put("filepath", filepath);
		output.put("filename", filename);
		
		return output;
	}

	@Override
	public Map<String, String> excelMeterValueDetail(Map<String, Object> param) throws Exception {
		Map<String, String> output = new HashMap<String, String>();
		MeterValue meterValue = new MeterValue();
		ConversionUtil.getModelByMap(meterValue, param);

		JSONArray channelL = (JSONArray)param.get("channelList");
		
		int defaultCol = 2;
		String[] header = new String[defaultCol+channelL.size()];
		header[0] = "????????????";
		header[1] = "?????? ??????";
		String cells = "read_dt,itime";
		
		
		for(int i=0; i< channelL.size() ; i++) {
			JSONObject json = (JSONObject)channelL.get(i);
			header[i+defaultCol] = (String)json.get("channel_name");
			cells += ",c"+(i+1)+"_metervalue";
		}
		
		String template_filepath = "/template/template_excel.xlsx";
		String filename = "meter_value_detail_" + DateUtil.getNowDateTime() + ".xlsx";			
		String filepath = fileDownloadDir + "/metervalue/" + DateUtil.GetYear() + "/" + DateUtil.GetMonth();
		
		List<Map<String, Object>> result = this.meterValueDAO.getMeterValueDetail(meterValue);
		
		ExcelRef excelRef = new ExcelRef();
		excelRef.setTitle("?????? ?????? ????????????");
		excelRef.setHeaders(header);
		excelRef.setCells(cells);
		
		ExcelUtil.makeExcelTemplate(template_filepath, filepath, filename, result, excelRef);
		
		output.put("filepath", filepath);
		output.put("filename", filename);
		
		return output;
	}
	
	

}
