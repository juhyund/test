package com.nuri.kepco.generator.util;

import java.util.Date;
import java.util.concurrent.TimeUnit;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.google.common.cache.CacheBuilder;
import com.google.common.cache.CacheLoader;
import com.google.common.cache.LoadingCache;


public class GeneratorId {
	private static final Logger logger = LoggerFactory.getLogger(GeneratorId.class);
	
	private static GeneratorId instance = null;
	private LoadingCache<String, String> generatorMap = null;
	private SnowflakeIDGenerator idGenerator = null;

	public static GeneratorId getInstance() {
		if(instance == null) {
			synchronized (GeneratorId.class) {
				if(instance == null) {
					instance = new GeneratorId();
				}
			}
		}
		
		return instance;
	}
	
	public GeneratorId() {		
		init();
	}
	
	private void init() {
		idGenerator = new SnowflakeIDGenerator(getInitValue());
		
		if(generatorMap == null) {
			generatorMap = CacheBuilder.newBuilder()
					.expireAfterAccess(1, TimeUnit.HOURS)					
					.build(
						new CacheLoader<String, String>() {
							
							@Override
							public String load(String key) throws Exception {
								return String.valueOf(idGenerator.getId());
							}
						}
				);
		}
	}
	
	private long getInitValue() {
		String s = String.valueOf(new Date().getTime());
		String ss = s.substring(s.length() -3, s.length());
		return Integer.parseInt(ss);
	}
	
	public String getId(String deviceId) {
		if(deviceId == null)
				return null;
		
		if(idGenerator != null) {
			while(true) {
				long Id = idGenerator.getId();
				String key = deviceId + Id;
				String value = deviceId + Id;
				
				if(generatorMap.getIfPresent(key) == null) {
					put(key, value);
					return key;
				}
			}
		}
		
		return null;
	}
	
	public String get(String key) {
		try {
			return generatorMap.get(key);
		} catch (Exception e) { }
		
		return null;
	}
	
	public void put(String key, String value) {
		generatorMap.put(key, value);
	}
	
	public void delete(String key) {
		generatorMap.invalidate(key);
	}
	
	public static void main(String[] args) {
		GeneratorId gid = new GeneratorId(); 
		//new GeneratorId().getInstance();
		System.out.println(gid.getId("abc"));
		System.out.println(gid.get("abc"));
		GeneratorId.getInstance().delete("abc");
		System.out.println(GeneratorId.getInstance().get("abc"));
		System.out.println(new GeneratorId().getId("abc"));
		
	}
	
}
