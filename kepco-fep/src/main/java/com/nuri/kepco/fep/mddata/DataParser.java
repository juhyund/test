package com.nuri.kepco.fep.mddata;

import com.nuri.kepco.fep.datatype.ResultMessage;

public abstract class DataParser {
	
	public abstract void parser(String data, String deviceId, String modemTime) throws Exception;
	
	public abstract void parser(ResultMessage data, String deviceId, String modemTime) throws Exception;
	
}