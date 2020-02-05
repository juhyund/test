package com.nuri.kepco.fep.parser;

import com.nuri.kepco.fep.datatype.MDData;

public abstract class AbstractMDParser {

	public abstract MDData parser(byte[] data) throws Exception;
	
}