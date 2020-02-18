Ext.require([
    'Ext.tab.*',
    'Ext.window.*',
    'Ext.tip.*',
    'Ext.layout.container.Border'
]);

var winOccupCode;
var func_name;

var codeStore1 = Ext.create('Ext.data.Store', {	
	id: 'codeStore1',
    remoteSort: true,
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxCodeOccup',
        reader: {root: 'result'},
        simpleSortMode: true,
        extraParams: {class_cd:'1'}
    },
    fields: [{ name: 'occup_cd' },{ name: 'occup_nm' },{ name: 'occup_gd' },{ name: 'drive_gd' },{ name: 'class_cd' }]
});	

var codeStore2 = Ext.create('Ext.data.Store', {	
	id: 'codeStore1',
    remoteSort: true,
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxCodeOccup',
        reader: {root: 'result'},
        simpleSortMode: true,
        extraParams: {class_cd:'2'}
    },
    fields: [{ name: 'occup_cd' },{ name: 'occup_nm' },{ name: 'occup_gd' },{ name: 'drive_gd' },{ name: 'class_cd' }]
});	

var codeStore3 = Ext.create('Ext.data.Store', {
	id: 'codeStore1',
    remoteSort: true,
	proxy: {
        type: 'ajax',
        url: COMMON_URL + '/ajaxCodeOccup',
        reader: {root: 'result'},
        simpleSortMode: true,
        extraParams: {class_cd:'3'}
    },
    fields: [{ name: 'occup_cd' },{ name: 'occup_nm' },{ name: 'occup_gd' },{ name: 'drive_gd' },{ name: 'class_cd' }]
});

var winOccupCodePop = function(_func_name) {
	
	func_name = _func_name;
	
	var popButtonPanel = Ext.create('Ext.form.Panel', {		
		bodyPadding: 5,	    
	    width: '100%',
	    padding: '0 0 5 0',
	    layout: {
	        type: 'hbox',
	        align: 'stretch'
	    },
	    defaultType: 'textfield',	    
	    items: [
				{
				    width: 16,
				    height: 16,
				    xtype: 'image',
				    imgCls: 'icon-mn003'
				},
	            { 	
					fieldLabel: '직업', 
					name: 'searchquery',
					id: 'searchquery', 
					flex:1,					
					margin: '0 0 0 5',
					listeners:  {
		                specialkey: function (f,e) {    
		                    if (e.getKey() == e.ENTER) {		                    	 
		                    	 var form = this.up('form').getForm();    					
		 	    	            var searchquery = form.findField("searchquery").getValue();
			 	    	   		var check_searchquery = "";
	
			 	    			if(searchquery != ""){
			 	    				check_searchquery = specialTxT(searchquery);
			 	    				form.findField("searchquery").setValue(check_searchquery);
			 	    				searchquery = form.findField("searchquery").getValue(); 
			 	    			}    	            
		 	    	            
		 	    				codeStore3.load({
		 	            			params: {	            				
		 	            				'class_cd': "3",
		 	            				'searchquery': searchquery
		 	            			}
		 	            		});
		                    }
		                }
		            }
	            },
	            {
	    			xtype: 'button',    	    	
	    			align:'right',
	    			text: '직업조회',
	    			style:'text-align:right',
	    			iconCls: 'icon-search',	
	    			margin: '0 0 0 5',
	    			handler: function() {
	    				
	    				var form = this.up('form').getForm();    					
	    	            var searchquery = form.findField("searchquery").getValue();
	    	            var check_searchquery = "";

	    	            if(searchquery != ""){
	    	            	check_searchquery = specialTxT(searchquery);
	    	            	form.findField("searchquery").setValue(check_searchquery);
	    	            	searchquery = form.findField("searchquery").getValue();
	    	            }
	    	            
	    				codeStore3.load({
	            			params: {	            				
	            				'class_cd': "3",
	            				'searchquery': searchquery
	            			}
	            		});
	    			}
	    		}
	    ]
	});
		
	var codeClassPanel1 = {
		title:'대분류',
		xtype: 'grid',
	    columns: [
	            {xtype: 'rownumberer', header : '번호', align: 'center', width: 40},
				{
					text : "분류명",
					dataIndex : 'occup_nm',
					flex : 1,
					align : 'center',
					sortable : false
				}
	    ], 
	    listeners: {
        	'cellclick': function(iView, iCellEl, iColIdx, iStore, iRowEl, iRowIdx, iEvent) {
        		var rec = codeStore1.getAt(iRowIdx);	
        		var occup_cd = rec.get("occup_cd");
        		
        		codeStore2.load({
        			params: {'occup_cd': occup_cd,
        				'class_cd': "2"
        			}
        		});        		
        	}
        },
	    store: codeStore1,
	    id: 'class1Grid',
	    name: 'class1Grid',	    
	    flex: 1
	};
	
	var codeClassPanel2 = {
		id: 'codeClassPanel2',
		title:'중분류',
		xtype: 'grid',
	    columns: [
	            {xtype: 'rownumberer', header : '번호', align: 'center', width: 40},
				{
					text : "분류명",
					dataIndex : 'occup_nm',
					flex : 1,
					align : 'center',
					sortable : false
				}
	    ], 
	    store: codeStore2,
	    listeners: {
        	'cellclick': function(iView, iCellEl, iColIdx, iStore, iRowEl, iRowIdx, iEvent) {
        		var rec = codeStore2.getAt(iRowIdx);	
        		var occup_cd = rec.get("occup_cd");
        		
        		codeStore3.load({
        			params: {'occup_cd': occup_cd,
        				'class_cd': "3"
        			}
        		});        		
        	}
        },
	    id: 'class2Grid',
	    name: 'class2Grid',
	    flex: 1,
		margin: '0 0 0 5'
	};
	
	var codeClassPanel3 = {
		title:'직업선택',	
		xtype: 'grid',
		flex: 2,
		margin: '0 0 0 5',
	    columns: [
            {xtype: 'rownumberer', header : '번호', align: 'center', width: 40},
            {
				text : "직업코드",
				dataIndex : 'occup_cd',
				width : 70,
				align : 'center',
				sortable : false
			},
			{
				text : "직업",
				dataIndex : 'occup_nm',
				flex: 1,
				align : 'center',
				sortable : false
			},
			{
				text : "직업급수",
				dataIndex : 'occup_gd',
				width : 60,
				align : 'center',
				sortable : false
			}
			,
			{
				text : "운전급수",
				dataIndex : 'drive_gd',
				width : 60,
				align : 'center',
				sortable : false
			}
	    ], 
	    store: codeStore3,
	    id: 'class3Grid',
	    name: 'class3Grid',
	    flex: 1.5,
		margin: '0 0 0 5',
		listeners: {
        	'celldblclick': function(iView, iCellEl, iColIdx, iStore, iRowEl, iRowIdx, iEvent) {
        		
        		var rec = codeStore3.getAt(iRowIdx);	
        		
        		var occup_cd = rec.get("occup_cd");
        		var occup_nm = rec.get("occup_nm");
        		var occup_gd = rec.get("occup_gd");
        		var drive_gd = rec.get("drive_gd");
        		
        		eval(func_name+"('" + occup_cd + "','" + occup_nm + "','" + occup_gd + "','" + drive_gd + "')");
        		
        		winOccupCode.hide();
        	}
        }
	};
		
	var codeClassPanel = Ext.create('Ext.panel.Panel', {		
	    width: '100%',
	    height: 500, 
	    border: 0,
	    layout: {
	        type: 'hbox',       // Arrange child items vertically
	        align: 'stretch',    // Each takes up full width
	        padding: 0
	    },
	    items: [codeClassPanel1, codeClassPanel2, codeClassPanel3]
	});
	
	var winPanel = Ext.create('Ext.panel.Panel', {		
	    width: '100%',
	    height: 570, 
	    layout: {
	        type: 'vbox',       // Arrange child items vertically
	        align: 'stretch',    // Each takes up full width
	        padding: 5
	    },
	    items: [popButtonPanel, codeClassPanel]
	});
	
	
	if (!winOccupCode) {
		 
		winOccupCode = Ext.create('widget.window', {
	        title: '직업조회',
	        closable: true,
	        closeAction: 'hide',
            width: 900,
            minWidth: 520,
            height: 600, 
            border: 0,
            frame: true,
            layout:{
            	type:'vbox',
            	align:'center'
            },
            items: [winPanel]
        });
    }

    if (winOccupCode.isVisible()) {
        winOccupCode.hide();
    } else {
    	winOccupCode.show();
    }
    
    codeStore1.load();
}