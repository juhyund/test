/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : CRMFileUploader.js
* @Author : kyunghee.yoon
* @Date : 2015.12.22
**************************************/

Ext.onReady(function() {	

	var fileListeners = {
    	"change" : function(me, value, eOpts) {	            		
    		var ext = value.slice(value.indexOf(".") + 1).toLowerCase().trim();
    		
    		var extFormat = /(jpeg)|(jpg)|(gif)|(pdf)|(zip)|(png)|(tiff)/;
    		if(!extFormat.test(ext))
            {
    			Ext.Msg.alert('Warning', '허용된 확장자가 아닙니다.\n파일을 다시 선택하여 주십시오');
    			me.reset();
    			return;
    		}	
    	}
	};
    
    var html = '<div style="line-height:19px;">'; 
	html += '<ol start="1">';
	html += '<li> 파일찾기 버튼을 클릭하여 <u><font color="#FF0000">업로드 할 파일(.jpg .gif .pdf .zip .png .tiff 확장자 유의)</font></u>을 선택하고</li>';
	html += '<li> [업로드]버튼을 클릭하여 <u>파일 업로드</u>를 시작합니다.</li>';
	html += '<li> 파일 업로드가 완료되면 업로드 결과를 확인합니다.</li>';	
	html += '</ol></div>';
	
    //팝업 form
    var insertform = Ext.create('Ext.form.Panel', {
    	id: 'insertform',
	    bodyPadding: 10,	    
	    border: 1,	    
	    layout: 'anchor',
	    defaults: {
	        anchor: '100%',
	        labelWidth: 60
	    },
	    height: 240,
	    items: [{
	        xtype:'hiddenfield',
	        name: 'prd_no',
	        value: prd_no
	    }, {
	        xtype:'fieldset',
	        bodyPadding: 5,
	        title: '업로드 주의사항',
	        defaults: {anchor: '100%'},
	        layout: 'anchor',
	        items :[{'html' : html, border: 0}]
	    }, {
			xtype: 'textfield',			
            name: 'prd_nm',
            fieldLabel: '제품정보',
            flex: 1,
        	padding: '20 0 0 5',
        	value: prd_nm,
        	readOnly: true
	    }, {
			xtype: 'fileuploadfield',			
            name: 'filename',		 
            fieldLabel: '업로드',
            flex: 1,
        	padding: '0 0 0 5',
        	buttonText: '파일찾기',
        	buttonConfig: {
                iconCls: 'icon-upload'
            }
	    	,
            listeners: fileListeners
	    }],
	    buttons: [		
        '->',	        
        {
	        text: '업로드',
	        formBind: true, 
	        iconCls: 'icon-yes',
	        handler: function() {
	        	
	        	var form = this.up('form').getForm();
	        	
	        	if(form.findField('prd_no').getValue() == "") {
	        		Ext.Msg.alert('Notice', '제품정보를 먼저 선택하여 주시기 바랍니다.');
	        		return;
	        	}
	        	
	        	if(form.findField('filename').getValue() == "") {
	        		Ext.Msg.alert('Notice', '업로드 할 파일을 먼저 선택하여 주시기 바랍니다.');
	        		return;
	        	}
	        	
	        	if (form.isValid()) {
	        		
	                form.submit({
                        url: COMMON_URL + '/ajaxFileUpload?savePath=CUST_PRD',
                        submitEmptyText: false,
	                    success: function(form, action) {
	                    	
	                    	Ext.getBody().mask('파일 업로드 중 입니다.');
	                    	
	                    	Ext.Ajax.request({
	                    		url: COMMON_URL + '/ajaxCustPrdFilesInsert',
	                    		success: function(result, request) {
	                    			Ext.getBody().unmask();        							 
	                    			
	                    			var obj = Ext.decode(result.responseText);        							 
	                    			
	                    			Ext.Msg.alert('Success', '파일 업로드 완료되었습니다.');
	                    			
	                    			loadFileList(cust_no);
	                    		},
	                    		failure: function(result, request) {
	                    			Ext.getBody().unmask();        							 
	                    			Ext.Msg.alert('Error', '파일 업로드 중 오류가 발생하였습니다.');	        							 
	                    		},
	                    		params: {
	                    			'cust_no': cust_no,
	                    			'prd_no': prd_no,
	                    			'file_name': action.result.fileName,
	                    			'file_path': action.result.filePath,
	                    			'file_size': action.result.fileSize,
	                    			'file_save_name': action.result.realFileName
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
	        	self.close();
        	}
        }]
	});
    
    Ext.define('DataThread', {
        extend: 'Ext.data.Model',
        fields: [
              'cust_no'
         	, 'file_seq_no'
         	, 'file_name'
         	, 'file_path'
         	, 'file_size'
         	, 'file_save_name'
         	, 'insert_id'
         	, 'insert_nm'
         	, 'insert_dt'
         	, 'prd_no'
         	, 'prd_serial_no'
         	, 'prd_nm'
        ]
    });

    // 파일조회
    var fileListStore = Ext.create('Ext.data.Store', {        
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxCustPrdFilesList',
            reader: {
            	root: 'result'
            },
            simpleSortMode: true
        }
    });
    
    // 첨부파일 리스트
    var grid = new Ext.create('Ext.grid.Panel', {
        title: '첨부파일 리스트',
        padding: '10 0 0 0',
        flex: 1,
        store: fileListStore, 
        columns: [
            {xtype: 'rownumberer', header : '번호', align: 'center', width: 40},
            {
                xtype: 'actioncolumn',
                header: '다운',
                width: 50,
                align:'center',
                items: [{
                    iconCls: 'icon-disk',
                    tooltip: 'download',
                    handler: function(grid, rowIndex, colIndex) {
                  	  	
                    	var rec = fileListStore.getAt(rowIndex);   
                    	location.href = COMMON_URL + "/common/CustPrdFileDown.jsp?fileDir="+rec.data.file_path+"&fileName="+rec.data.file_name;
                    }
                }]
            },
            {
                xtype: 'actioncolumn',
                header: '삭제',
                width: 50,
                align:'center',
                items: [{
                    iconCls: 'icon-remove',
                    tooltip: 'delete',
                    handler: function(grid, rowIndex, colIndex) {
                  	  	var rec = fileListStore.getAt(rowIndex);
                  	  	deleteFile(rec.data.cust_no, rec.data.prd_no, rec.data.file_seq_no);
                    }
                }]
            },
            { text: '제품번호',  dataIndex: 'prd_serial_no', align:'center'},
            { text: '제품명',  dataIndex: 'prd_nm', align:'center'},            
            { text: '파일명', dataIndex: 'file_save_name', align:'center', renderer: function(dat, meta, rec, rowIndex, colIndex) {    	    	
            	return "<a href='"+ COMMON_URL + "/common/CustPrdFileDown.jsp?fileDir="+rec.data.file_path+"&fileName="+rec.data.file_name+"'>"+dat+"</a>";        		
    	    }},    
            { text: '등록자', dataIndex: 'insert_nm', align:'center'},
            { text: '등록일시', dataIndex: 'insert_dt', align:'center'}
        ]
    });
    
    function deleteFile(cust_no, prd_no, file_seq_no) {
    	
    	Ext.Msg.confirm('Confirm', '선택한 파일을 삭제 하시겠습니까?', function(e) {
    		
			if(e == 'yes') {
				
				Ext.Ajax.request({
		    		url: COMMON_URL + '/ajaxCustPrdFilesDelete',
		    		success: function(result, request) {
		    			Ext.getBody().unmask();       	
		    			Ext.Msg.alert('Success', '파일 삭제 되었습니다.');
		    			loadFileList(cust_no);
		    					    			
		    		},
		    		failure: function(result, request) {
		    			Ext.getBody().unmask();        							 
		    			Ext.Msg.alert('Error', '파일 삭제 중 오류가 발생하였습니다.');	        							 
		    		},
		    		params: {
		    			'cust_no': cust_no,
		    			'prd_no': prd_no,
		    			'file_seq_no': file_seq_no
		    		},
		    		timeout: TIMEOUT_SEC
		    	});
				
			} else {
				return;
			}
		});
    }
    
    function loadFileList(cust_no) {
    	fileListStore.getProxy().extraParams = {'cust_no':cust_no};
		fileListStore.load();
    }
    
    loadFileList(cust_no);
    
    // layout
	Ext.create('Ext.form.Panel', {
		id:'Content',
		title: '첨부파일 업로드',
	    border: 0,
	    flex: 1,
	    height: FRAME_CONTENT_HEIGHT,
	    renderTo: Ext.getBody(),
	    layout: {
	        type: 'vbox',	        
	        align: 'stretch',
	        padding: 5
	    },
	    items: [insertform, grid]
	});
    
});    