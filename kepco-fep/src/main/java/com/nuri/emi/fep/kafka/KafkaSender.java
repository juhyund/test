package com.nuri.emi.fep.kafka;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.kafka.core.KafkaTemplate;
import org.springframework.messaging.handler.annotation.Payload;
import org.springframework.stereotype.Service;

@Service
public class KafkaSender {

	private static final Logger LOG = LoggerFactory.getLogger(KafkaSender.class);

	@Autowired
	private KafkaTemplate<String, String> kafkaTemplate;

	@Value("${kafka.topic.mddata}")
	private String mdDataTopic;
	
	@Value("${kafka.topic.dpdata}")
	private String dpEventTopic;

	@Value("${kafka.topic.eventdata}")
	private String eventDataTopic;

	public void sendMDData(String message) {
		LOG.info("sending message='{}' to topic='{}'", message, mdDataTopic);
		kafkaTemplate.send(mdDataTopic, message);
	}
	
	public void sendDPEvent(String message) {
		LOG.info("sending message='{}' to topic='{}'", message, dpEventTopic);
		kafkaTemplate.send(dpEventTopic, message);
	}

	public void sendEventData(String message) {
		LOG.info("sending message='{}' to topic='{}'", message, eventDataTopic);
		kafkaTemplate.send(eventDataTopic, message);
	}

	public void send(String message, String topic) {
		LOG.info("sending message='{}' to topic='{}'", message, topic);
		kafkaTemplate.send(topic, message);
	}
	
}