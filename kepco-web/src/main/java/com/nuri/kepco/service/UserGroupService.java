package com.nuri.kepco.service;

import com.nuri.kepco.model.GroupInfo;
import com.nuri.kepco.model.UserGroup;
import com.nuri.kepco.model.dao.GenericDAO;

public interface UserGroupService extends GenericDAO<UserGroup> {

	GroupInfo getGroupInfoByUserSeq(int user_seq) throws Exception;
}
