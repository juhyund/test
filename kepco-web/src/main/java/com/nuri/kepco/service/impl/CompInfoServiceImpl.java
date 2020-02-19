package com.nuri.kepco.service.impl;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.nuri.kepco.model.dao.CompInfoDAO;
import com.nuri.kepco.service.CompInfoService;
import com.nuri.kepco.model.CompInfo;

@Service
@Transactional
public class CompInfoServiceImpl implements CompInfoService {

	@Autowired
	CompInfoDAO compInfoDAO;


	@Override
	public CompInfo selectOne(CompInfo param) throws Exception {
		return this.compInfoDAO.selectOne(param);
	}

	@Override
	public List<CompInfo> selectList(CompInfo param) throws Exception {
		return this.compInfoDAO.selectList(param);
	}

	@Override
	public int selectCount(CompInfo param) throws Exception {
		return this.compInfoDAO.selectCount(param);
	}

	@Override
	public int insert(CompInfo param) throws Exception {
		return this.compInfoDAO.insert(param);
	}

	@Override
	public int update(CompInfo param) throws Exception {
		return this.compInfoDAO.update(param);
	}

	@Override
	public CompInfo getCompInfoByUser(int user_seq) throws Exception {
		return this.compInfoDAO.getCompInfoByUser(user_seq);
	}

}
