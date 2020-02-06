package com.nuri.kepco.fep.saver;

import java.util.ArrayList;
import java.util.List;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.nuri.kepco.fep.datatype.LPData;
import com.nuri.kepco.fep.datatype.MDData;
import com.nuri.kepco.fep.mddata.AbstractMDSaver;
import com.nuri.kepco.fep.mddata.IMeasurementData;
import com.nuri.kepco.fep.mddata.MeterDataParser;
import com.nuri.kepco.fep.parser.KepcoMDDataParser;
import com.nuri.kepco.model.MeterInfo;
import com.nuri.kepco.model.MeterValue;
import com.nuri.kepco.model.dao.MeterValueDAO;

@Service
public class KepcoMDDataSaver extends AbstractMDSaver {
	
	private static final Logger LOG = LoggerFactory.getLogger(KepcoMDDataParser.class);
	
	@Autowired
	MeterValueDAO meterValueDAO;
		
	@Override
	public boolean save(IMeasurementData md) throws Exception {
		
		KepcoMDDataParser parser = (KepcoMDDataParser)md.getMeterDataParser();		
		List<MDData> mdList = parser.getMDList();
		
		String deviceSerial = md.getDeviceId();
		
		// checkDevice
		checkDevice(deviceSerial);
		
		if(getDeviceInfo() != null) {
				
			for (MDData mdData : mdList) {
				
				// 0. check meter
				checkMeter(mdData);
				
				if(mdData.getMeterInfo() != null) {
					// 1. save lp
					saveLpData(mdData);
				}
			}
		}
		
		return false;
	}
	
	/**
	 * saveLpData
	 * @param mdData
	 * @return
	 */
	public int saveLpData(MDData mdData) {
		
		List<MeterValue> meterValues = new ArrayList<MeterValue>();
		List<LPData> lpDatas = mdData.getLpDatas();
		
		MeterInfo meterInfo = mdData.getMeterInfo();
		
		for (LPData lpData : lpDatas) {
			
			MeterValue lp = new MeterValue();
			
			lp.setMeter_id(meterInfo.getMeter_id());
			lp.setRead_dt(lpData.getRead_dt());
			lp.setChannel(lpData.getChannel());
			lp.setMeter_value(lpData.getValue());
			lp.setSect_meter_value(lpData.getValue());
			
			meterValues.add(lp);
		}
		
		return this.meterValueDAO.insertAll(meterValues);
	}

}