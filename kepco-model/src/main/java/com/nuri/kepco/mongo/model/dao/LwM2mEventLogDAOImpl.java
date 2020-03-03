package com.nuri.kepco.mongo.model.dao;

import java.util.List;

import org.springframework.data.mongodb.core.MongoTemplate;
import org.springframework.data.mongodb.core.query.Criteria;
import org.springframework.data.mongodb.core.query.Query;
import org.springframework.stereotype.Repository;

import com.nuri.kepco.mongo.model.CmdResultData;
import com.nuri.kepco.mongo.model.ConnectivityMonitor;
import com.nuri.kepco.mongo.model.LwM2mEventLog;
import com.nuri.kepco.mongo.model.RamUsageMonitor;

@Repository
public class LwM2mEventLogDAOImpl implements LwM2mEventLogDAO {

	private final MongoTemplate mongoTemplate;

	public LwM2mEventLogDAOImpl(MongoTemplate mongoTemplate) {
		this.mongoTemplate = mongoTemplate;
	}

	@Override
	public void add(LwM2mEventLog lwM2mEventLog) throws Exception {
		mongoTemplate.insert(lwM2mEventLog);
	}

	@Override
	public void add(List<LwM2mEventLog> lists) throws Exception {
		mongoTemplate.insert(lists);
	}

	@Override
	public long getCount(LwM2mEventLog param) throws Exception {
		Query query = getQuery(param);
		return mongoTemplate.count(query, LwM2mEventLog.class);
	}
	
	public Query getQuery(LwM2mEventLog param) throws Exception {

		Query query = new Query();

		if (param.getEnpoint() != null) {
			query.addCriteria(Criteria.where("endpoint").is(param.getEnpoint()));
		}

		return query;
	}

}
