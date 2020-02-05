package com.nuri.emi.fep.parser;

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
import com.nuri.emi.fep.datatype.LPData;
import com.nuri.emi.fep.datatype.MDData;
import com.nuri.emi.fep.parser.DLMSVARIABLE.DLMS_CLASS_ATTR;
import com.nuri.emi.fep.parser.DLMSVARIABLE.OBIS;
import com.nuri.emi.fep.parser.LPChannel.CHANNEL;

public class MDDataParser extends AbstractMDParser {
	
	private static final Logger LOG = LoggerFactory.getLogger(MDDataParser.class);
	
	LinkedHashMap<String, Map<String, Object>> result = new LinkedHashMap<String, Map<String, Object>>();

	MDData mdData = new MDData();

	String customerID = "";
	String modemTime = "";
	String meterTime = "";
	String fwVersion = "";	
	String meterID = "";
	String meterType = "";
	String meterModel = "";
	String billingDate = "";
	
	int dcnt = 0;
	
	public void parseMeterInfo(byte[] frame) throws Exception {
				
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
		
		System.arraycopy(data, pos, DCNT, 0, DCNT.length);
		pos += DCNT.length;
		DataUtil.convertEndian(true, DCNT);
		int dcnt = DataUtil.getIntTo2Byte(DCNT);		
				
		String modemTime = getBCDTime(ITIME);
		
		mdData.setMeterID(meterID);
		mdData.setModemTime(modemTime);
		
		setMeterModel(meterID);
	}

	@Override
	public MDData parser(byte[] frame) throws Exception {

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
			if(_obisCode.equals("0100000102") || _obisCode.equals("0000620101") || _obisCode.equals("0000620103")) {
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
			} else if (dlms.getDlmsHeader().getObis() == DLMSVARIABLE.OBIS.BILLING_DATE) {
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
			} else if (dlmsData != null && !dlmsData.isEmpty()) {
				result.put(obisCode, dlmsData);
			} 
		}
		
		
		setLpData();
	
		return mdData;
	}

	public void setMeterInfo() {

		try {

			Map<String, Object> map = null;
			
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

			map = (Map<String, Object>) result.get(OBIS.BILLING_DATE.getCode());
			if (map != null) {
				Object obj = map.get(OBIS.BILLING_DATE.getName());
				if (obj != null)
					billingDate = (String) obj;
				if (billingDate != null && billingDate.length() != 14) {
					billingDate = billingDate + "00";
				}
				LOG.debug("BILLINGDATE[" + billingDate + "]");
				mdData.setBillingDate(billingDate);
			}
			map = (Map<String, Object>) result.get(OBIS.METER_VERSION.getCode());
			if (map != null) {
				Object obj = map.get(OBIS.METER_VERSION.getName());
				if (obj != null)
					fwVersion = (String) obj;
				LOG.debug("METER_VERSION[" + fwVersion + "]");
			}

		} catch (Exception e) {
			LOG.error("error {}", e);
		}
	}

	public void setLpData() {

		try {

			Map<String, Object> lpMap = null;
			List<LPData> lpDataList = new ArrayList<LPData>();

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

						// 단상 2선식 40(10)A & CHANNEL2 번 결선체결확인인 경우를 제외하고 단위 설정
						LOG.debug("meterType [" + meterType + "] : [" + DLMSVARIABLE.METERMODEL.ET1P2W40A.getName()
								+ "]");
						if (!meterType.equals(DLMSVARIABLE.METERMODEL.ET1P2W40A.getName())) {
							chValue = (chValue) * 0.001;
						}

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

			mdData.setLpDatas(lpDataList);
			Collections.sort(mdData.getLpDatas());

		} catch (Exception e) {
			LOG.error("error {}", e);
		}

	}

	public void setMeterModel(String meter_name) {

		String vendorCd = meter_name.substring(0, 2);
		String modelCd = meter_name.substring(2, 4);

		LOG.debug("setMeterModel vendorCd : [" + vendorCd + "] modelCd : [" + modelCd + "]");

		DLMSVARIABLE.VENDOR vendor = DLMSVARIABLE.VENDOR.getVendor(vendorCd);
		DLMSVARIABLE.METERMODEL model = DLMSVARIABLE.METERMODEL.getMeterModel(modelCd);

		String vendorShortName = (vendor == null) ? "" : vendor.getSname();
		String meterType = (model == null) ? "" : model.getName();

		this.meterModel = vendorShortName + meterType;
		this.meterType = meterType;

		mdData.setMeterModel(meterModel);
		mdData.setMeterType(meterType);
	}
	
	/**
	 * getBCDTime
	 * bcd(7byte) time -> stirng 
	 * @param bcd
	 * @return
	 */
	private String getBCDTime(byte[] bcdTime) {
		
		StringBuffer strBCDTime = new StringBuffer();
		String appender = "";
		for(int i = 0; i < bcdTime.length; i++) {
			
			appender = (i==0) ? "20" : "";
			if(i != 3) {
				strBCDTime.append(appender + Util.frontAppendNStr('0', Integer.toHexString(bcdTime[i]), 2));
			}
		}
			
		return strBCDTime.toString();
	}
}
