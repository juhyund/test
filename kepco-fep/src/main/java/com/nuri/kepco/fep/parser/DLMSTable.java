package com.nuri.kepco.fep.parser;

import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.aimir.util.DataFormat;
import com.aimir.util.DataUtil;
import com.aimir.util.Hex;
import com.nuri.kepco.fep.parser.DLMSVARIABLE.DLMS_CLASS;
import com.nuri.kepco.fep.parser.DLMSVARIABLE.DLMS_CLASS_ATTR;
import com.nuri.kepco.fep.parser.DLMSVARIABLE.DLMS_TAG_TYPE;
import com.nuri.kepco.fep.parser.DLMSVARIABLE.ENERGY_LOAD_PROFILE;
import com.nuri.kepco.fep.parser.DLMSVARIABLE.OBIS;
import com.nuri.kepco.model.MeterInfo;


public class DLMSTable {

	private static final Logger LOG = LoggerFactory.getLogger(DLMSTable.class);
	
	private DLMSHeader dlmsHeader = new DLMSHeader();
	private List<DLMSTag> dlmsTags = new ArrayList<DLMSTag>();
	private MeterInfo meterInfo;

	public DLMSHeader getDlmsHeader() {
		return dlmsHeader;
	}

	public void setDlmsHeader(DLMSHeader dlmsHeader) {
		this.dlmsHeader = dlmsHeader;
	}

	public List<DLMSTag> getDlmsTags() {
		return dlmsTags;
	}

	public void setDlmsTags(List<DLMSTag> dlmsTags) {
		this.dlmsTags = dlmsTags;
	}

	public void addDlmsTag(DLMSTag tag) {
		this.dlmsTags.add(tag);
	}

	public void setObis(String obisCode) {
		this.dlmsHeader.setObis(obisCode);
	}

	public void setClazz(int clazz) {
		this.dlmsHeader.setClazz(clazz);
	}

	public void setAttr(int attr) {
		this.dlmsHeader.setAttr(attr);
	}

	public void setLength(int length) {
		this.dlmsHeader.setLength(length);
	}

	public void setMeter(MeterInfo meterInfo) {
		this.meterInfo = meterInfo;
	}

	public void parseDlmsTag(byte[] data) throws Exception {

		int len = DLMS_TAG_TYPE.Null.getLenth() - 1;
		int pos = 0;
		DLMSTag dlmsTag = null;
		byte[] bx = null;

		while (pos < data.length) {

			LOG.debug("LEN[" + data.length + "] POS[" + pos + "]");
			dlmsTag = new DLMSTag();
			dlmsTag.setTag(data[pos]);
			pos += 1;

			/*
			 * BitString, OctetString, VisibleString 태그에 대해서만 data[1] 바이트를 확장 길이로 사용하고 데이타에
			 * 대한 길이이다.
			 */
			if (data.length > pos) {
				if (dlmsTag.getTag() == DLMS_TAG_TYPE.OctetString || dlmsTag.getTag() == DLMS_TAG_TYPE.VisibleString) {
					len = DataUtil.getIntToByte(data[pos]);
					pos += 1;
				} else if (dlmsTag.getTag() == DLMS_TAG_TYPE.Array || dlmsTag.getTag() == DLMS_TAG_TYPE.Structure) { // INSERT
																														// SP-715
					if ((0x80 & data[pos]) == 0x80) { // higgest bit of the first byte is set if number of items is more
														// than 127
						len = 0x0f & data[pos]; // Lowest 4bit tells how many bytes takes to show the number
						pos += 1;
					} else { // number of items is 127 or less
						len = dlmsTag.getTag().getLenth();
					}
				} else
					len = dlmsTag.getTag().getLenth();
			} else
				continue;

			bx = new byte[len];

			// pos와 data의 길이 합이 data.length를 넘어갈 수도 있기 때문에 비교를 한 후에 arrayindexout 예외가 발생하지
			// 않도록 한다.
			if (pos + len > data.length)
				break;

			System.arraycopy(data, pos, bx, 0, bx.length);
			pos += bx.length;

			dlmsTag.setLength(len);
			dlmsTag.setData(bx);

			LOG.debug(dlmsTag.toString());

			dlmsTags.add(dlmsTag);
		}
	}

	/**
	 * class, attr에 따라 데이타의 개수와 유형이 달라진다.
	 * 
	 * @return
	 */
	public Map<String, Object> getData() {
		Map<String, Object> ret = new LinkedHashMap<String, Object>(16, 0.75f, false);
		DLMS_CLASS clazz = dlmsHeader.getClazz();
		DLMS_CLASS_ATTR attr = dlmsHeader.getAttr();
		OBIS obis = dlmsHeader.getObis();
		LOG.debug("CLAZZ[" + clazz + "] ATTR[" + attr + "] OBIS[" + obis + "] TAG_SIZE[" + dlmsTags.size() + "]");
		switch (clazz) {
		case DATA:
			switch (attr) {
			case DATA_ATTR01:
				if (obis == OBIS.CUSTOMER_ID && dlmsTags.size() != 0) {
					ret.put(OBIS.CUSTOMER_ID.getName(), Hex.decode(dlmsTags.get(0).getOCTET().getValue()));
				}
				if (obis == OBIS.MANUFACTURE_ID && dlmsTags.size() != 0) {
					ret.put(OBIS.MANUFACTURE_ID.getName(), Hex.decode(dlmsTags.get(0).getOCTET().getValue()));
				}
				if (obis == OBIS.METER_VERSION && dlmsTags.size() != 0) {
					ret.put(OBIS.METER_VERSION.getName(), Hex.decode(dlmsTags.get(0).getOCTET().getValue()));
				}
				if (obis == OBIS.HW_VER && dlmsTags.size() != 0) {
					ret.put(OBIS.HW_VER.getName(), Hex.decode(dlmsTags.get(0).getOCTET().getValue()));
				}
				if (obis == OBIS.BILLING_DATE && dlmsTags.size() != 0) {
					byte[] data = dlmsTags.get(0).getOCTET().getValue();
					if (data.length == 12) {
						try {
							String str = getDateTime(data);
							ret.put(OBIS.BILLING_DATE.getName(), str);
						} catch (Exception e) {
							LOG.warn("Exception : {}", e);
						}
					}
				}
			default:
				break;
			}
			break;
		case REGISTER:
			switch (attr) {
			case REGISTER_ATTR02: // value
				if (obis == OBIS.ACTIVEPOWER_CONSTANT && dlmsTags.size() != 0) {
					ret.put(OBIS.ACTIVEPOWER_CONSTANT.getName(), dlmsTags.get(0).getValue());
				}
				if (obis == OBIS.REACTIVEPOWER_CONSTANT && dlmsTags.size() != 0) {
					ret.put(OBIS.REACTIVEPOWER_CONSTANT.getName(), dlmsTags.get(0).getValue());
				}
				if (obis == OBIS.APPRENTPOWER_CONSTANT && dlmsTags.size() != 0) {
					ret.put(OBIS.APPRENTPOWER_CONSTANT.getName(), dlmsTags.get(0).getValue());
				}
				if (obis == OBIS.LP_INTERVAL && dlmsTags.size() != 0) {
					ret.put(OBIS.LP_INTERVAL.getName(), dlmsTags.get(0).getValue());
				}
				break;
			case REGISTER_ATTR03: // scaler_unit
				break;
			default:
				break;
			}
			break;
		case PROFILE_GENERIC:
			switch (attr) {
			case PROFILE_GENERIC_ATTR02: // buffer
			case PROFILE_GENERIC_ATTR03: // Array
				if (dlmsTags.size() == 0)
					break;
				putData(dlmsTags, ret, obis);
				break;
			case PROFILE_GENERIC_ATTR04: // capture period
				if (dlmsTags.size() == 0)
					break;
				break;
			case PROFILE_GENERIC_ATTR07: // entries_in_use
				if (dlmsTags.size() == 0)
					break;
				ret.put("Entry", dlmsTags.get(0).getValue());
				break;
			case PROFILE_GENERIC_ATTR08: // prfile_entries
				if (dlmsTags.size() == 0)
					break;
				ret.put("Entries", dlmsTags.get(0).getValue());
				break;
			default:
				break;
			}
			break;
		case CLOCK:
			if (attr == null)
				break;

			switch (attr) {
			case CLOCK_ATTR02:
				if (obis == OBIS.METER_TIME && dlmsTags.size() != 0) {

					byte[] data = dlmsTags.get(0).getOCTET().getValue();
					if (data.length == 12) {
						try {
							String str = getDateTime(data);
							ret.put(OBIS.METER_TIME.getName(), str);
						} catch (Exception e) {
							LOG.warn("Exception : {}", e);
						}
					}
				}
				
				break;
			default:
				break;
			}
			break;
		case SCRIPT_TABLE:
			break;
		case RELAY_CLASS:
			break;
		case MBUS_CLIENT_CLASS:
			break;
		default:
			break;
		}

		return ret;
	}

	/*
	 * 하나의 OBIS에 여러 개의 태그를 가지는 경우 그 순서에 따라 데이타 유형이 결정된다.
	 */
	/*
	 * 하나의 OBIS에 여러 개의 태그를 가지는 경우 그 순서에 따라 데이타 유형이 결정된다.
	 */
	private void putData(List<DLMSTag> tags, Map<String, Object> ret, OBIS obis) {
		String name = null;
		@SuppressWarnings("unused")
		int channelCount = 0;
		int channelIndex = 1;
		
		if (obis != null) {
			
			if (obis.equals(OBIS.ENERGY_LOAD_PROFILE) 
					|| obis.equals(OBIS.BILLING) 
					|| obis.equals(OBIS.BILLING_REVERSE)) {
				name = "";
				for (DLMSTag tag : tags) {
					if (tag.getTag().equals(DLMS_TAG_TYPE.Structure)) {
						channelIndex = 1;
					} else {
						if (tag.getTag().equals(DLMS_TAG_TYPE.OctetString)) { // Date
							// name = "DateTime";
							name = "DateTime";
						} else if (tag.getTag().equals(DLMS_TAG_TYPE.UINT32)) { // Channel
							name = "Channel[" + channelIndex + "]";
							channelIndex++;
						} else if (tag.getTag().equals(DLMS_TAG_TYPE.UINT16)) { // Channel
							name = "Channel[" + channelIndex + "]";
							channelIndex++;
						} else if (tag.getTag().equals(DLMS_TAG_TYPE.FLOAT32)) { // Channel
							name = "Channel[" + channelIndex + "]";
							channelIndex++;
						} else if (tag.getTag().equals(DLMS_TAG_TYPE.BitString)) { // Status
							name = "Status";
						} else {
						
						}
	
						putData(ret, obis, name, tag);
					}
				}
	
			} else {
				for (int i = 0; i < tags.size(); i++) {
					LOG.debug(obis.getName() + ",tag=" + tags.get(i).getTag().name() + ", value=" + tags.get(i).getValue());
					// name = DLMSVARIABLE.getDataName(obis, i);
					putData(ret, obis, name, tags.get(i));
				}
			}
		}
	}

	private Object putData(Map<String, Object> map, OBIS obis, String dataName, DLMSTag tag) {
		try {
			switch (obis) {
			case ENERGY_LOAD_PROFILE:
				getOBIS_CODE_LOAD_PROFILE(map, dataName, tag);
				break;
			case BILLING:
				getOBIS_CODE_BILLING_PROFILE(map, dataName, tag);
				break;
			case BILLING_REVERSE:
				getOBIS_CODE_BILLING_REVERSE_PROFILE(map, dataName, tag);
				break;			
			}

		} catch (Exception e) {
			e.printStackTrace();
			LOG.error("obis:" + obis + ":dataName:" + dataName + ":tag:" + tag);
		}
		return tag.getValue();
	}

	private void getOBIS_CODE_LOAD_PROFILE(Map<String, Object> map, String dataName, DLMSTag tag) throws Exception {

		if (dataName != null && dataName.startsWith("DateTime")) {
			byte[] data = tag.getData();
			if (data.length == 12) {

				String str = getDateTime(data);
				String key = dataName;

				for (int cnt = 0;; cnt++) {
					key = dataName + "-" + cnt;
					if (!map.containsKey(key)) {
						map.put(key, str);

						LOG.debug("DATA_NAME[" + key + "] VALUE[" + str + "]");

						break;
					}
				}
			}
		} else if (dataName.equals(ENERGY_LOAD_PROFILE.Status.toString())) {
			byte[] data = tag.getData();
			int value = DataUtil.getIntToBytes(data);

			String binaryString = Integer.toBinaryString(value);

			while (binaryString.length() % 8 != 0) {
				binaryString = "0" + binaryString;
			}
			String key = dataName;
			for (int cnt = 0;; cnt++) {
				key = dataName + "-" + cnt;
				if (!map.containsKey(key)) {
					LOG.debug("DATA_NAME[" + key + "] VALUE[" + binaryString + "]");
					map.put(key, binaryString);
					break;
				}
			}
		} else {
			String key = dataName;
			for (int cnt = 0;; cnt++) {
				key = dataName + "-" + cnt;
				if (!map.containsKey(key)) {
					LOG.debug("DATA_NAME[" + key + "] VALUE[" + tag.getValue() + "]");
					map.put(key, tag.getValue());
					break;
				}
			}
		}
	}

	// 현재검침
	private void getOBIS_CODE_BILLING_PROFILE(Map<String, Object> map, String dataName, DLMSTag tag)
			throws Exception {

		String key = dataName;
		for (int cnt = 0;; cnt++) {
			key = dataName + "-" + cnt;
			if (!map.containsKey(key)) {
				LOG.debug("DATA_NAME[" + key + "] VALUE[" + tag.getValue() + "]");
				map.put(key, tag.getValue());
				break;
			}
		}
	}

	// 전월검침
	private void getOBIS_CODE_BILLING_REVERSE_PROFILE(Map<String, Object> map, String dataName, DLMSTag tag)
			throws Exception {

		String key = dataName;
		for (int cnt = 0;; cnt++) {
			key = dataName + "-" + cnt;
			if (!map.containsKey(key)) {
				LOG.debug("DATA_NAME[" + key + "] VALUE[" + tag.getValue() + "]");
				map.put(key, tag.getValue());
				break;
			}
		}
	}

	

	/**
	 * DLMS 12bytes OCTET 시간 포맷 년 : 0,1 월 : 2 일 : 3 시 : 5 분 : 6
	 * 
	 * @param data
	 * @return
	 * @throws Exception
	 */
	private String makeDateTime4week(byte[] data) throws Exception {
		int year = DataFormat.getIntTo2Byte(DataFormat.select(data, 0, 2));
		int month = DataFormat.getIntToByte(data[2]);
		int day = DataFormat.getIntToByte(data[3]);
		int hour = DataFormat.getIntToByte(data[5]);
		int min = DataFormat.getIntToByte(data[6]);

		DecimalFormat df = new DecimalFormat("00");
		String str = ":date=" + year + df.format(month) + df.format(day) + df.format(hour) + df.format(min);

		return str;
	}

	public static String getLP_STATUS(byte[] value) {
		StringBuffer str = new StringBuffer("");
		int byte0 = value[0] & 0xFF;
		for (int i = 0; i < 8; i++) {
			if ((byte0 & (1 << (7 - i))) > 0) {
				str.append(DLMSVARIABLE.LP_STATUS_BIT[i] + ", \n");
			}
		}
		if (byte0 == 0x00) {
			str.append("Valid");
		}
		return str.toString();
	}

	public String getDateTime(byte[] data) throws Exception {

		int year = DataFormat.getIntTo2Byte(DataFormat.select(data, 0, 2));
		int month = DataFormat.getIntToByte(data[2]);
		int day = DataFormat.getIntToByte(data[3]);
		int week = DataFormat.getIntToByte(data[4]);
		int hour = DataFormat.getIntToByte(data[5]);
		int min = DataFormat.getIntToByte(data[6]);

		DecimalFormat ydf = new DecimalFormat("0000");
		DecimalFormat df = new DecimalFormat("00");

		if (year >= 65535) {
			year = 0;
		}
		if (month >= 255)
			month = 0;
		if (day >= 255)
			day = 0;
		if (hour >= 255)
			hour = 0;
		if (min >= 255)
			min = 0;

		String str = ydf.format(year) + df.format(month) + df.format(day) + df.format(hour) + df.format(min);

		LOG.debug("getDateTime[" + str + "]");

		return str;
	}

}