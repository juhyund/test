package com.nuri.kepco.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class PageController {

	@RequestMapping("/index")
	public String demo() throws Exception {
		return "mainFrame";
	}
	
	@RequestMapping("/main")
	public String main() throws Exception {
		return "main/main";
	}
	
	@RequestMapping("/login")
	public String login() throws Exception {
		return "login/login";
	}
	
}
