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
	'Ext.grid.column.RowNumberer'
]);

	var store = null;
	
	var url;
	var arr_mat_no = "";
	var sel_prd_no = "";
	var sel_site = "";

	Ext.define('DataThread', {
        extend: 'Ext.data.Model',
        fields: [
            'prd_mat_no'
			, 'prd_no'
			, 'prd_serial_no'
			, 'prd_nm'
			, 'prd_cate1'
			, 'prd_cate2'
			, 'mat_no'
			, 'mat_serial_no'
			, 'mat_nm'
			, 'as_price'
			, 'as_cost'
			, 'mat_cost'
			, 'labor_cost'
			, 'mk_cost'
			, 'as_travel_cost'
			, 'prd_member_id'
			, 'road_prd_cost'
			, 'road_labor_cost'
			, 'road_cost'
			, 'mat_spec'
			, 'mat_merit'
			, 'mat_desc'
        ]
    });
	
	store = Ext.create('Ext.data.Store', {
        pageSize: 30,
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxPrdMaterialsList',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
            },
            simpleSortMode: true
        },
        sorters: [{
            property: 'mat_no',
            direction: 'ASC'
        }]
    });
	
	var treeCateStore = Ext.create('Ext.data.TreeStore', {
    	id: 'treeCateStore',
        root: {
            expanded: true
        },
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/treePrdCate'
        }  
    });
	
	// 
	var treeCatePanel = Ext.create('Ext.tree.Panel', {
		title: '제품구분',		
		width: 300,
		store: treeCateStore,
		root: {text: '전체',  expanded:true},
        dockedItems: [{
            xtype: 'toolbar',
            items: [{
                text: '열기',
                iconCls: 'folder-open',
                handler: function(){
                	treeCatePanel.expandAll();
                }
            }, {
                text: '닫기',
                iconCls: 'folder-close',
                handler: function(){
                	treeCatePanel.collapseAll();
                }
            }]
        }],
        listeners: {
            itemdblclick: function(view, rec, node, index, e) {                	
            	
            	sel_prd_no = "";  
            	sel_site = "";
            	
            	if(rec.raw.leaf) {                		
            		sel_prd_no = rec.raw.prd_no;
            		sel_site = rec.raw.site; 
            		
            		Ext.getCmp("txt_prd_no").setValue(rec.raw.prd_cate);                		
            		Ext.getCmp("txt_prd_nm").setValue(rec.raw.prd_cate_nm);
            		
            		reload();
            	}
            }
        }
    });
	
	
	var columns = [
	    {xtype: 'rownumberer', header : '번호', align: 'center', width: 50},
        {
   			dataIndex : 'prd_serial_no',
   			text : '제품번호',
   			width : 120,
   			align : 'center'
   		}, {
   			dataIndex : 'prd_nm',
   			text : '제품명',
   			width : 120,
   			align : 'center'
   		}, {
   			dataIndex : 'mat_serial_no',
   			text : '자재번호',
   			width : 120,
   			align : 'center'
   		}, {
   			dataIndex : 'mat_nm',
   			text : '자재명',
   			width : 120,
   			align : 'center'
   		}, {
   			dataIndex : 'mat_spec',
   			text : '자재SPEC',
   			width : 200,
   			align : 'center'
   		}, {
   			dataIndex : 'as_price',
   			text : '단가',
   			width : 100,
   			align : 'right',
   			sortable : false,
   			renderer: Ext.util.Format.numberRenderer('0,000')
   		}, {
   			dataIndex : 'mat_cost', 
   			text : '자재비',
   			width : 100,
   			align : 'right',
   			sortable : false,
   			renderer: Ext.util.Format.numberRenderer('0,000')
   		}, {
   			dataIndex : 'labor_cost',
   			text : '공임비',
   			width : 100,
   			align : 'right',
   			sortable : false,
   			renderer: Ext.util.Format.numberRenderer('0,000')
   		}, {
   			dataIndex : 'as_cost',
   			text : 'AS비용',
   			width : 100,
   			align : 'right',
   			sortable : false,
   			renderer: Ext.util.Format.numberRenderer('0,000')
   		}, {
   			dataIndex : 'as_travel_cost',
   			text : 'AS출장비',
   			width : 100,
   			align : 'right',
   			sortable : false,
   			renderer: Ext.util.Format.numberRenderer('0,000')
   		}, {
   			dataIndex : 'road_cost',
   			text : '로드단가',
   			width : 100,
   			align : 'right',
   			sortable : false,
   			renderer: Ext.util.Format.numberRenderer('0,000')
   		}, {
   			dataIndex : 'mat_desc',
   			text : '비고',
   			width : 200,
   			align : 'center'
   		}
   	];
	
	
	var sm = new Ext.selection.CheckboxModel({		
		name:'chkbox',	    	
	    checkOnly: true,
	    menuDisabled: true,
		sortable : false,
	    listeners: {
	    	selectionchange: function(me, selected, eOpts) {
	    		
	    		arr_mat_no = "";
	    		
	    		Ext.each(selected, function(rec) {	            	
	    			arr_mat_no += rec.data.mat_no + "|";	            	
	            });
	    	}
	    }
	});	
	 
	var gridListPanel = new Ext.create('Ext.grid.Panel', {
	    title: '제품별 자재정보',
	    padding: '0 0 0 5',
	    flex: 1,
	    columns: columns,
	    store: store,
	    scroll: 'both',
	    selModel : sm,
	    tbar : [{
		    iconCls: 'icon-add',
		    text: '자재정보추가',
		    scope: this,
		    handler: onInsertMat
		}, {
		    iconCls: 'icon-remove',
		    text: '선택삭제',
		    scope: this,
		    handler: onDeleteMat
		},
		'|',
		'제품번호 : ',		
		{
		    xtype: 'textfield',
		    id: 'txt_prd_no'
		} ,
		'제품명 : ', 			
		{
		    xtype: 'textfield',
		    id: 'txt_prd_nm',
		    width: 150
		}],
		bbar: Ext.create('Ext.PagingToolbar', {
			pageSize: 30,
			store: store,
			displayInfo: true,
			displayMsg: '{0} - {1} of {2} 건',
			emptyMsg: "데이터가 없습니다."
		})
	});

	
	/**
	 * 자재정보 선택삭제
	 */
	function onDeleteMat() {
		
    	var result = arr_mat_no.split("|");
    	
    	if(sel_prd_no == "") {
    		Ext.Msg.alert("Warning", "제품구분을 선택하세요");
    		return;
    	}
    	
    	if(result.length == 1) {
    		Ext.Msg.alert("Warning", "삭제할 자재정보를 선택하세요");
    		return;
    	}
    	
    	Ext.Msg.show({
		    title:'Delete',
		    msg: '해당 제품의 선택된 자재정보를 삭제하시겠습니까?',
		    buttons: Ext.Msg.YESNO,
		    icon: Ext.Msg.QUESTION,
		    fn: function(btn) {
		        if (btn === 'yes') {
		        	
		        	Ext.Ajax.request({
		    	        url: COMMON_URL + '/ajaxPrdMaterialsDelete',
		    	        params: { 'prd_no'	: sel_prd_no
		    	        		, 'strPrdNo'  : arr_mat_no
		    	        },
		    	        success: function(response) {		    	    				    	    		
		    	        	var obj = toJson(response.responseText);		    	        	
		    	        	Ext.Msg.alert('Success', obj.msg);
		    	        	reload();
		    	        },
		    	        failure: function(result, request) {
		    	        	Ext.Msg.alert('Failed', "삭제 중 오류가 발생하였습니다.");
		    			}
		    	    });		
		        	
		        } else if (btn === 'no') {
		            return;
		        } else {
		            return;
		        } 
		    }
		});
	}	
	
	/**
	 * 자재정보 추가
	 */
	function onInsertMat() {
		
		if(sel_prd_no == "") {
			Ext.Msg.alert('Warnning', "제품을 선택해 주세요!");
		} else {						
			var theURL = COMMON_URL + '/jsp/Prd/PrdMatListPop.jsp?prd_no='+sel_prd_no+"&site="+sel_site;			
			window.open(theURL, 'pop', "menubar=no, scrollbars=yes, resizable=yes, width=" + 800 + ", height=" + 600);			
		}		
	}
	

	//list reload
	function reload() {		
		store.getProxy().extraParams = {'prd_no' : sel_prd_no};		
		store.loadPage(1);
	}

Ext.onReady(function() {
	    
	Ext.create('Ext.panel.Panel', {
		id:'Content',	    
	    flex: 1,
	    height: FRAME_CONTENT_HEIGHT,
	    renderTo: Ext.getBody(),
	    layout: {
	        type: 'hbox',       // Arrange child items vertically
	        align: 'stretch',    // Each takes up full width
	        padding: 5
	    },
	    items: [treeCatePanel, gridListPanel]
	});	
});

