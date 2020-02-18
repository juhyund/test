/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : PrdInfoList.js
* @Author : kyunghee.yoon
* @Date : 2015.11.06
**************************************/
Ext.require([
	'Ext.tree.*',
	'Ext.form.field.Text',
	'Ext.resizer.Splitter',
	'Ext.grid.Panel',
	'Ext.grid.column.RowNumberer'
]);

Ext.onReady(function(){
	var toDate = Ext.Date.format(new Date(),'Ymd');
	var url;
	var arr_prd_stock_idx = "";
	
    Ext.define('DataThread', {
        extend: 'Ext.data.Model',
        fields: [
            'prd_no'
            , 'prd_serial_no'
            , 'prd_cate1_nm'
			, 'prd_cate2_nm'
			, 'prd_nm'
			, 'mat_no'
			, 'mat_serial_no'
			, 'mat_nm'
			, 'mat_desc'
			, 'mc_cost'
			, 'as_n_qty'
			, 'as_n_amt'
			, 'as_y_qty'
			, 'as_y_amt'
			, 'as_t_qty'			
			, 'as_t_amt'
			, 'order_n_qty'
			, 'order_n_amt'
			, 'order_y_qty'
			, 'order_y_amt'
			, 'order_t_qty'
			, 'order_t_amt'
			, 'go_n_qty'
			, 'go_n_amt'
			, 'go_y_qty'
			, 'go_y_amt'
			, 'go_t_qty'
			, 'go_t_amt'
			, 'tot_n_qty'
			, 'tot_n_amt'
			, 'tot_y_qty'
			, 'tot_y_amt'
			, 'tot_t_qty'
			, 'tot_t_amt'
        ]
    });
	
    store = Ext.create('Ext.data.Store', {
        pageSize: 30,
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxPrdReceivePayList',
            reader: {
            	root: 'result'
            },
            simpleSortMode: true
        },
        sorters: [{
            property: 'insert_dt',
            direction: 'DESC'
        }]
    });

    var columns = [
        {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
			dataIndex : 'prd_cate1_nm',
			text : '대분류',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'prd_cate2_nm',
			text : '중분류',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'mat_serial_no',
			text : '자재코드',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'mat_nm',
			text : '자재명',
			width : 150,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'mat_desc',
			text : '구분',
			width : 150,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'mc_cost', 
			text : 'MC',
			width : 80,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
		}, {			 
			text : '출고',
			columns: [{			 
				text : 'A/S(본사)',
				columns: [{
	                text: "유상수량",
	                dataIndex: 'as_n_qty',  
	                width: 80,
	                align	 : 'right',
	                sortable: false,
	                renderer: Ext.util.Format.numberRenderer('0,000'),
	                summaryType: 'sum'
	            },{
	                text: "유상금액",
	                dataIndex: 'as_n_amt',  
	                width: 80,
	                align	 : 'right',
	                sortable: false,
	                renderer: Ext.util.Format.numberRenderer('0,000'),
	                summaryType: 'sum'
	            },{
	                text: "무상수량",
	                dataIndex: 'as_y_qty',  
	                width: 80,
	                align	 : 'right',
	                sortable: false,
	                renderer: Ext.util.Format.numberRenderer('0,000'),
	                summaryType: 'sum'
	            },{
	                text: "무상금액",
	                dataIndex: 'as_y_amt',  
	                width: 80,
	                align	 : 'right',
	                sortable: false,
	                renderer: Ext.util.Format.numberRenderer('0,000'),
	                summaryType: 'sum'
	            },{
	                text: "수량소계",
	                dataIndex: 'as_t_qty',  
	                width: 80,
	                align	 : 'right',
	                sortable: false,
	                renderer: Ext.util.Format.numberRenderer('0,000'),
	                summaryType: 'sum'
	            },{
	                text: "금액소계",
	                dataIndex: 'as_t_amt',  
	                width: 80,
	                align	 : 'right',
	                sortable: false,
	                renderer: Ext.util.Format.numberRenderer('0,000'),
	                summaryType: 'sum'
	            }]
			}            
            ,{			 
    			text : '주문',
    			columns: [{
                    text: "유상수량",
                    dataIndex: 'order_n_qty',  
                    width: 80,
                    align	 : 'right',
                    sortable: false,
                    renderer: Ext.util.Format.numberRenderer('0,000'),
                    summaryType: 'sum'
                },{
                    text: "유상금액",
                    dataIndex: 'order_n_amt',  
                    width: 80,
                    align	 : 'right',
                    sortable: false,
                    renderer: Ext.util.Format.numberRenderer('0,000'),
                    summaryType: 'sum'
                },{
                    text: "무상수량",
                    dataIndex: 'order_y_qty',  
                    width: 80,
                    align	 : 'right',
                    sortable: false,
                    renderer: Ext.util.Format.numberRenderer('0,000'),
                    summaryType: 'sum'
                },{
                    text: "무상금액",
                    dataIndex: 'order_y_amt',  
                    width: 80,
                    align	 : 'right',
                    sortable: false,
                    renderer: Ext.util.Format.numberRenderer('0,000'),
                    summaryType: 'sum'
                },{
                    text: "수량소계",
                    dataIndex: 'order_t_qty',  
                    width: 80,
                    align	 : 'right',
                    sortable: false,
                    renderer: Ext.util.Format.numberRenderer('0,000'),
                    summaryType: 'sum'
                },{
                    text: "금액소계",
                    dataIndex: 'order_t_amt',  
                    width: 80,
                    align	 : 'right',
                    sortable: false,
                    renderer: Ext.util.Format.numberRenderer('0,000'),
                    summaryType: 'sum'
                }]
    		}
            ,{			 
    			text : '출고',
    			columns: [{
                    text: "유상수량",
                    dataIndex: 'go_n_qty',  
                    width: 80,
                    align	 : 'right',
                    sortable: false,
                    renderer: Ext.util.Format.numberRenderer('0,000'),
                    summaryType: 'sum'
                },{
                    text: "유상금액",
                    dataIndex: 'go_n_amt',  
                    width: 80,
                    align	 : 'right',
                    sortable: false,
                    renderer: Ext.util.Format.numberRenderer('0,000'),
                    summaryType: 'sum'
                },{
                    text: "무상수량",
                    dataIndex: 'go_y_qty',  
                    width: 80,
                    align	 : 'right',
                    sortable: false,
                    renderer: Ext.util.Format.numberRenderer('0,000'),
                    summaryType: 'sum'
                },{
                    text: "무상금액",
                    dataIndex: 'go_y_amt',  
                    width: 80,
                    align	 : 'right',
                    sortable: false,
                    renderer: Ext.util.Format.numberRenderer('0,000'),
                    summaryType: 'sum'
                },{
                    text: "수량소계",
                    dataIndex: 'go_t_qty',  
                    width: 80,
                    align	 : 'right',
                    sortable: false,
                    renderer: Ext.util.Format.numberRenderer('0,000'),
                    summaryType: 'sum'
                },{
                    text: "금액소계",
                    dataIndex: 'go_t_amt',  
                    width: 80,
                    align	 : 'right',
                    sortable: false,
                    renderer: Ext.util.Format.numberRenderer('0,000'),
                    summaryType: 'sum'
                }]
    		}]
		}, {			 
			text : '합계',
			columns: [{
                text: "유상수량",
                dataIndex: 'tot_n_qty',  
                width: 80,
                align	 : 'right',
                sortable: false,
                renderer: Ext.util.Format.numberRenderer('0,000'),
                summaryType: 'sum'
            },{
                text: "유상금액",
                dataIndex: 'tot_n_amt',  
                width: 80,
                align	 : 'right',
                sortable: false,
                renderer: Ext.util.Format.numberRenderer('0,000'),
                summaryType: 'sum'
            },{
                text: "무상수량",
                dataIndex: 'tot_y_qty',  
                width: 80,
                align	 : 'right',
                sortable: false,
                renderer: Ext.util.Format.numberRenderer('0,000'),
                summaryType: 'sum'
            },{
                text: "무상금액",
                dataIndex: 'tot_y_amt',  
                width: 80,
                align	 : 'right',
                sortable: false,
                renderer: Ext.util.Format.numberRenderer('0,000'),
                summaryType: 'sum'
            },{
                text: "수량소계",
                dataIndex: 'tot_t_qty',  
                width: 80,
                align	 : 'right',
                sortable: false,
                renderer: Ext.util.Format.numberRenderer('0,000'),
                summaryType: 'sum'
            },{
                text: "금액소계",
                dataIndex: 'tot_t_amt',  
                width: 80,
                align	 : 'right',
                sortable: false,
                renderer: Ext.util.Format.numberRenderer('0,000'),
                summaryType: 'sum'
            }]
		}
	];
      
   
    // 사이트
    var comboSite = Ext.create('Ext.form.ComboBox', {
        store: siteStore,
        width: 120,        
        name: 'site',
        queryMode: 'local',
        displayField: 'name',
        valueField: 'code',        
	    padding: '0 0 0 5',
        emptyText: '사이트구분',
        value: '1'
    });
    
    var searchForm = Ext.create('Ext.form.Panel', {		
    	id: 'searchForm',
    	bodyPadding: 5,
    	layout: {
	        type: 'vbox',       // Arrange child items vertically
	        align: 'stretch'    // Each takes up full width
	    },
	    items: [
	        {
	        	border: 0,
				layout: {
					type: 'hbox',  
					align: 'stretch',
					padding: '0 5 0 5'
				},      
				items: [
					{
					    width: 16,
					    height: 16,
					    xtype: 'image',
					    margin: '0 5 0 5',
					    imgCls: 'icon-mn004'				        
					},
					{
						xtype: 'displayfield',					    
						fieldLabel: '조건검색', 
						margin: '0 5 0 5',
						labelWidth: 55
					},
					comboSite,
					{
			        	width: 120,
				        xtype: 'datefield',
				        name: 'sdate',		
				        format: 'Ymd',
				        submitFormat: 'Ymd',
				        submitValue: true,
				        value: toDate,
				        margin: '0 0 0 5',
			    		emptyText: '등록일(시작)',
			    		listeners:  {
			                specialkey: function (f,e) {    
			                     if (e.getKey() == e.ENTER) {
			                    	 reload();
			                    }
			                }
			            }
			        },
			        {
			        	width: 120,
				        xtype: 'datefield',
				        name: 'edate',		
				        format: 'Ymd',
				        submitFormat: 'Ymd',
				        submitValue: true,
				        value: toDate,
				        margin: '0 0 0 5',
			    		emptyText: '등록일(종료)',
			    		listeners:  {
			                specialkey: function (f,e) {    
			                     if (e.getKey() == e.ENTER) {
			                    	 reload();
			                    }
			                }
			            }
			        },
			        {
			            xtype: 'button',
			            text: '오늘',
			            margin: '0 0 0 5',
			        	handler: function() {
			        		setFormDate('today');
			        	}
			        },
			        {
			            xtype: 'button',
			            text: '주간',
			            margin: '0 0 0 5',
			            handler: function() {
			        		setFormDate('week');
			        	}
			        },
			        {
			            xtype: 'button',
			            text: '월간',
			            margin: '0 0 0 5',
			            handler: function() {
			        		setFormDate('month');
			        	}
			        },
			        {
			            xtype: 'button',
			            iconCls: 'icon-search',
			            margin: '0 0 0 5',				
			        	handler: reload
			        }]
	        	}
	    ]
	});
    
//    var sm = new Ext.selection.CheckboxModel({		
//		name:'chkbox',	    	
//	    checkOnly: true,
//	    menuDisabled: true,
//		sortable : false,
//	    listeners: {
//	    	selectionchange: function(me, selected, eOpts) {	    		
//	    		arr_prd_stock_idx = "";
//	    		
//	    		Ext.each(selected, function(rec) {	            	
//	    			arr_prd_stock_idx += rec.data.prd_stock_idx + "|";	            	
//	            });
//	    	}
//	    }
//	});
    
    
    var sm = new Ext.selection.CheckboxModel({
    	id:'chkbox',
    	name:'chkbox',	    	
        checkOnly: true,
        showHeaderCheckbox: true,
        menuDisabled: true,
    	sortable : false,
        listeners: {
        	selectionchange: function(me, selected, eOpts) {

        		Ext.each(selected, function(rec) {
        			//alert(rec.data.fileid)
	            });
        		
        		//Ext.getCmp("tot_premium_amt").setValue(Ext.util.Format.number(tot_premium_amt, '0,000'));
        	}
        }
    });	    
    
    
	Ext.create('Ext.panel.Panel', {
		id:'Content',
	    title: name,
	    flex: 1,
	    height: FRAME_CONTENT_HEIGHT,
	    renderTo: Ext.getBody(),
	    layout: {
	        type: 'vbox',       // Arrange child items vertically
	        align: 'stretch',    // Each takes up full width
	        padding: 5
	    },
	    items: [
	        searchForm,
	        { // Details Panel specified as a config object (no xtype defaults to 'panel').
		    bodyPadding: 5,
		    padding: '5 0 0 0',
		    layout: {
		        type: 'hbox',
		        align: 'stretch'
		    },
		    items: [/*{
		    	xtype: 'button',
		    	text: '선택삭제',
		    	align:'right',
		    	style:'text-align:right',
		    	iconCls: 'icon-delete',
		    	handler: onDeletePrdNo
		    }, */{
		    	xtype: 'tbfill'
		    }, {
		    	xtype: 'button',
		    	text: '엑셀다운로드',
		    	align:'right',
		    	style:'text-align:right',
		    	iconCls: 'icon-excel',
		    	handler: function() {
		    		download();
		    	}
		    }]
		}, {
	        xtype: 'splitter'
	    }, {               
	        xtype: 'grid',
	        columns: columns,
	        store: store,
	        selModel : sm,
	        flex: 1,
	        id: 'grid',
	        name: 'grid',
	        scroll: 'both',
	        features: [{
	            ftype: 'summary'
	        }]
	    }]
	});
	
	// form reload
	function reload() {
		
		var form = Ext.getCmp('searchForm').getForm();
		
		var sdate = form.findField("sdate");
		var edate = form.findField("edate");
		var site = form.findField("site");
		
		if(sdate.getSubmitValue() == "" 
			&& edate.getSubmitValue() == ""
		) {
			Ext.Msg.alert('Notice', '검색할 기간을 반드시 입력해 주세요');
			return;			
		}
		
		if((sdate.getSubmitValue() == "" && edate.getSubmitValue() != "") || 
				(sdate.getSubmitValue() != "" && edate.getSubmitValue() == "")) {
			Ext.Msg.alert('Notice', '기간검색은 시작일자와 종료일자 모두 입력해 주세요!');
			return;
		}
		
		store.getProxy().extraParams = form.getValues();
		store.loadPage(1);
	}
	
	// form date
	function setFormDate(flag) {
		
		var form = Ext.getCmp('searchForm').getForm();
		
		var toDate = Ext.Date.format(new Date(),'Ymd');
		
		if(flag == "today") { // 오늘			
			form.findField("sdate").setValue(toDate);
			form.findField("edate").setValue(toDate);			
		} else if (flag == "week") { // 주간
			form.findField("sdate").setValue(getWeekDay());			
			form.findField("edate").setValue(toDate);
		} else if (flag == "month") { // 월간
			form.findField("sdate").setValue(getMonthDay());
			form.findField("edate").setValue(toDate);
		} else { //공백
			form.findField("sdate").setValue("");
			form.findField("edate").setValue("");
		}		
	}
	
	function download() {
		
		Ext.getBody().mask('파일 다운로드 중...');
		
		Ext.Ajax.request({
			url: COMMON_URL + '/ajaxPrdReceivePayExcel',
			success: function(result, request) {
				Ext.getBody().unmask();
				var obj = Ext.decode(result.responseText);
				location.href = COMMON_URL + "/common/FileDown.jsp?fileName="+obj.filename+"&fileDir="+obj.filepath;
			},
			failure: function(result, request) {
				Ext.getBody().unmask();        							 
				Ext.Msg.alert('Error', '다운로드 중 오류가 발생하였습니다.');	        							 
			},
			params : Ext.getCmp('searchForm').getForm().getValues(),  
			timeout: TIMEOUT_SEC
		});
	}
	
});
