package com.nuri.kepco.service;

import org.json.simple.JSONObject;

public interface UserGroupService extends GenericService {

	JSONObject getGroupInfoByUserSeq(int user_seq) throws Exception;
}
