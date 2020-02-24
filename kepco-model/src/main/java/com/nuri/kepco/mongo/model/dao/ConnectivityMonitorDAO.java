package com.nuri.kepco.mongo.model.dao;

import java.util.List;

import com.nuri.kepco.mongo.model.ConnectivityMonitor;

public interface ConnectivityMonitorDAO {
	
	public void add(ConnectivityMonitor connectivityMonitor) throws Exception;
	
	public void add(List<ConnectivityMonitor> lists) throws Exception;
	
	public long getCount(ConnectivityMonitor param) throws Exception;
	
	public List<ConnectivityMonitor> getConnectivityMonitor(ConnectivityMonitor param) throws Exception;
	
}
