/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : DeptInfoList.js
* @Author : kyunghee.yoon
* @Date : 2015.10.16
**************************************/
Ext.require([
	'Ext.tree.*',
	'Ext.form.field.Text',
	'Ext.resizer.Splitter',
	'Ext.grid.Panel',
	'Ext.grid.column.RowNumberer',
	'Ext.window.*',
]);

Ext.onReady(function(){
	
	var url;
	
    Ext.define('DataThread', {
        extend: 'Ext.data.Model',
        fields: [
              'agency_cd'
         	, 'agency_nm'
         	, 'agency_zipcode'
         	, 'agency_addr1'
         	, 'agency_addr2'
         	, 'agency_tel'
         	, 'engineer_nm'
         	, 'engineer_tel'
         	, 'ceo_nm'
         	, 'ceo_tel'
         	, 'visit_yn'
         	, 'use_yn'
         	, 'area_summary'
         	, 'member_id'
         	, 'member_nm'
         	, 'remark'
         	, 'insert_id'
         	, 'insert_dt'
         	, 'update_id'         	
         	, 'update_dt'
        ]
    });
	
    store = Ext.create('Ext.data.Store', {
        pageSize: 25,
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxHappyAgencyInfoList',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
            },
            simpleSortMode: true
        },
        sorters: [{
            property: 'd.dept_cd',
            direction: 'ASC'
        }]
    });

    var columns = [
        {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
			dataIndex : 'agency_cd',
			text : '대리점코드',
			width : 80,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'agency_nm',
			text : '대리점명',
			width : 100,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'area_summary',
			text : '해피매니저 담당지역',
			width : 200,
			align : 'center',
			sortable : true
		}, 
		{
			dataIndex : 'agency_addr1',
			text : '대리점 주소',
			width : 200,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'agency_tel',
			text : '대리점전화번호',
			width : 120,
			align : 'center',
			sortable : true,
			renderer: maskPhoneNo
		}, {
			dataIndex : 'engineer_nm',
			text : '기사명',
			width : 100,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'engineer_tel',
			text : '기사전화번호',
			width : 120,
			align : 'center',
			sortable : false,
			renderer: maskPhoneNo
		}, {
			dataIndex : 'ceo_nm',
			text : '대표자명',
			width : 100,
			align : 'center',
			sortable : false
		}, {
			dataIndex : 'ceo_tel',
			text : '대표자전화번호',
			width : 120,
			align : 'center',
			sortable : true,
			renderer: maskPhoneNo
		}, {
			dataIndex : 'member_id',
			text : '담당자아이디',
			width : 80,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'member_nm',
			text : '담당자명',
			width : 100,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'visit_yn',
			text : '내방여부',
			width : 80,
			align : 'center',
			sortable : true
		}, {
			dataIndex : 'insert_id',
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
			dataIndex : 'update_id',
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
    
    var visitYNStore = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"Y", "name":"가능"},
            {"code":"N", "name":"불가"}
        ]
    });
    
    var useYNStore = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"Y", "name":"사용"},
            {"code":"N", "name":"미사용"}
        ]
    });	
    
    var searchType = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"d.dept_nm", "name":"대리점명"},
            {"code":"d.dept_cd", "name":"대리점코드"},
            {"code":"a.engineer_nm", "name":"기사명"},
            {"code":"a.ceo_nm", "name":"대표자명"}
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
        value: 'd.dept_nm'
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
		        value: '',
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
		        value: '',
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
			comboSearch,
	        {
	            width: 200,
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
    
    var leftForm = {
		xtype: 'panel',		
		flex: 2,
		minWidth: 700,
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
		    }, {
		    	xtype: 'button',
		    	text: '엑셀다운로드',
		    	align:'right',
		    	style:'text-align:right',		    	
		    	iconCls: 'icon-excel',
		    	margin: '0 0 0 5px',
		    	handler: function(){
		    		insertPop();
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
				pageSize: 25,
				store: store,
				displayInfo: true,
				displayMsg: '{0} - {1} of {2} 건',
				emptyMsg: "데이터가 없습니다."
			}),
			listeners: {
	        	'celldblclick': function(iView, iCellEl, iColIdx, iStore, iRowEl, iRowIdx, iEvent) {
	        		loadData(iRowIdx);
	        	}
	        }
	    }]
    } 
    
    var loadData = function(iRowIdx) {
    	
    	insertform.getForm().reset();
    	
		if(iRowIdx != undefined) {
			
			var rec = store.getAt(iRowIdx);
			
			insertform.getForm().loadRecord(rec);
			
			insertform.getForm().findField("agency_tel").setValue(maskPhoneNo(rec.data.agency_tel));
			insertform.getForm().findField("engineer_tel").setValue(maskPhoneNo(rec.data.engineer_tel));
			insertform.getForm().findField("ceo_tel").setValue(maskPhoneNo(rec.data.ceo_tel));
			
			if(rec.data.visit_yn == "") {
				insertform.getForm().findField("visit_yn").setValue("Y");
			}
			
			member_id = rec.data.member_id;
			agency_cd = rec.data.agency_cd;
			
			//serviceAreaStore.proxy.extraParams = {"agency_cd": agency_cd};
			//serviceAreaStore.load();
		}	    	
		
    	if(member_id == "") {
    		url = COMMON_URL + '/ajaxAgencyInfoInsert';
		} else {
			url = COMMON_URL + '/ajaxAgencyInfoUpdate';
		}
    }
    
    //팝업 form
    var insertform = Ext.create('Ext.form.Panel', {
    	id: 'insertform',
    	title: '홈케어지점관리',
        bodyPadding: 10,	   
	    border: 1,
	    margins: '0 0 5 0',
	    defaultType: 'textfield',
	    height: 380,
	    layout: 'anchor',
	    fieldDefaults: {
	        labelWidth: 70
	    }, 
	    items: [
			{
			    xtype: 'hiddenfield',
			    name: 'arr_area_cd'
			},
			{
			    xtype: 'hiddenfield',
			    name: 'arr_sido'
			},
			{
			    xtype: 'hiddenfield',
			    name: 'arr_sigungu'
			},
			{
			    xtype: 'hiddenfield',
			    name: 'agency_cd'
			},
			{
			    xtype: 'hiddenfield',
			    name: 'gubun',
			    value: '2'
			},
			{
	            xtype: 'fieldcontainer',            
	            layout: 'hbox',     
	            fieldLabel: '대리점',
	            defaultType: 'textfield',
	            afterLabelTextTpl: [MARK_ASTERISK],
	            items: [{
	                name: 'agency_nm',
	                flex: 1,
	                emptyText: '대리점명'
	            }, {
	                name: 'agency_tel',
	                margin: '0 0 0 5', 
	                flex: 1,
	                emptyText: '전화번호',
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
	            }]
	        },	        
	        {
	            xtype: 'fieldcontainer',            
	            layout: 'hbox',     
	            fieldLabel: '기사',
	            defaultType: 'textfield',
	            items: [{
	                name: 'engineer_nm',
	                flex: 1,
	                emptyText: '기사명'
	            }, {
	                name: 'engineer_tel',
	                margin: '0 0 0 5', 
	                flex: 1,
	                emptyText: '전화번호',
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
	            }]
	        },
	        {
	            xtype: 'fieldcontainer',            
	            layout: 'hbox',     
	            fieldLabel: '대표자',
	            defaultType: 'textfield',
	            items: [{
	                name: 'ceo_nm',
	                flex: 1,
	                emptyText: '대표자명'
	            }, {
	                name: 'ceo_tel',
	                margin: '0 0 0 5', 
	                flex: 1,
	                emptyText: '전화번호',
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
	            }]
	        },
	        {
	            xtype: 'fieldcontainer',            
	            layout: 'hbox',     
	            fieldLabel: '대리점주소',
	            defaultType: 'textfield',
	            items: [{
	                name: 'agency_zipcode',
	                width: 60,
	                readOnly: true,
	                editable: false
	            }, {
	    	    	xtype: 'button',
	    	    	id: 'btnLoadCust',	    	    	
	    	    	align:'right',
	    	    	style:'text-align:right',
	    	    	iconCls: 'icon-search',
	    	    	margin: '0 0 0 5',
	    	    	handler: function() {
	    	    		zipcode('setZipcode1');
	    	    	}
	    	    }, {   
				    name: 'agency_addr1',
				    flex: 1,
				    margin: '0 0 0 5',
				    readOnly: true,
	                editable: false
				}]
	        },			
			{   
			    name: 'agency_addr2',
			    fieldLabel: '상세주소',
			    anchor: '100%'
			},
			{
	            xtype: 'fieldcontainer',            
	            layout: 'hbox',     
	            fieldLabel: '담당자',
	            defaultType: 'textfield',
	            afterLabelTextTpl: [MARK_ASTERISK],
	            items: [{
				    xtype: 'hiddenfield',
				    name: 'member_id'
				}, {
	                name: 'member_nm',
	                flex: 1,
	                readOnly: true,
	                editable: false
	            }, {
	    	    	xtype: 'button',	    	    		    	    	
	    	    	align:'right',
	    	    	style:'text-align:right',
	    	    	iconCls: 'icon-search',
	    	    	margin: '0 0 0 5',
	    	    	handler: function() {
	    	    		searchMemberInfoPop('setMemberId');
	    	    	}
	    	    }, {   
	    	    	xtype: 'combo',
	    	    	fieldLabel: '내방여부',
	    	    	labelWidth: 60,
	    	    	store: visitYNStore,  
	    	        name: 'visit_yn',
	    	        queryMode: 'local',
	    	        displayField: 'name',
	    	        valueField: 'code',
	    	        editable: false,
	    		    padding: '0 0 0 5',
	    	        value: 'Y'
				}]
	        },
	        {   
			    xtype: 'textareafield',
				name: 'area_summary',
			    fieldLabel: '담당지역',
			    anchor: '100%',
			    height: 40
			},
			{   
			    xtype: 'textareafield',
				name: 'remark',
			    fieldLabel: '비고',
			    anchor: '100%',
			    height: 40
			},
			{   
    	    	xtype: 'combo',
    	    	fieldLabel: '사용여부',    	    	
    	    	store: useYNStore,  
    	        name: 'use_yn',
    	        queryMode: 'local',
    	        displayField: 'name',
    	        valueField: 'code',
    	        editable: false,
    	        value: 'Y'
			}
	    ],
	    buttons: [    	  	
    	  	'->',
    	  	{
    	  		icon: COMMON_URL + '/common/images/default/icons/accept.png',
    		    text: '홈케어지역추가',
    		    itemId: 'btnServiceArea',
    		    scope: this,
    		    handler: popServiceArea
    	  	},
    	  	{
    	  		icon: COMMON_URL + '/common/images/default/icons/accept.png',
    		    text: '등록된홈케어지역',
    		    itemId: 'btnServiceAreaList',
    		    scope: this,
    		    handler: popServiceArea2
    	  	},
    	  	{
    	  		icon: COMMON_URL + '/common/images/default/icons/accept.png',
    		    text: '홈케어정보 저장',
    		    itemId: 'save',
    		    scope: this,
    		    handler: onSave
    	  	}]
	});
    
    var rightForm = {
		xtype: 'panel',
		border: 0,
		width: 500,		
		minWidth: 500,
		maxWidth: 500,
		layout: {
	        type: 'vbox',       // Arrange child items vertically
	        align: 'stretch'
	    },
	    items: [insertform]
    }
    
	Ext.create('Ext.panel.Panel', {
		id:'Content',
	    title: '홈케어지점관리',
	    flex: 1,
	    height: FRAME_CONTENT_HEIGHT,
	    renderTo: Ext.getBody(),
	    layout: {
	        type: 'hbox',       // Arrange child items vertically
	        align: 'stretch',    // Each takes up full width
	        padding: 5
	    },
	    items: [leftForm, { xtype: 'splitter' }, rightForm]
	});
    
    function onSave() {
    	
    	var form = Ext.getCmp("insertform").getForm();    	
    	
        var agency_cd = form.findField("agency_cd");
        var agency_nm = form.findField("agency_nm");
        
        var member_id = form.findField("member_id");
        var member_nm = form.findField("member_nm");
        
        var visit_yn = form.findField("visit_yn");
        
        var agency_tel = form.findField("agency_tel");
        var engineer_tel = form.findField("engineer_tel");
        var ceo_tel = form.findField("ceo_tel");
        
        var use_yn = form.findField("use_yn");
        
        var arr_area_cd = "";
    	var arr_sido = "";
    	var arr_sigungu = "";
    	
    	var sido = "";
    	var sigungu = "";
    	var area_cd = "";
                
        if(agency_cd.getValue() == "") {					
			focusMsgAlert('Warning', '대리점을 선택해 주세요', agency_nm);
			return;
		}
        
        if(member_id.getValue() == "") {					
			focusMsgAlert('Warning', '담당자를 선택해 주세요', member_nm);
			return;
		}
        
        if(visit_yn.getValue() == "") {					
			focusMsgAlert('Warning', '내방여부를 선택해 주세요', visit_yn);
			return;
		}
        
        if(use_yn.getValue() == "") {					
			focusMsgAlert('Warning', '사용여부를 선택해 주세요', use_yn);
			return;
		}
        
        agency_tel.setValue(remainNumber(agency_tel.getValue()));
        engineer_tel.setValue(remainNumber(engineer_tel.getValue()));
		ceo_tel.setValue(remainNumber(ceo_tel.getValue()));
        
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
    
    
    function popServiceArea() {
    	
    	var form = Ext.getCmp("insertform").getForm();    	
    	
        var agency_cd = form.findField("agency_cd").getValue();
        var agency_nm = form.findField("agency_nm").getValue();
        
        if(agency_cd == "") {
        	Ext.Msg.alert('Notice', '홈케어지역을 추가할 대리점을 먼저 선택해 주세요!');
        } else {
        	window.open(COMMON_URL+'/jsp/System/HappyAgencyPop.jsp?agency_cd='+agency_cd+'&agency_nm='+agency_nm,'pop1','width=800, height=600');
        }
    }
    
    function popServiceArea2() {
    	var form = Ext.getCmp("insertform").getForm();    	
    	
        var agency_cd = form.findField("agency_cd").getValue();
        var agency_nm = form.findField("agency_nm").getValue();
        
        if(agency_cd == "") {
        	Ext.Msg.alert('Notice', '홈케어지역을 조회할 대리점을 먼저 선택해 주세요!');
        } else {
        	window.open(COMMON_URL+'/jsp/System/HappyAgencySearchPop.jsp?agency_cd='+agency_cd+'&agency_nm='+agency_nm,'pop2','width=800, height=600');
        }
    }
   
	// form reload
	function reload() {
		
		var form = Ext.getCmp('searchForm').getForm();
		
		var sdate = form.findField("sdate");
		var edate = form.findField("edate");
		
		if((sdate.getSubmitValue() == "" && edate.getSubmitValue() != "") || 
				(sdate.getSubmitValue() != "" && edate.getSubmitValue() == "")) {
			Ext.Msg.alert('Notice', '조회기간을 시작일자와 종료일자 모두 입력해 주세요!');
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
	reload();		
});

function setMemberId(member_id, member_nm) {
	
	var form = Ext.getCmp("insertform").getForm();
	
	form.findField("member_id").setValue(member_id);
	form.findField("member_nm").setValue(member_nm);
}

function setZipcode1(zipcode, address1) {
	
	var form = Ext.getCmp('insertform').getForm();
	
	form.findField("agency_zipcode").setValue(zipcode);
	form.findField("agency_addr1").setValue(address1);
}