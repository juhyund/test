package com.nuri.kepco.fep.saver;

import java.util.List;

import org.eclipse.leshan.json.JsonArrayEntry;
import org.eclipse.leshan.json.JsonRootObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.nuri.kepco.fep.mddata.AbstractMDSaver;
import com.nuri.kepco.fep.mddata.IMeasurementData;
import com.nuri.kepco.fep.parser.ObjectLinkDataParser;
import com.nuri.kepco.model.DeviceInfo;
import com.nuri.kepco.model.DeviceResource;
import com.nuri.kepco.model.dao.DeviceResourceDAO;

@Service
public class ObjectLinkDataSaver extends AbstractMDSaver {
	
	private static final Logger LOG = LoggerFactory.getLogger(ObjectLinkDataSaver.class);
	
	@Autowired
	DeviceResourceDAO deviceResourceDAO;

	@Override
	public boolean save(IMeasurementData md) throws Exception {
		
		ObjectLinkDataParser parser = (ObjectLinkDataParser)md.getMeterDataParser();
		
		List<DeviceResource> deviceResourceList = parser.getDeviceResourceList();
		
		String deviceSerial = md.getDeviceId();
		
		// checkDevice
		checkDevice(deviceSerial, md.getModemTime());
		
		// deviceInfo 
		DeviceInfo deviceInfo = getDeviceInfo();
		
		for (DeviceResource deviceResource : deviceResourceList) {			
			deviceResource.setDevice_id(deviceInfo.getDevice_id());
		}
		
		LOG.debug("DEVICE : {}" ,  deviceResourceList);
		
		deviceResourceDAO.insertAll(deviceResourceList);
		
		return false;
	}
}