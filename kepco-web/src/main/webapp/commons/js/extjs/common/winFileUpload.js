Ext.require([
			'Ext.tab.*'
			, 'Ext.window.*'
			, 'Ext.tip.*'
			, 'Ext.layout.container.Border'
			, 'Ext.form.File'
			, 'Ext.form.FileUploadField'
			, 'Ext.ux.form.FileUploadField'
]);

// 참고글
var guide_html = '<BR>※ 업로드 방법<BR>'
	+'1) 템플릿을 다운로드 하여 업로드 할 데이터를 저장합니다.<BR>'
	+'2) 파일찾기 를 <font color="red">click</font>해서 <B style="color:blue;">1)</B>번에서 작업한 템플릿파일을 선택 후 <font color="red">열기</font>을 누릅니다.<BR>'
	+'3) 업로드 를 <font color="red">click</font> 하면 데이터가 업로드 됩니다.<BR>'
	+'4) 리스트의 업로드 필드에 <font color="red">오류</font>, <font color="red">성공</font>으로 표시되며 오류데이터는 수정 후 재업로드 합니다.<BR><BR><BR>'


var upload_Win;
var func_name;

var winUpload_Pop = function(_func_name){
	
	func_name = _func_name; 
	
	if(!upload_Win){
		upload_Win = Ext.create('Ext.window.Window', {
						title: '파일 업로드',
						height: 250,
						width: 560,
						closeAction: 'close',
						modal: false,
						resizable: false,
						items:[ upload_Panel ]
					});
	}

	if(upload_Win.isVisible()){
		upload_Win.hide();
	}else{
		upload_Win.show();
    	
    	if(_func_name  !="" ) {
    		upload_Panel.getForm().findField("upload_type").setValue(_func_name);
		}	
	}
}		

//팝업 form
var upload_Panel = Ext.create('Ext.form.Panel', {
					width : 550,
					frame : true,
					items : [{
								xtype: 'hiddenfield',
								id : 'upload_type'
							}, {
								xtype: 'fieldcontainer',
								layout: 'hbox',
								items:[{
											xtype : 'filefield',
											name : 'fileUpload',
											fieldLabel : '파일명',
											labelWidth : 50,
											msgTarget : 'side',
											allowBlank : false,
											anchor : '100%',
											width:460,
											buttonText : '파일 찾기'
										},{
											xtype: 'button',
											text: '업로드',
											id: 'btn_upload',
											iconCls: 'icon-Upload',
											margin:'0 0 0 5',
											handler: upformSend
										}
								],
								margin:'5 0 12 5'
							}, {
						        xtype: 'fieldset',
						        title: '주의사항',
						        anchor: '100%',
								html : guide_html
					}],
					buttons : [{
						    		text : '템플릿다운로드',
						    		id   : 'btn_template',
						    		iconCls: 'icon-Download',
					    			handler : downTemplate
						    	}, {
							        text: '닫기',
							        iconCls: 'icon-close',
							        handler: function() {
							        			upload_Win.hide();
						        			}
						    	}
					]
});



// 템플릿 다운
function downTemplate()
{
    var form = this.up('form').getForm();
    var upload_type = form.findField("upload_type").getValue();

	if(upload_type == "product"){
		window.location = COMMON_URL_FILE_TEMPLATE + '/product.xlsx';
	}else if(upload_type == "prdRate"){		
		window.location = COMMON_URL_FILE_TEMPLATE + '/rate.xlsx';
	}else if(upload_type == "prdLayer"){		
		window.location = COMMON_URL_FILE_TEMPLATE + '/layer.xlsx';
	}else{
		Ext.Msg.alert('Info', "탬플릿이 없습니다.");
	}
}


// 업로드 실행
function upformSend() 
{
	var form = this.up('form').getForm();
	var upload_type = form.findField("upload_type").getValue();
	
	if (form.isValid()) {

		form.submit({
					url : COMMON_URL + '/common/FileUpload.jsp?savePath='+ COMMON_URL_FILE_UP,
					waitMsg : '업로드 중....',
					success : function(fp, o) {
									file_name = o.result.file;
									
									if(!uploadfile_checkXlsx(file_name)){
										Ext.Msg.alert('Info', "xlsx 만 가능합니다.");
										return false;
									}else{
										if(upload_type != ""){
											uploadFile_Insert(upload_type, file_name);
										}else{						
											Ext.Msg.alert('Info', "탬플릿이 없습니다.");
										}
									}
									upload_Win.hide();
							  }
				});  
	}
} 


// 업로드된 파일로 DB에 insert실행하기
function uploadFile_Insert(upload_type, file_name)
{
	$("#loading").show();
	
	var ajax_url = "";
	
	if(upload_type == "product"){
		ajax_url = COMMON_URL + 'ajaxUploadFileInsert_Product';
	}else if(upload_type == "prdRate"){
		ajax_url = COMMON_URL + 'ajaxUploadFileInsert_PrdRate';
	}else if(upload_type == "prdLayer"){
		ajax_url = COMMON_URL + 'ajaxUploadFileInsert_PrdLayer';
	}

	Ext.Ajax.request({
        url: ajax_url,
        params: { 'upload_type': upload_type
        		, 'file_name'  : file_name
        },
        success: function(response){
    		$("#loading").hide();
    		
        	var obj = toJson(response.responseText);
        	
        	var msg_text = "";

        	if (obj.totalCount > 0 ) {
        		if (obj.errorCount > 0 ) {
        			//msg_text = obj.errorCount +"건은 데이타에 오류가 있어  등록을 실패하였습니다.\\n\\n해당 파일의 "+ obj.error_MSG +" 라인을  확인하시기 바랍니다."
        			msg_text = obj.error_MSG +" 라인을  수정하신 후 재업로드하시기 바랍니다."
        		} else {
        			msg_text = obj.totalCount+"건의 데이타 등록을 성공하였습니다."
        		}
        		
        		Ext.Msg.alert('Success', msg_text);
        		store.reload();
        		return;
        	}
        },
        failure: function(result, request) {	
    		$("#loading").hide();
    		
        	Ext.Msg.alert('Error', '등록을 실패하였습니다.');
		}
    });
}
