package com.nuri.kepco.service.impl;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.nuri.kepco.util.ConversionUtil;
import com.nuri.kepco.model.AllCode;
import com.nuri.kepco.model.dao.AllCodeDAO;
import com.nuri.kepco.service.AllCodeService;

@Service
@Transactional
public class AllCodeServiceImpl implements AllCodeService {

	@Value("${file.download.dir:/files}")
	String fileDownloadDir;
	
	@Autowired
	AllCodeDAO allCodeDAO;

	@Override
	public int selectCount(Map<String, Object> param) throws Exception {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public JSONArray selectList(Map<String, Object> param) throws Exception {
		//
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
	public List<Map<String, Object>> selectCombo(Map<String, Object> param) throws Exception {
		AllCode allCode = new AllCode();
		ConversionUtil.getModelByMap(allCode, param);
		List<Map<String, Object>> list = this.allCodeDAO.selectCombo(allCode);

		return ConversionUtil.getJSONArrayByModel(list, allCode.getStart());
	}


}
