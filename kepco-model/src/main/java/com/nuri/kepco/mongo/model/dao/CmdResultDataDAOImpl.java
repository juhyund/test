package com.nuri.kepco.mongo.model.dao;

import java.util.List;

import org.springframework.data.mongodb.core.MongoTemplate;
import org.springframework.data.mongodb.core.query.Criteria;
import org.springframework.data.mongodb.core.query.Query;
import org.springframework.stereotype.Repository;

import com.nuri.kepco.mongo.model.CmdResultData;

@Repository
public class CmdResultDataDAOImpl implements CmdResultDataDAO {

	private final MongoTemplate mongoTemplate;

	public CmdResultDataDAOImpl(MongoTemplate mongoTemplate) {
		this.mongoTemplate = mongoTemplate;
	}

	@Override
	public void add(CmdResultData cmdResultData) throws Exception {
		mongoTemplate.insert(cmdResultData);
	}

	@Override
	public void add(List<CmdResultData> lists) throws Exception {
		mongoTemplate.insertAll(lists);
	}

	@Override
	public long getCount(CmdResultData param) throws Exception {
		Query query = getQuery(param);
		return mongoTemplate.count(query, CmdResultData.class);
	}

	@Override
	public List<CmdResultData> getCmdResultData(CmdResultData param) throws Exception {

		Query query = getQuery(param);
		query.skip(param.getOffset());
		query.limit(param.getRow());
		
		return mongoTemplate.find(query, CmdResultData.class);
	}

	public Query getQuery(CmdResultData param) throws Exception {

		Query query = new Query();

		if (param.getDeviceId() != null) {
			query.addCriteria(Criteria.where("deviceId").is(param.getDeviceId()));
		}

		return query;
	}

}
