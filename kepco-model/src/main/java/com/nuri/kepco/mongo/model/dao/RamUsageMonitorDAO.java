package com.nuri.kepco.mongo.model.dao;

import java.util.List;

import com.nuri.kepco.mongo.model.RamUsageMonitor;

public interface RamUsageMonitorDAO {
	
	public void add(RamUsageMonitor ramUsageMonitor) throws Exception;
	
	public void add(List<RamUsageMonitor> lists) throws Exception;
	
	public long getCount(RamUsageMonitor param) throws Exception;
	
	public List<RamUsageMonitor> getRamUsageMonitor(RamUsageMonitor param) throws Exception;	
}
