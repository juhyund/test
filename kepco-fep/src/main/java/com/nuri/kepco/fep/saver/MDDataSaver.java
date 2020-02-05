package com.nuri.kepco.fep.saver;

import java.util.ArrayList;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.nuri.kepco.fep.datatype.LPData;
import com.nuri.kepco.fep.datatype.MDData;
import com.nuri.kepco.model.MeterValue;
import com.nuri.kepco.model.dao.MeterValueDAO;

@Service
public class MDDataSaver extends AbstractMDSaver {
	
	@Autowired
	MeterValueDAO meterValueDAO;
	
	private String meter_serial;
	private String meter_id;
	
	
	@Override
	public void save(MDData mddata) {
		
		this.meter_serial = mddata.getMeterID();		
		
		// check meterInfo
		this.checkMeter(meter_serial);
		
		if(this.getMeter() != null) {			
			
			this.meter_id = this.getMeter().getMeter_id();
			
			// lp save
			int lpResult = this.saveLpData(mddata.getLpDatas());
		}
	}

	@Override
	public int saveLpData(List<LPData> lpDatas) {
		
		List<MeterValue> meterValues = new ArrayList<MeterValue>();
		
		for (LPData lpData : lpDatas) {
			
			MeterValue lp = new MeterValue();
			
			lp.setMeter_id(meter_id);
			lp.setRead_dt(lp.getRead_dt());
			lp.setChannel(lpData.getChannel());
			lp.setMeter_value(lpData.getValue());
			lp.setSect_meter_value(lpData.getValue());
			
			meterValues.add(lp);
		} 
		
		return this.meterValueDAO.insertAll(meterValues);
	}
}