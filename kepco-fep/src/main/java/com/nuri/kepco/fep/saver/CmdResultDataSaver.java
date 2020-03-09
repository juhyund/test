package com.nuri.kepco.fep.saver;

import java.util.List;

import org.eclipse.leshan.core.node.LwM2mPath;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.nuri.kepco.fep.mddata.AbstractMDSaver;
import com.nuri.kepco.fep.mddata.IMeasurementData;
import com.nuri.kepco.fep.parser.CmdResultDataParser;
import com.nuri.kepco.fep.parser.KepcoDLMSParser;
import com.nuri.kepco.model.DeviceFwHistory;
import com.nuri.kepco.model.DeviceInfo;
import com.nuri.kepco.model.OperationLog;
import com.nuri.kepco.model.dao.DeviceFwHistoryDAO;
import com.nuri.kepco.model.dao.DeviceInfoDAO;
import com.nuri.kepco.model.dao.OperationLogDAO;
import com.nuri.kepco.mongo.model.CmdResultData;
import com.nuri.kepco.mongo.model.dao.CmdResultDataDAO;

@Service
public class CmdResultDataSaver extends AbstractMDSaver {
	
	private static final Logger LOG = LoggerFactory.getLogger(CmdResultDataSaver.class);
	
	private static final Integer FIRMWARE_OBJECT_ID = 5;
	
	@Autowired
	CmdResultDataDAO cmdResultDataDAO;
	
	@Autowired
	OperationLogDAO operationLogDAO;
	
	@Autowired
	DeviceFwHistoryDAO deviceFwHistoryDAO;
	
	@Autowired
	DeviceInfoDAO deviceInfoDAO;
	
	@Override
	public boolean save(IMeasurementData md) throws Exception {
		
		CmdResultDataParser parser = (CmdResultDataParser)md.getMeterDataParser();
		
		List<CmdResultData> list = parser.getCmdResultDataList();
		
		// save to mongodb
		saveCmdResultData(list);
		
		// save to mariadb
		saveOperationLog(list);
		
		// save to mariadb (fw history)
		// fimware write 또는 execute 실행에 대한 응답 일자만 저장!
		saveFirmwareHistoryLog(list);
		
		return true;
	}
	
	/**
	 * 
	 * @param list
	 */
	private void saveCmdResultData(List<CmdResultData> list) {
		
		try {
			if(list != null) {
				if(list.size() > 0) { cmdResultDataDAO.add(list); }
			}
		} catch(Exception e) {
			LOG.error("error", e);
		}
		
	}
	
	/**
	 * 
	 * @param list
	 */
	private int saveOperationLog(List<CmdResultData> list) {
		int result = 0;
		try {
			
			for(CmdResultData data : list) {
				
				boolean isInsert = false;
				
				LwM2mPath path = new LwM2mPath(data.getResource());
				
				DeviceInfo deviceInfo = deviceInfoDAO.selectByDeviceSerial(data.getDeviceId());
				
				// tid로 검색하여 operationLog가 있는지 확인한다.
				OperationLog operationLog = operationLogDAO.selectByTID(data.getTid());
				
				if(operationLog == null) { // 없으면 insert 
					isInsert = true;
					operationLog = new OperationLog();
					operationLog.setDevice_id(deviceInfo.getDevice_id()); // 단말아이디
					operationLog.setRequest_dt(data.getResultTime()); // 요청일시 
					operationLog.setTid(data.getTid());
				}				
				
				operationLog.setObject_id(path.getObjectId());
				operationLog.setObject_instance_id(path.getObjectInstanceId());
				operationLog.setResource_id(path.getResourceId());
				operationLog.setResource_instance_id(path.getResourceInstanceId());				
				operationLog.setFormat(data.getFormat());
				operationLog.setMethod(data.getMethod());
				operationLog.setPayload(data.getPayload());
				operationLog.setMid(data.getMid());
				operationLog.setToken(data.getToken());
				operationLog.setResult_dt(data.getResultTime());
				
				
				if(data.getResult()) {
					operationLog.setResult(1); //true
				} else {
					operationLog.setResult(0); //false
				}
				
				LOG.debug("operationLog :{}", operationLog);
				
				if(isInsert) {
					result += operationLogDAO.insert(operationLog);
				} else {
					result += operationLogDAO.update(operationLog);
				}				
			}
			
		} catch(Exception e) {
			LOG.error("error", e);
		}
		
		return result;		
	}
	
	/**
	 * saveFirmwareHistoryLog
	 * @param list
	 * @return
	 */
	private int saveFirmwareHistoryLog(List<CmdResultData> list) {
		int result = 0;
		try {
			
			for(CmdResultData data : list) { // 실행에 대한 응답 일자를 업데이트 한다.
				
				LwM2mPath path = new LwM2mPath(data.getResource());
				
				if(path.getObjectId().equals(FIRMWARE_OBJECT_ID)) {
					
					// tid로 검색하여 deviceFwHistory가 있는지 확인한다.
					DeviceFwHistory deviceFwHistory = deviceFwHistoryDAO.selectByTid(data.getTid());
					
					if(deviceFwHistory != null) { // null이 아닌 경우 update						
						deviceFwHistory.setResult_dt(data.getResultTime());
						result += deviceFwHistoryDAO.update(deviceFwHistory);
					}
				}
			}
			
		} catch(Exception e) {
			LOG.error("error", e);
		}
		
		return result;		
	}
}
