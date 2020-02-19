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
	    width: '100%',
	    bodyPadding: '0 5 5 10',
	    renderTo: Ext.getBody(),
	    layout: {
	        type: 'vbox',	        
	        align: 'stretch'
	    },
	    items:[
             custInfoFormPanel
           , serviceInfoFormPanel
           , serviceFormPrdPanel
           , orderFormPanel
           , asFormPanel
           , paymentFormPanel
           , pickupFormPanel
           , deliveryFormPanel
           , transFormPanel
           , remarkFormPanel
           , smsFormPanel
           , logFormPanel
           , fileFormPanel]
	});
});

