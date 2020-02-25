package com.nuri.kepco.model.dao;

import java.util.List;
import java.util.Map;
import org.apache.ibatis.annotations.Mapper;
import com.nuri.kepco.model.AllCode;

@Mapper
public interface AllCodeDAO extends GenericDAO<AllCode> {

	List<Map<String, Object>> selectCombo(AllCode param) throws Exception;

}
