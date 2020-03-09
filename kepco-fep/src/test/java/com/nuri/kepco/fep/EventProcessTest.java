package com.nuri.kepco.fep;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import com.nuri.kepco.fep.process.LwM2mEventLogProcess;
import com.nuri.kepco.fep.process.MDDataProcess;

@RunWith(SpringRunner.class)
@SpringBootTest
public class EventProcessTest {
	
	@Autowired
	LwM2mEventLogProcess process;

	@Test
    public void test() {
		
//		      String json = "{\"deviceId\":\"LeshanClientDemo\",\"method\":\"DATAPUSH\",\"format\":\"JSON\",\"token\":\"C459567D93A97621\",\"mid\":\"14748\",\"payload\":\"{\\\"bn\\\":\\\"/31008/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"101\\\",\\\"sv\\\":\\\"MTIzNDU2Nzgx\\\"},{\\\"n\\\":\\\"102/0\\\",\\\"sv\\\":\\\"MjQxNDAwMDA5MDQUAhoDCBM5AQA=\\\"},{\\\"n\\\":\\\"103/0\\\",\\\"sv\\\":\\\"AAABAAD/AAgCAA4JDAfkAhoDERgv//3kAAAAAQAA/wAIAgAOCQwH5AIaAxEYMP/95AAAAGIBAf8ABwIAQAYAAMXMBgAAAAAJBD+AAAAGAADFzAYAAAAACQQ/gAAABgAAAAAGAAAAAAkEAAAAAAYAAAAABgAAAAAJBAAAAAA=\\\"}]}\"}";
		String json = "{\"ep\":\"01220885233\",\"ip\":\"/42.29.60.183\",\"port\":\"33682\",\"lastUpdate\":\"Mon Mar 09 10:44:08 KST 2020\",\"registrationDate\":\"Mon Mar 09 10:44:08 KST 2020\",\"method\":\"REGISTRATION\",\"date\":\"20200309104408\",\"payload\":\"{\\\"endpoint\\\":\\\"01220885233\\\",\\\"registrationId\\\":\\\"01220885233\\\",\\\"registrationDate\\\":\\\"2020-03-09T10:44:08+09:00\\\",\\\"lastUpdate\\\":\\\"2020-03-09T10:44:08+09:00\\\",\\\"address\\\":\\\"42.29.60.183:33682\\\",\\\"lwM2mVersion\\\":\\\"1.0\\\",\\\"lifetime\\\":30,\\\"bindingMode\\\":\\\"U\\\",\\\"lepMode\\\":false,\\\"rootPath\\\":\\\"/\\\",\\\"objectLinks\\\":[{\\\"url\\\":\\\"/\\\",\\\"attributes\\\":{\\\"rt\\\":\\\"oma.lwm2m\\\"}},{\\\"url\\\":\\\"/1/0\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/3/0\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/4/0\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/5/0\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/6/0\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/3303/0\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/26241/0\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/26243/0\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/26245/0\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/26247/0\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31004/0\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31008/0\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/10\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/11\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/12\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/13\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/14\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/15\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/30\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/31\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/32\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/33\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/34\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/50\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/51\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/52\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/53\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/54\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/55\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/56\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/57\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/58\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/59\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/60\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/61\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/62\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/63\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/64\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/65\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/66\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/67\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/68\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/69\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/70\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/71\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/72\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/80\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/81\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/82\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/83\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/84\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/85\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/86\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/87\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/88\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/89\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/90\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/91\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/92\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/93\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/94\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/95\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/96\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/97\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/98\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/99\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/100\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31011/101\\\",\\\"attributes\\\":{}},{\\\"url\\\":\\\"/31012/0\\\",\\\"attributes\\\":{}}],\\\"secure\\\":false,\\\"additionalRegistrationAttributes\\\":{}}\"}";
		
		process.process(json);
		
		System.out.println("test");		
    }
	
}
