package com.nuri.kepco.service.impl;

import java.util.List;
import java.util.Map;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.nuri.kepco.model.ObjectModel;
import com.nuri.kepco.model.dao.ObjectModelDAO;
import com.nuri.kepco.service.ObjectModelService;
import com.nuri.kepco.util.ConversionUtil;

@Service
@Transactional
public class ObjectModelServiceImpl implements ObjectModelService {

	@Autowired
	ObjectModelDAO objectModelDAO;

	@Override
	public JSONObject selectOne(Map<String, Object> param) throws Exception {
		ObjectModel objectModel = new ObjectModel();
		ConversionUtil.getModelByMap(objectModel, param);
		objectModel = this.objectModelDAO.selectOne(objectModel);

		return ConversionUtil.getJSONObjectByModel(objectModel);
	}

	@Override
	public JSONArray selectList(Map<String, Object> param) throws Exception {
		ObjectModel objectModel = new ObjectModel();
		ConversionUtil.getModelByMap(objectModel, param);
		List<ObjectModel> list = this.objectModelDAO.selectList(objectModel);
		
		return ConversionUtil.getJSONArrayByModel(list);
	}

	@Override
	public int selectCount(Map<String, Object> param) throws Exception {
		ObjectModel objectModel = new ObjectModel();
		ConversionUtil.getModelByMap(objectModel, param);

		return this.objectModelDAO.selectCount(objectModel);
	}

	@Override
	public int insert(Map<String, Object> param) throws Exception {
		ObjectModel objectModel = new ObjectModel();
		ConversionUtil.getModelByMap(objectModel, param);

		return this.objectModelDAO.insert(objectModel);
	}

	@Override
	public int update(Map<String, Object> param) throws Exception {
		ObjectModel objectModel = new ObjectModel();
		ConversionUtil.getModelByMap(objectModel, param);

		return this.objectModelDAO.update(objectModel);
	}

	@Override
	public JSONArray selectObjectList(Map<String, Object> param) throws Exception {
		ObjectModel objectModel = new ObjectModel();
		ConversionUtil.getModelByMap(objectModel, param);
		List<ObjectModel> list = this.objectModelDAO.selectObjectList(objectModel);
		
		return ConversionUtil.getJSONArrayByModel(list);
	}

}
