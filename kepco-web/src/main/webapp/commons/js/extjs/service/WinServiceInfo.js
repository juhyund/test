/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : WinServiceInfo.js
* @Author : kyunghee.yoon
* @Date : 2016.01.14
**************************************/
Ext.require([
	'Ext.tree.*',
	'Ext.form.field.Text',
	'Ext.resizer.Splitter',
	'Ext.grid.Panel',
	'Ext.grid.column.RowNumberer'
]);

var SERVICE_CODE_AS = '10'; // 서비스구분 AS
var SERVICE_CODE_ORDER = '11'; // 서비스구분 주문 
var SERVICE_CODE_GO1 = '12'; // 서비스구분 찾서 
var SERVICE_CODE_HAPPY = '13'; // 홈케어
var SERVICE_CODE_SALES = '14'; // 서비스구분 보상판매
var SERVICE_CODE_GENERAL = '15'; // 고객상담
var SERVICE_CODE_CLAIME1 = '16'; // 클레임(일반)
var SERVICE_CODE_CLAIME2 = '17'; // 클레임(일반)
var SERVICE_CODE_ETC = '18'; // 내방

// 불량유형1
var badCode1Store = Ext.create('Ext.data.Store', {    	  
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxPrdBadCode1',
        reader: {root: 'result'}
    },
    fields: [{ name: 'bad_cd' },{ name: 'bad_nm' }],
    autoLoad:true
});

// 불량유형 2
var badCode2Store = Ext.create('Ext.data.Store', {    	  
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxPrdBadCode2',
        reader: {root: 'result'}
    },
    fields: [{ name: 'bad_cd' },{ name: 'bad_nm' }],
    autoLoad:true
});

// 서비스구분코드
var serviceTypeStore = Ext.create('Ext.data.Store', {    	  
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxServiceCodeCombo',
        reader: {root: 'result'}           
    },
    fields: [{ name: 'code' },{ name: 'code_nm' }],
    autoLoad:true  
});

// 서비스상태코드
var serviceStatusStore = Ext.create('Ext.data.Store', {    	  
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxServiceStatusCombo',
        reader: {root: 'result'}           
    },
    fields: [{ name: 'code' },{ name: 'code_nm' }]
});

var iYear = Ext.Date.format(new Date(),'Y');
var iMonth = Ext.Date.format(new Date(),'m');

var yearStore = new Ext.data.ArrayStore({        
    fields : ['code','val']
});

var monthStore = new Ext.data.ArrayStore({        
    fields : ['code','val']
});

for(i = 0; i < 11; i++) {
	year = (iYear - i)+"";		
	yearStore.add({'code' : year, 'val' : year + '년'});
}

for(i = 0; i < 12; i++) {
	mon = i+1;
	monthStore.add({'code' : lpad(mon,2,'0'), 'val' : lpad(mon,2,'0') + '월'});
}

//제품군
var prdCate1Store = Ext.create('Ext.data.Store', {
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxPrdCate1',
        reader: {root: 'result'},
        simpleSortMode: true
    },
    fields: [{ name: 'cate' },{ name: 'cate_nm' }]
});

// 모델군
var prdCate2Store = Ext.create('Ext.data.Store', {
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxPrdCate2',
        reader: {root: 'result'},
        simpleSortMode: true
    },
    fields: [{ name: 'cate' },{ name: 'cate_nm' }]
});

// 제품
var prdNoStore = Ext.create('Ext.data.Store', {
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxPrdNoCombo',
        reader: {root: 'result'},
        simpleSortMode: true
    },
    fields: [{ name: 'prd_no' },{ name: 'prd_serial_no' },{ name: 'prd_nm' },{ name: 'site' }]
});

// 제조번호구분
var manufactureTypeStore = Ext.create('Ext.data.Store', {    	  
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxCodeCombo',
        reader: {root: 'result'},           
        extraParams: {class_cd: 'MT', use_yn:'Y', display_yn:'Y'}
    },
    fields: [{ name: 'code' },{ name: 'code_nm' }],
    autoLoad:true  
});

// 제품구매처
var buyShopStore = Ext.create('Ext.data.Store', {    	  
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxCodeCombo',
        reader: {root: 'result'},           
        extraParams: {class_cd: 'PS', use_yn:'Y', display_yn:'Y'}
    },
    fields: [{ name: 'code' },{ name: 'code_nm' }],
    autoLoad:true  
});

var comboServiceType = Ext.create('Ext.form.ComboBox', {
    store: serviceTypeStore,
    name: 'service_type',
    fieldLabel: '서비스구분',
    flex:1,
    displayField: 'code_nm',
    valueField: 'code',
    emptyText: '선택',
    editable: false,
    value: '',
    afterLabelTextTpl: [MARK_ASTERISK],
    listeners: {
    	change: function(combo, record, index) {
    		
			comboServiceStatus.clearValue();
    		serviceStatusStore.getProxy().extraParams = {"service_cd1": combo.lastValue};
    		serviceStatusStore.load();
    		
    		var form = serviceInfoform.getForm();
    		var site = form.findField("site").getValue();
    		
    		if(combo.lastValue == SERVICE_CODE_GENERAL) { // 고객상담
    			
    			// 불량코드선택
    			comboPrdBadCode1.clearValue();
    			comboPrdBadCode2.clearValue();
	    		badCode1Store.getProxy().extraParams = {"prd_no": "99999", "site": site};
	    		badCode1Store.load();
	    		
    		} else {
    			
    			var prd_no = serviceInfoform.getForm().findField("prd_no").getValue();
    			if(prd_no == "0") prd_no = "";
    			
				badCode1Store.getProxy().extraParams = {"prd_no": prd_no, "site": site};
				badCode1Store.load();
    			
    		}
        }
    }
});


var comboServiceStatus = Ext.create('Ext.form.ComboBox', {
    store: serviceStatusStore,
    name: 'service_status',
    fieldLabel: '처리상태',
    flex:1,
    displayField: 'code_nm',
    valueField: 'code',
    emptyText: '선택',
    editable: false,
    value: '',    
    margin: '0 0 0 15',
    afterLabelTextTpl: [MARK_ASTERISK]
});

var comboPrdBadCode1 = Ext.create('Ext.form.ComboBox', {
    store: badCode1Store,
    name: 'bad_cd1',    
    fieldLabel: '불량유형',
    flex:1,
    displayField: 'bad_nm',
    valueField: 'bad_cd',
    emptyText: '선택',
    editable: false,
    value: '',
    afterLabelTextTpl: [MARK_ASTERISK],
    listeners: {
    	'select' : function(combo, record, index) {
    		
    		var form = serviceInfoform.getForm();
    		var site = form.findField("site").getValue();
    		var prd_no = form.findField("prd_no").getValue();
    		
    		if(serviceInfoform.getForm().findField("service_type").getValue() == SERVICE_CODE_GENERAL) {
    			prd_no = "99999";
    		}
    		
    		if(prd_no != "") {
    			// 불량코드2선택
	    		comboPrdBadCode2.clearValue();
	    		badCode2Store.getProxy().extraParams = {"prd_no": prd_no, "bad_m_cd": combo.lastValue, "site":site};
	    		badCode2Store.load();
    		}
    	}
    }
});

var comboPrdBadCode2 = Ext.create('Ext.form.ComboBox', {
    store: badCode2Store,
    name: 'bad_cd2',   
    fieldLabel: '불량유형상세',
    flex:1,
    displayField: 'bad_nm',
    valueField: 'bad_cd',
    emptyText: '선택',
    editable: false,
    margin: '0 0 0 15',
    value: '',
    afterLabelTextTpl: [MARK_ASTERISK]
});


var comboPrdCate1 = Ext.create('Ext.form.ComboBox', {
    store: prdCate1Store,
    width: 130,
    id: 'prd_cate1',
    name: 'prd_cate1',
    queryMode: 'local',
    displayField: 'cate_nm',
    valueField: 'cate',
    emptyText: '제품군',
    editable: false,
    value: '',
    afterLabelTextTpl: [MARK_ASTERISK],
    listeners: {
    	select: function(combo, record, index) {
    		
    		// 제품명
    		var form = serviceInfoform.getForm();
    		var site = form.findField("site").getValue();
    		var prd_cate1 = combo.lastValue;
    		
    		comboPrdCate2.clearValue();
    		comboPrdNo.clearValue();
    		
    		prdCate2Store.getProxy().extraParams = {"site": site, "prd_cate1": prd_cate1};
    		prdCate2Store.load();
        }
    }
});

var comboPrdCate2 = Ext.create('Ext.form.ComboBox', {
    store: prdCate2Store,
    width: 130,   
    name: 'prd_cate2',
    queryMode: 'local',
    displayField: 'cate_nm',
    valueField: 'cate',        
    padding: '0 0 0 5',
    emptyText: '모델군',
    editable: false,
    value: '',
    afterLabelTextTpl: [MARK_ASTERISK],
    listeners: {
    	select: function(combo, record, index) {                     		
    	
    		comboPrdNo.clearValue();
    		
    		// 제품명
    		var form = serviceInfoform.getForm();
    		var service_no = form.findField("service_no").getValue();
    		
    		var site = form.findField("site").getValue();
    		var prd_cate1 = form.findField("prd_cate1").getValue();
    		var prd_cate2 = combo.lastValue;
    		
    		prdNoStore.getProxy().extraParams = {"site": site, "prd_cate1": prd_cate1, "prd_cate2": prd_cate2};
    		prdNoStore.load();
        }
    }
});


var comboPrdNo = Ext.create('Ext.form.ComboBox', {
    store: prdNoStore,
    flex: 1,       
    name: 'prd_no',
    queryMode: 'local',
    displayField: 'prd_nm',
    valueField: 'prd_no',        
    padding: '0 0 0 5',
    emptyText: '제품',
    editable: false,
    value: '',
    afterLabelTextTpl: [MARK_ASTERISK],
    listeners: {    	
    	select: function(combo, record, index) {
    		
    		// 제품명
    		var form = serviceInfoform.getForm();
    		var service_no = form.findField("service_no").getValue();
    		var service_type = form.findField("service_type").getValue();    		
    		var site = form.findField("site").getValue();
    		
    		if(service_no != "") {  
    			if(service_type == SERVICE_CODE_GENERAL) {
    				// 불량코드1선택
    				badCode1Store.getProxy().extraParams = {"prd_no": "99999"};
    				badCode1Store.load();
    			} else {
    				// 불량코드1선택
    				badCode1Store.getProxy().extraParams = {"prd_no": combo.lastValue, "site":site};
    				badCode1Store.load();
    			}
    		}
        }
    }
});


//년도
var comboYear = Ext.create('Ext.form.ComboBox', {	
	store: yearStore,
    width: 75,        
    name: 'manufacture_year',
    queryMode: 'local',
    displayField: 'val',
    valueField: 'code',
    editable: false,
    padding: '0 0 0 0',
    emptyText: '년',
    value: iYear,
});

// 월
var comboMonth = Ext.create('Ext.form.ComboBox', {
    store: monthStore,
    width: 50,        
    name: 'manufacture_month',
    queryMode: 'local',
    displayField: 'val',
    valueField: 'code', 
    editable: false,
    padding: '0 0 0 5',
    emptyText: '월',
    value: iMonth
});

// 제조번호구분
var comboManufactureType = Ext.create('Ext.form.ComboBox', {
    store: manufactureTypeStore,
    width: 130,
    name: 'manufacture_type',
    queryMode: 'local',
    displayField: 'code_nm',
    valueField: 'code', 
    editable: false,
    padding: '0 0 0 5',
    emptyText: '제조번호구분',
    value: ''
});


// 구매처
var comboBuyShop = Ext.create('Ext.form.ComboBox', {
    store: buyShopStore,
    flex: 1,
    name: 'buy_shop',
    queryMode: 'local',
    displayField: 'code_nm',
    valueField: 'code', 
    editable: false,
    padding: '0 0 0 5',
    emptyText: '제품구매처',
    value: ''
});


var winServiceInfo = null;

//팝업 window
var winServiceInfoPop = function(service_no) {
	
	serviceDeliveryform.getForm().reset();
	
	if(!winServiceInfo) {
		
    	winServiceInfo = Ext.create('Ext.window.Window', {
            title: '서비스접수정보',
            height: 420,
            width: 600,
            closeAction: 'close',
            modal: false,
            resizable: false,
            draggable: true,
            items:[
                   serviceInfoform
            ]
        });
	}
	
	if(winServiceInfo.isVisible()) {
		winServiceInfo.hide();
	} else {
		loadDataServiceInfo(service_no);
		winServiceInfo.show();			
	}
}
var get_repair_dt2;
/**
 * 서비스 처리정보
 * @param service_no
 */
function loadDataServiceInfo(service_no) {

	var form = serviceInfoform.getForm();
	
	if(service_no != undefined && service_no != "") {
		
		Ext.Ajax.request({
		
	        url: COMMON_URL + '/ajaxServiceInfoDetailCRM',
	        params: { 'service_no' : service_no},
	        success: function(response) {	        	
	        	
	        	var obj = Ext.decode(response.responseText);	        	
	        	
	        	var serviceInfoData = obj.serviceInfoData;
	        	var servicePrdResult = obj.servicePrdResult;
	        	
	        	form.setValues(serviceInfoData);
	        	
	        	var get_site = serviceInfoData.site;
	        	var get_prd_cate1 = serviceInfoData.prd_cate1;
	        	var get_prd_cate2 = serviceInfoData.prd_cate2;
	        	var get_prd_no = serviceInfoData.prd_no;	        	
	        	var get_bad_cd1 = serviceInfoData.bad_cd1;
	        	var get_bad_cd2 = serviceInfoData.bad_cd2;
	        	var get_service_type = serviceInfoData.service_type;
	        	var get_repair_dt = serviceInfoData.repair_dt;
	        	var get_service_dt = serviceInfoData.service_dt;
	        	
	        	
	        	if(get_prd_no == "0") get_prd_no = "";
	        	
	        	setPrdInfoForm(get_site, get_prd_cate1, get_prd_cate2, get_prd_no, get_service_type);
	        	
	        	if(get_service_type == SERVICE_CODE_GENERAL) {	        		
	        		setBadCdForm("99999", get_bad_cd1, get_bad_cd2, get_site, get_service_type);
	        	} else {
	        		setBadCdForm(get_prd_no, get_bad_cd1, get_bad_cd2, get_site, get_service_type);
	        	}
	        	
	        	form.findField("manufacture_year").setValue(servicePrdResult.manufacture_year);
	        	form.findField("manufacture_month").setValue(servicePrdResult.manufacture_month);
	        	form.findField("manufacture_type").setValue(servicePrdResult.manufacture_type);
	        	form.findField("manufacture_no").setValue(servicePrdResult.manufacture_no);
	        	get_repair_dt2 = get_repair_dt;
	        	// console.log("get_repair_dt : "+get_repair_dt);
	        	form.findField("repair_dt").setValue(get_repair_dt);
	        	form.findField("service_dt").setValue(get_service_dt);
	        	
	        },
	        failure: function(result, request) {
	        	Ext.Msg.alert('Notice', "조회 중 오류가 발생하였습니다.");
	    		return;
			}
		});	
	}		
}

// 팝업 form
var serviceInfoform = Ext.create('Ext.form.Panel', {
	id: 'serviceInfoform',
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
        	name: 'site'
		},  
		{
			xtype: 'hiddenfield',
        	name: 'cust_no'
		}, 
		{
			xtype: 'hiddenfield',
        	name: 'cust_prd_seq_no'
		}, 
		{
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [{
				name: 'service_no',
				fieldLabel: '서비스번호',			        	        
		        editable: false,
		        readOnly: true,
		        flex: 1
			}, {
				name: 'site_nm',
				fieldLabel: '사이트',			        	        
		        editable: false,
		        readOnly: true,
		        flex: 1,
		        margin: '0 0 0 15'
			}]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [comboServiceType, comboServiceStatus]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [comboPrdBadCode1, comboPrdBadCode2]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [{
				name: 'insert_nm',
				fieldLabel: '접수자',			        	        
		        editable: false,
		        readOnly: true,
		        flex: 1
			}, {
				name: 'insert_dt',
				fieldLabel: '접수일시',
				editable: false,
			    readOnly: true,
		        flex: 1,
		        margin: '0 0 0 15'
			}]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [{
				name: 'repair_nm',
				fieldLabel: 'AS수리자',			        	        
		        editable: false,
		        readOnly: true,
		        flex: 1
			}, {
				name: 'repair_dt',
				fieldLabel: '수리일시',
		        flex: 1,
		        margin: '0 0 0 15'
			}]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [{
	        	xtype: 'hiddenfield',
		        flex: 1
			}, {
				name: 'service_dt',
				fieldLabel: '처리일시',
		        flex: 1,
		        margin: '0 0 0 294'
			}]
		}, {   
		    xtype: 'textareafield',
			name: 'memo',
		    fieldLabel: '상담내용',
		    height: 95
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        fieldLabel: '보유제품',	
	        defaultType: 'textfield',
	        items: [comboPrdCate1, comboPrdCate2, comboPrdNo],
	        afterLabelTextTpl: [MARK_ASTERISK]
		}, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        fieldLabel: '제조년월',	
	        defaultType: 'textfield',
	        afterLabelTextTpl: [MARK_ASTERISK],
	        items: 
	        	[
	        	 comboYear,
	        	 comboMonth, 
	        	 comboManufactureType,
	        	 {	
	        		 name: 'manufacture_no',
	        		 flex: 1,
	        		 margin: '0 0 0 5',
	        		 emptyText: '제조번호'
	        	 }
	        	 ]
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
        	
            var service_no = form.findField("service_no");
            
			if(service_no != "") { // 수정
				url = COMMON_URL + '/ajaxServiceInfoUpdate';
			}
											
            if (form.isValid()) {
                form.submit({
                	url: url,
                	submitEmptyText: false,
                    success: function(form, action) {	                    	
                       Ext.Msg.alert('Success', action.result.msg);
                       reload(service_no.getValue());
                       winServiceInfo.hide();
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
        	winServiceInfo.hide();
    	}
    }]
});


/**
 * 보유제품 세팅
 * @param get_site
 * @param get_prd_cate1
 * @param get_prd_cate2
 * @param get_prd_no
 */
function setPrdInfoForm(get_site, get_prd_cate1, get_prd_cate2, get_prd_no, get_service_type) {
	
	var form = serviceInfoform.getForm();
		
	// 제품군
	prdCate1Store.getProxy().extraParams = {"site": get_site};
	prdCate1Store.load({
		
		callback: function(records, operation, success) {				
		
			form.findField("prd_cate1").setValue(get_prd_cate1);
			
			// 모델군
			prdCate2Store.getProxy().extraParams = {"site": get_site, "prd_cate1": get_prd_cate1};
			prdCate2Store.load({
				
				callback: function(records, operation, success) {						
				
					form.findField("prd_cate2").setValue(get_prd_cate2);
					
					// 제품
					prdNoStore.getProxy().extraParams = {"site": get_site, "prd_cate1": get_prd_cate1, "prd_cate2": get_prd_cate2, "prd_no": get_prd_no};
					prdNoStore.load({						
						callback: function(records, operation, success) {
							form.findField("prd_no").setValue(Number(get_prd_no));
						}
					});
				} // call back
			});
		} // call back
	});
}

/**
 * 불량코드 세팅
 * @param get_prd_no
 * @param get_bad_cd1
 * @param get_bad_cd2
 */
function setBadCdForm(get_prd_no, get_bad_cd1, get_bad_cd2, get_site, get_service_type) {
	
	var form = serviceInfoform.getForm();
	if(get_prd_no == "0") get_prd_no = "";
	
	
	badCode1Store.getProxy().extraParams = {"prd_no": get_prd_no, "site":get_site, "service_type":get_service_type, "bad_m_cd":get_bad_cd1};
	badCode1Store.load({
			
		callback: function(records, operation, success) {				
			
			if(get_bad_cd1 != "") { 
				form.findField("bad_cd1").setValue(get_bad_cd1);
						
				// 불량코드2선택
	    		badCode2Store.getProxy().extraParams = {"prd_no": get_prd_no, "bad_m_cd": get_bad_cd1, "site":get_site, "service_type":get_service_type, "bad_cd":get_bad_cd2};
	    		badCode2Store.load({
				
	    			callback: function(records, operation, success) {	
	    				form.findField("bad_cd2").setValue(get_bad_cd2);
					}	
	    		
	    		});	
			}
		}
	});
}

				    		