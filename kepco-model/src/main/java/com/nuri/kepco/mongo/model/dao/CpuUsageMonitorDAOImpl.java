package com.nuri.kepco.mongo.model.dao;

import java.util.List;

import org.springframework.data.mongodb.core.MongoTemplate;
import org.springframework.data.mongodb.core.query.Criteria;
import org.springframework.data.mongodb.core.query.Query;
import org.springframework.stereotype.Repository;

import com.nuri.kepco.mongo.model.CpuUsageMonitor;

@Repository
public class CpuUsageMonitorDAOImpl implements CpuUsageMonitorDAO {

	private final MongoTemplate mongoTemplate;

	public CpuUsageMonitorDAOImpl(MongoTemplate mongoTemplate) {
		this.mongoTemplate = mongoTemplate;
	}

	@Override
	public void add(CpuUsageMonitor cpuUsageMonitor) throws Exception {
		mongoTemplate.insert(cpuUsageMonitor);
	}

	@Override
	public void add(List<CpuUsageMonitor> lists) throws Exception {
		mongoTemplate.insertAll(lists);
	}

	@Override
	public long getCount(CpuUsageMonitor param) throws Exception {
		Query query = getQuery(param);
		return mongoTemplate.count(query, CpuUsageMonitor.class);
	}

	@Override
	public List<CpuUsageMonitor> getCpuUsageMonitor(CpuUsageMonitor param) throws Exception {

		Query query = getQuery(param);
		query.skip(param.getOffset());
		query.limit(param.getRow());
//		query.limit(10);

		return mongoTemplate.find(query, CpuUsageMonitor.class);
	}

	public Query getQuery(CpuUsageMonitor param) throws Exception {

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
