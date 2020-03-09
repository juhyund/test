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

import com.nuri.kepco.model.MeterBilling;
import com.nuri.kepco.model.dao.MeterBillingDAO;
import com.nuri.kepco.service.MeterBillingService;
import com.nuri.kepco.util.ConversionUtil;
import com.nuri.kepco.util.DateUtil;
import com.nuri.kepco.util.ExcelUtil;


@Service
@Transactional
public class MeterBillingServiceImpl implements MeterBillingService {

	@Value("${file.download.dir:/files}")
	String fileDownloadDir;
	
	@Autowired
	MeterBillingDAO meterBillingDAO;


	@Override
	public int selectCount(Map<String, Object> param) throws Exception {
		MeterBilling meterBilling = new MeterBilling();
		ConversionUtil.getModelByMap(meterBilling, param);

		return this.meterBillingDAO.selectCount(meterBilling);
	}

	@Override
	public JSONArray selectList(Map<String, Object> param) throws Exception {
		MeterBilling meterBilling = new MeterBilling();
		ConversionUtil.getModelByMap(meterBilling, param);
		List<MeterBilling> list = this.meterBillingDAO.selectList(meterBilling);

		return ConversionUtil.getJSONArrayByModel(list,meterBilling.getStart());
	}
	
	@Override
	public JSONArray selectListDetail(Map<String, Object> param) throws Exception {
		MeterBilling meterBilling = new MeterBilling();
		ConversionUtil.getModelByMap(meterBilling, param);
		List<MeterBilling> list = this.meterBillingDAO.selectListDetail(meterBilling);

		return ConversionUtil.getJSONArrayByModel(list,meterBilling.getStart());
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
	public Map<String, String> excelMeterBilling(Map<String, Object> param) throws Exception {
		Map<String, String> output = new HashMap<String, String>();
		MeterBilling meterBilling = new MeterBilling();
		ConversionUtil.getModelByMap(meterBilling, param);
		
		
		String template_filepath = "/template/template_meter_billing.xlsx";
		String filename = "meter_billing_" + DateUtil.getNowDateTime() + ".xlsx";			
		String filepath = fileDownloadDir + "/meterBiling/" + DateUtil.GetYear() + "/" + DateUtil.GetMonth();

		List<MeterBilling> result = this.meterBillingDAO.selectList(meterBilling);
		
		ExcelUtil.makeExcelTemplate(template_filepath, filepath, filename, result);
		
		output.put("filepath", filepath);
		output.put("filename", filename);
		
		return output;
	}


}
