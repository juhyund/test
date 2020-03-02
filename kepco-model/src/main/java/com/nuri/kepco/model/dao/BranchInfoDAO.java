package com.nuri.kepco.model.dao;

import java.util.List;

import org.apache.ibatis.annotations.Mapper;

import com.nuri.kepco.model.BranchInfo;

@Mapper
public interface BranchInfoDAO extends GenericDAO<BranchInfo> {
	List<BranchInfo> selectParent();
}
