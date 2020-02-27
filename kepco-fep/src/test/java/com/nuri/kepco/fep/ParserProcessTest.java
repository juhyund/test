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
//		String json = "{\"deviceId\":\"LeshanClientDemo\",\"method\":\"DATAPUSH\",\"format\":\"JSON\",\"token\":\"24724587C932D1A9\",\"mid\":\"20123\",\"payload\":\"{\\\"bn\\\":\\\"/31008/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"101\\\",\\\"sv\\\":\\\"MTIzNDU2Nzgx\\\"},{\\\"n\\\":\\\"102/0\\\",\\\"sv\\\":\\\"MjYyNTAwMDgyNzgH5AIXBxAuAQA=\\\"},{\\\"n\\\":\\\"103/0\\\",\\\"sv\\\":\\\"AQBjAQD/AAcCACcGAAAAAAYAAAAABgAAAAAGAAAAAAkMB+QCFwcQLQD//lyzBBgcAAQ=\\\"}]}\"}";
		
		// 
//		String json = "{\"deviceId\":\"LeshanClientDemo\",\"method\":\"DATAPUSH\",\"format\":\"JSON\",\"token\":\"C459567D93A97621\",\"mid\":\"14748\",\"payload\":\"{\\\"bn\\\":\\\"/31008/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"101\\\",\\\"sv\\\":\\\"MTIzNDU2Nzgx\\\"},{\\\"n\\\":\\\"102/0\\\",\\\"sv\\\":\\\"MjQyNTAwNzkzNDgH5AIWBgACAQA=\\\"},{\\\"n\\\":\\\"103/0\\\",\\\"sv\\\":\\\"AAABAAD/AAgCAA4JDAfkAhYGAAIqUoAAAAEAAAECLQABAgAOCQwH5AIUBAYFHv+AAAAAAGIBAy0ABwIAfQYAAAAABgAAAAAGAAAAAAYAAAAAF7+AAAAGAAAAAAYAAAAABgAAAAAGAAAAABe/gAAABgAAAAAGAAAAAAYAAAAABgAAAAAXv4AAAAYAAAAABgAAAAAGAAAAAAYAAAAAF7+AAAAGAAAAAAYAAAAABgAAAAAGAAAAABe/gAAA\\\"}]}\"}";
		
		
//		String json = "{\"deviceId\":\"StypeTest\",\"method\":\"DATAPUSH\",\"format\":\"JSON\",\"token\":\"C459567D93A97621\",\"mid\":\"14748\",\"payload\":\"{\\\"bn\\\":\\\"/31008/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"101\\\",\\\"sv\\\":\\\"MTIzNDU2Nzgx\\\"},{\\\"n\\\":\\\"102/0\\\",\\\"sv\\\":\\\"MDkzNDAwMDI3MDYUAhkCERENAQA=\\\"},{\\\"n\\\":\\\"103/0\\\",\\\"sv\\\":\\\"AQBjAQD/AAcCAB0SAAASAAASAAASAAAJDAfkAhn/EQ8A/4AAAAQBAg==\\\"}]}\"}";
		
		// etype 정기검침
//		String json = "{\"deviceId\":\"Aging1\",\"method\":\"DATAPUSH\",\"format\":\"JSON\",\"token\":\"C459567D93A97621\",\"mid\":\"14748\",\"payload\":\"{\\\"bn\\\":\\\"/31008/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"101\\\",\\\"sv\\\":\\\"MjAwMTQ4MDcgMQ==\\\"},{\\\"n\\\":\\\"102/0\\\",\\\"sv\\\":\\\"MjYxNzA3MTEwNzUUAhoDDwEfAQA=\\\"},{\\\"n\\\":\\\"103/0\\\",\\\"sv\\\":\\\"AAABAAD/AAgCAA4JDAfkAhoDDwEe/4AAAAEBAQgAAQAEBQAOCQwH0AEPBgAAAP8CHAIBAQEIAAEABAIABQYABTeV\\\"}]}\"}";
		
		// 24140000904
//		String json = "{\"deviceId\":\"24140000904\",\"method\":\"DATAPUSH\",\"format\":\"JSON\",\"token\":\"C459567D93A97621\",\"mid\":\"14748\",\"payload\":\"{\\\"bn\\\":\\\"/31008/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"101\\\",\\\"sv\\\":\\\"MTIzNDU2Nzgx\\\"},{\\\"n\\\":\\\"102/0\\\",\\\"sv\\\":\\\"MjQxNDAwMDA5MDQUAhoDABg2BAA=\\\"},{\\\"n\\\":\\\"103/0\\\",\\\"sv\\\":\\\"AAABAAD/AAgCAA4JDAfkAhoDCR0q//3kAAAAKgAA/wABAgASCRBETVAtMTEwN3h4QSAgICAgAQEACAT/AAMCAAIRDwAADwAA/wAWBAARAQECAgkEAAAA/wkF////Af8BAQADAP8AAwIABgkERPoAAAEBAAMB/wADAgAGCQRE+gAA\\\"}]}\"}";
		
		
		// 24140000904
//		String json = "{\"deviceId\":\"LeshanClientDemo\",\"method\":\"DATAPUSH\",\"format\":\"JSON\",\"token\":\"C459567D93A97621\",\"mid\":\"14748\",\"payload\":\"{\\\"bn\\\":\\\"/31008/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"101\\\",\\\"sv\\\":\\\"MTIzNDU2Nzgx\\\"},{\\\"n\\\":\\\"102/0\\\",\\\"sv\\\":\\\"MjQxNDAwMDA5MDQUAhoDCBM5AQA=\\\"},{\\\"n\\\":\\\"103/0\\\",\\\"sv\\\":\\\"AAABAAD/AAgCAA4JDAfkAhoDERgv//3kAAAAAQAA/wAIAgAOCQwH5AIaAxEYMP/95AAAAGIBAf8ABwIAQAYAAMXMBgAAAAAJBD+AAAAGAADFzAYAAAAACQQ/gAAABgAAAAAGAAAAAAkEAAAAAAYAAAAABgAAAAAJBAAAAAA=\\\"}]}\"}";
		
		// 양방향
//		String json = "{\"deviceId\":\"LeshanClientDemo\",\"method\":\"DATAPUSH\",\"format\":\"JSON\",\"token\":\"C459567D93A97621\",\"mid\":\"14748\",\"payload\":\"{\\\"bn\\\":\\\"/31008/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"101\\\",\\\"sv\\\":\\\"MjA4ODM3NTYgMQ==\\\"},{\\\"n\\\":\\\"102/0\\\",\\\"sv\\\":\\\"MDgxOTAwMDAwNTMUAhsEDioVCQA=\\\"},{\\\"n\\\":\\\"103/0\\\",\\\"sv\\\":\\\"AAABAAD/AAgCAA4JDAfkAhsEDioR//3kAAAAKgAA/wABAgASCRBOSkMgMTYwNjAyQSAgIDIxAQEACAT/AAMCAAIRDwAADwAA/wAWBAARAQECAgkEAAAA/wkF////Af8BAQADAP8AAwIABRdEegAAAQAA8gD/AAECAAoJCBMDAAEAAAcIAQCAAAz/AAMCAAIRDwEBAAMB/wADAgAFF0R6AAABAQADAv8AAwIABRdEegAA\\\"}]}\"}";
		
		
		String json = "{\"deviceId\":\"LeshanClientDemo\",\"method\":\"DATAPUSH\",\"format\":\"JSON\",\"token\":\"C459567D93A97621\",\"mid\":\"14748\",\"payload\":\"{\\\"bn\\\":\\\"/31008/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"101\\\",\\\"sv\\\":\\\"MjA4ODM3NTYgMQ==\\\"},{\\\"n\\\":\\\"102/0\\\",\\\"sv\\\":\\\"MDgxOTAwMDAwNTMUAhsEDw4zAQA=\\\"},{\\\"n\\\":\\\"103/0\\\",\\\"sv\\\":\\\"AAABAAD/AAgCAA4JDAfkAhsEDw4v//3kAAEAAAECDwABAgAOCQwH5AIUBAYFMf/95AAAAGIBAQ8ABwIAfQYAAAplBgAAGz0GAAAAAAYAABksFz+AAAAGAAAKZQYAABs9BgAAAAAGAAAZLBc/gAAABgAAAAAGAAAAAAYAAAAABgAAAAAXv4AAAAYAAAAABgAAAAAGAAAAAAYAAAAAF7+AAAAGAAAAAAYAAAAABgAAAAAGAAAAABe/gAAA\\\"}]}\"}";
		
		process.process(json);

		System.out.println("test");		
    }
	
}
