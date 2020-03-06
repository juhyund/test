package com.nuri.kepco.model.dao;

import java.util.List;

import org.apache.ibatis.annotations.Mapper;

import com.nuri.kepco.model.MeterBilling;

@Mapper
public interface MeterBillingDAO extends GenericDAO<MeterBilling> {

	int insertImport(MeterBilling param) throws Exception;
	
	int insertExport(MeterBilling param) throws Exception;
	
	List<MeterBilling> selectListDetail(MeterBilling param) throws Exception;
	
}