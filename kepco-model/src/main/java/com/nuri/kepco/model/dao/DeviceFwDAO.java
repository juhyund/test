package com.nuri.kepco.model.dao;

import org.apache.ibatis.annotations.Mapper;

import com.nuri.kepco.model.DeviceFw;
import com.nuri.kepco.model.DeviceInfo;

@Mapper
public interface DeviceFwDAO extends GenericDAO<DeviceFw> {
	
	DeviceFw selectOneByPackageUri(String fw_pkg_uri) throws Exception;

}
