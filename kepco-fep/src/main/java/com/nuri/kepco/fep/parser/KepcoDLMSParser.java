package com.nuri.kepco.fep.parser;

import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.aimir.fep.protocol.fmp.datatype.OCTET;
import com.aimir.util.DataUtil;
import com.aimir.util.Hex;
import com.aimir.util.Util;
import com.nuri.kepco.fep.datatype.LPData;
import com.nuri.kepco.fep.datatype.MDData;
import com.nuri.kepco.fep.parser.DLMSVARIABLE.DLMS_CLASS_ATTR;
import com.nuri.kepco.fep.parser.DLMSVARIABLE.OBIS;
import com.nuri.kepco.fep.parser.LPChannel.CHANNEL;
import com.nuri.kepco.model.MeterBilling;

public class KepcoDLMSParser {

	private static final Logger LOG = LoggerFactory.getLogger(KepcoDLMSParser.class);
	private static final String KEPCO_LD = "2"; // KEPCO 관리용 번호
	private static final int KEPCO_SECURE_METER = 30; // KEPCO 보안계기버전

	LinkedHashMap<String, Map<String, Object>> result = null;
	
	MDData mdData = null;
	
	String modemTime = "";
	String meterID = "";
	String meterTime = "";
	String billingDate = "";
	String fwVersion = "";
	String meterType = "";
	String meterModel = "";
	
	public MDData parser(byte[] meterInfo, byte[] meterData) throws Exception {
			
		mdData = new MDData();
		result = new LinkedHashMap<String, Map<String, Object>>();
		
		// parse meterInfo
		parseMeterInfo(meterInfo);
		
		// parser meterData
		parserMeterData(meterData);		
		
		return mdData;
	}
	
	/**
	 * 미터정보 (/31008/0/102) 
	 * @param frame
	 * @throws Exception
	 */
	private void parseMeterInfo(byte[] frame) throws Exception {
		
		LOG.debug("parseMeterInfo [" + Hex.decode(frame) + "]");
		
		int total_len = frame.length;
		int pos = 0;
		byte[] data = new byte[total_len];
		System.arraycopy(frame, pos, data, 0, total_len);

		byte[] MID = new byte[11];
		byte[] ITIME = new byte[7];
		byte[] DCNT = new byte[2];

		System.arraycopy(data, pos, MID, 0, MID.length);
		pos += MID.length;
		meterID = new String(MID);

		System.arraycopy(data, pos, ITIME, 0, ITIME.length);
		pos += ITIME.length;
		LOG.debug("ITIME : {}", Hex.decode(ITIME));
		String modemTime = getBCDTime(ITIME);

		System.arraycopy(data, pos, DCNT, 0, DCNT.length);
		pos += DCNT.length;
		DataUtil.convertEndian(true, DCNT);
		int dcnt = DataUtil.getIntTo2Byte(DCNT); // 계기당 전송될 OBIS(/31011/x/112) 개수

		mdData.setMeterID(meterID); // MeterID 
		mdData.setModemTime(modemTime); // 해당미터 검침 값 수신시 모뎀시간
			 
	}
	
	/**
	 * DLMS_MeteringData /31008/0/103
	 * @param frame
	 * @throws Exception
	 */
	public void parserMeterData(byte[] frame) throws Exception {

		String obisCode = "";
		int clazz = 0;
		int attr = 0;
		int pos = 0;
		int len = 0;
		int total_len = frame.length;

		byte[] data = new byte[total_len];
		System.arraycopy(frame, pos, data, 0, total_len);

		LOG.debug("meterID : ["+meterID+"] + [" + Hex.decode(data) + "]");
		pos = 0;

		byte[] OBIS = new byte[6];
		byte[] CLAZZ = new byte[2];
		byte[] ATTR = new byte[1];
		byte[] LEN = new byte[2];
		byte[] TAGDATA = null;

		DLMSTable dlms = null;

		while (pos < data.length) {

			dlms = new DLMSTable();

			System.arraycopy(data, pos, OBIS, 0, OBIS.length);
			pos += OBIS.length;
			obisCode = Hex.decode(OBIS);
			dlms.setObis(obisCode);

			System.arraycopy(data, pos, CLAZZ, 0, CLAZZ.length);
			pos += CLAZZ.length;
			clazz = DataUtil.getIntTo2Byte(CLAZZ);
			dlms.setClazz(clazz);

			System.arraycopy(data, pos, ATTR, 0, ATTR.length);
			pos += ATTR.length;
			attr = DataUtil.getIntToBytes(ATTR);
			dlms.setAttr(attr);

			System.arraycopy(data, pos, LEN, 0, LEN.length);
			pos += LEN.length;
			len = DataUtil.getIntTo2Byte(LEN);
			dlms.setLength(len);

			TAGDATA = new byte[len];
			if (pos + TAGDATA.length <= data.length) {
				System.arraycopy(data, pos, TAGDATA, 0, TAGDATA.length);
				pos += TAGDATA.length;
			} else {
				System.arraycopy(data, pos, TAGDATA, 0, data.length - pos);
				pos += data.length - pos;
			}

			String _obisCode = obisCode.substring(0, 10);
			if (_obisCode.equals("0100000102") || _obisCode.equals("0000620101") || _obisCode.equals("0000620103")) {
				obisCode = _obisCode + "00";
				dlms.setObis(obisCode);
			}

			LOG.debug("OBIS[" + obisCode + "] CLASS[" + clazz + "] ATTR[" + attr + "] LENGTH[" + len + "] TAGDATA=["
					+ Hex.decode(TAGDATA) + "]");

			dlms.parseDlmsTag(TAGDATA);
			Map<String, Object> dlmsData = dlms.getData();

			if (dlms.getDlmsHeader().getObis() == DLMSVARIABLE.OBIS.ENERGY_LOAD_PROFILE) {
				for (int cnt = 0;; cnt++) {
					obisCode = dlms.getDlmsHeader().getObis().getCode() + "-" + cnt;
					if (!result.containsKey(obisCode)) {
						result.put(obisCode, dlmsData);
						break;
					}
				}
			} else if (dlms.getDlmsHeader().getObis() == DLMSVARIABLE.OBIS.METER_TIME
					&& dlms.getDlmsHeader().getAttr() != DLMS_CLASS_ATTR.CLOCK_ATTR02) {
				result.put(obisCode + "-" + dlms.getDlmsHeader().getAttr().getAttr(), dlmsData);
			} else if (dlms.getDlmsHeader().getObis() == DLMSVARIABLE.OBIS.HW_VER) { // cosem
				result.put(obisCode, dlmsData);
			} else if (dlms.getDlmsHeader().getObis() == DLMSVARIABLE.OBIS.ACTIVEPOWER_CONSTANT) { // 유효전력량 계기정수
				result.put(obisCode, dlmsData);	
			} else if (dlms.getDlmsHeader().getObis() == DLMSVARIABLE.OBIS.REACTIVEPOWER_CONSTANT) { // 무효전력량 계기정수
				result.put(obisCode, dlmsData);
			} else if (dlms.getDlmsHeader().getObis() == DLMSVARIABLE.OBIS.APPRENTPOWER_CONSTANT) { // 피상전력량계기정수
				result.put(obisCode, dlmsData);				
			} else if (dlms.getDlmsHeader().getObis() == DLMSVARIABLE.OBIS.MEASUREMENT_DATE) { // 정기검침일
				result.put(obisCode, dlmsData);		
			} else if (dlms.getDlmsHeader().getObis() == DLMSVARIABLE.OBIS.LP_INTERVAL) { // LP PERIOD
				result.put(obisCode, dlmsData);
			} else if (dlms.getDlmsHeader().getObis() == DLMSVARIABLE.OBIS.AVG_POWER_PERIOD) { // AVG_POWER_PERIOD
				result.put(obisCode, dlmsData);
			} else if (dlms.getDlmsHeader().getObis() == DLMSVARIABLE.OBIS.NET_METERING) { // NET_METERING
				result.put(obisCode, dlmsData);	
			} else if (dlms.getDlmsHeader().getObis() == DLMSVARIABLE.OBIS.BILLING) {// 순방향 전력량 (월별)

				for (int cnt = 0;; cnt++) {
					obisCode = dlms.getDlmsHeader().getObis().getCode() + "-" + cnt;
					LOG.debug("obisCode : " + obisCode);
					if (!result.containsKey(obisCode)) {
						result.put(obisCode, dlmsData);
						break;
					}
				}
			} else if (dlms.getDlmsHeader().getObis() == DLMSVARIABLE.OBIS.BILLING_REVERSE) {// 역방향 전력량 (월별)
				for (int cnt = 0;; cnt++) {
					obisCode = dlms.getDlmsHeader().getObis().getCode() + "-" + cnt;
					LOG.debug("obisCode : " + obisCode);
					if (!result.containsKey(obisCode)) {
						result.put(obisCode, dlmsData);
						break;
					}
				}
			} else if (dlms.getDlmsHeader().getObis() == DLMSVARIABLE.OBIS.ETYPE_BILLING) {// ETYPE 정기검침
				for (int cnt = 0;; cnt++) {
					obisCode = dlms.getDlmsHeader().getObis().getCode() + "-" + cnt;
					LOG.debug("obisCode : " + obisCode);
					if (!result.containsKey(obisCode)) {
						result.put(obisCode, dlmsData);
						break;
					}
				}
			} else if (dlmsData != null && !dlmsData.isEmpty()) {
				result.put(obisCode, dlmsData);
			}
		}
		
		setMeterInfo();
		
		List<LPData> lpDatas = setLpData();
		mdData.setLpDatas(lpDatas);
		
		// 정기검침 순방향과 역박향이 각각 올라온다.
		// 미터시간은 정기검침을 조회한 시간이다.
		// 정기검침은 정기검침일에 생성된 데이터이다.		
		List<MeterBilling> billingImport = setBillingImportData();
		List<MeterBilling> billingExport = setBillingExportData();
		List<MeterBilling> etypeBillingImport = setEtypeBillingImportData(); // etype 정기검침
		
		mdData.setBillingImportData(billingImport);
		mdData.setBillingExportData(billingExport);
		mdData.setETypeBillingImportData(etypeBillingImport);
	}		
	
	public void setMeterInfo() {
		
		try {
			
			String cosem_device_id = "";
			String meterTime = "";
			String billingDay = "0";
			int lpInterval = 0;
			Double acon = 0.0;
			Double rcon = 0.0;
			Double pcon = 0.0;
			int netMetering = 0;
			int avgPowerPeriod = 0;
			
			Map<String, Object> map = null;
			map = (Map<String, Object>) result.get(OBIS.HW_VER.getCode()); // cosem_id
			if (map != null) {
				
				Object obj = null;
				obj = map.get(OBIS.HW_VER.getName());
				if (obj != null)
					cosem_device_id = new String(Hex.encode((String) obj));
				LOG.debug("COSEM_ID(HW_VER) [" + cosem_device_id + "]");
				mdData.setCosemDeviceName(cosem_device_id);
				
				byte[] bcosem = Hex.encode((String) obj);
				byte[] blogicalDeviceNo = new byte[1];
				byte[] bversion = new byte[1];
				
				System.arraycopy(bcosem, 14, blogicalDeviceNo, 0, blogicalDeviceNo.length);
				System.arraycopy(bcosem, 15, bversion, 0, bversion.length);
				
				String logicalDeviceNo = new String(blogicalDeviceNo);
				String version = DataUtil.getBCDtoBytes(bversion);
				
				mdData.setCosemLogicalDevice(logicalDeviceNo);
				mdData.setCosemVersion(version);
				
				LOG.debug("COSEM_ID(logicalDeviceNo) [" + logicalDeviceNo + "]");
				LOG.debug("COSEM_ID(version) [" + version + "]");				
			}

			map = (Map<String, Object>) result.get(OBIS.METER_TIME.getCode());
			if (map != null) {
				Object obj = map.get(OBIS.METER_TIME.getName());
				if (obj != null)
					meterTime = (String) obj;
				if (meterTime != null && meterTime.length() != 14) {
					meterTime = meterTime + "00";
				}
				LOG.debug("METER_TIME[" + meterTime + "]");
				mdData.setMeterTime(meterTime);
			}

			map = (Map<String, Object>) result.get(OBIS.MEASUREMENT_DATE.getCode());
			if (map != null) {
				Object obj = map.get(OBIS.MEASUREMENT_DATE.getName());
				if (obj != null)
					billingDay = (String) obj;
				
				LOG.debug("MEASUREMENT_DATE[" + billingDay + "]"); // 정기검침일(미터정보 업데이트)
				mdData.setBillingDay(billingDay);
			}
			
			map = (Map<String, Object>) result.get(OBIS.LP_INTERVAL.getCode());
			if (map != null) {
				Object obj = map.get(OBIS.LP_INTERVAL.getName());
				if (obj != null)
					lpInterval = Integer.parseInt(String.valueOf(obj));
				LOG.debug("LP INTERVAL[" + lpInterval + "]");
				mdData.setLpPeriod(lpInterval);
			}
			
			map = (Map<String, Object>) result.get(OBIS.ACTIVEPOWER_CONSTANT.getCode());
			if (map != null) {
				Object obj = map.get(OBIS.ACTIVEPOWER_CONSTANT.getName());
				
				LOG.debug("ACTIVEPOWER_CONSTANT : {} ", Hex.encode(String.valueOf(obj)));
				if (obj != null)
					acon = Double.parseDouble(String.valueOf(obj));
				LOG.debug("ACON[" + acon + "]");
				mdData.setAcon(acon);
			}
			
			map = (Map<String, Object>) result.get(OBIS.REACTIVEPOWER_CONSTANT.getCode());
			if (map != null) {
				Object obj = map.get(OBIS.REACTIVEPOWER_CONSTANT.getName());
				if (obj != null)
					rcon = Double.parseDouble(String.valueOf(obj));
				LOG.debug("RCON[" + rcon + "]");
				mdData.setRcon(rcon);
			}
			
			map = (Map<String, Object>) result.get(OBIS.APPRENTPOWER_CONSTANT.getCode());
			if (map != null) {
				Object obj = map.get(OBIS.APPRENTPOWER_CONSTANT.getName());
				if (obj != null)
					pcon = Double.parseDouble(String.valueOf(obj));
				LOG.debug("PCON[" + pcon + "]");
				mdData.setPcon(pcon);
			}
			
			// 정기검침정보에 올라온다.
			map = (Map<String, Object>) result.get(OBIS.BILLING_DATE.getCode());
			if (map != null) {
				Object obj = map.get(OBIS.BILLING_DATE.getName());
				if (obj != null)
					billingDate = (String) obj;
				
				LOG.debug("BILLING_DATE[" + billingDate + "]"); // monthly billing date (정기검침테이블 업데이트)
				mdData.setBillingDate(billingDate);
			}
			
			// 양향방
			map = (Map<String, Object>) result.get(OBIS.NET_METERING.getCode());
			if (map != null) {
				Object obj = map.get(OBIS.NET_METERING.getName());
				if (obj != null)
					netMetering = (Integer)obj;
				
				LOG.debug("NET_METERING[" + netMetering + "]");
				mdData.setNetMetering(netMetering);
			}
			
			// 평균전압주기
			map = (Map<String, Object>) result.get(OBIS.AVG_POWER_PERIOD.getCode());
			if (map != null) {
				Object obj = map.get(OBIS.AVG_POWER_PERIOD.getName());
				if (obj != null)
					avgPowerPeriod = (Integer)obj;
				
				LOG.debug("AVG_POWER_PERIOD[" + avgPowerPeriod + "]");
				mdData.setAvgPowerPeriod(avgPowerPeriod);
			}
						
			
		} catch (Exception e) {
			LOG.error("error setMeterInfo", e);
		}
		
		// meter model
		setMeterModel(meterID, mdData.getCosemLogicalDevice(), mdData.getCosemVersion());
	}
	
	/**
	 * setLpData
	 * @return
	 */
	public List<LPData> setLpData() {
		
		Map<String, Object> lpMap = null;
		List<LPData> lpDataList = new ArrayList<LPData>();
		
		try {

			for (int i = 0; i < result.size(); i++) {

				if (!result.containsKey(OBIS.ENERGY_LOAD_PROFILE.getCode() + "-" + i))
					break;

				if (result.containsKey(OBIS.ENERGY_LOAD_PROFILE.getCode() + "-" + i)) {
					lpMap = (Map<String, Object>) result.get(OBIS.ENERGY_LOAD_PROFILE.getCode() + "-" + i);
				}

				if (lpMap == null) {
					break;
				}

				Object value = null;
				int cnt = 0;
				Double chValue = 0.0;

				while ((value = lpMap.get("Channel[1]" + "-" + cnt)) != null) {

					String read_dt = (String) lpMap.get("DateTime" + "-" + cnt);
					LOG.debug("read_dt {}", read_dt);
					if (value instanceof OCTET)
						chValue = (double) DataUtil.getLongToBytes(((OCTET) value).getValue());
					else if (value instanceof Long)
						chValue = ((Long) value).doubleValue();
					else if (value instanceof Float)
						chValue = ((Float) value).doubleValue();

					chValue = (chValue) * 0.001; // Cumulative active energy -import

					LPData lp = new LPData();
					lp.setRead_dt(read_dt);
					lp.setChannel(CHANNEL.CH1.getCode());
					lp.setValue(chValue);
					
					lpDataList.add(lp);

					value = lpMap.get("Channel[2]" + "-" + cnt);
					if (value != null) {
						if (value instanceof OCTET)
							chValue = (double) DataUtil.getLongToBytes(((OCTET) value).getValue());
						else if (value instanceof Long)
							chValue = ((Long) value).doubleValue();
						else if (value instanceof Float)
							chValue = ((Float) value).doubleValue();
						
						chValue = (chValue) * 0.001;

						lp = new LPData();
						lp.setRead_dt(read_dt);
						lp.setChannel(CHANNEL.CH2.getCode());
						lp.setValue(chValue);
						lpDataList.add(lp);
					}

					value = lpMap.get("Channel[3]" + "-" + cnt);
					if (value != null) {
						if (value instanceof OCTET)
							chValue = (double) DataUtil.getLongToBytes(((OCTET) value).getValue());
						else if (value instanceof Long)
							chValue = ((Long) value).doubleValue();
						else if (value instanceof Float)
							chValue = ((Float) value).doubleValue();

						chValue = (chValue) * 0.001; // Cumulative active energy -import rate 2

						lp = new LPData();
						lp.setRead_dt(read_dt);
						lp.setChannel(CHANNEL.CH3.getCode());
						lp.setValue(chValue);
						lpDataList.add(lp);
					}

					value = lpMap.get("Channel[4]" + "-" + cnt);
					if (value != null) {
						if (value instanceof OCTET)
							chValue = (double) DataUtil.getLongToBytes(((OCTET) value).getValue());
						else if (value instanceof Long)
							chValue = ((Long) value).doubleValue();
						else if (value instanceof Float)
							chValue = ((Float) value).doubleValue();

						chValue = (chValue) * 0.001; // Cumulative active energy -import rate 3

						lp = new LPData();
						lp.setRead_dt(read_dt);
						lp.setChannel(CHANNEL.CH4.getCode());
						lp.setValue(chValue);
						lpDataList.add(lp);
					}

					value = lpMap.get("Channel[5]" + "-" + cnt);
					if (value != null) {
						if (value instanceof OCTET)
							chValue = (double) DataUtil.getLongToBytes(((OCTET) value).getValue());
						else if (value instanceof Long)
							chValue = ((Long) value).doubleValue();
						else if (value instanceof Float)
							chValue = ((Float) value).doubleValue();

						chValue = (chValue) * 0.001; // Cumulative active energy -import rate 3

						lp = new LPData();
						lp.setRead_dt(read_dt);
						lp.setChannel(CHANNEL.CH5.getCode());
						lp.setValue(chValue);
						lpDataList.add(lp);
					}

					value = lpMap.get("Channel[6]" + "-" + cnt);
					if (value != null) {
						if (value instanceof OCTET)
							chValue = (double) DataUtil.getLongToBytes(((OCTET) value).getValue());
						else if (value instanceof Long)
							chValue = ((Long) value).doubleValue();
						else if (value instanceof Float)
							chValue = ((Float) value).doubleValue();

						chValue = (chValue) * 0.001; // Cumulative active energy -import rate 3

						lp = new LPData();
						lp.setRead_dt(read_dt);
						lp.setChannel(CHANNEL.CH6.getCode());
						lp.setValue(chValue);
						lpDataList.add(lp);
					}

					value = lpMap.get("Channel[7]" + "-" + cnt);
					if (value != null) {
						if (value instanceof OCTET)
							chValue = (double) DataUtil.getLongToBytes(((OCTET) value).getValue());
						else if (value instanceof Long)
							chValue = ((Long) value).doubleValue();
						else if (value instanceof Float)
							chValue = ((Float) value).doubleValue();

						chValue = (chValue) * 0.001; // Cumulative active energy -import rate 3

						lp = new LPData();
						lp.setRead_dt(read_dt);
						lp.setChannel(CHANNEL.CH7.getCode());
						lp.setValue(chValue);
						lpDataList.add(lp);
					}

					value = lpMap.get("Channel[8]" + "-" + cnt);
					if (value != null) {
						if (value instanceof OCTET)
							chValue = (double) DataUtil.getLongToBytes(((OCTET) value).getValue());
						else if (value instanceof Long)
							chValue = ((Long) value).doubleValue();
						else if (value instanceof Float)
							chValue = ((Float) value).doubleValue();

						chValue = (chValue) * 0.001; // Cumulative active energy -import rate 3

						lp = new LPData();
						lp.setRead_dt(read_dt);
						lp.setChannel(CHANNEL.CH8.getCode());
						lp.setValue(chValue);
						lpDataList.add(lp);
					}
					cnt++;
				} // end while
			}
			
			Collections.sort(lpDataList);

		} catch (Exception e) {
			LOG.error("error", e);
		}
		
		return lpDataList;

	}
	
	/**
	 * 미터 모델 정보
	 * @param meterSerial
	 */
	public void setMeterModel(String meterSerial, String cosemLogicalDeviceNo, String cosemVersion) {

		String vendorCd = meterSerial.substring(0, 2);
		String modelCd = meterSerial.substring(2, 4);

		LOG.debug("setMeterModel meterSerial : [" + meterSerial + "] vendorCd : [" + vendorCd + "] modelCd : [" + modelCd + "]");
		LOG.debug("setMeterModel meterSerial : [" + meterSerial + "] cosemLogicalDeviceNo : [" + cosemLogicalDeviceNo + "] cosemVersion : [" + cosemVersion + "]");
		
		DLMSVARIABLE.METERTYPE type = DLMSVARIABLE.METERTYPE.getMeterType(modelCd);
		DLMSVARIABLE.METERPHASE phase = DLMSVARIABLE.METERPHASE.getMeterPhase(modelCd);
				
		// 보안계기 구분 : LD = 2 이고 Version > 3.x 이상일 때 보안계기타입 
		if(KEPCO_LD.equals(cosemLogicalDeviceNo)) {
			if(Integer.parseInt(cosemVersion) >= KEPCO_SECURE_METER) {					
				type = DLMSVARIABLE.METERTYPE.SECMETERTYPE;
				
				LOG.debug("setMeterModel meterSerial : [" + meterSerial + "] type : [" + type.getName() + "]");
			}
		}
		
		if(type != null) {
			mdData.setMeterType(type.getName());
		} else {
			mdData.setMeterType(DLMSVARIABLE.METERTYPE.UNKNOWN.getName());
		}
		
		if(phase != null) {
			mdData.setMeterPhase(phase.getName());
		} else {
			mdData.setMeterPhase(DLMSVARIABLE.METERPHASE.UNKNOWN.getName());
		}
		
		LOG.debug("METER TYPE : {}", mdData.getMeterType());
		LOG.debug("METER PHASE : {}", mdData.getMeterPhase());
		
		mdData.setVendorCd(vendorCd);
	}

	/**
	 * getBCDTime bcd(7byte) time -> stirng
	 * 
	 * @param bcd
	 * @return
	 */
	private String getBCDTime(byte[] bcdTime) {

		StringBuffer strBCDTime = new StringBuffer();
		String appender = "";
		
		for (int i = 0; i < bcdTime.length; i++) {
			
			appender = (i == 0) ? "20" : "";
			
			if (i != 3) {				
				int b = bcdTime[i];
//				strBCDTime.append(appender + Util.frontAppendNStr('0', Integer.toHexString(bcdTime[i]), 2));
				strBCDTime.append(appender + Util.frontAppendNStr('0', String.valueOf(b), 2));
			}
		}
		
		return strBCDTime.toString();
	}
	
	public List<MeterBilling> setBillingImportData() {
		try {

			Map<String, Object> lpMap = null;
			List<MeterBilling> billingList = new ArrayList<MeterBilling>();
			
			for (int i = 0; i < result.size(); i++) {

				if (!result.containsKey(OBIS.BILLING.getCode() + "-" + i))
					break;

				if (result.containsKey(OBIS.BILLING.getCode() + "-" + i)) {
					lpMap = (Map<String, Object>) result.get(OBIS.BILLING.getCode() + "-" + i);
				}
				
				if (lpMap == null) {
					break;
				}

				Object value = null;
				int cnt = 0;
				Double[] billing = new Double[25];
				Double chValue = 0.0;

				while ((value = lpMap.get("Channel[1]" + "-" + cnt)) != null) {

					for (int j = 0; j < 25; j++) {
						
						value = lpMap.get("Channel[" + (j + 1) + "]" + "-" + cnt);
						
						if (value instanceof OCTET)
							chValue = (double) DataUtil.getLongToBytes(((OCTET) value).getValue());
						else if (value instanceof Long)
							chValue = ((Long) value).doubleValue();
						else if (value instanceof Float)
							chValue = ((Float) value).doubleValue();

						billing[j] = chValue;
					}
					
					if(mdData.getMeterType().equals(DLMSVARIABLE.METERTYPECODE.STYPE.getCode())) {
						
						LOG.debug("BillingDate : {}",  billingDate);
						MeterBilling billingImport = new MeterBilling();
						billingImport.setMeter_id(meterID);
						billingImport.setBilling_dt(billingDate);
						billingImport.setMtime(meterTime); // 미터타임
						billingImport.setItime(modemTime); // 모뎀타임
						
						// total
						billingImport.setActive_imp_tot(billing[0] * 0.001); // 순방향 유효
						billingImport.setLagging_imp_tot(billing[1] * 0.001); // 지상 무효
						billingImport.setPf_imp_tot(billing[2]); // 역률
						// tariff1
						billingImport.setActive_imp_rate1(billing[3] * 0.001); // 순방향 유효
						billingImport.setLagging_imp_rate1(billing[4] * 0.001); // 지상 무효
						billingImport.setPf_imp_rate1(billing[5]); // 역률
						
						// tariff2
						billingImport.setActive_imp_rate2(billing[6] * 0.001);	// 순방향 유효					
						billingImport.setLagging_imp_rate2(billing[7] * 0.001); // 지상 무효
						billingImport.setPf_imp_rate2(billing[8]); // 역률
						
						// tariff3
						billingImport.setActive_imp_rate3(billing[9] * 0.001); // 순방향 유효	
						billingImport.setLagging_imp_rate3(billing[10] * 0.001); // 지상 무효
						billingImport.setPf_imp_rate3(billing[11]); // 역률

						billingList.add(billingImport);
						
					} else {
						MeterBilling billingImport = new MeterBilling();
						
						billingImport.setMeter_id(meterID);
						billingImport.setBilling_dt(billingDate);
						billingImport.setMtime(meterTime); // 미터타임
						billingImport.setItime(modemTime); // 모뎀타임
						
						billingImport.setActive_imp_tot(billing[0] * 0.001);
						billingImport.setApprent_imp_tot(billing[1] * 0.001);
						billingImport.setLead_imp_tot(billing[2] * 0.001);
						billingImport.setLagging_imp_tot(billing[3] * 0.001);
						billingImport.setPf_imp_tot(billing[4]);

						billingImport.setActive_imp_rate1(billing[5] * 0.001);
						billingImport.setApprent_imp_rate1(billing[6] * 0.001);
						billingImport.setLead_imp_rate1(billing[7] * 0.001);
						billingImport.setLagging_imp_rate1(billing[8] * 0.001);
						billingImport.setPf_imp_rate1(billing[9]);

						billingImport.setActive_imp_rate2(billing[10] * 0.001);
						billingImport.setApprent_imp_rate2(billing[11] * 0.001);
						billingImport.setLead_imp_rate2(billing[12] * 0.001);
						billingImport.setLagging_imp_rate2(billing[13] * 0.001);
						billingImport.setPf_imp_rate2(billing[14]);

						billingImport.setActive_imp_rate3(billing[15] * 0.001);
						billingImport.setApprent_imp_rate3(billing[16] * 0.001);
						billingImport.setLead_imp_rate3(billing[17] * 0.001);
						billingImport.setLagging_imp_rate3(billing[18] * 0.001);
						billingImport.setPf_imp_rate3(billing[19]);

						billingImport.setActive_imp_rate4(billing[20] * 0.001);
						billingImport.setApprent_imp_rate4(billing[21] * 0.001);
						billingImport.setLead_imp_rate4(billing[22] * 0.001);
						billingImport.setLagging_imp_rate4(billing[23] * 0.001);
						billingImport.setPf_imp_rate4(billing[24]);
						
						billingList.add(billingImport);
					}
					
					cnt++;

				} // end while
				
				return billingList;
			}
		} catch (Exception e) {
			LOG.error("error", e);
		}
		
		return null;
	}
	
	public List<MeterBilling> setBillingExportData() {
		
		try {

			Map<String, Object> lpMap = null;
			List<MeterBilling> billingList = new ArrayList<MeterBilling>();

			for (int i = 0; i < result.size(); i++) {

				if (!result.containsKey(OBIS.BILLING_REVERSE.getCode() + "-" + i))
					break;

				if (result.containsKey(OBIS.BILLING_REVERSE.getCode() + "-" + i)) {
					lpMap = (Map<String, Object>) result.get(OBIS.BILLING_REVERSE.getCode() + "-" + i);
				}

				if (lpMap == null) {
					break;
				}

				Object value = null;
				int cnt = 0;
				Double[] billing = new Double[25];
				Double chValue = 0.0;

				while ((value = lpMap.get("Channel[1]" + "-" + cnt)) != null) {

					for (int j = 0; j < 25; j++) {

						value = lpMap.get("Channel[" + (j + 1) + "]" + "-" + cnt);

						if (value instanceof OCTET)
							chValue = (double) DataUtil.getLongToBytes(((OCTET) value).getValue());
						else if (value instanceof Long)
							chValue = ((Long) value).doubleValue();
						else if (value instanceof Float)
							chValue = ((Float) value).doubleValue();

						billing[j] = chValue;
					}

					MeterBilling billingImport = new MeterBilling();

					billingImport.setMeter_id(meterID);
					billingImport.setBilling_dt(billingDate);
					billingImport.setMtime(meterTime); // 미터타임
					billingImport.setItime(modemTime); // 모뎀타임
					
					billingImport.setActive_exp_tot(billing[0] * 0.001);
					billingImport.setApprent_exp_tot(billing[1] * 0.001);
					billingImport.setLead_exp_tot(billing[2] * 0.001);
					billingImport.setLagging_exp_tot(billing[3] * 0.001);
					billingImport.setPf_exp_tot(billing[4]);

					billingImport.setActive_exp_rate1(billing[5] * 0.001);
					billingImport.setApprent_exp_rate1(billing[6] * 0.001);
					billingImport.setLead_exp_rate1(billing[7] * 0.001);
					billingImport.setLagging_exp_rate1(billing[8] * 0.001);
					billingImport.setPf_exp_rate1(billing[9]);

					billingImport.setActive_exp_rate2(billing[10] * 0.001);
					billingImport.setApprent_exp_rate2(billing[11] * 0.001);
					billingImport.setLead_exp_rate2(billing[12] * 0.001);
					billingImport.setLagging_exp_rate2(billing[13] * 0.001);
					billingImport.setPf_exp_rate2(billing[14]);

					billingImport.setActive_exp_rate3(billing[15] * 0.001);
					billingImport.setApprent_exp_rate3(billing[16] * 0.001);
					billingImport.setLead_exp_rate3(billing[17] * 0.001);
					billingImport.setLagging_exp_rate3(billing[18] * 0.001);
					billingImport.setPf_exp_rate3(billing[19]);

					billingImport.setActive_exp_rate4(billing[20] * 0.001);
					billingImport.setApprent_exp_rate4(billing[21] * 0.001);
					billingImport.setLead_exp_rate4(billing[22] * 0.001);
					billingImport.setLagging_exp_rate4(billing[23] * 0.001);
					billingImport.setPf_exp_rate4(billing[24]);
					
					billingList.add(billingImport);
					
					cnt++;

				} // end while
				
				return billingList;
			}
			
		} catch (Exception e) {
			LOG.error("error", e);
		}
		
		return null;
	}
	
	public List<MeterBilling> setEtypeBillingImportData() {
		
		List<MeterBilling> billingList = new ArrayList<MeterBilling>();
		Map<String, Object> map = null;
		String billingDate = "";
		Double billingValue = null;
		
		try {				
			for (int i = 0; i < result.size(); i++) {
				
				if (!result.containsKey(OBIS.ETYPE_BILLING.getCode() + "-" + i))
					break;

				if (result.containsKey(OBIS.ETYPE_BILLING.getCode() + "-" + i)) {
					map = (Map<String, Object>) result.get(OBIS.ETYPE_BILLING.getCode() + "-" + i);
				}

				if (map == null) {
					break;
				}
				
				if (map.get(OBIS.ETYPE_BILLING.getName() + "-date") != null) {				
					
					Object obj = map.get(OBIS.ETYPE_BILLING.getName() + "-date");
					if (obj != null)
						billingDate = (String) obj;
						LOG.debug("ETYPE_BILLING_DATE[" + (String) obj + "]");				
				}			
							
				if (map.get(OBIS.ETYPE_BILLING.getName()) != null) {		
					Object value = null;
					Double chValue = 0.0;
					
					value = map.get(OBIS.ETYPE_BILLING.getName());				
					if (value instanceof OCTET)
						chValue = (double) DataUtil.getLongToBytes(((OCTET) value).getValue());
					else if (value instanceof Long)
						chValue = ((Long) value).doubleValue();
					else if (value instanceof Float)
						chValue = ((Float) value).doubleValue();
					
					billingValue = chValue;
					LOG.debug("ETYPE_BILLING_VALUE[" + chValue + "]");			
				}				
			}
			
			if(billingValue != null) {
				
				MeterBilling billingImport = new MeterBilling();

				billingImport.setMeter_id(meterID);
				billingImport.setBilling_dt(billingDate);
				billingImport.setActive_imp_tot(billingValue * 0.001);
				
				billingList.add(billingImport);
			}
						
		} catch (Exception e) {
			LOG.error("error", e);
		}
		
		return billingList;
	}
}