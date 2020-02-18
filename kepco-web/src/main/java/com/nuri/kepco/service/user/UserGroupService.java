package com.nuri.kepco.service.user;

import com.nuri.kepco.model.GroupInfo;
import com.nuri.kepco.model.dao.UserGroupDAO;

public interface UserGroupService extends UserGroupDAO {

	public GroupInfo getGroupInfoByUserSeq(int user_seq) throws Exception;
}
