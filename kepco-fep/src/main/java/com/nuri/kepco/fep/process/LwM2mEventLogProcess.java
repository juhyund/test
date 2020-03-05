package com.nuri.kepco.fep.process;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.google.gson.Gson;
import com.nuri.kepco.mongo.model.LwM2mEventLog;
import com.nuri.kepco.mongo.model.dao.LwM2mEventLogDAO;

@Service
public class LwM2mEventLogProcess {

	private static final Logger LOG = LoggerFactory.getLogger(LwM2mEventLogProcess.class);
	
	@Autowired
	LwM2mEventLogDAO lwm2mEventLogDAO;

	/**
	 * process - queue로 부터 수신된 데이터를 처리한다.
	 * 
	 * @param message
	 */
	public void process(String message) {

		Gson gson = new Gson();

		try {
			LwM2mEventLog lwm2mEventLog = new LwM2mEventLog();
			lwm2mEventLog = gson.fromJson(message, LwM2mEventLog.class);
		
			String endpoint = lwm2mEventLog.getEnpoint();
			String saveTime = lwm2mEventLog.getSaveTime();
			String method = lwm2mEventLog.getMethod();
			
			LOG.debug("enpoint : {}, method : {}", endpoint, method);
			
			lwm2mEventLogDAO.equals(lwm2mEventLog);

		} catch (Exception e) {
			LOG.error("error", e);
		}
	}

}
