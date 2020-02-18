Ext.require([
	'Ext.tree.*',
	'Ext.form.field.Text',
	'Ext.resizer.Splitter',
	'Ext.grid.Panel',
	'Ext.grid.column.RowNumberer'
]);

Ext.onReady(function() {

    Ext.define('DataThread', {
        extend: 'Ext.data.Model',
        fields: [
			'call_no'
			,'service_no'
			,'cust_no'
			,'buffer_record'
			,'cam_cd'
			,'cust_nm'
			,'call_ymd'
			,'call_ring_time'
			,'call_start_time'
			,'call_stop_time'
			,'call_end_time'
			,'member_id'
			,'member_nm'
			,'remark'
			,'contact_no'
			,'call_result'
			,'call_time'
			,'ars_no'
			,'station'
			,'call_div'
        ]
    });
	
    var store = Ext.create('Ext.data.Store', {
        pageSize: 20,
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxCrmCallList',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
            },
            simpleSortMode: true
        },
        sorters: [{
            property: 'insert_dt',
            direction: 'DESC'
        }]
    });

    var columns = [
        {xtype: 'rownumberer', header : '번호', align: 'center', width: 40},
        {
            xtype: 'actioncolumn',
            header: '청취',
            width: 40,
            align:'center',
            sortable : false,
            items: [{
            		icon   : COMMON_PATH_IMG + '/default/icons1/Play.png',
            		tooltip: '청취',                   
            		handler: function(grid, rowIndex, colIndex) {
            			
            			var rec = store.getAt(rowIndex);   
            			
            			var year = rec.get("call_ymd").substring(0,4);
            	    	var month = rec.get("call_ymd").substring(4,6);
            	    	var day = rec.get("call_ymd").substring(6,8);
            	    	var cust_no = rec.get("cust_no");
            	    	var cust_nm = rec.get("cust_nm");
            	    	var member_id = rec.get("member_id");
            	    	var member_nm = rec.get("member_nm");
            	    	var call_time = rec.get("call_time");
            	    	var call_ymd = rec.get("call_ymd")+" "+rec.get("call_ring_time");
            	    	var remark = rec.get("remark");
            	    	var RECORD_TYPE = year+month+day;
            	    	var RECORD_FILE = rec.get("buffer_record");
            	    	var RECORD_FILE = rec.get("buffer_record")+".WAV";
            	    	var RECORD_DATE = "/" + year + "/" + month + "/" + day + "/";            	    	
            	    	var RECORD_URL = COMMON_URL + "/common/AudioPlayer.jsp?record_url=kcrm.ihaan.com"+RECORD_DATE + RECORD_FILE+"&rec_key="+rec.get("buffer_record")+"&type="+RECORD_TYPE+"&cust_no="+cust_no+"&cust_nm="+cust_nm+"&call_time="+call_time+"&call_ymd="+call_ymd+"&member_id="+member_id+"&member_nm="+member_nm+"&remark="+remark;
            	    	
            	    	//var RECORD_URL = COMMON_URL + "/common/AudioPlayer.jsp?url="+RECORD_FILE;

            	    	var win1 = window.open(RECORD_URL,"_blank","menubar=no, scrollbars=no, resizable=no, width=350, height=450");
            	    	win1.focus();
            		}
            }]
        },
        {
			text : "아이디",
			dataIndex : 'member_id',
			width : 90,
			align : 'center',
			sortable : false
		}, {
			text : "상담원명",
			dataIndex : 'member_nm',
			width : 90,
			align : 'center',
			sortable : false
		}, {
			text : "내선번호",
			dataIndex : 'station',
			width : 90,
			align : 'center',
			sortable : true
		},{
			text : "일자",
			dataIndex : 'call_ymd',
			width : 90,
			align : 'center',
			sortable : false
		}, {
			text : "통화시작",
			dataIndex : 'call_start_time',
			width : 90,
			align : 'center',
			sortable : false
		}, {
			text : "통화종료",
			dataIndex : 'call_stop_time',
			width : 90,
			align : 'center',
			sortable : false
		}, {
			text : "통화시간",
			dataIndex : 'call_time',
			width : 90,
			align : 'center',
			sortable : false
		}, {
			text : "통화결과",
			dataIndex : 'call_result',
			width : 100,
			align : 'center',
			sortable : false
		}, {
			text : "대표번호",
			dataIndex : 'ars_no',
			width : 100,
			align : 'center',
			sortable : true
		}, {
			text : "발신자번호",
			dataIndex : 'contact_no',
			width : 90,
			align : 'center',
			sortable : false
		}, {
			text : "I/O구분",
			dataIndex : 'call_div',
			width : 90,
			align : 'center',
			sortable : false
		}];
    
	var ArsNoStore = Ext.create('Ext.data.Store', {
		id: 'camInfoStore',
        remoteSort: true,
    	proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxArsNoCombo',
            reader: {root: 'result'},
	        simpleSortMode: true,
	        extraParams: {use_yn:'Y',display_yn:'Y'}
        },
        fields: [{ name: 'ars_no' },{ name: 'ars_name' }]
    });    

	var searchType = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"a.cust_nm", "name":"고객명"},
            {"code":"a.cust_no", "name":"고객번호"},
            {"code":"a.contact_no", "name":"연락처"},
            {"code":"a.member_id", "name":"사원ID"},
            {"code":"a.member_nm", "name":"사원명"},
            {"code":"a.station", "name":"내선번호"}
        ]
    });	
	
	var searchType2 = Ext.create('Ext.data.Store', {
        fields: ['code', 'name'],
        data : [
            {"code":"IN", "name":"IN"},
            {"code":"OUT", "name":"OUT"}
        ]
    });	
	
	var combo1 = Ext.create('Ext.form.ComboBox', {
        store: ArsNoStore.load(),
        width: 110,
        id: 'ars_no',
        name: 'ars_no',
        queryMode: 'local',
        displayField: 'ars_name',
        valueField: 'ars_no',
	    padding: '0 0 0 5',
        emptyText: '대표번호 전체'
    });  
	
	 var combo2 = Ext.create('Ext.form.ComboBox', {
	        store: searchType,
	        width: 90,
	        id: 'searchfield',
	        name: 'searchfield',
	        queryMode: 'local',
	        displayField: 'name',
	        valueField: 'code',
		    padding: '0 0 0 5',
	        emptyText: '검색조건'
	    });    
	 
	 var combo3 = Ext.create('Ext.form.ComboBox', {
	        store: searchType2,
	        width: 90,
	        id: 'call_div',
	        name: 'call_div',
	        queryMode: 'local',
	        displayField: 'name',
	        valueField: 'code',
		    padding: '0 0 0 5',
	        emptyText: 'I/O전체'
	    });    

    var toDate = Ext.Date.format(new Date(),'Ymd');
    
    var audio = null;
    
	Ext.create('Ext.form.Panel', {
		id:'Content',
	    title: name,
	    flex: 1,
	    height: 635,
	    renderTo: Ext.getBody(),
	    layout: {
	        type: 'vbox',       // Arrange child items vertically
	        align: 'stretch',    // Each takes up full width
	        padding: 5
	    },
	    items: [
		{ // Details Panel specified as a config object (no xtype defaults to 'panel').
			 bodyPadding: 7,
			 layout: {
		        type: 'hbox',
		        align: 'stretch'
		    },
		    items: [
		        {
		            width: 16,
		            height: 16,
			        xtype: 'image',
			        imgCls: 'icon-mn002'
		        },
		        {
		            //labelCls: 'icon-search',
		            width: 85,
			        xtype: 'datefield',
			        id: 'sdate',
			        name: 'sdate',
			        format: 'Ymd',
			        submitFormat: 'Ymd',
			        value: toDate,
				    padding: '0 0 0 5',
			        emptyText: '시작 일자'
		        },
		        {
		            width: 85,
			        xtype: 'datefield',
			        id: 'edate',
			        name: 'edate',
			        format: 'Ymd',
			        value: toDate,
				    padding: '0 0 0 5',
			        emptyText: '종료 일자'
		        },
		        combo1,
		        combo3,
		        combo2,
		        {
		            width: 90,
			        xtype: 'textfield',
			        id: 'searchquery',
			        name: 'searchquery',
			        emptyText: '검색어 입력',
			        padding: '0 5 0 5',
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
	            }
		    ]
		},{
	        xtype: 'splitter'   // A splitter between the two child items
	    },{               // Results grid specified as a config object with an xtype of 'grid'
	        xtype: 'grid',
	        columns: columns,// One header just for show. There's no data,
	        store: store.load(), // A dummy empty data store
	        id: 'calllog_grid',
	        name: 'calllog_grid',
	        scroll: 'horizontal',
	        flex: 1,
			bbar: Ext.create('Ext.PagingToolbar', {
			
				pageSize: 20,
				store: store,
				displayInfo: true,
				displayMsg: '{0} - {1} of {2} 건',
				emptyMsg: "데이터가 없습니다."
			})
	    }]
	});
	
	function reload() {
		
		if(Ext.getCmp("sdate").getValue() == null)
			Ext.getCmp("sdate").setValue('');
		if(Ext.getCmp("edate").getValue() == null)
			Ext.getCmp("edate").setValue('');
		if(Ext.getCmp("ars_no").getValue() == null)
			Ext.getCmp("ars_no").setValue('');
		if(Ext.getCmp("searchfield").getValue() == null)
			Ext.getCmp("searchfield").setValue('');
		if(Ext.getCmp("searchquery").getValue() == null)
			Ext.getCmp("searchquery").setValue('');
		if(Ext.getCmp("call_div").getValue() == null)
			Ext.getCmp("call_div").setValue('');
		

		if(Ext.getCmp("sdate").getValue() == "" && Ext.getCmp("edate").getValue() != ""){
			alert("시작일자를 선택해 주세요");
			Ext.getCmp("sdate").focus();
			return;
		}
		
		if(Ext.getCmp("edate").getValue() == "" && Ext.getCmp("sdate").getValue() != ""){
			alert("종료일자를 선택해 주세요");
			Ext.getCmp("edate").focus();
			return;
		}

		Ext.getCmp("calllog_grid").store.load({
			params: {'sdate': Ext.getCmp("sdate").getSubmitValue()
					,'edate': Ext.getCmp("edate").getSubmitValue()
					,'ars_no': Ext.getCmp("ars_no").getValue()
					,'searchfield': Ext.getCmp("searchfield").getValue()
					,'searchquery': Ext.getCmp("searchquery").getValue()
					,'call_div': Ext.getCmp("call_div").getValue()
			}
		});
	}
	
	
	store.on('beforeload',function(store, operation,eOpts){
        operation.params = {'sdate': Ext.getCmp("sdate").getSubmitValue()
				,'edate': Ext.getCmp("edate").getSubmitValue()
    			,'ars_no': Ext.getCmp("ars_no").getValue()
    			,'searchfield': Ext.getCmp("searchfield").getValue()
				,'searchquery': Ext.getCmp("searchquery").getValue()
				,'call_div': Ext.getCmp("call_div").getValue()
		};
	},this);

});
