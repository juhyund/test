/**
 * Created by hyunhee on 2019. 7. 3.
 */


/**
 * AG-GRID 정의.
 * @param gridDivId : grid가 적용될 div 태그의 id 값.
 * @param columnDefs : grid 컬럼 정의 객체(array)
 * @param autoResizable : div 영역 내 자동 사이즈 조절 유무. 
 * @returns
 */
let grid_key = "Yesinsoft,_Inc._on_behalf_of_NURI_Telecom_Co.,_Ltd._MultiApp_1Devs25_September_2020__MTYwMDk4ODQwMDAwMA==9b1e8d92b0a4b8000a23bef3508ba47e";
agGrid.LicenseManager.setLicenseKey(grid_key);


var DataGrid = function(gridDivId, columnDefs, autoResizable, height){
		DataGrid(gridDivId, columnDefs, autoResizable, height, false);
}

var DataGrid = function(gridDivId, columnDefs, autoResizable, height, useRowClickEvent){
	var _this = this;
	/* grid 영역 정의 */
    this.gridDiv = gridDivId;
    /* grid option 정의  */
    this.getColumnDefs = function(){ // param 추가. gridoption
    	var gridOpts = CommonGrid.getDefaultGridOpt(columnDefs, autoResizable, height,useRowClickEvent);
    	return gridOpts;
    };
	this.gridOps = null;
	/* 모든 column 확인 가능하도록 size 조정	 */
	this.sizeToFit = function(){ 
		_this.gridOpts.api.sizeColumnsToFit();
	};
	/*  window size가 변경되었을 경우 자동 조정.*/
	this.onGridSizeChanged = function(){
		_this.gridOpts.api.onGridSizeChanged();
	};
	/* 설정한 width대로 column 확인. 넘는 경우 scroll.*/
	this.autoSizeAll = function(){
		var allColumnIds = [];
		_this.gridOpts.columnApi.getAllColumns().forEach(function(column) {
	        allColumnIds.push(column.colId);
	    });
		_this.gridOpts.columnApi.autoSizeColumns(allColumnIds);
	};
	/* show overlay loading message : 조회 전의 message로 셋팅.*/
	this.showOverlayDefault = function(){
		_this.gridOpts.api.showLoadingOverlay();
	};
	/* show overlay no rows message : no rows to show*/
	this.showNoRows = function(){
		_this.gridOpts.api.showNoRowsOverlay();
	};
	this.hideOverlay = function(){
		_this.gridOpts.api.hideOverlay();
	};
	/* excel export 기능 */
	this.onBtExport = function(option){
		_this.gridOpts.api.exportDataAsExcel(option);
	};
	/* grid option 적용 및 data setting. */
	this.makeGrid = function(){
		_this.gridOpts = _this.getColumnDefs();
		CommonGrid.makeGridCommon(_this.gridDiv, _this.gridOpts)
	};
	this.setData = function(data){
		CommonGrid.setRowData(_this.gridOpts, data);
	};
	/* 선택된 row 반환 */
	this.getSelectedRow = function(){
		return _this.gridOpts.api.getSelectedRows();
	};
};
/**
 *  공통 그리드 option
 * 
 */
var CommonGrid = {	
	/*,defaultBlank : "-"*/
	/* 칼럼정의 값으로 기본 grid option을 생성. */      
    getDefaultGridOpt : function(pColumnDefs, autoResizable, height,useRowClickEvent) {
    	//onclick 있는게 default
    	var suppressRowClickSelection = false;
    	var rowClickEvent = onRowClicked;
    	
    	if(useRowClickEvent == false){
    		suppressRowClickSelection = true;
    		rowClickEvent = null;
    	}
        return {
        	defaultColDef: {
				resizable: true
				,sortable: false
				,pagination: true
		    },
		    columnDefs: pColumnDefs,
		    //overlayLoadingTemplate: '<span class="ag-overlay-loading-center ag-overlay-loading-custom">'+ this.defaultMsg +'</span>',
		    //overlayNoRowsTemplate: '<span class="ag-overlay-no-rows-custom">'+ this.noRowsToShowMsg +'</span>',
            rowSelection: 'multiple', /* 'single' or 'multiple',*/
            enableRangeSelection: true,
            suppressRowClickSelection: suppressRowClickSelection,
            onRowClicked :rowClickEvent,
            suppressHorizontalScroll: false,
            // animateRows: true,
            domLayout: height,
           getRowStyle: function (param) { // row style 지정.
                if (param.node.rowPinned) { 
                    return {'font-weight': 'bold', background: '#dddddd'};
                }
                return {'text-align': 'center'};
            },
            getRowHeight: function(param) {
                if (param.node.rowPinned) {
                    return 30;
                }
                return 30;
            },
            onGridReady: function(params) {
            	if(autoResizable){
            		params.api.sizeColumnsToFit();
            	}
            },
            // 창 크기 변경 되었을 때 이벤트 
            onGridSizeChanged: function(params) {
            	if(autoResizable){
            		params.api.sizeColumnsToFit();
            	}
            },
            debug: false
        };
    }
    // 그리드 값 넣기 
    ,makeGridCommon : function (gridDiv, pGridOpts, rowData){
        $('#'+gridDiv).children().remove();
        var eGridDiv = document.querySelector('#'+gridDiv);
        new agGrid.Grid(eGridDiv, pGridOpts);
    }
    ,setRowData: function(pGridOpts, rowData){
    	pGridOpts.api.setRowData(rowData);
    }
}

/**
 * ag-grid cell style 및 column
 *
 */
const cellStyleComm =  {
	fontSize: '1em', 
	paddingLeft: '8px', 
	paddingRight: '8px',
}

const cellStyleCenter = {
	textAlign: 'center',
	fontSize: '1em',
	paddingLeft: '8px', 
	paddingRight: '8px',
}

const cellStyleAvg={
	fontSize: '1em', 
	fontWeight: 600,
	paddingLeft: '8px', 
	paddingRight: '8px',
	backgroundColor: '#e6edfd47'
	/*,width: 130*/
}

var getDateColumn = function(header_name, _width){
	return {
		headerName: header_name,
		field: "date",
		width: _width,
		suppressSizeToFit: true,
		pinned: 'left',
		sortable: true,
		cellStyle: cellStyleCenter,
		headerClass:"ag-center-header",
	}
}

var getNumericColumn = function(header_name, _field, _style, _width){
	return {
		headerName: header_name,
		field: _field,
		cellStyle: _style,
		width: _width,
		type: 'numericColumn',
		headerClass:"ag-center-header"
		/* ,editable: true */ // 해당 cell data는 편집됨
	}
}

/**
 * paging
 * @param totalData
 * @param dataPerPage
 * @param pageCount
 * @param currentPage
 * @returns
 */
function gridPage(totalData, dataPerPage, pageCount, currentPage){
	$("#grid-page").show();
    
	var totalPage = Math.ceil(totalData/dataPerPage); // 총 페이지 수
	if(totalPage < pageCount){
		pageCount=totalPage;
	}
	var pageGroup = Math.ceil(currentPage/pageCount); // 페이지 그룹
    
    var last = pageGroup * pageCount; // 화면에 보여질 마지막 페이지 번호
    if(last > totalPage)
        last = totalPage;
    var first = last - (pageCount-1);    // 화면에 보여질 첫번째 페이지 번호 
    var next = last+1;
    var prev = first-1;
    
    /* console.log("	last : " + last);
    console.log("	first : " + first);
    console.log("	next : " + next);
    console.log("	prev : " + prev); */

    var html = "<li id='prev' class='page-item disabled'><a href='#' title='이전 페이지로 이동'>&lt;&lt;</a></li>";
    
    for(var i=first; i <= last; i++){
    	if(i==currentPage) {
            html += "<li id="+ i +" class='page-item'><a class='page-link btn-outline btn-primary active' href='#'> "+ i +"</a></li> ";
    	}else{
            html += "<li id="+ i +" class='page-item'><a class='page-link btn-outline btn-primary' href='#'> "+ i +"</a></li> ";
    	}
    }
    
    html += "<li id='next' class='page-item disabled'><a class='page-link' href='#' title='다음 페이지로 이동'>&gt;&gt;</a></li>";
    
    $("#grid-page ul").html(html);    // 페이지 목록 생성

    if(prev > 0 ){
    	$("#prev").removeClass('disabled');
    	
    }
    if(last < totalPage){
    	$("#next").removeClass('disabled');
    }
    
    $('#cur_page_num').html(currentPage+"/"+totalPage + " page (총 " + totalData + "건)");
    
	$("#pagination li:not(.disabled)").click(function(){
		var $item = $(this);
        var $id = $item.attr("id");
        var selectedPage = $item.text();

        if($id == "next")    selectedPage = next;
        if($id == "prev")    selectedPage = prev;
        
        //새로운 페이지 정보 로딩
        $("#page").val(selectedPage);
        ajaxSearchForm();
        
		
    }); 
}

/*
 * grid row select event
 */
var onRowClicked = function (event) {
	//호출한 jsp에서 구현필요
};


/*
 * formatter
 * 사용법 : columnDefs생성 시  적용.
 * 
 */
function numberFormatter(params) {
	if(typeof params.value =="number"){
	    return params.value.format(4);
	  }else{
	    return "";
	  }
}
function obisListFormatter(params) {
	
	console.log(params);
	 return params.value.toString().replace(",", "\n\r");
}

