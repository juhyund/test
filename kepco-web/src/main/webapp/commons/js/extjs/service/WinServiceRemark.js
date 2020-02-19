/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : ServiceInfoList.js
* @Author : kyunghee.yoon
* @Date : 2015.12.23
**************************************/
Ext.require([
	'Ext.tree.*',
	'Ext.form.field.Text',
	'Ext.resizer.Splitter',
	'Ext.grid.Panel',
	'Ext.grid.column.RowNumberer'
]);
	
	var winServiceRemark = null;
    //팝업 window
    var winServiceRemarkPop = function(service_no, seq_no, cust_no, cust_nm) {
    	
    	serviceRemarkform.getForm().reset();
    	
    	if(!winServiceRemark) {
    		
	    	winServiceRemark = Ext.create('Ext.window.Window', {
	            title: '서비스처리이력',
	            height: 280,
	            width: 500,
	            closeAction: 'close',
	            modal: false,
	            resizable: false,
	            draggable: true,
	            items:[
	                   serviceRemarkform
	            ]
	        });
    	}
    	
    	if(winServiceRemark.isVisible()) {
			winServiceRemark.hide();
		} else {			
			
			loadDataServiceRemark(service_no, seq_no, cust_no, cust_nm);
			
			if(seq_no != undefined && seq_no != "") {
				Ext.getCmp("btnDeleteRemark").setDisabled(false);
			} else {
				Ext.getCmp("btnDeleteRemark").setDisabled(true);
			}
			
			winServiceRemark.show();			
		}
    }
    
    
    /**
	 * 서비스 처리정보
	 * @param service_no
	 */
	function loadDataServiceRemark(service_no, seq_no, cust_no, cust_nm) {
	
		var form = serviceRemarkform.getForm();
		
		form.findField("service_no").setValue(service_no);
		form.findField("cust_nm").setValue(cust_nm);
		form.findField("cust_no").setValue(cust_no);
		form.findField("insert_dt").setValue(toDateTime);
		
		if(seq_no != undefined && seq_no != "") {
			
			Ext.Ajax.request({
			
		        url: COMMON_URL + '/ajaxServiceRemarkSelect',
		        params: { 'service_no' : service_no, 'seq_no' : seq_no},
		        success: function(response) {
		        	
		        	var obj = Ext.decode(response.responseText);
		        	
		        	var result = obj.result[0]; // 서비스정보	
		        	
		        	form.setValues(result);
		        },
		        failure: function(result, request) {
		        	Ext.Msg.alert('Notice', "조회 중 오류가 발생하였습니다.");
		    		return;
				}
			});	
		}
			
	}

	// 팝업 form
    var serviceRemarkform = Ext.create('Ext.form.Panel', {
    	id: 'serviceRemarkform',
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
			    name: 'seq_no'
			},
			{
			    xtype: 'hiddenfield',
			    name: 'insert_id'
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
			        flex: 1,
			        afterLabelTextTpl: [MARK_ASTERISK]
				}, {
					name: 'insert_dt',
					fieldLabel: '접수일시',			        	        
			        editable: false,
			        readOnly: true,
			        flex: 1,
			        margin: '0 0 0 15',
			        afterLabelTextTpl: [MARK_ASTERISK]
				}]
			}, {
		        xtype: 'fieldcontainer',            
		        layout: 'hbox',         
		        defaultType: 'textfield',
		        items: [{
					name: 'cust_nm',
					fieldLabel: '고객명',			        	        
			        editable: false,
			        readOnly: true,
			        flex: 1,
			        afterLabelTextTpl: [MARK_ASTERISK]
				}, {
					name: 'cust_no',
					fieldLabel: '고객번호',			        	        
			        editable: false,
			        readOnly: true,
			        flex: 1,
			        margin: '0 0 0 15',
			        afterLabelTextTpl: [MARK_ASTERISK]
				}]
			},			
			{   
			    xtype: 'textareafield',
				name: 'remark',
			    fieldLabel: '처리내용',
			    height: 130,
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
	        	
	            var service_no = form.findField("service_no");
	            var seq_no = form.findField("seq_no");
	            var remark = form.findField("remark");
				
				if(service_no.getValue() == "" ) {					
					focusMsgAlert('Warning', '서비스번호가 없습니다.', service_no);
					return;
				}
				
				if(remark.getValue() == "") {					
					focusMsgAlert('Warning', '처리내용을 입력해 주세요.', remark);
					return;
				}
				
				if(seq_no.getValue() == "") { // 신규
					url = COMMON_URL + '/ajaxServiceRemarkInsert';
				} else { // 수정
					url = COMMON_URL + '/ajaxServiceRemarkUpdate';
				}
												
	            if (form.isValid()) {
	                form.submit({
	                	url: url,
	                	submitEmptyText: false,
	                    success: function(form, action) {	                    	
	                       Ext.Msg.alert('Success', action.result.msg);
	                       reload(service_no.getValue());
	                       winServiceRemark.hide();
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
	        text: '삭제',
	        formBind: true, 
	        id: 'btnDeleteRemark',
	        iconCls: 'icon-delete',
	        disabled: true,
	        handler: function() {	            
	        	var form = this.up('form').getForm();
	        	
	            var service_no = form.findField("service_no");
	            var seq_no = form.findField("seq_no");
				
				if(seq_no.getValue() == "" ) {					
					focusMsgAlert('Warning', '서비스 처리이력번호가 없습니다.', service_no);
					return;
				}
				
				url = COMMON_URL + '/ajaxServiceRemarkDelete';
				
				Ext.Msg.confirm('Confirm', '정말 삭제 하시겠습니까?', function(e) {
					
					if(e == 'yes') {	
													
			            if (form.isValid()) {
			                form.submit({
			                	url: url,
			                	submitEmptyText: false,
			                    success: function(form, action) {
			                       Ext.Msg.alert('Success', action.result.msg);
			                       reload(service_no.getValue());
			                       winServiceRemark.hide();
			                    },
			                    failure: function(form, action) {
			                        Ext.Msg.alert('Failed', action.result.msg);
			                        return;
			                    }
			                });
			            }
					}				
				});
	        }
	    },
	    {
	        text: '닫기',
	        iconCls: 'icon-cancel',
	        handler: function() {
	        	winServiceRemark.hide();
        	}
        }]
	});

