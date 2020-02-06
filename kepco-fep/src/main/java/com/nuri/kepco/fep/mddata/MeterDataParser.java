package com.nuri.kepco.fep.mddata;

import java.util.List;

import com.nuri.kepco.fep.datatype.MDData;
import com.nuri.kepco.model.DeviceInfo;
import com.nuri.kepco.model.MeterInfo;

public abstract class MeterDataParser {
	
	public abstract void parser(String data) throws Exception;
	
}