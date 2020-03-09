package com.nuri.kepco.fep.kafka;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.messaging.handler.annotation.Payload;
import org.springframework.stereotype.Service;

import com.nuri.kepco.fep.process.CmdResultDataProcess;
import com.nuri.kepco.fep.process.LwM2mEventLogProcess;
import com.nuri.kepco.fep.process.MDDataProcess;

@Service
public class KafkaReceiver {

	private static final Logger LOG = LoggerFactory.getLogger(KafkaReceiver.class);
	
	@Autowired
	MDDataProcess mdDataProcess;
	
	@Autowired
	CmdResultDataProcess cmdResultProcess;
	
	@Autowired
	LwM2mEventLogProcess lwM2mEventLogProcess;
	
	// command 요청에 대한 응답 처리
    @KafkaListener(topics = "${kafka.topic.mddata}")
    public void listen(@Payload String message) {    	
    	cmdResultProcess.process(message);
    	mdDataProcess.process(message);
    }
    
    @KafkaListener(topics = "${kafka.topic.dpdata}")
    public void dpDataListen(@Payload String message) {    	
    	mdDataProcess.process(message);
    }
    
    @KafkaListener(topics = "${kafka.topic.eventdata}")
    public void eventDatalisten(@Payload String message) {   
    	LOG.debug("message : {}", message);
    	lwM2mEventLogProcess.process(message);
    }
    
    @KafkaListener(topics = "${kafka.topic.objectlinkdata}")
    public void objectlinkDatalisten(@Payload String message) {    	
        mdDataProcess.process(message);
    }
    
    @KafkaListener(topics = "${kafka.topic.notifydata}")
    public void notifyDatalisten(@Payload String message) {    	
    	mdDataProcess.process(message);
    }
}