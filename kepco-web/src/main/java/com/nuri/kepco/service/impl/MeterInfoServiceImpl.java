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

import com.nuri.kepco.model.MeterInfo;
import com.nuri.kepco.model.dao.MeterInfoDAO;
import com.nuri.kepco.service.MeterInfoService;
import com.nuri.kepco.util.ConversionUtil;
import com.nuri.kepco.util.DateUtil;
import com.nuri.kepco.util.ExcelRef;
import com.nuri.kepco.util.ExcelUtil;

@Service
@Transactional
public class MeterInfoServiceImpl implements MeterInfoService {

	@Autowired
	MeterInfoDAO meterInfoDAO;
	
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
	public JSONArray getMeterList(Map<String, Object> param) throws Exception {
		MeterInfo meterInfo = new MeterInfo();
		ConversionUtil.getModelByMap(meterInfo, param);
		List<MeterInfo> list = this.meterInfoDAO.getMeterList(meterInfo);

		return ConversionUtil.getJSONArrayByModel(list,meterInfo.getStart());
	}

	@Override
	public int getMeterListCnt(Map<String, Object> param) throws Exception {
		MeterInfo meterInfo = new MeterInfo();
		ConversionUtil.getModelByMap(meterInfo, param);

		return this.meterInfoDAO.getMeterListCnt(meterInfo);
	}

	@Override
	public JSONObject getMeterDetailInfo(String meter_serial) throws Exception {
		MeterInfo meterInfo = meterInfoDAO.getMeterDetailInfo(meter_serial);
		return ConversionUtil.getJSONObjectByModel(meterInfo);
	}

	@Override
	public JSONArray getLpRate() throws Exception {
		MeterInfo meterInfo = new MeterInfo();
		List<MeterInfo> list = meterInfoDAO.getLpRate();
		
		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public Map<String, String> excelMeterList(Map<String, Object> param) throws Exception {
		Map<String, String> output = new HashMap<String, String>();
		MeterInfo meterInfo = new MeterInfo();
		ConversionUtil.getModelByMap(meterInfo, param);		
		
		String template_filepath = "/template/template_excel.xlsx";
		String filename = "meter_list_" + DateUtil.getNowDateTime() + ".xlsx";			
		String filepath = fileDownloadDir + "/meterList/" + DateUtil.GetYear() + "/" + DateUtil.GetMonth();

		List<MeterInfo> result = this.meterInfoDAO.getMeterList(meterInfo);
		
		
		ExcelRef excelRef = new ExcelRef();
		excelRef.setTitle("계기목록 다운로드");
		excelRef.setHeaders(new String[] {"본부", "지사", "계기타입", "계기번호", "검침주기", "통신상태","제조사", "마지막 검침 일시", "모뎀번호", "모뎀 최종통신일자", "인가여부"});
		excelRef.setCells("parent_branch_nm,branch_nm,meter_type,meter_serial,lp_period,device_status,vendor_nm,last_comm_dt,device_serial,last_comm_dt,allow_yn");
		
		ExcelUtil.makeExcelTemplate(template_filepath, filepath, filename, result, excelRef);
		
		output.put("filepath", filepath);
		output.put("filename", filename);
		
	return output;
		}
}
