package com.nuri.kepco.controller;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.core.io.InputStreamResource;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;

import com.nuri.kepco.service.DeviceInfoService;
import com.nuri.kepco.service.MeterBillingService;
import com.nuri.kepco.service.MeterDataService;
import com.nuri.kepco.service.MeterInfoService;
import com.nuri.kepco.service.MeterValueService;
import com.nuri.kepco.service.NMSInfoService;
import com.nuri.kepco.service.OperationLogService;
import com.nuri.kepco.service.DevicePowerLogService;
import com.nuri.kepco.util.ControllerUtil;

@Controller
public class FileDownloadController {

	Logger logger = LoggerFactory.getLogger(FileDownloadController.class);

	@Autowired
	private MeterValueService meterValueService;

	@Autowired
	private MeterBillingService meterBillingService;
	
	@Autowired
	private MeterDataService meterDataService;

	@Autowired
	private DeviceInfoService deviceInfoService;

	@Autowired
	private MeterInfoService meterInfoService;

	@Autowired
	private OperationLogService operationLogService;

	@Autowired
	private NMSInfoService nmsInfoService;

	@Autowired
	private DevicePowerLogService devicePowerLogService;
	
	/*
	 * downloadMeterValue
	 * 
	 * @desc MeterValue 엑셀다운로드
	 */
	@GetMapping("/downloadMeterValue")
	public ResponseEntity<InputStreamResource> downloadMeterValue(HttpServletRequest request) throws IOException {

		String[] commStr = { "meter_id", "meter_serial", "device_serial", "meter_type", "branch_id", "itime", "mtime" };
		String file_path = "";

		try {

			Map<String, Object> param = ControllerUtil.getCommonParam(request);

			for (String key : commStr) {
				if (request.getParameterMap().containsKey(key)) {
					param.put(key, request.getParameter(key));
				}
			}
			param.put("limit", 0);

			Map<String, String> output = this.meterValueService.excelMeterValue(param);
			file_path = output.get("filepath") + "/" + output.get("filename");

		} catch (Exception e) {
			logger.error("error : " + e);
		}

		File file = new File(file_path);
		InputStreamResource resource = new InputStreamResource(new FileInputStream(file));

		return ResponseEntity.ok().header(HttpHeaders.CONTENT_DISPOSITION, "attachment;filename=" + file.getName())
				.contentType(MediaType.APPLICATION_PDF).contentLength(file.length()).body(resource);
	}

	/*
	 * downloadMeterValueDetail
	 * 
	 * @desc MeterValueDetail 엑셀다운로드
	 */
	@GetMapping("/downloadMeterValueDetail")
	public ResponseEntity<InputStreamResource> downloadMeterValueDetail(HttpServletRequest request) throws IOException {

		String[] commStr = { "meter_id", "meter_serial", "device_serial", "meter_type", "branch_id", "itime", "mtime" };
		String file_path = "";

		try {

			Map<String, Object> param = ControllerUtil.getCommonParam(request);
			ControllerUtil.getCustomParam(request, commStr, param);

			List<Map<String, Object>> channelList = this.meterValueService.selectMeterChannel(param);
			param.put("channelList", channelList);

			for (String key : commStr) {
				if (request.getParameterMap().containsKey(key)) {
					param.put(key, request.getParameter(key));
				}
			}
			param.put("limit", 0);

			Map<String, String> output = this.meterValueService.excelMeterValueDetail(param);
			file_path = output.get("filepath") + "/" + output.get("filename");

		} catch (Exception e) {
			logger.error("error : " + e);
		}

		File file = new File(file_path);
		InputStreamResource resource = new InputStreamResource(new FileInputStream(file));

		return ResponseEntity.ok().header(HttpHeaders.CONTENT_DISPOSITION, "attachment;filename=" + file.getName())
				.contentType(MediaType.APPLICATION_PDF).contentLength(file.length()).body(resource);
	}

	@GetMapping("/downloadMeterBilling")
	public ResponseEntity<InputStreamResource> downloadMeterBilling(HttpServletRequest request) throws IOException {

		String[] commStr = { "meter_serial", "device_serial", "meter_type", "branch_parent_id", "branch_id",
				"billing_dt", "itime", "mtime", };
		String file_path = "";

		try {

			Map<String, Object> param = ControllerUtil.getCommonParam(request);

			for (String key : commStr) {
				if (request.getParameterMap().containsKey(key)) {
					param.put(key, request.getParameter(key));
				}
			}
			param.put("limit", 0);

			Map<String, String> output = this.meterBillingService.excelMeterBilling(param);
			file_path = output.get("filepath") + "/" + output.get("filename");

		} catch (Exception e) {
			logger.error("error : " + e);
		}

		File file = new File(file_path);
		InputStreamResource resource = new InputStreamResource(new FileInputStream(file));

		return ResponseEntity.ok().header(HttpHeaders.CONTENT_DISPOSITION, "attachment;filename=" + file.getName())
				.contentType(MediaType.APPLICATION_PDF).contentLength(file.length()).body(resource);
	}

	
	@GetMapping("/downloadMeterData")
	public ResponseEntity<InputStreamResource> downloadMeterData(HttpServletRequest request) throws IOException {

		String[] commStr = { "meter_id","meter_serial", "device_serial","meter_type","branch_id","itime","mtime"};
		String file_path = "";

		try {

			Map<String, Object> param = ControllerUtil.getCommonParam(request);

			for (String key : commStr) {
				if (request.getParameterMap().containsKey(key)) {
					param.put(key, request.getParameter(key));
				}
			}
			param.put("limit", 0);
			param.put("sort", "read_dt");
			param.put("dir", "DESC");

			Map<String, String> output = this.meterDataService.excelMeterData(param);
			file_path = output.get("filepath") + "/" + output.get("filename");

		} catch (Exception e) {
			logger.error("error : " + e);
		}

		File file = new File(file_path);
		InputStreamResource resource = new InputStreamResource(new FileInputStream(file));

		return ResponseEntity.ok().header(HttpHeaders.CONTENT_DISPOSITION, "attachment;filename=" + file.getName())
				.contentType(MediaType.APPLICATION_PDF).contentLength(file.length()).body(resource);
	}
	
	@GetMapping("/downloadDevicelist")
	public ResponseEntity<InputStreamResource> downloadDevicelist(HttpServletRequest request) throws IOException {

		String[] commStr = { "branch_parent_id", "branch_id", "device_status", "lsdate", "ledate", "fw_version" };
		String file_path = "";

		try {

			Map<String, Object> param = ControllerUtil.getCommonParam(request);

			for (String key : commStr) {
				if (request.getParameterMap().containsKey(key)) {
					param.put(key, request.getParameter(key));
				}
			}
			param.put("limit", 0);

			Map<String, String> output = this.deviceInfoService.excelDeviceList(param);
			file_path = output.get("filepath") + "/" + output.get("filename");

		} catch (Exception e) {
			logger.error("error : " + e);
		}

		File file = new File(file_path);
		InputStreamResource resource = new InputStreamResource(new FileInputStream(file));

		return ResponseEntity.ok().header(HttpHeaders.CONTENT_DISPOSITION, "attachment;filename=" + file.getName())
				.contentType(MediaType.APPLICATION_PDF).contentLength(file.length()).body(resource);
	}

	@GetMapping("/downloadMeterlist")
	public ResponseEntity<InputStreamResource> downloadMeterlist(HttpServletRequest request) throws IOException {

		String file_path = "";
		try {
			String[] commStr = { "branch_parent_id", "branch_id", "meter_type", "meter_serial", "device_serial",
					"device_status", "sdate", "edate" };

			Map<String, Object> param = ControllerUtil.getCommonParam(request);

			for (String key : commStr) {
				if (request.getParameterMap().containsKey(key)) {
					param.put(key, request.getParameter(key));
				}
			}
			param.put("limit", 0);

			Map<String, String> output = this.meterInfoService.excelMeterList(param);
			file_path = output.get("filepath") + "/" + output.get("filename");

		} catch (Exception e) {
			logger.error("error : " + e);
		}

		File file = new File(file_path);
		InputStreamResource resource = new InputStreamResource(new FileInputStream(file));

		return ResponseEntity.ok().header(HttpHeaders.CONTENT_DISPOSITION, "attachment;filename=" + file.getName())
				.contentType(MediaType.APPLICATION_PDF).contentLength(file.length()).body(resource);
	}

	@GetMapping("/downloadOperationLogList")
	public ResponseEntity<InputStreamResource> downloadOperationLogList(HttpServletRequest request) throws IOException {

		String file_path = "";
		try {
			String[] commStr = { "device_id", "method_type", "result_status", "tid", "request_sdate", "request_edate",
					"result_sdate", "result_edate", "target_meter" };

			Map<String, Object> param = ControllerUtil.getCommonParam(request);

			for (String key : commStr) {
				if (request.getParameterMap().containsKey(key)) {
					param.put(key, request.getParameter(key));
				}
			}

			param.put("sort", "request_dt");
			param.put("dir", "DESC");
			param.put("limit", 0);

			Map<String, String> output = this.operationLogService.excelOperationLogList(param);
			file_path = output.get("filepath") + "/" + output.get("filename");

		} catch (Exception e) {
			logger.error("error : " + e);
		}

		File file = new File(file_path);
		InputStreamResource resource = new InputStreamResource(new FileInputStream(file));

		return ResponseEntity.ok().header(HttpHeaders.CONTENT_DISPOSITION, "attachment;filename=" + file.getName())
				.contentType(MediaType.APPLICATION_PDF).contentLength(file.length()).body(resource);
	}

	@GetMapping("/downloadNMSList")
	public ResponseEntity<InputStreamResource> downloadNMSList(HttpServletRequest request) throws IOException {

		String file_path = "";
		try {
			String[] commStr = { "deviceId", "deviceSerial", "sdate", "edate", "data_per_page", "usageTime" };

			Map<String, Object> param = ControllerUtil.getCommonParam(request);

			for (String key : commStr) {
				if (request.getParameterMap().containsKey(key)) {
					param.put(key, request.getParameter(key));
				}
			}

			String deviceStatus = request.getParameter("device_status");
			String branch_parent_id = request.getParameter("branch_parent_id");
			String branchId = request.getParameter("branch_id");
			String searchfield = request.getParameter("searchfield");
			String searchquery = request.getParameter("searchquery");

			if (deviceStatus != null && !("").equals(deviceStatus)) {
				param.put("deviceStatus", deviceStatus);
			}
			if (branch_parent_id != null && !("").equals(branch_parent_id)) {
				param.put("parentBranchId", branch_parent_id);
			}
			if (branchId != null && !("").equals(branchId)) {
				param.put("branchId", branchId);
			}

			if (searchfield != null && !("").equals(searchfield)) {
				if (("deviceId").equals(searchfield)) {
					param.put("deviceId", searchquery);
				} else if (("deviceSerial").equals(searchfield)) {
					param.put("deviceSerial", searchquery);
				}

			}

			Map<String, String> output = this.nmsInfoService.excelNMSList(param);
			file_path = output.get("filepath") + "/" + output.get("filename");

		} catch (Exception e) {
			logger.error("error : " + e);
		}

		File file = new File(file_path);
		InputStreamResource resource = new InputStreamResource(new FileInputStream(file));

		return ResponseEntity.ok().header(HttpHeaders.CONTENT_DISPOSITION, "attachment;filename=" + file.getName())
				.contentType(MediaType.APPLICATION_PDF).contentLength(file.length()).body(resource);
	}

	
	@GetMapping("/downloadDevicePowerLoglist")
	public ResponseEntity<InputStreamResource> downloadDevicePowerLoglist(HttpServletRequest request) throws IOException {

		String[] commStr = { "branch_parent_id", "branch_id", "device_id", "power_status", "s_on_date", "e_on_date", "s_off_date", "e_off_date" };
		String file_path = "";

		try {

			Map<String, Object> param = ControllerUtil.getCommonParam(request);

			for (String key : commStr) {
				if (request.getParameterMap().containsKey(key)) {
					param.put(key, request.getParameter(key));
				}
			}
			param.put("limit", 0);

			Map<String, String> output = this.devicePowerLogService.excelDevicePowerLogList(param);
			file_path = output.get("filepath") + "/" + output.get("filename");

		} catch (Exception e) {
			logger.error("error : " + e);
		}

		File file = new File(file_path);
		InputStreamResource resource = new InputStreamResource(new FileInputStream(file));

		return ResponseEntity.ok().header(HttpHeaders.CONTENT_DISPOSITION, "attachment;filename=" + file.getName())
				.contentType(MediaType.APPLICATION_PDF).contentLength(file.length()).body(resource);
	}
}
