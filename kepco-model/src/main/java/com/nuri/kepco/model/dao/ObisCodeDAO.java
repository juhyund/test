package com.nuri.kepco.model.dao;

import java.util.List;
import java.util.Map;
import org.apache.ibatis.annotations.Mapper;
import com.nuri.kepco.model.AllCode;
import com.nuri.kepco.model.ObisCode;

@Mapper
public interface ObisCodeDAO extends GenericDAO<ObisCode> {

	List<Map<String, Object>> selectObisList(ObisCode obisCode);

	List<Map<String, Object>> selectObisList2(ObisCode obisCode);
	
	ObisCode selectObisByCode(ObisCode obisCode);
}
