package com.nuri.kepco.mongo.model.dao;

import java.util.List;

import com.nuri.kepco.mongo.model.LwM2mEventLog;

public interface LwM2mEventLogDAO {
	
	public void add(LwM2mEventLog lwM2mEventLog) throws Exception;
	
	public void add(List<LwM2mEventLog> lists) throws Exception;
	
	public long getCount(LwM2mEventLog param) throws Exception;
}
