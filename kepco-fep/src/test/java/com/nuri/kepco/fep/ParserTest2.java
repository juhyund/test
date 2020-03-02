package com.nuri.kepco.fep;

import java.lang.reflect.InvocationTargetException;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import com.nuri.kepco.fep.mddata.DataParser;
import com.nuri.kepco.fep.parser.KepcoDLMSParser;
import com.nuri.kepco.fep.process.MDDataProcess;
import com.nuri.kepco.fep.util.Hex;

@RunWith(SpringRunner.class)
@SpringBootTest
public class ParserTest2 {
	
	@Autowired
	MDDataProcess process;

	@Test
    public void test() {
			
		
//		String bx = "0000010000FF000802000E090C07E4021404060C12FFFE5CB301000001020D000102000E090C07E402140406071DFFFE5CB300006201010D000702007D060000000006000000000600000000060000000017BF800000060000000006000000000600000000060000000017BF800000060000000006000000000600000000060000000017BF800000060000000006000000000600000000060000000017BF800000060000000006000000000600000000060000000017BF800000";
//		
//		
//		KepcoMDDataParser parser = new KepcoMDDataParser();
//		try {
//			parser.parser(Hex.encode(bx));
////			parser.parser(Hex.encode(bx));
//		} catch (Exception e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
		
//		if("DATAPUSH".equals(method)) {				
//			parserClassName = "com.nuri.kepco.fep.parser.KepcoMDDataParser";
//			saverClassName = "kepcoMDDataSaver";				
//		} else if ("OBJECTLINK".equals(method)) {				
//			parserClassName = "com.nuri.kepco.fep.parser.ObjectLinkDataParser";
//			saverClassName = "objectLinkDataSaver";				
//		}  else if ("NOTIFICATION".equals(method)) {				
//			parserClassName = "com.nuri.kepco.fep.parser.NotifyDataParser";
//			saverClassName = "notifyDataSaver";
//		}
		
		String parserClassName = "";
		
		Class<?> clazz;		
		try {			
			clazz = Class.forName(parserClassName);
			DataParser parser = (DataParser)clazz.getDeclaredConstructor().newInstance();
			
			System.out.println(parser);
			
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InstantiationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchMethodException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }
	
}
