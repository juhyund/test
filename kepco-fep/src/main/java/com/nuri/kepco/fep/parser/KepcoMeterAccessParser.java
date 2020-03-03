package com.nuri.kepco.fep.parser;

import java.util.LinkedHashMap;
import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.aimir.util.DataUtil;
import com.aimir.util.Hex;
import com.nuri.kepco.fep.datatype.MeterAccessResult;
import com.nuri.kepco.fep.parser.DLMSVARIABLE.DLMS_CLASS_ATTR;
import com.nuri.kepco.fep.parser.DLMSVARIABLE.OBIS;

public class KepcoMeterAccessParser {

	private static final Logger LOG = LoggerFactory.getLogger(KepcoMeterAccessParser.class);

	LinkedHashMap<String, Map<String, Object>> result = null;
	
	MeterAccessResult meterAccessResult = null;
	
	public MeterAccessResult parser(byte[] frame, String OBIS, String APDU, Map<Integer, String> meterStatus) throws Exception {
		
		meterAccessResult = new MeterAccessResult();
		result = new LinkedHashMap<String, Map<String, Object>>();
		
		// data parsing
		parserMeterData(frame);
		
		// result msg
		meterAccessResult.setOBIS(OBIS);
		meterAccessResult.setAPDU(APDU);
		meterAccessResult.setResultMsg(getDataResult());
		meterAccessResult.setMeterStatus(meterStatus);
		
		return meterAccessResult;
	}
	
	/**
	 * METER ACCES
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

		LOG.debug("[" + Hex.decode(data) + "]");
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
	}		
	
	public String getDataResult() {
		
		String resultMsg = "";
		
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
				resultMsg += "COSEM_ID(HW_VER) [" + cosem_device_id + "]\n";				
			}

			map = (Map<String, Object>) result.get(OBIS.METER_TIME.getCode());
			if (map != null) {
				Object obj = map.get(OBIS.METER_TIME.getName());
				if (obj != null)
					meterTime = (String) obj;
				if (meterTime != null && meterTime.length() != 14) {
					meterTime = meterTime + "00";
				}
				resultMsg += "METER_TIME[" + meterTime + "]\n";
			}

			map = (Map<String, Object>) result.get(OBIS.MEASUREMENT_DATE.getCode());
			if (map != null) {
				Object obj = map.get(OBIS.MEASUREMENT_DATE.getName());
				if (obj != null)
					billingDay = (String) obj;
								
				resultMsg += "MEASUREMENT_DATE[" + billingDay + "]\n";				
			}
			
			map = (Map<String, Object>) result.get(OBIS.LP_INTERVAL.getCode());
			if (map != null) {
				Object obj = map.get(OBIS.LP_INTERVAL.getName());
				if (obj != null)
					lpInterval = Integer.parseInt(String.valueOf(obj));				
				resultMsg += "LP INTERVAL[" + lpInterval + "]\n";
			}
			
			map = (Map<String, Object>) result.get(OBIS.ACTIVEPOWER_CONSTANT.getCode());
			if (map != null) {
				Object obj = map.get(OBIS.ACTIVEPOWER_CONSTANT.getName());
				
				LOG.debug("ACTIVEPOWER_CONSTANT : {} ", Hex.encode(String.valueOf(obj)));
				if (obj != null)
					acon = Double.parseDouble(String.valueOf(obj));				
				resultMsg += "ACTIVEPOWER_CONSTANT[" + acon + "]\n";
			}
			
			map = (Map<String, Object>) result.get(OBIS.REACTIVEPOWER_CONSTANT.getCode());
			if (map != null) {
				Object obj = map.get(OBIS.REACTIVEPOWER_CONSTANT.getName());
				if (obj != null)
					rcon = Double.parseDouble(String.valueOf(obj));
				LOG.debug("RCON[" + rcon + "]");
			}
			
			map = (Map<String, Object>) result.get(OBIS.APPRENTPOWER_CONSTANT.getCode());
			if (map != null) {
				Object obj = map.get(OBIS.APPRENTPOWER_CONSTANT.getName());
				if (obj != null)
					pcon = Double.parseDouble(String.valueOf(obj));				
				resultMsg += "APPRENTPOWER_CONSTANT[" + pcon + "]\n";
			}
			
			// 양향방
			map = (Map<String, Object>) result.get(OBIS.NET_METERING.getCode());
			if (map != null) {
				Object obj = map.get(OBIS.NET_METERING.getName());
				if (obj != null)
					netMetering = (Integer)obj;
				
				LOG.debug("NET_METERING[" + netMetering + "]");
			}
			
			// 평균전압주기
			map = (Map<String, Object>) result.get(OBIS.AVG_POWER_PERIOD.getCode());
			if (map != null) {
				Object obj = map.get(OBIS.AVG_POWER_PERIOD.getName());
				if (obj != null)
					avgPowerPeriod = (Integer)obj;
				
				resultMsg += "AVG_POWER_PERIOD[" + avgPowerPeriod + "]\n";
			}
			
			LOG.debug("resultMsg : {}", resultMsg);						
			
		} catch (Exception e) {
			LOG.error("error setMeterInfo", e);
		}
		
		return resultMsg;
	}
}