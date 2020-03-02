package com.nuri.kepco.util;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.ResponseHandler;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.BasicResponseHandler;
import org.apache.http.impl.client.HttpClientBuilder;
import org.json.simple.JSONObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class HttpClientUtil {

	static Logger logger = LoggerFactory.getLogger(HttpClientUtil.class);
	
	public static JSONObject post(String requestURL, String contents, String tid) throws Exception {

		HttpClient client = HttpClientBuilder.create().build(); // HttpClient 생성
		HttpPost postRequest = new HttpPost(requestURL); //POST 메소드 URL 새성 
		postRequest.setHeader("Accept", "application/json");
		postRequest.setHeader("Connection", "keep-alive");
		postRequest.setHeader("Content-Type", "application/json");

		postRequest.setEntity(new StringEntity(contents)); //json 메시지 입력 

		HttpResponse response = client.execute(postRequest);

		JSONObject json = new JSONObject();
		ResponseHandler<String> handler = new BasicResponseHandler();
		String body = handler.handleResponse(response);
		
		logger.debug(body);
		
		json.put("statusCode", response.getStatusLine().getStatusCode());
		json.put("statusMsg", body);
		json.put("tid", tid);
		
		return json;
	}
}

