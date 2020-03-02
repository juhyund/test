package com.nuri.kepco.model.dao;

import org.apache.ibatis.annotations.Mapper;

import com.nuri.kepco.model.MeterBilling;

@Mapper
public interface MeterBillingDAO extends GenericDAO<MeterBilling> {

	int insertImport(MeterBilling param) throws Exception;
	
	int insertExport(MeterBilling param) throws Exception;
	
}