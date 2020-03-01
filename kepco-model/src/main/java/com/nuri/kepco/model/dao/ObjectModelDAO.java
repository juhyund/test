package com.nuri.kepco.model.dao;

import java.util.List;

import org.apache.ibatis.annotations.Mapper;

import com.nuri.kepco.model.ObjectModel;

@Mapper
public interface ObjectModelDAO extends GenericDAO<ObjectModel> {
	List<ObjectModel> selectObjectList(ObjectModel param) throws Exception;
}
