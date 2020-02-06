package com.nuri.emi.fep;

import java.util.Base64;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.eclipse.leshan.core.model.LwM2mModel;
import org.eclipse.leshan.core.node.LwM2mNode;
import org.eclipse.leshan.core.node.LwM2mPath;
import org.eclipse.leshan.core.node.codec.DefaultLwM2mNodeDecoder;
import org.eclipse.leshan.core.node.codec.LwM2mNodeDecoder;
import org.eclipse.leshan.core.request.ContentFormat;
import org.eclipse.leshan.json.JsonArrayEntry;
import org.eclipse.leshan.json.JsonRootObject;
import org.eclipse.leshan.json.LwM2mJson;
import org.eclipse.leshan.json.LwM2mJsonException;
import org.eclipse.leshan.util.Hex;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import com.google.gson.Gson;
import com.nuri.emi.redis.model.RedisModelProvider;
import com.nuri.kepco.fep.datatype.ResultMessage;
import com.nuri.kepco.fep.parser.MDDataParser;

@RunWith(SpringRunner.class)
@SpringBootTest
public class ParserTest {
	
	@Autowired
	RedisModelProvider redisModelProvider;

	@Test
    public void test() {
		String json = "{\"deviceId\":\"LG-PC02\",\"method\":\"DATAPUSH\",\"format\":\"JSON\",\"token\":\"806662840758920E\",\"mid\":\"18966\",\"payload\":\"{\\\"bn\\\":\\\"/31008/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"101\\\",\\\"sv\\\":\\\"MTIzNDU2NzgxNA\\u003d\\u003d\\\"},{\\\"n\\\":\\\"102/0\\\",\\\"sv\\\":\\\"MjUxOTAwODQ3MzUgARcFFAZQAQA\\u003d\\\"},{\\\"n\\\":\\\"103/0\\\",\\\"sv\\\":\\\"AQBjAQD/AAcCAD0CCgYAAKWdBgAAAAAGAAC9tAYAAZGvCQwH4wwBBwMeAP+AAAEEGBwABAYAAAAABgAAAAAGAAAAAAYAAAAA\\\"}]}\"}";
		
		Gson gson = new Gson();
		
		ResultMessage resultMessage = new ResultMessage();
		resultMessage = gson.fromJson(json, ResultMessage.class);
		
		String payload = resultMessage.getPayload();
		String format = resultMessage.getFormat();
		String method = resultMessage.getMethod();
		
	   	Map<Integer, byte[]> meterInfo = new HashMap<Integer, byte[]>();
	   	Map<Integer, byte[]> meterData = new HashMap<Integer, byte[]>();
		
		try {
		
			JsonRootObject jsonObject = LwM2mJson.fromJsonLwM2m(payload);
			String bn = jsonObject.getBaseName();
			
			for (JsonArrayEntry e : jsonObject.getResourceList()) {
				String strPath = bn + "/" + e.getName();
				
				LwM2mPath path = new LwM2mPath(strPath);
				
				if(path.getObjectId() == 31008) {
					
					if(path.getResourceId() == 101) { // modem info
						
					}
					
					if(path.getResourceId() == 102) { // meter info						
						if(path.getResourceInstanceId() != null) {
							meterInfo.put(path.getResourceInstanceId(), Base64.getDecoder().decode(e.getStringValue()));
						}						
					}
					
					if(path.getResourceId() == 103) { // DLMS_Metering Data 
						if(path.getResourceInstanceId() != null) {
							meterData.put(path.getResourceInstanceId(), Base64.getDecoder().decode(e.getStringValue()));
						}
					}
				}			
			}
			MDDataParser parser = new MDDataParser();
			
			for(Integer key : meterInfo.keySet()) {
				meterInfo.get(key);
				meterData.get(key);
				parser.parseMeterInfo(meterInfo.get(key));
				parser.parser(meterData.get(key));
			}
	
		} catch (Exception e) {
			e.printStackTrace();
		}
    }
	
}
