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
        ]
    });
	
    var store = Ext.create('Ext.data.Store', {
        pageSize: 20,
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxCrmInCallList',
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
			text : "아이디",
			dataIndex : 'member_id',
			width : 100,
			align : 'center',
			sortable : false
		}, {
			text : "상담원명",
			dataIndex : 'member_nm',
			width : 100,
			align : 'center',
			sortable : false
		}, {
			text : "내선번호",
			dataIndex : 'station',
			width : 100,
			align : 'center',
			sortable : true
		},{
			text : "일자",
			dataIndex : 'call_ymd',
			width : 100,
			align : 'center',
			sortable : false
		}, {
			text : "통화시작",
			dataIndex : 'call_start_time',
			width : 100,
			align : 'center',
			sortable : false
		}, {
			text : "통화종료",
			dataIndex : 'call_stop_time',
			width : 100,
			align : 'center',
			sortable : false
		}, {
			text : "통화시간",
			dataIndex : 'call_time',
			width : 100,
			align : 'center',
			sortable : false
		}, {
			text : "통화결과",
			dataIndex : 'call_result',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			text : "대표번호",
			dataIndex : 'ars_no',
			width : 110,
			align : 'center',
			sortable : true
		}, {
			text : "발신자번호",
			dataIndex : 'contact_no',
			width : 100,
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
			}
		});
	}
	
	
	store.on('beforeload',function(store, operation,eOpts){
        operation.params = {'sdate': Ext.getCmp("sdate").getSubmitValue()
				,'edate': Ext.getCmp("edate").getSubmitValue()
    			,'ars_no': Ext.getCmp("ars_no").getValue()
		};
	},this);

});
