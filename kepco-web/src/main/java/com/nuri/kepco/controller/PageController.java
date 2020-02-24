package com.nuri.kepco.controller;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.ModelAttribute;
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
	
	@RequestMapping("/model")
	public String model() throws Exception {
		return "model/model";
	}
	
	@RequestMapping("/device")
	public String device() throws Exception {
		return "device/device";
	}
	
	@RequestMapping("/deviceDetail")
	public String deviceDetail() throws Exception {
		return "device/deviceDetail";
	}
	
	@RequestMapping("/metering")
	public String metering() throws Exception {
		return "mvm/metering";
	}
	
	@RequestMapping("/NMS") 
	public String NMS() throws Exception {
		return "device/NMS";
	}
	
	@RequestMapping("/deviceControl")
	public String deviceControl() throws Exception {
		return "device/deviceControl";
	}
	
	@RequestMapping("/meter")
	public String meter() throws Exception {
		return "meter/meterManagement";
	}
	
	@RequestMapping("/meterDetail")
	public String meterDetail(@ModelAttribute(value="meter_serial") String meter_serial, Model model) throws Exception {
		model.addAttribute("meter_serial", meter_serial);
		return "meter/meterDetail";
	}
}
