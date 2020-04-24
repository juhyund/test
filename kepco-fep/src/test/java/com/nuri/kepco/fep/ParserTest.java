package com.nuri.kepco.fep;

import java.util.Base64;
import java.util.HashMap;
import java.util.Map;

import org.eclipse.leshan.core.node.LwM2mPath;
import org.eclipse.leshan.json.JsonArrayEntry;
import org.eclipse.leshan.json.JsonRootObject;
import org.eclipse.leshan.json.LwM2mJson;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import com.google.gson.Gson;
import com.nuri.kepco.fep.datatype.ResultMessage;
import com.nuri.kepco.fep.process.MDDataProcess;

@RunWith(SpringRunner.class)
@SpringBootTest
public class ParserTest {
	
	@Autowired
	MDDataProcess process;
	
	@Test
    public void test() {		
		//String json = "{\"deviceId\":\"01220884726\",\"method\":\"DATAPUSH\",\"format\":\"JSON\",\"token\":\"806662840758920E\",\"mid\":\"18966\",\"payload\":\"{\\\"bn\\\":\\\"/31008/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"101\\\",\\\"sv\\\":\\\"MjA4ODQ3MjYgMg==\\\"},{\\\"n\\\":\\\"102/0\\\",\\\"sv\\\":\\\"MjQxOTAxODc1NDcUBBcEFCgnAQA=\\\"},{\\\"n\\\":\\\"102/1\\\",\\\"sv\\\":\\\"MDI1MjAwMDAwMDMUBBcEFCgkAQA=\\\"},{\\\"n\\\":\\\"103/0\\\",\\\"sv\\\":\\\"AAANAAD/ABQCAAoJCDMwNFNSU0tF\\\"},{\\\"n\\\":\\\"103/1\\\",\\\"sv\\\":\\\"AAANAAD/ABQCAAoJCDIwMVJSVTAw\\\"}]}\"}";
		
		
		String json = "{\"deviceId\":\"01220884726\",\"method\":\"DATAPUSH\",\"format\":\"JSON\",\"token\":\"806662840758920E\",\"mid\":\"18966\",\"payload\":\"{\\\"bn\\\":\\\"/31008/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"101\\\",\\\"sv\\\":\\\"MjA4ODQ3MjYgMg==\\\"},{\\\"n\\\":\\\"102/0\\\",\\\"sv\\\":\\\"MjQxOTAxODc1NDcUBBcEFCkKAQA=\\\"},{\\\"n\\\":\\\"102/1\\\",\\\"sv\\\":\\\"MDI1MjAwMDAwMDMUBBcEFCkIAQA=\\\"},{\\\"n\\\":\\\"103/0\\\",\\\"sv\\\":\\\"AQEACAT/AAMCAAIRDw==\\\"},{\\\"n\\\":\\\"103/1\\\",\\\"sv\\\":\\\"AQEACAT/AAMCAAIRDw==\\\"}]}\"}";
		process.process(json);
    }
	
}
