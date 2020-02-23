package com.nuri.kepco.fep.mddata;

public abstract class DataParser {
	
	public abstract void parser(String data, String deviceId, String modemTime) throws Exception;
	
}