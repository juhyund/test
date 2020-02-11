package com.nuri.kepco.model.common;

import java.util.ArrayList;
import java.util.List;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class CommonObj {

	private String searchfield;
	private String searchquery;
	private int limit;
	private int page;
	private int start;
	private List<String> keywordList = new ArrayList<String>();
	private List<OrderByMap> orderByList = new ArrayList<OrderByMap>();
	private String filename;
	private String content;
	private String date_div;
	private String sdate;
	private String edate;
	private String range;

	public String getSearchfield() {
		return searchfield;
	}

	public void setSearchfield(String searchfield) {
		this.searchfield = searchfield;
	}

	public String getSearchquery() {
		return searchquery;
	}

	public void setSearchquery(String searchquery) {
		this.searchquery = searchquery;
	}

	public int getLimit() {
		return limit;
	}

	public void setLimit(int limit) {
		this.limit = limit;
	}

	public int getPage() {
		return page;
	}

	public void setPage(int page) {
		this.page = page;
		this.start = this.limit * (this.page - 1);
	}

	public int getStart() {
		return start;
	}

	public void setStart(int start) {
		this.start = start;
	}

	public List<String> getKeywordList() {
		return keywordList;
	}

	public void setKeywordList(List<String> keywordList) {
		this.keywordList = keywordList;
	}

	public String getFilename() {
		return filename;
	}

	public void setFilename(String filename) {
		this.filename = filename;
	}

	public String getContent() {
		return content;
	}

	public void setContent(String content) {
		this.content = content;
	}

	public String getDate_div() {
		return date_div;
	}

	public void setDate_div(String date_div) {
		this.date_div = date_div;
	}

	public String getSdate() {
		return sdate;
	}

	public void setSdate(String sdate) {
		this.sdate = sdate;
	}

	public String getEdate() {
		return edate;
	}

	public void setEdate(String edate) {
		this.edate = edate;
	}

	public List<OrderByMap> getOrderByList() {
		return orderByList;
	}

	public void setOrderByMap(List<OrderByMap> orderByList) {
		this.orderByList = orderByList;
	}

	public String getRange() {
		return range;
	}

	public void setRange(String range) {
		this.range = range;
	}

}
