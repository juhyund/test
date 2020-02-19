package com.nuri.kepco.fep.parser;

import java.util.ArrayList;
import java.util.List;

import org.eclipse.leshan.core.node.LwM2mPath;
import org.eclipse.leshan.json.JsonArrayEntry;
import org.eclipse.leshan.json.JsonRootObject;
import org.eclipse.leshan.json.LwM2mJson;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Service;

import com.google.gson.Gson;
import com.nuri.kepco.fep.mddata.DataParser;
import com.nuri.kepco.model.DeviceResource;

@Service
public class ObjectLinkDataParser extends DataParser {

	private static final Logger LOG = LoggerFactory.getLogger(ObjectLinkDataParser.class);

	private List<DeviceResource> deviceResourceList;
	
	@Override
	public void parser(String data) throws Exception {

		Gson gson = new Gson();
		
		deviceResourceList = new ArrayList<DeviceResource>();		
		try {

			JsonRootObject jsonObject = LwM2mJson.fromJsonLwM2m(data);			
			String bn = jsonObject.getBaseName();
			
			for (JsonArrayEntry e : jsonObject.getResourceList()) {
				
				String resourcePath = bn + "/" + e.getName();
				
				LwM2mPath path = new LwM2mPath(resourcePath);				
				DeviceResource resource = new DeviceResource();
				resource.setResource_path(resourcePath);
				resource.setObject_id(path.getObjectId());
				resource.setObject_instance_id(path.getObjectInstanceId());
				resource.setResource_id(path.getResourceId());
				resource.setResource_instance_id(path.getResourceInstanceId());
				resource.setResource_val(e.getResourceValue().toString());
				resource.setReg_id("system");
				resource.setUpdate_id("system");
				
				deviceResourceList.add(resource);
			}			

		} catch (Exception e) {
			LOG.error(e.toString());
		}
	}

	public List<DeviceResource> getDeviceResourceList() {
		return deviceResourceList;
	}
}
