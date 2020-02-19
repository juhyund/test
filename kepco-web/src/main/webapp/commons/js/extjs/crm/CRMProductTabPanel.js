/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : CRMProductTabPanel.js
* @Author : kyunghee.yoon
* @Date : 2015.10.30
**************************************/

var comboSite = Ext.create('Ext.form.ComboBox', {
    store: siteStore,        
    width: 120,  
    id: 'site',
    name: 'site',
    queryMode: 'local',
    displayField: 'name',
    valueField: 'code',
    emptyText: '사이트구분',
    value: '1',
    editable: false,
    listeners: {
    	change: function(combo, record, index) { 
    		
    		comboPrdCate1.clearValue();
    		comboPrdCate2.clearValue();
    		comboPrdNo.clearValue();
    		
    		prdCate1Store.getProxy().extraParams = {"site": combo.lastValue};
    		prdCate1Store.load();
        }
    }
});

var comboPrdCate1 = Ext.create('Ext.form.ComboBox', {
    store: prdCate1Store,
    width: 130,
    id: 'prd_cate1',
    name: 'prd_cate1',
    queryMode: 'local',
    displayField: 'cate_nm',
    valueField: 'cate',        
    padding: '0 0 0 5',
    emptyText: '제품군',
    editable: false,
    listeners: {
    	change: function(combo, record, index) {                     		
    		
    		comboPrdCate2.clearValue();
    		comboPrdNo.clearValue();
    		
    		prdCate2Store.getProxy().extraParams = {"site": Ext.getCmp("site").getValue(), "prd_cate1": combo.lastValue};
    		prdCate2Store.load();
        }
    }
});

var comboPrdCate2 = Ext.create('Ext.form.ComboBox', {
    store: prdCate2Store,
    width: 130,   
    id: 'prd_cate2',
    name: 'prd_cate2',
    queryMode: 'local',
    displayField: 'cate_nm',
    valueField: 'cate',        
    padding: '0 0 0 5',
    emptyText: '모델군',
    editable: false,
    listeners: {
    	change: function(combo, record, index) {                     		
    	
    		comboPrdNo.clearValue();
    		
    		prdNoStore.getProxy().extraParams = {"site": Ext.getCmp("site").getValue(), "prd_cate1": Ext.getCmp("prd_cate1").getValue(), "prd_cate2": combo.lastValue};
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
    listeners: {    	
    	change: function(combo, record, index) {
    		
    		// 제품명
    		var form = Ext.getCmp("serviceFormPanel").getForm();
    		var service_no = form.findField("service_no").getValue();
    		
    		if(service_no == "") {
	    		form.findField("prd_nm").setValue(combo.rawValue);
	    		
	    		// 불량코드1선택
	    		badCode1Store.getProxy().extraParams = {"prd_no": combo.lastValue};
	    		badCode1Store.load();	    		
    		}
        }
    }
});

//년도
var comboYear = Ext.create('Ext.form.ComboBox', {
	fieldLabel: '제조년월',
	store: yearStore,
    width: 130,        
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
    emptyText: '제조번호구분'
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
    emptyText: '제품구매처'
});

var fileListeners = {
	"change" : function(me, value, eOpts) {	            		
		var ext = value.slice(value.indexOf(".") + 1).toLowerCase().trim();		
		var extFormat = /(jpg)/;
		if(!extFormat.test(ext))
        {
			Ext.Msg.alert('Warning', '허용된 확장자가 아닙니다.\n파일을 다시 선택하여 주십시오');
			me.reset();
			return;
		}	
	}
};

// 제품 FORM PANEL
var productFormPanel = new Ext.form.Panel({		
	border: 0,	
	padding: '7 7 7 7',
	defaultType: 'textfield',
	fieldDefaults: {		            
		labelAlign: 'center',
		labelWidth: 60,
		labelSeparator: "",
	    enableKeyEvents: true
	},
	defaults: {anchor: '100%'},
	items: [
	    {
		    xtype: 'fieldcontainer',            
		    layout: 'hbox',  
		    defaultType: 'textfield',
		    items: [{
		        xtype: 'fieldcontainer',            
		        layout: 'hbox',
		        defaultType: 'textfield',
		        flex: 1,    	            
		        fieldLabel: '보유제품',
		        items: [
		            comboSite,
					comboPrdCate1,
					comboPrdCate2,
					comboPrdNo
		        ]
	        }]
	    }, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [
	        comboYear,
			comboMonth, 
			comboManufactureType,
			{	
	        	name: 'manufacture_no',
	            width: 130,
	            margin: '0 0 0 5',
	            emptyText: '제조번호'
	        },
	        comboBuyShop
	        ]
	    }, {
	        xtype: 'fieldcontainer',            
	        layout: 'hbox',         
	        defaultType: 'textfield',
	        items: [{
	        	fieldLabel: '비고',
	        	name: 'prd_remark',
	            flex:1
	        }, {
	        	xtype: 'checkbox',
	        	name: 'hold_yn',        	
	        	boxLabel  : '제품보유',        	
	        	inputValue: 'Y',
	        	width: '150',
	        	margin: '0 0 0 5',
	        	checked   : true
	        }]
	    },
	    {
	        xtype: 'fieldcontainer',
	        fieldLabel: '첨부',
	        defaultType: 'textfield',
	        layout: 'hbox',
	        items: [{        	
	            xtype: 'button',
	            text: '보유제품 파일업로드',
	            iconCls: 'icon-upload',
	            margin: '0 0 0 0',
	        	handler: function() {
	        		
	        		var cform = custInfoFormPanel.getForm();
	        		var pform = productFormPanel.getForm();
	        		
	        		var cust_no = cform.findField("cust_no").getValue();
	        		var prd_no = pform.findField("prd_no").getSubmitValue();
	        		var prd_nm = pform.findField("prd_no").rawValue;
	        		
	        		if(cust_no == "") {
	        			Ext.Msg.alert('Notice', '고객정보를 조회해 주세요');
	        			return;
	        		} else if(prd_no == "") {
	        			Ext.Msg.alert('Notice', '제품정보를 조회해 주세요');
	        			return;
	        		} else {
	        			fileUploadWin(cust_no, prd_no, prd_nm);
	        		}
	        	}
	        }, {
	            xtype: 'button',
	            text: '보유제품 파일보기',
	            iconCls: 'icon-list',
	            margin: '0 0 0 5',
	        	handler: function() {
	        		
	        		var cform = custInfoFormPanel.getForm();
	        		var pform = productFormPanel.getForm();
	        		
	        		var cust_no = cform.findField("cust_no").getValue();
	        		var prd_no = pform.findField("prd_no").getSubmitValue();	        		
	        		var prd_nm = pform.findField("prd_no").rawValue;
	        		
	        		if(cust_no == "") {
	        			Ext.Msg.alert('Notice', '고객정보를 조회해 주세요');
	        			return;
	        		} else {
	        			fileUploadWin(cust_no, prd_no, prd_nm);
	        		}
	        	}
	        }]
	    }
	]
});


//보유제품
var custPrdListPanel = new Ext.create('Ext.grid.Panel', {
	border: 0,
	flex: 1,
	height: 125,
	store: custPrdListStore, 
	columns: [
	    {xtype: 'rownumberer', header : '번호', align: 'center', width: 40},
	    { text: '제품번호',  dataIndex: 'prd_serial_no', align:'center', width: 100 },
	    { text: '제품군', dataIndex: 'prd_cate1_nm', align:'center', width: 110 },
	    { text: '품목', dataIndex: 'prd_cate2_nm', align:'center', width: 110 },
	    { text: '제품명', dataIndex: 'prd_nm', align:'center', flex: 1 },
	    { text: '제조일자', dataIndex: 'manufacture_year', align:'center', width: 60, renderer: manufactureDate},
	    { text: '제조번호', dataIndex: 'manufacture_no', align:'center', width: 80 },	    
	    { text: '파일', dataIndex: 'file_cnt', align:'center', width: 50, renderer: function(dat) {
	    	
	    	var cform = custInfoFormPanel.getForm();
    		var pform = productFormPanel.getForm();
    		
    		var cust_no = cform.findField("cust_no").getValue();
    		var prd_no = pform.findField("prd_no").getSubmitValue();
    		var prd_nm = pform.findField("prd_no").rawValue;
    		
    		
    		return "<a href=\"javascript:fileUploadWin('"+cust_no+"', '"+prd_no+"', '" + prd_nm +"')\">" + dat + "</a>" ;
    		
	    }}
	],	
    stripeRows: true,
    listeners: {
     	'celldblclick': function(iView, iCellEl, iColIdx, iStore, iRowEl, iRowIdx, iEvent) {
     		setCustPrdInfo(iRowIdx);
     	}
    }
});

// 보유제품 TAB PANEL
var productTabPanel = new Ext.tab.Panel({	 	
	border: 1,
	height: 150,		
	layout: {
        type: 'vbox',
        align: 'stretch'
    },
    items: [{
	    title: '제품정보',
	    items: [productFormPanel]
	},
	{
	    title: '보유제품리스트',
	    items: [custPrdListPanel]
	}]
});


/**
 * 보유제품리스트
 */
function loadCustPrdList(cust_no) {	
	custPrdListStore.getProxy().extraParams = {'cust_no':cust_no};
	custPrdListStore.load();	
}

/**
 * 보유제품 카테고리 1 load
 */
function loadPrdCate1() {
	
	var site = productFormPanel.getForm().findField("site").getSubmitValue();
	
	prdCate1Store.getProxy().extraParams = {"site": site};
	prdCate1Store.load();
}
/**
 * 보유제품 선택
 * @param iRowIdx
 */
function setCustPrdInfo(iRowIdx) {
	
	var form = productFormPanel.getForm();
	var rec = custPrdListStore.getAt(iRowIdx);
	
	var get_site = rec.get("site");
	var get_prd_cate1 = rec.get("prd_cate1");
	var get_prd_cate2 = rec.get("prd_cate2");
	var get_prd_no = rec.get("prd_no");
	
	form.loadRecord(rec);
	
	setPrdInfoForm(get_site, get_prd_cate1, get_prd_cate2, get_prd_no);
	
	productTabPanel.setActiveTab(0);
}

/**
 * 보유제품 세팅
 * @param get_site
 * @param get_prd_cate1
 * @param get_prd_cate2
 * @param get_prd_no
 */
function setPrdInfoForm(get_site, get_prd_cate1, get_prd_cate2, get_prd_no) {
	
	var form = productFormPanel.getForm();
	
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
					prdNoStore.getProxy().extraParams = {"site": get_site, "prd_cate1": get_prd_cate1, "prd_cate2": get_prd_cate2};
					prdNoStore.load({
						
						callback: function(records, operation, success) {							
							
							form.findField("prd_no").setValue(get_prd_no);
							
							// 불량코드1선택
				    		badCode1Store.getProxy().extraParams = {"prd_no": get_prd_no};
				    		badCode1Store.load();
						}
					});
				} // call back
			});
		} // call back
	});
}

loadPrdCate1();