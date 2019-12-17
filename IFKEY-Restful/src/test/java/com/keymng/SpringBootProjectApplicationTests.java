package com.keymng;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringRunner;

import com.keymng.restapi.RestApiApplication;

@RunWith(SpringRunner.class)
@ContextConfiguration
@SpringBootTest(classes={RestApiApplication.class})
public class SpringBootProjectApplicationTests {

	@Test
	public void contextLoads() {
	}

}
