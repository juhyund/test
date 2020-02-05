package com.nuri.emi.fep.kafka;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.messaging.handler.annotation.Payload;
import org.springframework.stereotype.Service;

//@Service
public class KafkaReceiver {

	private static final Logger LOG = LoggerFactory.getLogger(KafkaReceiver.class);
	
    @KafkaListener(topics = "${kafka.topic.mddata}")
    public void listen(@Payload String message) {    	
        LOG.info("received message='{}'", message);
    }
    
    @KafkaListener(topics = "${kafka.topic.dpdata}")
    public void dpDataListen(@Payload String message) {    	
        LOG.info("received message='{}'", message);
    }
    
    @KafkaListener(topics = "${kafka.topic.eventdata}")
    public void eventDatalisten(@Payload String message) {    	
        LOG.info("received message='{}'", message);
    }
    
    @KafkaListener(topics = "${kafka.topic.lwm2mdata}")
    public void lwm2mDatalisten(@Payload String message) {    	
        LOG.info("received message='{}'", message);
    }
    
    @KafkaListener(topics = "${kafka.topic.objectlinkdata}")
    public void objectlinkDatalisten(@Payload String message) {    	
        LOG.info("received message='{}'", message);
    }
}