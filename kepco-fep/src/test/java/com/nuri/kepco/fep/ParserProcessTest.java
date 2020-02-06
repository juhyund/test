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
		
		String json = "{\"deviceId\":\"LG-PC02\",\"method\":\"DATAPUSH\",\"format\":\"JSON\",\"token\":\"806662840758920E\",\"mid\":\"18966\",\"payload\":\"{\\\"bn\\\":\\\"/31008/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"101\\\",\\\"sv\\\":\\\"MTIzNDU2NzgxNA\\u003d\\u003d\\\"},{\\\"n\\\":\\\"102/0\\\",\\\"sv\\\":\\\"MjUxOTAwODQ3MzUgARcFFAZQAQA\\u003d\\\"},{\\\"n\\\":\\\"103/0\\\",\\\"sv\\\":\\\"AQBjAQD/AAcCAD0CCgYAAKWdBgAAAAAGAAC9tAYAAZGvCQwH4wwBBwMeAP+AAAEEGBwABAYAAAAABgAAAAAGAAAAAAYAAAAA\\\"}]}\"}";
		process.process(json);

		System.out.println("test");
		
    }
	
}
