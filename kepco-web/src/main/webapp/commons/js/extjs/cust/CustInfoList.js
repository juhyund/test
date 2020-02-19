/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : CustInfoList.js
* @Author : kyunghee.yoon
* @Date : 2015.10.14
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
	
    Ext.define('DataThread', {
        extend: 'Ext.data.Model',
        fields: [
              'cust_no'
         	, 'group_no'
         	, 'group_nm'
         	, 'cust_nm'
         	, 'birthdate'
         	, 'sex'
         	, 'tel_mobile'
         	, 'tel_home'
         	, 'tel_office'
         	, 'tel_etc'
         	, 'address_type'
         	, 'zipcode'
         	, 'address1'
         	, 'address2'
         	, 'black_yn'
         	, 'black_dt'
         	, 'black_remark'
         	, 'remark'
         	, 'use_yn'
         	, 'dept_cd'
         	, 'dept_nm'
         	, 'insert_id'
         	, 'insert_nm'
         	, 'insert_dt'
         	, 'update_nm'
         	, 'update_id'
         	, 'update_dt'
         	, 'agree_yn'
         	, 'agree_dt'
        ]
    });
	
    store = Ext.create('Ext.data.Store', {
        pageSize: 30,
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxCustInfoList',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
            },
            simpleSortMode: true
        },
        sorters: [{
            property: 'cust_no',
            direction: 'DESC'
        }]
    });

    var columns = [
        {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
			dataIndex : 'cust_no',
			text : '고객번호',
			width : 100,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'cust_nm',
			text : '고객명',
			width : 110,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'group_nm',
			text : '그룹명',
			width : 80,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'tel_mobile',
			text : '휴대번호',
			width : 110,
			align : 'center',
			sortable : false,
    		renderer: maskPhoneNo
		}, {
			dataIndex : 'tel_home',
			text : '전화번호',
			width : 110,
			align : 'center',
			sortable : false,
    		renderer: maskPhoneNo
		}, {
			dataIndex : 'zipcode',
			text : '우편번호',
			width : 80,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'address1',
			text : '주소1',
			width : 150,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'address2',
			text : '주소2',
			width : 150,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'agree_yn',
			text : '마케팅동의여부',
			width : 100,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'agree_dt',
			text : '마케팅동의일시',
			width : 150,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'insert_nm',
			text : '등록자',
			width : 80,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'insert_dt',
			text : '등록일시',
			width : 150,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'update_nm',
			text : '수정자',
			width : 80,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'update_dt',
			text : '수정일시',
			width : 150,
			align : 'center',
			sortable : true
		}
	];

    var searchType = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"cust_nm", "name":"고객명"},
            {"code":"cust_no", "name":"고객번호"},
            {"code":"address1", "name":"주소"},
        ]
    });	
    
    var comboSearch = Ext.create('Ext.form.ComboBox', {
        store: searchType,
        width: 100,
        id: 'searchfield',
        name: 'searchfield',
        queryMode: 'local',
        displayField: 'name',
        valueField: 'code',
        editable: false,
	    padding: '0 0 0 5',
        emptyText: '검색조건',
        value: 'cust_nm'
    });
    
    var agreeYNStore = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"", "name":"마케팅동의전체"},
            {"code":"Y", "name":"동의"},
            {"code":"N", "name":"미동의"},
        ]
    });	
    
    var comboAgreeYN = Ext.create('Ext.form.ComboBox', {
        store: agreeYNStore,
        width: 120,
        id: 'agree_yn',
        name: 'agree_yn',
        queryMode: 'local',
        displayField: 'name',
        valueField: 'code',
        editable: false,
	    padding: '0 0 0 5',
        emptyText: '마케팅동의',
        value: ''
    });
    
    // 그룹
    var custGroupStore = Ext.create('Ext.data.Store', {
    	id: 'custGroupStore',        
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxCustGroupCombo',
            reader: {root: 'result'},
            simpleSortMode: true,
            extraParams: {use_yn:'Y'}
        },
        fields: [{ name: 'group_no' },{ name: 'group_nm' }],
        autoLoad:true
    });
    
    var comboGroup = {
    	xtype: 'combobox',
    	id: 'group_no',
        store: custGroupStore,
        width: 120,        
        name: 'group_no',
        queryMode: 'local',
        displayField: 'group_nm',
        valueField: 'group_no',
	    padding: '0 0 0 5',
        emptyText: '그룹선택'
    }
    
    // 성별
    var sexType = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"1", "name":"남"},
            {"code":"2", "name":"여"}
        ]
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
					comboGroup,
			        {
			        	width: 120,
				        xtype: 'textfield',
				        name: 'tel_mobile',				        	              
				        margin: '0 0 0 5',
			    		emptyText: '휴대번호',
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
				        xtype: 'textfield',
				        name: 'tel_home',
				        margin: '0 0 0 5',
			    		emptyText: '전화번호',
			    		listeners:  {
			                specialkey: function (f,e) {    
			                     if (e.getKey() == e.ENTER) {
			                    	 reload();
			                    }
			                }
			            }
			        },
			        comboAgreeYN,
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
		    items: [{
		    	xtype: 'tbfill'
		    },{
		    	xtype: 'button',
		    	text: '고객정보등록',
		    	align:'right',
		    	style:'text-align:right',
		    	iconCls: 'icon-People',
		    	handler: function(){
		    		insertPop();
		    	}
		    },{
		    	xtype: 'button',
		    	text: '엑셀다운로드',
		    	align:'right',
		    	style:'text-align:right',		    	
		    	iconCls: 'icon-excel',
		    	margin: '0 0 0 5px',
		    	handler: function(){
		    		download();
		    	}
		    }]
		},{
	        xtype: 'splitter'   // A splitter between the two child items
	    },		
	    {               // Results grid specified as a config object with an xtype of 'grid'
	        xtype: 'grid',
	        columns: columns,// One header just for show. There's no data,
	        store: store, // A dummy empty data store
	        flex: 1,                                       // Use 1/3 of Container's height (hint to Box layout)
	        id: 'grid',
	        name: 'grid',
	        scroll: 'horizontal',
			bbar: Ext.create('Ext.PagingToolbar', {
				pageSize: 30,
				store: store,
				displayInfo: true,
				displayMsg: '{0} - {1} of {2} 건',
				emptyMsg: "데이터가 없습니다."
			}),
			listeners: {
	        	'celldblclick': function(iView, iCellEl, iColIdx, iStore, iRowEl, iRowIdx, iEvent) {
	        		insertPop(iRowIdx);
	        	}
	        }
	    }]
	});
	
	// form reload
	function reload() {
		
		var form = Ext.getCmp('searchForm').getForm();
		
		var sdate = form.findField("sdate");
		var edate = form.findField("edate");
		var searchquery = form.findField("searchquery");
		var tel_mobile = form.findField("tel_mobile");
		var tel_home = form.findField("tel_home");
		var group_no = form.findField("group_no");
		var agree_yn = form.findField("agree_yn");
				
		tel_mobile.setValue(remainNumber(tel_mobile.getValue()));
		tel_home.setValue(remainNumber(tel_home.getValue()));
		
		if(sdate.getSubmitValue() == "" 
			&& edate.getSubmitValue() == "" 
			&& searchquery.getValue() == "" 
			&& tel_mobile.getValue() == "" 
			&& tel_home.getValue() == "" 
			&& group_no.getValue() == null && agree_yn.getValue() == null) {				
			
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
		
	var win = null;
    //팝업 window
    var insertPop = function(iRowIdx) {
    	
    	insertform.getForm().reset();
    	var cust_no = "";
    	
    	if(!win) {
    		
	    	win = Ext.create('Ext.window.Window', {
	            title: '고객정보',
	            height: 370,
	            width: 600,
	            closeAction: 'close',
	            modal: false,
	            resizable: false,
	            draggable: true,
	            items:[
	                   insertform
	            ]
	        });
    	}
    	
    	if(win.isVisible()) {
			win.hide();
		} else {
			win.show();
			
			if(iRowIdx != undefined) {
				var rec = store.getAt(iRowIdx);			
				insertform.getForm().loadRecord(rec);
				
				// 휴대번호
				insertform.getForm().findField("tel_mobile").setValue(maskPhoneNo(rec.data.tel_mobile));
				// 전화번호
				insertform.getForm().findField("tel_home").setValue(maskPhoneNo(rec.data.tel_home));
				//고객번호
				cust_no = rec.data.cust_no;
			}
	    	
	    	if(cust_no == "") {
	    		url = COMMON_URL + '/ajaxCustInfoInsert';
			} else {				
				url = COMMON_URL + '/ajaxCustInfoUpdate';
			}
		}
    }
    
    //팝업 form
    var insertform = Ext.create('Ext.form.Panel', {
    	id: 'insertform',
	    bodyPadding: 7,
	    flex: 1,
	    border: 0,
	    layout: 'anchor',
	    defaults: {
	        anchor: '100%'
	    },
	    defaultType: 'textfield',
	    items: [
			{
			    xtype: 'hiddenfield',
			    name: 'cust_no'
			},
			{   
			    name: 'cust_nm',
			    fieldLabel: '고객명',
			    afterLabelTextTpl: [MARK_ASTERISK]
			},
			{   
				xtype: 'combobox',
				name: 'group_no',
				fieldLabel: '그룹',
		        store: custGroupStore,
		        queryMode: 'local',
		        displayField: 'group_nm',
		        valueField: 'group_no',
		        emptyText: '그룹선택',
		        editable: false,
		        value: '100'
			},			
			{   
			    name: 'tel_mobile',
			    fieldLabel: '휴대번호',
			    afterLabelTextTpl: [MARK_ASTERISK],
			    listeners: {
                	blur: function (t,n,o) {
                		if(t.getValue() != "") {
                		
	                		if ( !regPhone.test(t.getValue()) ) {
	                			focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br><br>[전화번호 예시]<br>- 휴대번호: 010-1234-1234 (010-0000-1111 사용불가)<br>- 유선번호: 02-123-1234 (지역번호 반드시 포함)<br>- 대표번호: 1577-3555(대표번호 8자리만 허용)<br>- 기타번호: 0505-1234-1234 (12자리 허용)", t);
		          			}
		          			
		          			if ( regPhone2.test(t.getValue()) ) {
		          				focusMsgAlert('Warning',"올바른 전화(휴대)번호 형식으로 입력하세요!<br>휴대번호 중간에 '0'만 올수 없습니다.", t);
		          			}
                		}
                	}
			    }
			},
			{   
			    name: 'tel_home',
			    fieldLabel: '전화번호',
			    afterLabelTextTpl: [MARK_ASTERISK],
			    listeners: {
                	blur: function (t,n,o) {
                		if(t.getValue() != "") {
	                		if ( !regPhone.test(t.getValue()) ) {
	                			focusMsgAlert('Warning',"올바른 전화(휴대)번호 형식으로 입력하세요!<br><br>[전화번호 예시]<br>- 휴대번호: 010-1234-1234 (010-0000-1111 사용불가)<br>- 유선번호: 02-123-1234 (지역번호 반드시 포함)<br>- 대표번호: 1577-3555(대표번호 8자리만 허용)<br>- 기타번호: 0505-1234-1234 (12자리 허용)", t);
		          			}
		          			
		          			if ( regPhone2.test(t.getValue()) ) {
		          				focusMsgAlert('Warning',"올바른 전화(휴대)번호 형식으로 입력하세요!<br>휴대번호 중간에 '0'만 올수 없습니다.", t);
		          			}
                		}
                	}
			    }
			},			
			{
	            xtype: 'fieldcontainer',            
	            layout: 'hbox',     
	            fieldLabel: '우편번호',
	            defaultType: 'textfield',
	            items: [{
	                name: 'zipcode',
	                flex: 1,
	                readOnly: true,
	                editable: false
	            }, {
	    	    	xtype: 'button',
	    	    	id: 'btnLoadCust',
	    	    	text: '우편번호검색',
	    	    	align:'right',
	    	    	style:'text-align:right',
	    	    	iconCls: 'icon-search',
	    	    	margin: '0 0 0 5',
	    	    	handler: function() {
	    	    		zipcode('setZipcode1');
	    	    	}
	    	    }]
	        },
			{   
			    name: 'address1',
			    fieldLabel: '주소1',
			    readOnly: true,
                editable: false
			},
			{   
			    name: 'address2',
			    fieldLabel: '주소2'
			},
			{   
			    xtype: 'textareafield',
				name: 'remark',
			    fieldLabel: '비고',
			    height: 80
			},
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

				var cust_no	= form.findField("cust_no");
				var cust_nm = form.findField("cust_nm");
				var group_no = form.findField("group_no");				
				var tel_mobile = form.findField("tel_mobile");
				var tel_home = form.findField("tel_home");
				
				if(cust_nm.getValue() == "") {					
					focusMsgAlert('Warning', '고객명을 입력해 주세요', cust_nm);
					return;
				}
				
				if(tel_mobile.getValue() == "" && tel_home.getValue() == "") {
					focusMsgAlert('Warning', '휴대전화 또는 전화번호를 입력해 주세요');					
					return;
				}
				
				if(tel_mobile.getValue() != "") {
					if ( !regPhone.test(tel_mobile.getValue()) ) {
						focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br><br>[전화번호 예시]<br>- 휴대번호: 010-1234-1234 (010-0000-1111 사용불가)<br>- 유선번호: 02-123-1234 (지역번호 반드시 포함)<br>- 대표번호: 1577-3555(대표번호 8자리만 허용)<br>- 기타번호: 0505-1234-1234 (12자리 허용)", tel_mobile);
						return;
	     			}
	     			
	     			if ( regPhone2.test(tel_mobile.getValue()) ) {	     				
	     				focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br>휴대번호 중간에 '0'만 올수 없습니다.", tel_mobile);
	     				return;
	     			}
				}
				
				if(tel_home.getValue() != "") {
					if ( !regPhone.test(tel_home.getValue()) ) {
						focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br><br>[전화번호 예시]<br>- 휴대번호: 010-1234-1234 (010-0000-1111 사용불가)<br>- 유선번호: 02-123-1234 (지역번호 반드시 포함)<br>- 대표번호: 1577-3555(대표번호 8자리만 허용)<br>- 기타번호: 0505-1234-1234 (12자리 허용)", tel_home);
						return;
	     			}
	     			
	     			if ( regPhone2.test(tel_home.getValue()) ) {	     				
	     				focusMsgAlert('Warning', "올바른 전화(휴대)번호 형식으로 입력하세요!<br>휴대번호 중간에 '0'만 올수 없습니다.", tel_home);
	     				return;
	     			}
				}
				
				tel_mobile.setValue(remainNumber(tel_mobile.getValue()));
				tel_home.setValue(remainNumber(tel_home.getValue()));
												
	            if (form.isValid()) {
	                form.submit({
	                	url: url,
	                	submitEmptyText: false,
	                    success: function(form, action) {
	                       Ext.Msg.alert('Success', action.result.msg);
	                       reload();
	                       win.hide();
	                    },
	                    failure: function(form, action) {
	                        Ext.Msg.alert('Failed', action.result.msg);
	                        return;
	                    }
	                });
	            }
	        }
	    },
	    {
	        text: '닫기',
	        iconCls: 'icon-cancel',
	        handler: function() {
	        	win.hide();
        	}
        }]
	});
	
});


function setZipcode1(zipcode, address1) {
	
	var form = Ext.getCmp('insertform').getForm();
	
	form.findField("zipcode").setValue(zipcode);
	form.findField("address1").setValue(address1);
}


function download() {
	
	Ext.getBody().mask('파일 다운로드 중...');
	
	Ext.Ajax.request({
		url: COMMON_URL + '/ajaxSelectCustExcel',
		success: function(result, request) {
			Ext.getBody().unmask();
			var obj = Ext.decode(result.responseText);
			// console.log(obj);
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