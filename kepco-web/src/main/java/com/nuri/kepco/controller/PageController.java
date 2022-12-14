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
	@RequestMapping("/billing")
	public String billing() throws Exception {
		return "mvm/billing";
	}
	
	@RequestMapping("/meterData")
	public String meterData() throws Exception {
		return "mvm/meterData";
	}
	
	@RequestMapping("/NMS") 
	public String NMS() throws Exception {
		return "device/NMS";
	}
	
	@RequestMapping("/NMSDetail") 
	public String NMSDetail(@ModelAttribute(value="deviceSerial") String deviceSerial,
							@ModelAttribute(value="deviceId") String deviceId,
							@ModelAttribute(value="usageTime") String usageTime,
							@ModelAttribute(value="deviceStatusNm") String deviceStatusNm, Model model) throws Exception {
		model.addAttribute("deviceSerial", deviceSerial);
		model.addAttribute("deviceId", deviceId);
		model.addAttribute("usageTime", usageTime);
		model.addAttribute("deviceStatusNm", deviceStatusNm);
		return "device/NMSDetail";
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
	
	@RequestMapping("/operationLog")
	public String controlHistory() throws Exception {
		return "history/operationLog";
	}
	
	@RequestMapping("/operationLogDetail")
	public String controlHistoryDetail(@ModelAttribute(value="device_id") String device_id,
										@ModelAttribute(value="request_dt") String request_dt, Model model) throws Exception {
		model.addAttribute("device_id", device_id);
		model.addAttribute("request_dt", request_dt);
		return "history/operationLogDetail";
	}
	
	@RequestMapping("/firmware")
	public String firmware() throws Exception {
		return "history/deviceFwHistory";
	}
	
	@RequestMapping("/devicePowerLog")
	public String devicePowerLog() throws Exception {
		return "device/devicePowerLog";
	}
	
	
}
