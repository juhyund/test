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
		
		String json = "{\"deviceId\":\"LG-PC02\",\"method\":\"DATAPUSH\",\"format\":\"JSON\",\"token\":\"806662840758920E\",\"mid\":\"18966\",\"payload\":\"{\\\"bn\\\":\\\"/31008/0\\\",\\\"e\\\":[{\\\"n\\\":\\\"101\\\",\\\"sv\\\":\\\"MTIzNDU2Nzgx\\\"},{\\\"n\\\":\\\"102/0\\\",\\\"sv\\\":\\\"MjQxOTAyMDQyNDIH4woSBRMCAQA=\\\"},{\\\"n\\\":\\\"103/0\\\",\\\"sv\\\":\\\"AAABAAD/AAgCAA4JDAfjChIFEwItAYAAAAEAAAECHgABAgAOCQwH4wETBg4NMgCAAAAAAGIBAR4ABwIAfQYAAGY7BgABGbcGAAAAAAYAAJciFz8M1RIGAAA2NgYAAJcEBgAAAAAGAABQURc/DpD3BgAAMAUGAACCswYAAAAABgAARtEXPwuoxgYAAAAABgAAAAAGAAAAAAYAAAAAF7+AAAAGAAAAAAYAAAAABgAAAAAGAAAAABe/gAAA\\\"}]}\"}";		
		process.process(json);
		process.process(json);
	
    }
	
}
