package com.nuri.kepco.mongo.model.dao;

import java.util.List;

import com.nuri.kepco.mongo.model.CpuUsageMonitor;

public interface CpuUsageMonitorDAO {
	
	public void add(CpuUsageMonitor cpuUsageMonitor) throws Exception;
	
	public void add(List<CpuUsageMonitor> lists) throws Exception;
	
	public long getCount(CpuUsageMonitor param) throws Exception;
	
	public List<CpuUsageMonitor> getCpuUsageMonitor(CpuUsageMonitor param) throws Exception;
	
}
