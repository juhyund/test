package com.nuri.kepco.mongo.model.dao;

import java.util.List;

import org.springframework.data.mongodb.core.MongoTemplate;
import org.springframework.data.mongodb.core.query.Criteria;
import org.springframework.data.mongodb.core.query.Query;
import org.springframework.stereotype.Repository;

import com.nuri.kepco.mongo.model.RamUsageMonitor;

@Repository
public class RamUsageMonitorDAOImpl implements RamUsageMonitorDAO {

	private final MongoTemplate mongoTemplate;

	public RamUsageMonitorDAOImpl(MongoTemplate mongoTemplate) {
		this.mongoTemplate = mongoTemplate;
	}

	@Override
	public void add(RamUsageMonitor ramUsageMonitor) throws Exception {
		mongoTemplate.insert(ramUsageMonitor);
	}

	@Override
	public void add(List<RamUsageMonitor> lists) throws Exception {
		mongoTemplate.insertAll(lists);
	}

	@Override
	public long getCount(RamUsageMonitor param) throws Exception {
		Query query = getQuery(param);
		return mongoTemplate.count(query, RamUsageMonitor.class);
	}

	@Override
	public List<RamUsageMonitor> getRamUsageMonitor(RamUsageMonitor param) throws Exception {

		Query query = getQuery(param);
		query.skip(param.getOffset());
		query.limit(param.getRow());
//		query.limit(10);

		return mongoTemplate.find(query, RamUsageMonitor.class);
	}

	public Query getQuery(RamUsageMonitor param) throws Exception {

		Query query = new Query();

		if (param.getDeviceId() != null) {
			query.addCriteria(Criteria.where("deviceId").is(param.getDeviceId()));
		}

		if (param.getDeviceSerial() != null) {
			query.addCriteria(Criteria.where("deviceSerial").is(param.getDeviceSerial()));
		}

		if (param.getSdate() != null) {
			query.addCriteria(Criteria.where("usageTime").gte(param.getSdate()).lte(param.getEdate()));
		}

		return query;
	}

}
