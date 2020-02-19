package com.nuri.kepco.fep;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import com.nuri.kepco.fep.parser.KepcoMDDataParser;
import com.nuri.kepco.fep.process.MDDataProcess;
import com.nuri.kepco.fep.util.Hex;

@RunWith(SpringRunner.class)
@SpringBootTest
public class ParserTest2 {
	
	@Autowired
	MDDataProcess process;

	@Test
    public void test() {
			
		String bx = "0000010000FF000802000E090C07E4020A01131B1AFFFDE40000002A0000FF000102001209104E5443203138303132324120202032320101000804FF0003020002110500000F0000FF0016040011010102020904000000FF0905FFFFFF04FF0101000300FF000302000517447A0000010000F200FF000102000A09081303000100000708010080000CFF0003020002110F0101000301FF000302000517447A00000101000302FF000302000517447A0000";
		KepcoMDDataParser parser = new KepcoMDDataParser();
		try {
			parser.parser(Hex.encode(bx));
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }
	
}
