/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : CRMServiceForm.js
* @Author : kyunghee.yoon
* @Date : 2015.10.26
**************************************/
Ext.onReady(function() {
	
	// layout
	Ext.create('Ext.form.Panel', {
		id:'Content',
	    border: 0,
	    flex: 1,
	    height: FRAME_CONTENT_HEIGHT,
	    renderTo: Ext.getBody(),
	    layout: {
	        type: 'hbox',	        
	        align: 'stretch',
	        padding: 5
	    },
	    items: [{	
        	xtype: 'form', 
        	width: 1.3,
        	border: 0,
        	layout: {
    	        type: 'vbox',	
    	        align: 'stretch',
    	        padding: 5
    	    },
    	    items: [custInfoFormPanel, productTabPanel, serviceFormPanel, transferFormPanel, serviceListPanel] 
        }, {	
        	xtype: 'form', 
        	flex: 1,
        	border: 0,	            	
        	layout: {
    	        type: 'vbox',
    	        align: 'stretch',
    	        padding: 5	        	        
    	    },
    	    items:[custInfoTabPanel, orderTabPanel, orderAddrTabPanel]
        }]
	});
});