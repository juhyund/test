package com.nuri.kepco.model.dao;

import java.util.List;

public interface GenericDAO<T> {

	int selectCount(T param) throws Exception;
	
	List<T> selectList(T param) throws Exception;
	
	T selectOne(T param) throws Exception;

	int insert(T param) throws Exception;

	int update(T param) throws Exception;
}