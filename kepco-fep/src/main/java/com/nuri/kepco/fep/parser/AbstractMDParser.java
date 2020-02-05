package com.nuri.emi.fep.parser;

import com.nuri.emi.fep.datatype.MDData;

public abstract class AbstractMDParser {

	public abstract MDData parser(byte[] data) throws Exception;
	
}