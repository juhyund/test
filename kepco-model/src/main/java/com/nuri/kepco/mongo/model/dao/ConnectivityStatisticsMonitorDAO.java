package com.nuri.kepco.mongo.model.dao;

import java.util.List;

import com.nuri.kepco.mongo.model.ConnectivityMonitor;
import com.nuri.kepco.mongo.model.ConnectivityStatisticsMonitor;

public interface ConnectivityStatisticsMonitorDAO {
	
	public void add(ConnectivityStatisticsMonitor connectivityStatisticsMonitor) throws Exception;
	
	public void save(ConnectivityStatisticsMonitor connectivityStatisticsMonitor) throws Exception;
	
	public void add(List<ConnectivityStatisticsMonitor> lists) throws Exception;
	
	public long getCount(ConnectivityStatisticsMonitor param) throws Exception;
	
	public List<ConnectivityStatisticsMonitor> getConnectivityStatisticsMonitor(ConnectivityStatisticsMonitor param) throws Exception;	
}
