package com.nuri.kepco.service.user;

import com.nuri.kepco.model.CompInfo;
import com.nuri.kepco.model.dao.CompInfoDAO;

public interface UserCompService extends CompInfoDAO {

	public CompInfo getCompInfoByUser(int user_seq) throws Exception;
}
