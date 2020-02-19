package com.nuri.kepco.service;

import com.nuri.kepco.model.CompInfo;
import com.nuri.kepco.model.dao.GenericDAO;

public interface CompInfoService extends GenericDAO<CompInfo> {

	CompInfo getCompInfoByUser(int user_seq) throws Exception;
}
