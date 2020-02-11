package com.nuri.kepco.fep;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import com.nuri.kepco.fep.process.MDDataProcess;

@RunWith(SpringRunner.class)
@SpringBootTest
public class ParserProcessTest {
	
	@Autowired
	MDDataProcess process;

	@Test
    public void test() {
		
//		String json = "{\"deviceId\":\"LG-PC02\",\"method\":\"DATAPUSH\",\"format\":\"JSON\",\"token\":\"806662840758920E\",\"mid\":\"18966\",\"payload\":\"{\\\"bn\\\":\\\"/31008/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"101\\\",\\\"sv\\\":\\\"MTIzNDU2NzgxNA\\u003d\\u003d\\\"},{\\\"n\\\":\\\"102/0\\\",\\\"sv\\\":\\\"MjUxOTAwODQ3MzUgARcFFAZQAQA\\u003d\\\"},{\\\"n\\\":\\\"103/0\\\",\\\"sv\\\":\\\"AQBjAQD/AAcCAD0CCgYAAKWdBgAAAAAGAAC9tAYAAZGvCQwH4wwBBwMeAP+AAAEEGBwABAYAAAAABgAAAAAGAAAAAAYAAAAA\\\"}]}\"}";

		// METER ENTERY
//		String json = "{\"deviceId\":\"LeshanClientDemo\",\"method\":\"DATAPUSH\",\"format\":\"JSON\",\"token\":\"E842FACFB5CC83D9\",\"mid\":\"44648\",\"payload\":\"{\\\"bn\\\":\\\"/31008/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"101\\\",\\\"sv\\\":\\\"MTIzNDU2Nzgx\\\"},{\\\"n\\\":\\\"102/0\\\",\\\"sv\\\":\\\"MjQxNzEwMTQ0OTYgARcFFAZQBQA\\u003d\\\"},{\\\"n\\\":\\\"103/0\\\",\\\"sv\\\":\\\"AAABAAD/AAgCAA4JDAfkAgcFAgEb/4AAAAAAKgAA/wABAgASCRBETVAgMTcxMTEzQSAgIDExAQEACAT/AAMCAAIRDwAADwAA/wAWBAARAQECAgkEAAAA/wkF////E/8BAQADAP8AAwIABRdEegAA\\\"}]}\"}\n";
		
		// LP SAMPLE
//		String json = "{\"deviceId\":\"LeshanClientDemo\",\"method\":\"DATAPUSH\",\"format\":\"JSON\",\"token\":\"24724587C932D1A9\",\"mid\":\"20123\",\"payload\":\"{\\\"bn\\\":\\\"/31008/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"101\\\",\\\"sv\\\":\\\"MTIzNDU2Nzgx\\\"},{\\\"n\\\":\\\"102/0\\\",\\\"sv\\\":\\\"MjQxOTAyMDQyNjEgARcFFAZQAQA\\u003d\\\"},{\\\"n\\\":\\\"103/0\\\",\\\"sv\\\":\\\"AQBjAQD/AAcCADsGAAAAIgYAAAACBgAAAAAGAAAAKAkMB+QCBwUGMAAAgAAABBgMAAAGAAAAAAYAAAAABgAAAAAGAAAAAA\\u003d\\u003d\\\"}]}\"}";
		
		// 
		String json = "{\"deviceId\":\"LeshanClientDemo\",\"method\":\"DATAPUSH\",\"format\":\"JSON\",\"token\":\"C459567D93A97621\",\"mid\":\"14748\",\"payload\":\"{\\\"bn\\\":\\\"/31008/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"101\\\",\\\"sv\\\":\\\"MTIzNDU2Nzgx\\\"},{\\\"n\\\":\\\"102/0\\\",\\\"sv\\\":\\\"MjQyNTAwNzkzNDggARcFFAZQAAA\\u003d\\\"},{\\\"n\\\":\\\"103/0\\\",\\\"sv\\\":\\\"AAABAAD/AAgCAA4JDAfkAgcFBwQBRYAAAAAAYgEDKQAHAgB9BgAAAAAGAAAAAAYAAAAABgAAAAAXv4AAAAYAAAAABgAAAAAGAAAAAAYAAAAAF7+AAAAGAAAAAAYAAAAABgAAAAAGAAAAABe/gAAABgAAAAAGAAAAAAYAAAAABgAAAAAXv4AAAAYAAAAABgAAAAAGAAAAAAYAAAAAF7+AAAA\\u003d\\\"}]}\"}";
		
		process.process(json);

		System.out.println("test");		
    }
	
}
