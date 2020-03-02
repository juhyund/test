package com.nuri.kepco.model.dao;

import java.util.List;

import org.apache.ibatis.annotations.Mapper;

import com.nuri.kepco.model.DeviceResource;

@Mapper
public interface DeviceResourceDAO extends GenericDAO<DeviceResource> {

	int insertAll(List<DeviceResource> param);

	int delete(DeviceResource param);
	
	List<DeviceResource> getResourceModelList(DeviceResource param);
	
	List<DeviceResource> getMeterResourceList(DeviceResource param);
}

