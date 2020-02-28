package com.nuri.kepco.mongo.model.dao;

import java.util.List;

import com.nuri.kepco.mongo.model.CmdResultData;

public interface CmdResultDataDAO {
	
	public void add(CmdResultData cmdResultData) throws Exception;
	
	public void add(List<CmdResultData> lists) throws Exception;
	
	public long getCount(CmdResultData param) throws Exception;
	
	public List<CmdResultData> getCmdResultData(CmdResultData param) throws Exception;	
}
