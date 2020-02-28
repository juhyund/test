package com.nuri.kepco.mongo.model.dao;

import java.util.List;

import org.springframework.data.mongodb.core.MongoTemplate;
import org.springframework.data.mongodb.core.query.Criteria;
import org.springframework.data.mongodb.core.query.Query;
import org.springframework.stereotype.Repository;

import com.nuri.kepco.mongo.model.ConnectivityMonitor;

@Repository
public class ConnectivityMonitorDAOImpl implements ConnectivityMonitorDAO {

	private final MongoTemplate mongoTemplate;

	public ConnectivityMonitorDAOImpl(MongoTemplate mongoTemplate) {
		this.mongoTemplate = mongoTemplate;
	}

	@Override
	public void add(ConnectivityMonitor connectivityMonitor) throws Exception {
		mongoTemplate.insert(connectivityMonitor);	
	}

	@Override
	public void add(List<ConnectivityMonitor> lists) throws Exception {
		mongoTemplate.insertAll(lists);
	}

	@Override
	public long getCount(ConnectivityMonitor param) throws Exception {
		Query query = getQuery(param);
		return mongoTemplate.count(query, ConnectivityMonitor.class);
	}

	@Override
	public List<ConnectivityMonitor> getConnectivityMonitor(ConnectivityMonitor param) throws Exception {
		
		Query query = getQuery(param);
		query.skip(param.getOffset());
//		query.limit(param.getRow());
		query.limit(10);

		return mongoTemplate.find(query, ConnectivityMonitor.class);
	}
	
	public Query getQuery(ConnectivityMonitor param) throws Exception {

		Query query = new Query();

		if (param.getDeviceId() != null) {
			query.addCriteria(Criteria.where("deviceId").is(param.getDeviceId()));
		}

		if (param.getDeviceSerial() != null) {
			query.addCriteria(Criteria.where("deviceSerial").is(param.getDeviceSerial()));
		}

		if (param.getSdate() != null) {
			query.addCriteria(Criteria.where("insertDt").gte(param.getSdate()).lte(param.getEdate()));
		}

		return query;
	}
}
