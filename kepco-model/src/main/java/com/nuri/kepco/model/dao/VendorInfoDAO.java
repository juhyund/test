package com.nuri.kepco.model.dao;

import org.apache.ibatis.annotations.Mapper;

import com.nuri.kepco.model.VendorInfo;

@Mapper
public interface VendorInfoDAO extends GenericDAO<VendorInfo> {
	
	VendorInfo selectVendorByName(String vendor_nm) throws Exception;
	
	VendorInfo selectVendorByCode(String vendor_code) throws Exception;
}
