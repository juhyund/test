package com.keymng.restapi.repository;

import java.util.List;

import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.repository.query.Param;

import com.keymng.restapi.model.Authorize;

/**
 * 
 * @author : shinh5
 * @Date   : 2019. 3. 13.
 * @Version: 키정보 입출력 제공(extends CrudRepository in JpaRepository)
 */
public interface KeyinfoRepository extends CrudRepository<Authorize, String>{
	List<Authorize> findAll();

	// Customer Query
	@Query(nativeQuery = true, value =
			"INSET INTO TAUTHORIZE (CALLING_ID,SYS_TITLE,FEP_KEY,NMS_KEY,CREATE_DT) VALUES " 
			+ " ( :calling_id, :sys_title, :fep_key, :nms_key, to_char(sysdate, 'yyyymmddhh24miss') ) "
	)void putAuthKey(String calling_id, String sys_title, String fep_key, String nms_key);
	
	@Query("SELECT COUNT(*) FROM Authorize WHERE CALLING_ID = :calling_id "
	)Long isExistByCallind(@Param("calling_id") String calling_id);
	
	@Query("SELECT a FROM Authorize a WHERE a.Calling_id = :calling_id "
	)List<Authorize> getAuthByCallId(@Param("calling_id") String calling_id);
	
}
