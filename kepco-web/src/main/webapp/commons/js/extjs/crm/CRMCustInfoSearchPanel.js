/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : CRMCustInfoSearchPanel.js
* @Author : kyunghee.yoon
* @Date : 2015.10.30
**************************************/

//서비스상담이력
var searchListPanel = new Ext.create('Ext.grid.Panel', {
	border: 0,
	flex: 1,
	height: 310,
	store: custSearchStore, 
	columns: [
	    { xtype: 'rownumberer', header : '번호', align: 'center', width: 40},	    
		{ text: '고객명', dataIndex: 'cust_nm', align: 'center', width:80},
		{ text: '휴대번호', dataIndex: 'tel_mobile', align: 'center', renderer: maskPhoneNo},
		{ text: '전화번호', dataIndex: 'tel_home', align: 'center', renderer: maskPhoneNo},
		{ text: '주소', dataIndex: 'address1', flex: 1, renderer: rendererAddr}
	],
	tbar : ['휴대번호 : ', 
	{
		xtype: 'textfield',
		id: 'search_tel_mobile',
		name: 'search_tel_mobile',
		emptyText: '',
		width: 120,
		listeners: {
			specialkey: function(f, e) {
				if(e.getKey() == e.ENTER) custInfoSearch();
			}
		} 
	}, '|', {
        xtype: 'combo',
        id: 'searchfield',        
        store: new Ext.data.SimpleStore({
        	fields: ['id','value'],
        	data: [["cust_nm","고객명"], ["invoice_no","송장번호"], ["account_no","계좌번호"],  ["address1","주소"],  ["cust_no","고객번호"]]
        }),
        displayField: 'value',
        valueField: 'id',
        value: 'cust_nm',
        selectOnFocus: true,
        mode: 'local',
        typeAhead: true,
        editable: false,
        triggerAction: 'all',        
        width: 80
	}, {
	     xtype: 'textfield',
	     id: 'searchquery',
	     name: 'searchquery',
	     listeners: {
	    	 specialkey: function(f, e) {
	    		 if(e.getKey() == e.ENTER) custInfoSearch();
	    	 }
	     } 
	 }, {
	     xtype: 'button',
	     text: '검색',
	     tooltip: 'search',
	     handler: function() {
	    	 custInfoSearch();
	     }
	 }],
	 bbar: Ext.create('Ext.PagingToolbar', {
         store: custSearchStore,
         displayInfo: true,
         displayMsg: '{0} - {1} of {2}',
         emptyMsg: "검색결과가 없습니다."
     }),
     stripeRows: true,
     listeners: {
     	'celldblclick': function(iView, iCellEl, iColIdx, iStore, iRowEl, iRowIdx, iEvent) {
     		     		
     		loadCRMForm(iRowIdx);
     	}
     }
});



// 예약고객검색
var custBookingListPanel = new Ext.create('Ext.grid.Panel', {
	border: 0,
	flex: 1,
	height: 310,
	store: custBookingStore,
	columns: [
	    { xtype: 'rownumberer', header : '번호', align: 'center', width: 40},
		{ text: '고객명', dataIndex: 'cust_nm', align: 'center', width: 70},
		{ text: '휴대번호', dataIndex: 'tel_mobile', align: 'center', width: 90, renderer:MaskPhoneNo2},
		{ text: '예약일자', dataIndex: 'booking_date', align: 'center', width: 70, renderer:MaskDate},
		{ text: '예약시간', dataIndex: 'booking_time', align: 'center', width: 60 },
		{ text: '처리상태', dataIndex: 'booking_status_nm', align: 'center', width: 60},
		{ text: '등록일시', dataIndex: 'insert_dt', align: 'center', flex:1},
		{ text: '처리일시', dataIndex: 'process_dt', align: 'center', flex:1}
	],
	tbar : [
	{	
	    xtype: 'datefield',
	    id: 'sdate',
	    name: 'sdate',		
	    format: 'Ymd',
	    submitFormat: 'Ymd',
	    submitValue: true,
	    value: getWeekDay(),	
	    width: 80,
		emptyText: '등록일(시작)',
		listeners:  {
	        specialkey: function (f,e) {    
	            if (e.getKey() == e.ENTER) custBookingSearch();
	        }
	    }
	},
	{
		xtype: 'datefield',
	    id: 'edate',
	    name: 'edate',	
	    format: 'Ymd',
	    submitFormat: 'Ymd',
	    submitValue: true,
	    value: toDate,
	    width: 80,
		emptyText: '등록일(종료)',
		listeners:  {
	        specialkey: function (f,e) {    
	            if (e.getKey() == e.ENTER) custBookingSearch();
	        }
	    }
	},
	'|',
	{
        xtype: 'combo',
        id: 'booking_status',
        name: 'booking_status',
        store: new Ext.data.SimpleStore({
        	fields: ['id','value'],
        	data: [["BS001","예약대기"], ["BS002","통화완료"], ["BS003","예약취소"], ["","전체"]]
        }), 
        displayField: 'value',
        valueField: 'id',
        value: 'BS001',            
        editable: false,
        width: 80
	},
	'|',
	{
        xtype: 'combo', 
        id: 'searchfield2',
        name: 'searchfield2',
        store: new Ext.data.SimpleStore({
        	fields: ['id','value'],
        	data: [["cust_nm","고객명"], ["tel_mobile","휴대번호"]]
        }), 
        displayField: 'value',
        valueField: 'id',
        value: 'cust_nm',            
        editable: false,        
        width: 60
	}, {
	     xtype: 'textfield',
	     id: 'searchquery2',
	     name: 'searchquery2',
	     width: 100,
	     listeners: {
	    	 specialkey: function(f, e) {
	    		 if(e.getKey() == e.ENTER) custBookingSearch();
	    	 }
	     } 
	 }, {
	     xtype: 'button',
	     text: '검색',
	     tooltip: 'search',
	     handler: function() {
	    	 custBookingSearch();
	     }
	 }],
	 bbar: Ext.create('Ext.PagingToolbar', {
         store: custBookingStore,
         displayInfo: true,
         displayMsg: '{0} - {1} of {2}',
         emptyMsg: "검색결과가 없습니다."
     }),
     stripeRows: true, 
     listeners: {
      	'celldblclick': function(iView, iCellEl, iColIdx, iStore, iRowEl, iRowIdx, iEvent) {
      		
      		var rec = custBookingStore.getAt(iRowIdx);
      		
      		var booking_no = rec.get('booking_no');
      			
      		custBookingWin('','','','',booking_no);
      	}
     }
});


/**
 * 예약고객정보 검색
 */
function custBookingSearch() {
	
	var sdate = Ext.getCmp('sdate').getSubmitValue();
	var edate = Ext.getCmp('edate').getSubmitValue();
	var booking_status = Ext.getCmp('booking_status').getSubmitValue();
	var searchfield = Ext.getCmp('searchfield2').getValue();
	var searchquery = Ext.getCmp('searchquery2').getValue();
	
	if(sdate == "" && edate == "" && booking_status == "" && searchquery == "" ) {
		Ext.Msg.alert('Notice','검색조건을 하나 이상 입력해 주세요!');
		return;
	}
	
	if((sdate == "" && edate != "") || 
			(sdate != "" && edate == "")) {
		Ext.Msg.alert('Notice', '기간검색은 시작일자와 종료일자 모두 입력해 주세요!');
		return;
	}
	
	custBookingStore.getProxy().extraParams = {'searchfield':searchfield, 'searchquery':searchquery, 'booking_status':booking_status, 'sdate':sdate, 'edate':edate};
	custBookingStore.loadPage(1);
}


// 고객정보검색 TAB PANEL
var custInfoTabPanel = new Ext.tab.Panel({	 	
	border: 1,
	height: 337,		
	layout: {
        type: 'vbox',
        align: 'stretch'
    },
    items: [
	{
	    title: '고객정보검색',
	    items: [searchListPanel]
	},
	{
	    title: '예약고객검색',
	    items: [custBookingListPanel]
	}]
});

/**
 * 고객정보 검색
 */
function custInfoSearch() {
	
	var searchfield = Ext.getCmp('searchfield').getValue();
	var searchquery = Ext.getCmp('searchquery').getValue();
	var search_tel_mobile = remainNumber(Ext.getCmp('search_tel_mobile').getValue());
	
	Ext.getCmp('search_tel_mobile').setValue(search_tel_mobile);
	
	if(searchquery == "" && search_tel_mobile == "") {
		Ext.Msg.alert('Notice','검색조건을 하나 이상 입력해 주세요!');
	} else {
		custSearchStore.getProxy().extraParams = {'searchfield':searchfield, 'searchquery':searchquery, 'tel_mobile':search_tel_mobile};
		custSearchStore.loadPage(1);
	}
}