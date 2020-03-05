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
import com.nuri.kepco.fep.datatype.MeterAccessResult;
import com.nuri.kepco.fep.datatype.ResultMessage;
import com.nuri.kepco.fep.mddata.DataParser;

public class KepcoMDDataParser extends DataParser {

	private static final Logger LOG = LoggerFactory.getLogger(KepcoMDDataParser.class);
	
	private final int METERING_DATA_ID = 31008;
	private final int MODEM_INFO_RESOURCE_ID = 101;
	private final int METER_INFO_RESOURCE_ID = 102;
	private final int DLMS_RESOURCE_ID = 103;
	
	private final int METER_ACCESS_ID = 31012;
	private final int OBIS_RESOURCE_ID = 105;
	private final int APDU_RESOURCE_ID = 106;
	private final int STATUS_RESOURCE_ID = 107;
	
	List<MDData> mdLists = null;
	byte[] modemInfo = null;
	Map<Integer, byte[]> meterInfo = null;
	Map<Integer, byte[]> meterData = null;
	Map<Integer, String> meterStatus = null;
	MeterAccessResult meterAccessResult = null;
	
	String deviceId = "";
	String modemTime = "";
	String mobileNo = "";
	
	String OBIS = "";
	String APDU = "";
	
	public void parser(String frame, String deviceId, String modemTime) throws Exception {
		
		this.mdLists = new ArrayList<MDData>();
		this.meterInfo = new HashMap<Integer, byte[]>();
		this.meterData = new HashMap<Integer, byte[]>();
		this.meterStatus = new HashMap<Integer, String>(); // meter access result
		
		this.deviceId = deviceId;
		this.modemTime = modemTime;
	
		String meterAccessFrame = "";	
		try {
		
			JsonRootObject jsonObject = LwM2mJson.fromJsonLwM2m(frame);
			String bn = jsonObject.getBaseName();
			
			for (JsonArrayEntry e : jsonObject.getResourceList()) {
				
				String strPath = bn + "/" + e.getName();
				LwM2mPath path = new LwM2mPath(strPath);

				if (path.getObjectId() == METERING_DATA_ID) {

					if (path.getResourceId() == MODEM_INFO_RESOURCE_ID) { // modem info
						
						LOG.debug("e.getStringValue() :{}", Hex.decode(Base64.getDecoder().decode(e.getStringValue())) );						
						modemInfo = Base64.getDecoder().decode(e.getStringValue());
						byte[] mobileNo = new byte[8];
						System.arraycopy(modemInfo, 0, mobileNo, 0, mobileNo.length);
											
						this.mobileNo = new String(mobileNo);						
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
				} else if(path.getObjectId() == METER_ACCESS_ID) {
					
					if (path.getResourceId() == OBIS_RESOURCE_ID) { // obis						
						meterAccessFrame += Hex.decode(Base64.getDecoder().decode(e.getStringValue()));
						OBIS = Hex.decode(Base64.getDecoder().decode(e.getStringValue()));
					}

					if (path.getResourceId() == APDU_RESOURCE_ID) { // apdu						
						meterAccessFrame += Hex.decode(Base64.getDecoder().decode(e.getStringValue()));
						APDU = Hex.decode(Base64.getDecoder().decode(e.getStringValue()));
					}

					if (path.getResourceId() == STATUS_RESOURCE_ID) { // status						
						if (path.getResourceInstanceId() != null) {					
							meterStatus.put(path.getResourceInstanceId(), String.valueOf(e.getFloatValue().intValue()));
						}
					}					
				}
			}
			
			if(meterInfo != null) {
				for(Integer key : meterInfo.keySet()) {
					
					KepcoDLMSParser dlmsParser = new KepcoDLMSParser();
					MDData mdData = dlmsParser.parser(meterInfo.get(key), meterData.get(key));
					mdLists.add(mdData);
				}
			}	
			
			if(!"".equals(meterAccessFrame)) {
				KepcoMeterAccessParser dlmsParser = new KepcoMeterAccessParser();
				meterAccessResult = dlmsParser.parser(Hex.encode(meterAccessFrame), OBIS, APDU, meterStatus);
			}
			
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
	
	public String getMobileNo() {
		return mobileNo;
	}
	
	public MeterAccessResult getMeterAccessResult() {
		return meterAccessResult;
	}

	public void setMeterAccessResult(MeterAccessResult meterAccessResult) {
		this.meterAccessResult = meterAccessResult;
	}

	@Override
	public void parser(ResultMessage data, String deviceId, String modemTime) throws Exception {
		// TODO Auto-generated method stub
		
	}

}
