package com.nuri.kepco.util;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.ResponseHandler;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.client.methods.HttpPut;
import org.apache.http.client.methods.HttpDelete;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.BasicResponseHandler;
import org.apache.http.impl.client.HttpClientBuilder;
import org.json.simple.JSONObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class HttpClientUtil {

	static Logger logger = LoggerFactory.getLogger(HttpClientUtil.class);
	
	public static JSONObject send(String requestURL, String contents, String method) throws Exception {

		HttpClient client = HttpClientBuilder.create().build(); // HttpClient 생성
		HttpResponse response = null;
		logger.debug("requestURL: " + requestURL + ", contents: " + contents + ", method: " + method);
		
		if("Read".equals(method) || "Discover".equals(method)) {
			HttpGet getRequest = new HttpGet(requestURL);
			getRequest.setHeader("Accept", "application/json");
			getRequest.setHeader("Content-Type", "application/json");

			response = client.execute(getRequest);
			
		} else if ("Execute".equals(method) || "Observe".equals(method)
				|| "Firmware".equals(method) || "coapping".equals(method)) {

			HttpPost postRequest = new HttpPost(requestURL); 
			postRequest.setHeader("Accept", "application/json");
			postRequest.setHeader("Content-Type", "application/json");

			postRequest.setEntity(new StringEntity(contents)); 

			response = client.execute(postRequest);

		} else if ("Write".equals(method) || "WriteAttribute".equals(method)) {
			
			HttpPut putRequest = new HttpPut(requestURL);
			putRequest.setHeader("Accept", "application/json");
			putRequest.setHeader("Content-type", "application/json");
			
			putRequest.setEntity(new StringEntity(contents));

			response = client.execute(putRequest);

		} else if ("Delete".equals(method) || "observeCancel".equals(method)) {
			HttpDelete deleteRequest = new HttpDelete(requestURL);
			deleteRequest.setHeader("Accept", "application/json");
			deleteRequest.setHeader("Content-Type", "application/json");

			response = client.execute(deleteRequest);

		} else {
			throw new Exception("Undefined method[" + method + "]");
		}

		JSONObject json = new JSONObject();
		ResponseHandler<String> handler = new BasicResponseHandler();
		int statusCode = response.getStatusLine().getStatusCode();
		String body = handler.handleResponse(response);
		
		logger.debug("StatusCode: " + statusCode + ", result body: " + body);
		
		json.put("statusCode", statusCode);
		json.put("statusMsg", body);
		
		return json;
	}
}

