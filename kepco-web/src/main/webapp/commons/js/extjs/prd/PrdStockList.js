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
	
	var url;
	var arr_prd_stock_idx = "";
	
    Ext.define('DataThread', {
        extend: 'Ext.data.Model',
        fields: [
            'prd_stock_idx'
            , 'prd_no'
            , 'prd_serial_no'
			, 'prd_nm'
			, 'prd_spec'
			, 'seq_no'
			, 'io_flag'
			, 'stock_id'
			, 'stock_nm'
			, 'stock_qty'
			, 'stock_date'
			, 'order_no'
			, 'chg_type'
			, 'chg_type_nm'
			, 'chg_remark'			
			, 'insert_id'
			, 'insert_dt'
			, 'update_id'
			, 'update_dt'
        ]
    });
	
    store = Ext.create('Ext.data.Store', {
        pageSize: 30,
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxPrdStockList',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
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
			dataIndex : 'prd_serial_no',
			text : '자재번호',
			width : 150,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'prd_nm',
			text : '자재명',
			width : 150,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'prd_spec',
			text : '규격',
			width : 150,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'stock_date',
			text : '입고일자',
			width : 150,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'stock_nm',
			text : '입고지',
			width : 150,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'stock_qty', 
			text : '입고수량',
			width : 150,
			align : 'right',
			sortable : false,
			renderer: Ext.util.Format.numberRenderer('0,000')
		}, {
			dataIndex : 'chg_type_nm', 
			text : '입고유형',
			width : 150,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'chg_remark', 
			text : '보정사유',
			width : 150,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'insert_id',
			text : '등록자',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'insert_dt',
			text : '등록일시',
			width : 150,
			align : 'center',
			sortable : false
		}
	];
       
    var deptCodeStore = Ext.create('Ext.data.Store', {
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxDeptCdStoreCombo',
            reader: {root: 'result'},
            simpleSortMode: true
        },
        fields: [{ name: 'dept_cd' },{ name: 'dept_nm' }],
        autoLoad:true
    });
    
   
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
    
    // 입고지
    var comboIList = Ext.create('Ext.form.ComboBox', {
        store: deptCodeStore,
        width: 120,        
        name: 'stock_id',
        queryMode: 'local',
        displayField: 'dept_nm',
        valueField: 'dept_cd',
        editable: false,
	    padding: '0 0 0 5',
        emptyText: '입고지'
    });
        
    var searchType = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"p.prd_serial_no", "name":"제품자재번호"},
            {"code":"p.prd_nm", "name":"제품자재명"},
            {"code":"p.prd_spec", "name":"자재SPEC"}
        ]
    });
    
    var asStore = Ext.create('Ext.data.Store', {
        fields: ['dept_cd', 'dept_nm'],
        data : [
            {"dept_cd":"10004", "dept_nm":"AS본사"}
        ]
    });	
    
    var comboSearch = Ext.create('Ext.form.ComboBox', {
        store: searchType,
        width: 120,
        id: 'searchfield',
        name: 'searchfield',
        queryMode: 'local',
        displayField: 'name',
        valueField: 'code',
        editable: false,
	    padding: '0 0 0 5',
        emptyText: '검색조건',
        value: 'p.prd_serial_no'
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
						fieldLabel: '기간검색', 
						margin: '0 5 0 5',
						labelWidth: 55
					},
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
			            text: '공백',
			            margin: '0 0 0 5',
			            handler: function() {
			        		setFormDate('blank');
			        	}
			        }]
	        }, // 1 row
			{
				border: 0,
				layout: {
					type: 'hbox',  
					align: 'stretch',
					padding: '5 5 0 5'
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
					comboIList,					
			        comboSearch,
			        {
			            width: 150,
				        xtype: 'textfield',
				        name: 'searchquery',
				        emptyText: '검색어 입력',
				        margin: '0 5 0 5',
				        style: 'IME-MODE:ACTIVE',
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
			            iconCls: 'icon-search',
			        	handler: reload
			        }]
			} // 2 row
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
		    	text: '자재입고 엑셀업로드',
		    	align:'right',
		    	style:'text-align:right',
		    	iconCls: 'icon-excel',
		    	handler: function() {
		    		insertPop();
		    	}
		    }, {
		    	xtype: 'button',
		    	text: '자재입고 건별등록',
		    	align:'right',
		    	style:'text-align:right',
		    	iconCls: 'icon-write',
		    	margins: '0 0 0 5',
		    	handler: function() {
		    		insertPop2();
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
			bbar: Ext.create('Ext.PagingToolbar', {
				pageSize: 30,
				store: store,
				displayInfo: true,
				displayMsg: '{0} - {1} of {2} 건',
				emptyMsg: "데이터가 없습니다."
			})
	    }]
	});
	
	// form reload
	function reload() {
		
		var form = Ext.getCmp('searchForm').getForm();
		
		var sdate = form.findField("sdate");
		var edate = form.findField("edate");
		var searchquery = form.findField("searchquery");
		
		var site = form.findField("site");
		var prd_type = form.findField("prd_type");
		
		if(sdate.getSubmitValue() == "" 
			&& edate.getSubmitValue() == "" 
			&& searchquery.getValue() == ""
			&& site.getValue() == ""
			&& prd_type.getValue() == ""
		) {
			Ext.Msg.alert('Notice', '검색조건을 하나 이상 입력해 주세요');
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
	
	
	/**
	 * 자재정보 선택삭제
	 */
	function onDeletePrdNo() {
		
    	var result = arr_prd_stock_idx.split("|");
    	
    	if(result.length == 1) {
    		Ext.Msg.alert("Warning", "삭제할 자재정보를 선택하세요");
    		return;
    	}
    	
    	Ext.Msg.show({
		    title:'Delete',
		    msg: '선택된 자재정보를 삭제하시겠습니까?',
		    buttons: Ext.Msg.YESNO,
		    icon: Ext.Msg.QUESTION,
		    fn: function(btn) {
		        if (btn === 'yes') {
		        	
		        	Ext.Ajax.request({
		    	        url: COMMON_URL + '/ajaxPrdStockDelete',
		    	        params: {'strPrdStockIdx'  : arr_prd_stock_idx},
		    	        success: function(response) {		    	    				    	    		
		    	        	var obj = Ext.decode(response.responseText);		    	        	
		    	        	Ext.Msg.alert('Success', obj.msg);
		    	        	reload();
		    	        },
		    	        failure: function(result, request) {
		    	        	Ext.Msg.alert('Failed', "삭제 중 오류가 발생하였습니다.");
		    			}
		    	    });		
		        	
		        } else if (btn === 'no') {
		            return;
		        } else {
		            return;
		        } 
		    }
		});
	}
	
	
	var win = null;
    //팝업 window
    var insertPop = function(iRowIdx) {
    	
    	insertform.getForm().reset();
    	
    	if(!win) {
    		
	    	win = Ext.create('Ext.window.Window', {
	            title: '자재입고 엑셀업로드',
	            height: 330,
	            width: 500,
	            closeAction: 'close',
	            modal: false,
	            resizable: false,
	            draggable: true,
	            items:[insertform]
	        });
    	}
    	
    	if(win.isVisible()) {
			win.hide();
		} else {
			win.show();
		}
    }
    
    var fileListeners = {
    	"change" : function(me, value, eOpts) {	            		
    		var ext = value.slice(value.indexOf(".") + 1).toLowerCase().trim();    		
    		var extFormat = /(xls)/;
    		if(!extFormat.test(ext))
            {
    			Ext.Msg.alert('Warning', '허용된 확장자가 아닙니다.\n파일을 다시 선택하여 주십시오');
    			me.reset();
    			return;
    		}	
    	}
	};
    
    var html = '<div style="line-height:19px;">'; 
	html += '<ol start="1"><li> 엑셀업로드 양식을 다운로드 하여 형식에 맞게 기재합니다.</li>';
	html += '<li> 파일찾기 버튼을 클릭하여 <u><font color="#FF0000">업로드 할 파일(.xls, 확장자 유의)</font></u>을 선택하고</li>';
	html += '<li> [업로드]버튼을 클릭하여 <u>데이터 업로드</u>를 시작합니다.</li>';
	html += '<li> 데이터 업로드가 완료되면 업로드 결과를 확인합니다.</li>';
	html += '<li><font color="#FF0000">업로드 중 오류가 있는 경우 오류파일을 다운로드 하여 수정 후 다시 업로드 합니다.</font></li>';
	html += '</ol></div>';
	
    //팝업 form
    var insertform = Ext.create('Ext.form.Panel', {
    	id: 'insertform',    	
	    bodyPadding: 10,
	    flex: 1,
	    border: 0,
	    layout: 'anchor',
	    defaults: {
	        anchor: '100%'
	    },
	    height: 280,
	    items: [{
	        xtype:'fieldset',
	        bodyPadding: 5,
	        title: '업로드 주의사항',
	        defaults: {anchor: '100%'},
	        layout: 'anchor',
	        items :[{'html' : html, border: 0}]
	    }, {
			xtype: 'fileuploadfield',			
            name: 'filename',		 
            fieldLabel: '자재입고등록',
            flex: 1,
        	padding: '20 0 0 5',
        	buttonText: '파일찾기',
        	buttonConfig: {
                iconCls: 'icon-upload'
            },
            listeners: fileListeners
	    }],
	    buttons: [
		{
		    text: '업로드양식 다운로드',
		    iconCls: 'icon-excel',
		    handler: function() {
		    	location.href = COMMON_URL + "/common/templates/자재입고정보_등록양식.xls"
			}
		},
        '->',	        
        {
	        text: '업로드',
	        formBind: true, 
	        iconCls: 'icon-yes',
	        handler: function() {
	        	
	        	var form = this.up('form').getForm();
	        	
	        	if (form.isValid()) {
	        		
	                form.submit({
                        url: COMMON_URL + '/ajaxFileUpload?savePath=PRD',
                        submitEmptyText: false,
	                    success: function(form, action) {
	                    	
	                    	Ext.getBody().mask('자재입고 등록 중 입니다.');
	                    	
	                    	Ext.Ajax.request({
	                    		url: COMMON_URL + '/ajaxPrdStockExcelUpload',
	                    		success: function(result, request) {
	                    			Ext.getBody().unmask();        							 
	                    			var obj = Ext.decode(result.responseText);        							 
	                    			var msg = '자재입고 업로드가 완료 되었습니다.<br><br> - 전체 : ' + obj.total + '건<br> - 성공 : ' + obj.success + '건<br> - 오류 : ' + obj.error + '건<br>';
 
	                    			Ext.Msg.alert('Success', msg, function(btn, text) {
	                    				if (btn == 'ok') {
	                    					if(obj.error > 0) {
	                    						location.href = COMMON_URL + "/common/FileDown.jsp?fileName="+obj.errFileName+"&fileDir="+obj.errFilePath
	                    					}
	                    					
	                    					reload();
	                    				}
	                    			});
	                    		},
	                    		failure: function(result, request) {
	                    			Ext.getBody().unmask();        							 
	                    			Ext.Msg.alert('Error', '자재입고 업로드 중 오류가 발생하였습니다.');	        							 
	                    		},
	                    		params: {
	                    			'filename':action.result.fileName,
	                    			'filepath':action.result.filePath
	                    		},
	                    		timeout: TIMEOUT_SEC
	                    	});
	                    },
	                    failure: function(form, action) {	
	                    	Ext.getBody().unmask();
	                        Ext.Msg.alert('Failed', action.result.msg);
	                        return;
	                    },
	                    timeout: TIMEOUT_SEC
	                });
	            } // form check
	        } // handle
	    },
	    {
	        text: '닫기',
	        iconCls: 'icon-cancel',
	        handler: function() {
	        	win.hide();
        	}
        }]
	});
    
    
    var win2 = null;
    //팝업 window
    var insertPop2 = function(iRowIdx) {
    	
    	insertform2.getForm().reset();
    	
    	if(!win2) {
    		
    		win2 = Ext.create('Ext.window.Window', {
	            title: '자재입고 건별등록',
	            height: 250,
	            width: 500,
	            closeAction: 'close',
	            modal: false,
	            resizable: false,
	            draggable: true,
	            items:[insertform2]
	        });
    	}
    	
    	if(win2.isVisible()) {
    		win2.hide();
		} else {
			win2.show();
		}
    }
    
    // 팝업 form
    var insertform2 = Ext.create('Ext.form.Panel', {
    	id: 'insertform2',
	    bodyPadding: 7,
	    flex: 1,
	    border: 0,
	    layout: 'anchor',
	    height: 205,
	    defaults: {
	        anchor: '100%'
	    },
	    defaultType: 'textfield',
	    items: [		
		{   
		    name: 'prd_serial_no',
		    fieldLabel: '자재번호',
		    afterLabelTextTpl: [MARK_ASTERISK]
		},
		{   
			xtype: 'datefield',
			name: 'stock_date',
			fieldLabel: '출고일자',
			format: 'Ymd',
	        submitFormat: 'Ymd',
	        submitValue: true,
	        value: toDate,
		    afterLabelTextTpl: [MARK_ASTERISK]
		},
		{   
			xtype: 'combobox',
			name: 'o_id',
			fieldLabel: '출고지',
	        store: asStore,
	        queryMode: 'local',
	        displayField: 'dept_nm',
	        valueField: 'dept_cd',	        
	        editable: false,	        
	        value: '10004',
		    afterLabelTextTpl: [MARK_ASTERISK]
		},
		{   
			xtype: 'combobox',
			name: 'stock_id',
			fieldLabel: '입고지',
	        store: deptCodeStore,
	        queryMode: 'local',
	        displayField: 'dept_nm',
	        valueField: 'dept_cd',	        
	        editable: false,	        
		    afterLabelTextTpl: [MARK_ASTERISK]
		},
		{   
			xtype: 'numberfield',
			name: 'stock_qty',
		    fieldLabel: '입고수량',
		    hideTrigger: true,
		    afterLabelTextTpl: [MARK_ASTERISK]
		}
		],
	    buttons: [	
	    '<font color="red">*</font>  항목은 필수 항목입니다.',          
        '->',	        
        {
	        text: '저장',
	        formBind: true, 
	        iconCls: 'icon-yes',
	        handler: function() {
	        	
	        	var form = this.up('form').getForm();
	        	
	        	var prd_serial_no	= form.findField("prd_serial_no");
				var o_id = form.findField("o_id");
				var stock_id = form.findField("stock_id");
				var stock_qty = form.findField("stock_qty");
				
				if(prd_serial_no.getValue() == "") {					
					focusMsgAlert('Warning', '자재번호를 입력해 주세요', prd_serial_no);
					return;
				}
				
				if(o_id.getSubmitValue() == "") {					
					focusMsgAlert('Warning', '출고지를 선택해 주세요', o_id);
					return;
				}
				
				if(stock_id.getSubmitValue() == "") {					
					focusMsgAlert('Warning', '입고지를 선택해 주세요', stock_id);
					return;
				}
				
				if(stock_qty.getSubmitValue() == "") {					
					focusMsgAlert('Warning', '입고 수량을 입력해 주세요', stock_qty);
					return;
				}
												
	            if (form.isValid()) {
	                form.submit({
	                	url: COMMON_URL + "/ajaxPrdStockInsert",
	                	submitEmptyText: false,
	                    success: function(form, action) {
	                       Ext.Msg.alert('Success', action.result.msg);
	                       reload();
	                       win2.hide();
	                    },
	                    failure: function(form, action) {
	                        Ext.Msg.alert('Failed', action.result.msg);
	                        return;
	                    }
	                });
	            } // form
	            
	        } // handle
	    },
	    {
	        text: '닫기',
	        iconCls: 'icon-cancel',
	        handler: function() {
	        	win2.hide();
        	}
        }]
	});
});