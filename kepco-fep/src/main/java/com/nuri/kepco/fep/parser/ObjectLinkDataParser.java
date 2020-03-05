package com.nuri.kepco.fep.parser;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

import org.eclipse.leshan.core.node.LwM2mPath;
import org.eclipse.leshan.json.JsonArrayEntry;
import org.eclipse.leshan.json.JsonRootObject;
import org.eclipse.leshan.json.LwM2mJson;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.nuri.kepco.fep.datatype.FIRMWARE;
import com.nuri.kepco.fep.datatype.FIRMWARE.FIRMWAREUPDATE;
import com.nuri.kepco.fep.datatype.MeterEntry.METERENTRY;
import com.nuri.kepco.fep.datatype.ResultMessage;
import com.nuri.kepco.fep.mddata.DataParser;
import com.nuri.kepco.model.DeviceResource;
import com.nuri.kepco.model.MeterInfo;

public class ObjectLinkDataParser extends DataParser {

	private static final Logger LOG = LoggerFactory.getLogger(ObjectLinkDataParser.class);

	private static final Integer METERENTRY_OBJECTID = 31004; // METER ENTRY
	private static final Integer FIRMWARE_OBJECTID = 5; // FIRMWARE UPDATE OBJECT

	private List<DeviceResource> deviceResourceList = null;

	private Map<Integer, MeterInfo> meterInfoList = null;
	private Map<Integer, Object> firmwareInfo = null;

	@Override
	public void parser(String data, String deviceId, String modemTime) throws Exception {

		deviceResourceList = new ArrayList<DeviceResource>();

		try {

			JsonRootObject jsonObject = LwM2mJson.fromJsonLwM2m(data);
			String bn = jsonObject.getBaseName();

			LwM2mPath basePath = new LwM2mPath(bn);


			if (METERENTRY_OBJECTID.equals(basePath.getObjectId())) {

				// METERENTRY
				parseMeterInfo(jsonObject);
				
			} else if(FIRMWARE_OBJECTID.equals(basePath.getObjectId())) {
				
				// FIRMWARE UPDATE
				parseFirmwareInfo(jsonObject);
			}

			// OBJECTLINK
			for (JsonArrayEntry e : jsonObject.getResourceList()) {

				String resourcePath = bn + "/" + e.getName();

				LwM2mPath path = new LwM2mPath(resourcePath);
				DeviceResource resource = new DeviceResource();
				resource.setResource_path(resourcePath);
				if(path.getObjectId() != null) resource.setObject_id(String.valueOf(path.getObjectId()));
				if(path.getObjectInstanceId() != null) resource.setObject_instance_id(String.valueOf(path.getObjectInstanceId()));
				if(path.getResourceId() != null) resource.setResource_id(String.valueOf(path.getResourceId()));
				if(path.getResourceInstanceId() != null) resource.setResource_instance_id(String.valueOf(path.getResourceInstanceId()));
				resource.setResource_val(e.getResourceValue().toString());
				resource.setReg_id("system");
				resource.setUpdate_id("system");

				deviceResourceList.add(resource);
			}

		} catch (Exception e) {
			LOG.error("error", e);
		}
	}

	private void parseMeterInfo(JsonRootObject jsonObject) {

		meterInfoList = new HashMap<Integer, MeterInfo>();

		for (JsonArrayEntry e : jsonObject.getResourceList()) {

			String resourcePath = METERENTRY_OBJECTID + "/" + e.getName();

			LwM2mPath path = new LwM2mPath(resourcePath);
			MeterInfo meterInfo = meterInfoList.get(path.getObjectInstanceId());

			if (meterInfo == null) {
				meterInfo = new MeterInfo();
				meterInfoList.put(path.getObjectInstanceId(), meterInfo);
			}

			if (METERENTRY.METERID.getCode().equals(path.getResourceId())) {
				meterInfo.setMeter_serial(e.getStringValue());
			}

			if (METERENTRY.COSEMDEVICENAME.getCode().equals(path.getResourceId())) {
				meterInfo.setCosem_device_name(e.getStringValue());
			}

			if (METERENTRY.ACON.getCode().equals(path.getResourceId())) {
				meterInfo.setAcon(Double.parseDouble(e.getResourceValue().toString()));
			}

			if (METERENTRY.RCON.getCode().equals(path.getResourceId())) {
				meterInfo.setRcon(Double.parseDouble(e.getResourceValue().toString()));
			}

			if (METERENTRY.MRD.getCode().equals(path.getResourceId())) {
				meterInfo.setBilling_dt(e.getStringValue()); // 정기검침일
			}

			if (METERENTRY.ITIME.getCode().equals(path.getResourceId())) {
				meterInfo.setItime(getDateFormat(e.getResourceValue().toString()));
			}

			if (METERENTRY.MTIME.getCode().equals(path.getResourceId())) {
				meterInfo.setMtime(getDateFormat(e.getResourceValue().toString()));
			}

			if (METERENTRY.LPPERIOD.getCode().equals(path.getResourceId())) {
				meterInfo.setLp_period(e.getFloatValue().intValue());
			}

			if (METERENTRY.PCON.getCode().equals(path.getResourceId())) {
				meterInfo.setPcon(Double.parseDouble(e.getResourceValue().toString()));
			}

			if (METERENTRY.NETMETERING.getCode().equals(path.getResourceId())) {
				meterInfo.setNet_metering(e.getFloatValue().intValue());
			}
		}

	}
	
	/**
	 * firmware update (5) 객체의 정보를 파싱한다
	 * @param jsonObject
	 */
	private void parseFirmwareInfo(JsonRootObject jsonObject) {

		for (JsonArrayEntry e : jsonObject.getResourceList()) {

			String resourcePath = FIRMWARE_OBJECTID + "/" + e.getName();

			LwM2mPath path = new LwM2mPath(resourcePath);			
			firmwareInfo = new HashMap<Integer, Object>();

			if (FIRMWAREUPDATE.PACKAGEURI.getCode().equals(path.getResourceId())) {
				firmwareInfo.put(FIRMWAREUPDATE.PACKAGEURI.getCode(), e.getResourceValue().toString());
			}
			
			if (FIRMWAREUPDATE.STATE.getCode().equals(path.getResourceId())) {
				firmwareInfo.put(FIRMWAREUPDATE.STATE.getCode(), e.getFloatValue().intValue());
			}
			
			if (FIRMWAREUPDATE.UPDATERESULT.getCode().equals(path.getResourceId())) {
				firmwareInfo.put(FIRMWAREUPDATE.UPDATERESULT.getCode(), e.getFloatValue().intValue());
			}
			
			if (FIRMWAREUPDATE.PACKAGENAME.getCode().equals(path.getResourceId())) {
				firmwareInfo.put(FIRMWAREUPDATE.PACKAGENAME.getCode(), e.getResourceValue().toString());
			}
			
			if (FIRMWAREUPDATE.PACKAGEVERSION.getCode().equals(path.getResourceId())) {
				firmwareInfo.put(FIRMWAREUPDATE.PACKAGEVERSION.getCode(), e.getResourceValue().toString());
			}
			
			if (FIRMWAREUPDATE.PROTOCOL.getCode().equals(path.getResourceId())) {
				firmwareInfo.put(FIRMWAREUPDATE.PROTOCOL.getCode(), e.getFloatValue().intValue());
			}
			
			if (FIRMWAREUPDATE.METHOD.getCode().equals(path.getResourceId())) {
				firmwareInfo.put(FIRMWAREUPDATE.METHOD.getCode(), e.getFloatValue().intValue());
			}
		}
	}

	public List<DeviceResource> getDeviceResourceList() {
		return deviceResourceList;
	}

	public Map<Integer, MeterInfo> getMeterInfoList() {
		return meterInfoList;
	}
	
	public Map<Integer, Object> getFirmwareInfo() {
		return firmwareInfo;
	}

	private String getDateFormat(String textDate) {

		String strDate = null;

		SimpleDateFormat recvSimpleFormat = new SimpleDateFormat("E MMM dd HH:mm:ss z yyyy", Locale.ENGLISH);

		SimpleDateFormat tranSimpleFormat = new SimpleDateFormat("yyyyMMddHHmmss", Locale.ENGLISH);

		try {

			Date data = recvSimpleFormat.parse(textDate);
			strDate = tranSimpleFormat.format(data);

		} catch (ParseException e) {
			e.printStackTrace();
		}

		return strDate;
	}

	@Override
	public void parser(ResultMessage data, String deviceId, String modemTime) throws Exception {
		// TODO Auto-generated method stub
		
	}
}

