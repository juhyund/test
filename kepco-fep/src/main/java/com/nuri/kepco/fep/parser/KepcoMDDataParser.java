package com.nuri.kepco.fep.parser;

import java.util.ArrayList;
import java.util.Base64;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.eclipse.leshan.core.node.LwM2mPath;
import org.eclipse.leshan.json.JsonArrayEntry;
import org.eclipse.leshan.json.JsonRootObject;
import org.eclipse.leshan.json.LwM2mJson;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.aimir.util.Hex;
import com.nuri.kepco.fep.datatype.MDData;
import com.nuri.kepco.fep.mddata.DataParser;

public class KepcoMDDataParser extends DataParser {

	private static final Logger LOG = LoggerFactory.getLogger(KepcoMDDataParser.class);
	
	private final int METERING_DATA_ID = 31008;
	private final int MODEM_INFO_RESOURCE_ID = 101;
	private final int METER_INFO_RESOURCE_ID = 102;
	private final int DLMS_RESOURCE_ID = 103;
	
	List<MDData> mdLists = null;
	Map<Integer, byte[]> meterInfo = null;
	Map<Integer, byte[]> meterData = null;
	
	String deviceId = "";
	String modemTime = "";
	
	public void parser(String frame, String deviceId, String modemTime) throws Exception {
		
		this.mdLists = new ArrayList<MDData>();
		this.meterInfo = new HashMap<Integer, byte[]>();
		this.meterData = new HashMap<Integer, byte[]>();
		
		this.deviceId = deviceId;
		this.modemTime = modemTime;
		
		try {
		
			JsonRootObject jsonObject = LwM2mJson.fromJsonLwM2m(frame);
			String bn = jsonObject.getBaseName();
			
			for (JsonArrayEntry e : jsonObject.getResourceList()) {
				
				String strPath = bn + "/" + e.getName();
				LwM2mPath path = new LwM2mPath(strPath);

				if (path.getObjectId() == METERING_DATA_ID) {

					if (path.getResourceId() == MODEM_INFO_RESOURCE_ID) { // modem info
						// TODO - MacAddress(8) + Count(2)
						LOG.debug("e.getStringValue() :{}", Hex.decode(Base64.getDecoder().decode(e.getStringValue())) );
					}

					if (path.getResourceId() == METER_INFO_RESOURCE_ID) { // meter info
						if (path.getResourceInstanceId() != null) {
							meterInfo.put(path.getResourceInstanceId(), Base64.getDecoder().decode(e.getStringValue()));
						}
					}

					if (path.getResourceId() == DLMS_RESOURCE_ID) { // DLMS_Metering Data
						if (path.getResourceInstanceId() != null) {
							meterData.put(path.getResourceInstanceId(), Base64.getDecoder().decode(e.getStringValue()));
						}
					}
				}
			}
			
			for(Integer key : meterInfo.keySet()) {
				
				KepcoDLMSParser dlmsParser = new KepcoDLMSParser();
				MDData mdData = dlmsParser.parser(meterInfo.get(key), meterData.get(key));
				mdLists.add(mdData);
			}
			
			LOG.debug("mdLists SIZE : {}", mdLists.size());
			
		} catch (Exception e) {
			e.printStackTrace();
		}	
	}
	
	public List<MDData> getMDList() {
		return mdLists;
	}

	public Map<Integer, byte[]> getMeterInfo() {
		return meterInfo;
	}

	public Map<Integer, byte[]> getMeterData() {
		return meterData;
	}

}
