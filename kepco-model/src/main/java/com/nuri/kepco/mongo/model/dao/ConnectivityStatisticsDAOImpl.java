package com.nuri.kepco.mongo.model.dao;

import java.util.List;

import org.springframework.data.mongodb.core.MongoTemplate;
import org.springframework.data.mongodb.core.query.Criteria;
import org.springframework.data.mongodb.core.query.Query;
import org.springframework.stereotype.Repository;

import com.nuri.kepco.mongo.model.ConnectivityStatisticsMonitor;

@Repository
public class ConnectivityStatisticsDAOImpl implements ConnectivityStatisticsMonitorDAO {

	private final MongoTemplate mongoTemplate;

	public ConnectivityStatisticsDAOImpl(MongoTemplate mongoTemplate) {
		this.mongoTemplate = mongoTemplate;
	}

	@Override
	public void add(ConnectivityStatisticsMonitor ConnectivityStatisticsMonitor) throws Exception {
		mongoTemplate.insert(ConnectivityStatisticsMonitor);	
	}
	
	@Override
	public void add(List<ConnectivityStatisticsMonitor> lists) throws Exception {
		mongoTemplate.insertAll(lists);
	}
	
	@Override
	public void save(ConnectivityStatisticsMonitor ConnectivityStatisticsMonitor) throws Exception {
		mongoTemplate.save(ConnectivityStatisticsMonitor);	
	}

	@Override
	public long getCount(ConnectivityStatisticsMonitor param) throws Exception {
		Query query = getQuery(param);
		return mongoTemplate.count(query, ConnectivityStatisticsMonitor.class);
	}

	@Override
	public List<ConnectivityStatisticsMonitor> getConnectivityStatisticsMonitor(ConnectivityStatisticsMonitor param) throws Exception {
		
		Query query = getQuery(param);
		query.skip(param.getOffset());
		query.limit(param.getRow());

		return mongoTemplate.find(query, ConnectivityStatisticsMonitor.class);
	}
	
	public Query getQuery(ConnectivityStatisticsMonitor param) throws Exception {

		Query query = new Query();

		if (param.getDeviceId() != null) {
			query.addCriteria(Criteria.where("deviceId").is(param.getDeviceId()));
		}

		if (param.getDeviceSerial() != null) {
			query.addCriteria(Criteria.where("deviceSerial").is(param.getDeviceSerial()));
		}
		
		if (param.getDeviceStatus() != null) {
			query.addCriteria(Criteria.where("deviceStatus").is(param.getDeviceStatus()));
		}
		
		if (param.getParentBranchId() != null) {
			query.addCriteria(Criteria.where("parentBranchId").is(param.getParentBranchId()));
		}
		
		if (param.getBranchId() != null) {
			query.addCriteria(Criteria.where("branchId").is(param.getBranchId()));
		}

		if (param.getSdate() != null) {
			query.addCriteria(Criteria.where("usageTime").gte(param.getSdate()).lte(param.getEdate()));
		}

		return query;
	}

	
}
