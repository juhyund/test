package com.nuri.kepco.model.dao;

import org.apache.ibatis.annotations.Mapper;

import com.nuri.kepco.model.DeviceModel;

@Mapper
public interface DeviceModelDAO extends GenericDAO<DeviceModel> {
	
	DeviceModel selectModelByName(String model_nm) throws Exception;
	
	DeviceModel selectModelByVendorCode(String vendor_seq) throws Exception;

}
