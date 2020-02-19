package com.nuri.kepco.service;

import org.json.JSONObject;

public interface UserGroupService extends GenericService {

	JSONObject getGroupInfoByUserSeq(int user_seq) throws Exception;
}
