package com.nuri.kepco.model.common;

import java.util.List;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class PagingGridReturnObj {

	private List<?> resultgrid;
	private int totalcount;

	// getter & setter
	public List<?> getResultgrid() {
		return resultgrid;
	}

	public void setResultgrid(List<?> resultgrid) {
		this.resultgrid = resultgrid;
	}

	public int getTotalcount() {
		return totalcount;
	}

	public void setTotalcount(int totalcount) {
		this.totalcount = totalcount;
	}
}