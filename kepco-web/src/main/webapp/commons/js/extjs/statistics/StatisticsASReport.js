/*************************************
* @Copyright : (주)한국고용정보
* @ProjectName : HaanCRM
* @FileName : CustInfoList.js
* @Author : kyunghee.yoon
* @Date : 2015.10.14
**************************************/
Ext.require([
	'Ext.tree.*',
	'Ext.form.field.Text',
	'Ext.resizer.Splitter',
	'Ext.grid.Panel',
	'Ext.grid.column.RowNumberer'
]);

Ext.onReady(function(){
	
	var url;
	
    Ext.define('DataThread', {
        extend: 'Ext.data.Model',
        fields: [
			'prd_cate1_nm'
			,'prd_cate2_nm'
			,'prd_serial_no'
			,'prd_nm'
			,'FREE_N_CNT'
			,'FREE_Y_CNT'
			,'TOT_CNT'
			,'TOT_AMT'
			,'AS_10_CNT_AMT'
			,'AS_10_TOT_AMT'
			,'AS_10_ITEM01_CNT'
			,'AS_10_ITEM02_CNT'
			,'AS_10_ITEM04_CNT'
			,'AS_10_ITEM05_CNT'
			,'AS_10_ITEM06_CNT'
			,'AS_10_ITEM01_AMT'
			,'AS_10_ITEM02_AMT'
			,'AS_10_ITEM04_AMT'
			,'AS_10_ITEM05_AMT'
			,'AS_10_ITEM06_AMT'
			,'AS_10_ITEM11_CNT'
			,'AS_10_ITEM12_CNT'
			,'AS_10_ITEM14_CNT'
			,'AS_10_ITEM15_CNT'
			,'AS_10_ITEM16_CNT'
			,'AS_10_ITEM11_AMT'
			,'AS_10_ITEM12_AMT'
			,'AS_10_ITEM14_AMT'
			,'AS_10_ITEM15_AMT'
			,'AS_10_ITEM16_AMT'
			,'AS_11_CNT_AMT'
			,'AS_11_TOT_AMT'
			,'AS_11_ITEM01_CNT'
			,'AS_11_ITEM02_CNT'
			,'AS_11_ITEM04_CNT'
			,'AS_11_ITEM05_CNT'
			,'AS_11_ITEM06_CNT'
			,'AS_11_ITEM01_AMT'
			,'AS_11_ITEM02_AMT'
			,'AS_11_ITEM04_AMT'
			,'AS_11_ITEM05_AMT'
			,'AS_11_ITEM06_AMT'
			,'AS_11_ITEM11_CNT'
			,'AS_11_ITEM12_CNT'
			,'AS_11_ITEM14_CNT'
			,'AS_11_ITEM15_CNT'
			,'AS_11_ITEM16_CNT'
			,'AS_11_ITEM11_AMT'
			,'AS_11_ITEM12_AMT'
			,'AS_11_ITEM14_AMT'
			,'AS_11_ITEM15_AMT'
			,'AS_11_ITEM16_AMT'
			,'AS_12_CNT_AMT'
			,'AS_12_TOT_AMT'
			,'AS_12_ITEM01_CNT'
			,'AS_12_ITEM02_CNT'
			,'AS_12_ITEM04_CNT'
			,'AS_12_ITEM05_CNT'
			,'AS_12_ITEM06_CNT'
			,'AS_12_ITEM01_AMT'
			,'AS_12_ITEM02_AMT'
			,'AS_12_ITEM04_AMT'
			,'AS_12_ITEM05_AMT'
			,'AS_12_ITEM06_AMT'
			,'AS_12_ITEM11_CNT'
			,'AS_12_ITEM12_CNT'
			,'AS_12_ITEM14_CNT'
			,'AS_12_ITEM15_CNT'
			,'AS_12_ITEM16_CNT'
			,'AS_12_ITEM11_AMT'
			,'AS_12_ITEM12_AMT'
			,'AS_12_ITEM14_AMT'
			,'AS_12_ITEM15_AMT'
			,'AS_12_ITEM16_AMT'
			,'AS_14_CNT_AMT'
			,'AS_14_TOT_AMT'
			,'AS_14_ITEM01_CNT'
			,'AS_14_ITEM02_CNT'
			,'AS_14_ITEM04_CNT'
			,'AS_14_ITEM05_CNT'
			,'AS_14_ITEM06_CNT'
			,'AS_14_ITEM01_AMT'
			,'AS_14_ITEM02_AMT'
			,'AS_14_ITEM04_AMT'
			,'AS_14_ITEM05_AMT'
			,'AS_14_ITEM06_AMT'
			,'AS_14_ITEM11_CNT'
			,'AS_14_ITEM12_CNT'
			,'AS_14_ITEM14_CNT'
			,'AS_14_ITEM15_CNT'
			,'AS_14_ITEM16_CNT'
			,'AS_14_ITEM11_AMT'
			,'AS_14_ITEM12_AMT'
			,'AS_14_ITEM14_AMT'
			,'AS_14_ITEM15_AMT'
			,'AS_14_ITEM16_AMT'
			,'AS_18_CNT_AMT'
			,'AS_18_TOT_AMT'
			,'AS_18_ITEM01_CNT'
			,'AS_18_ITEM02_CNT'
			,'AS_18_ITEM04_CNT'
			,'AS_18_ITEM05_CNT'
			,'AS_18_ITEM06_CNT'
			,'AS_18_ITEM01_AMT'
			,'AS_18_ITEM02_AMT'
			,'AS_18_ITEM04_AMT'
			,'AS_18_ITEM05_AMT'
			,'AS_18_ITEM06_AMT'
			,'AS_18_ITEM11_CNT'
			,'AS_18_ITEM12_CNT'
			,'AS_18_ITEM14_CNT'
			,'AS_18_ITEM15_CNT'
			,'AS_18_ITEM16_CNT'
			,'AS_18_ITEM11_AMT'
			,'AS_18_ITEM12_AMT'
			,'AS_18_ITEM14_AMT'
			,'AS_18_ITEM15_AMT'
			,'AS_18_ITEM16_AMT'
        ]
    });
	
    store = Ext.create('Ext.data.Store', {
        pageSize: 30,
        model: 'DataThread',
        remoteSort: true,
        proxy: {
            type: 'ajax',
            url: COMMON_URL + '/ajaxPrdASReport',
            reader: {
            	root: 'resultGrid',
                totalProperty: 'totalCount'
            },
            simpleSortMode: true
        }
    });

    var columns = [
        {
			text : "대분류",
			dataIndex : 'prd_cate1_nm',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			text : "중분류",
			dataIndex : 'prd_cate2_nm',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			text : "접수제품",
			dataIndex : 'prd_serial_no',
			width : 120,
			align : 'center',
			sortable : true
		},{
			text : "제품이름",
			dataIndex : 'prd_nm',
			width : 120,
			align : 'center',
			sortable : false
		}, {
			text : "처리수량",
			columns: [{
				text : "유상",
				dataIndex : 'FREE_N_CNT',
				width : 60,
				align : 'right',
				sortable : false
			},{
				text : "무상",
				dataIndex : 'FREE_Y_CNT',
				width : 60,
				align : 'right',
				sortable : false
			},{
				text : "합계",
				dataIndex : 'TOT_CNT',
				width : 60,
				align : 'right',
				sortable : false
			},{
				text : "금액",
				dataIndex : 'TOT_AMT',
				width : 80,
				align : 'right',
				sortable : false,
				renderer: function(data) {
					return amt_numberic(data);
				}
			}]
		}, {
			text : "AS",
			columns: [{				
					text : "유상",
					columns: [{
						text : "가상계좌",
						columns: [{
							text : "수량",
							dataIndex : 'AS_10_ITEM01_CNT',
							width : 50,
							align : 'right',
							sortable : false
						},{
							text : "금액",
							dataIndex : 'AS_10_ITEM01_AMT',
							width : 80,
							align : 'right',
							sortable : false,
							renderer: function(data) {
								return amt_numberic(data);
							}
						}]
					},{
						text : "고객센터-카드",
						columns: [{
							text : "수량",
							dataIndex : 'AS_10_ITEM02_CNT',
							width : 50,
							align : 'right',
							sortable : false
						},{
							text : "금액",
							dataIndex : 'AS_10_ITEM02_AMT',
							width : 80,
							align : 'right',
							sortable : false,
							renderer: function(data) {
								return amt_numberic(data);
							}
						}]
					},{
						text : "찾서-현금",
						columns: [{
							text : "수량",
							dataIndex : 'AS_10_ITEM04_CNT',
							width : 50,
							align : 'right',
							sortable : false
						},{
							text : "금액",
							dataIndex : 'AS_10_ITEM04_AMT',
							width : 80,
							align : 'right',
							sortable : false,
							renderer: function(data) {
								return amt_numberic(data);
							}
						}]
					},{
						text : "찾서-카드",
						columns: [{
							text : "수량",
							dataIndex : 'AS_10_ITEM05_CNT',
							width : 50,
							align : 'right',
							sortable : false
						},{
							text : "금액",
							dataIndex : 'AS_10_ITEM05_AMT',
							width : 80,
							align : 'right',
							sortable : false,
							renderer: function(data) {
								return amt_numberic(data);
							}
						}]
					}]
				},{
					text : "무상",
					columns: [{
						text : "가상계좌",
						columns: [{
							text : "수량",
							dataIndex : 'AS_10_ITEM11_CNT',
							width : 50,
							align : 'right',
							sortable : false
						},{
							text : "금액",
							dataIndex : 'AS_10_ITEM11_AMT',
							width : 80,
							align : 'right',
							sortable : false,
							renderer: function(data) {
								return amt_numberic(data);
							}
						}]
					},{
						text : "고객센터-카드",
						columns: [{
							text : "수량",
							dataIndex : 'AS_10_ITEM12_CNT',
							width : 50,
							align : 'right',
							sortable : false
						},{
							text : "금액",
							dataIndex : 'AS_10_ITEM12_AMT',
							width : 80,
							align : 'right',
							sortable : false,
							renderer: function(data) {
								return amt_numberic(data);
							}
						}]
					},{
						text : "찾서-현금",
						columns: [{
							text : "수량",
							dataIndex : 'AS_10_ITEM14_CNT',
							width : 50,
							align : 'right',
							sortable : false
						},{
							text : "금액",
							dataIndex : 'AS_10_ITEM14_AMT',
							width : 80,
							align : 'right',
							sortable : false,
							renderer: function(data) {
								return amt_numberic(data);
							}
						}]
					},{
						text : "찾서-카드",
						columns: [{
							text : "수량",
							dataIndex : 'AS_10_ITEM15_CNT',
							width : 50,
							align : 'right',
							sortable : false
						},{
							text : "금액",
							dataIndex : 'AS_10_ITEM15_AMT',
							width : 80,
							align : 'right',
							sortable : false,
							renderer: function(data) {
								return amt_numberic(data);
							}
						}]
					}]
				},{
					text : "합계",
					columns: [{
						text : "수량",
						dataIndex : 'AS_10_CNT_AMT',
						width : 50,
						align : 'right',
						sortable : false
					},{
						text : "금액",
						dataIndex : 'AS_10_TOT_AMT',
						width : 80,
						align : 'right',
						sortable : false,
						renderer: function(data) {
							return amt_numberic(data);
						}
					}]
				}]
		}, {
			text : "주문",
			columns: [{				
					text : "유상",
					columns: [{
						text : "가상계좌",
						columns: [{
							text : "수량",
							dataIndex : 'AS_11_ITEM01_CNT',
							width : 50,
							align : 'right',
							sortable : false
						},{
							text : "금액",
							dataIndex : 'AS_11_ITEM01_AMT',
							width : 80,
							align : 'right',
							sortable : false,
							renderer: function(data) {
								return amt_numberic(data);
							}
						}]
					},{
						text : "고객센터-카드",
						columns: [{
							text : "수량",
							dataIndex : 'AS_11_ITEM02_CNT',
							width : 50,
							align : 'right',
							sortable : false
						},{
							text : "금액",
							dataIndex : 'AS_11_ITEM02_AMT',
							width : 80,
							align : 'right',
							sortable : false,
							renderer: function(data) {
								return amt_numberic(data);
							}
						}]
					},{
						text : "찾서-현금",
						columns: [{
							text : "수량",
							dataIndex : 'AS_11_ITEM04_CNT',
							width : 50,
							align : 'right',
							sortable : false
						},{
							text : "금액",
							dataIndex : 'AS_11_ITEM04_AMT',
							width : 80,
							align : 'right',
							sortable : false,
							renderer: function(data) {
								return amt_numberic(data);
							}
						}]
					},{
						text : "찾서-카드",
						columns: [{
							text : "수량",
							dataIndex : 'AS_11_ITEM05_CNT',
							width : 50,
							align : 'right',
							sortable : false
						},{
							text : "금액",
							dataIndex : 'AS_11_ITEM05_AMT',
							width : 80,
							align : 'right',
							sortable : false,
							renderer: function(data) {
								return amt_numberic(data);
							}
						}]
					}]
				},{
					text : "무상",
					columns: [{
						text : "가상계좌",
						columns: [{
							text : "수량",
							dataIndex : 'AS_11_ITEM11_CNT',
							width : 50,
							align : 'right',
							sortable : false
						},{
							text : "금액",
							dataIndex : 'AS_11_ITEM11_AMT',
							width : 80,
							align : 'right',
							sortable : false,
							renderer: function(data) {
								return amt_numberic(data);
							}
						}]
					},{
						text : "고객센터-카드",
						columns: [{
							text : "수량",
							dataIndex : 'AS_11_ITEM12_CNT',
							width : 50,
							align : 'right',
							sortable : false
						},{
							text : "금액",
							dataIndex : 'AS_11_ITEM12_AMT',
							width : 80,
							align : 'right',
							sortable : false,
							renderer: function(data) {
								return amt_numberic(data);
							}
						}]
					},{
						text : "찾서-현금",
						columns: [{
							text : "수량",
							dataIndex : 'AS_11_ITEM14_CNT',
							width : 50,
							align : 'right',
							sortable : false
						},{
							text : "금액",
							dataIndex : 'AS_11_ITEM14_AMT',
							width : 80,
							align : 'right',
							sortable : false,
							renderer: function(data) {
								return amt_numberic(data);
							}
						}]
					},{
						text : "찾서-카드",
						columns: [{
							text : "수량",
							dataIndex : 'AS_11_ITEM15_CNT',
							width : 50,
							align : 'right',
							sortable : false
						},{
							text : "금액",
							dataIndex : 'AS_11_ITEM15_AMT',
							width : 80,
							align : 'right',
							sortable : false,
							renderer: function(data) {
								return amt_numberic(data);
							}
						}]
					}]
				},{
					text : "합계",
					columns: [{
						text : "수량",
						dataIndex : 'AS_11_CNT_AMT',
						width : 50,
						align : 'right',
						sortable : false
					},{
						text : "금액",
						dataIndex : 'AS_11_TOT_AMT',
						width : 80,
						align : 'right',
						sortable : false,
						renderer: function(data) {
							return amt_numberic(data);
						}
					}]
				}]
		}, {
			text : "보상판매",
			columns: [{				
				text : "유상",
				columns: [{
					text : "가상계좌",
					columns: [{
						text : "수량",
						dataIndex : 'AS_14_ITEM01_CNT',
						width : 50,
						align : 'right',
						sortable : false
					},{
						text : "금액",
						dataIndex : 'AS_14_ITEM01_AMT',
						width : 80,
						align : 'right',
						sortable : false,
						renderer: function(data) {
							return amt_numberic(data);
						}
					}]
				},{
					text : "고객센터-카드",
					columns: [{
						text : "수량",
						dataIndex : 'AS_14_ITEM02_CNT',
						width : 50,
						align : 'right',
						sortable : false
					},{
						text : "금액",
						dataIndex : 'AS_14_ITEM02_AMT',
						width : 80,
						align : 'right',
						sortable : false,
						renderer: function(data) {
							return amt_numberic(data);
						}
					}]
				},{
					text : "찾서-현금",
					columns: [{
						text : "수량",
						dataIndex : 'AS_14_ITEM04_CNT',
						width : 50,
						align : 'right',
						sortable : false
					},{
						text : "금액",
						dataIndex : 'AS_14_ITEM04_AMT',
						width : 80,
						align : 'right',
						sortable : false,
						renderer: function(data) {
							return amt_numberic(data);
						}
					}]
				},{
					text : "찾서-카드",
					columns: [{
						text : "수량",
						dataIndex : 'AS_14_ITEM05_CNT',
						width : 50,
						align : 'right',
						sortable : false
					},{
						text : "금액",
						dataIndex : 'AS_14_ITEM05_AMT',
						width : 80,
						align : 'right',
						sortable : false,
						renderer: function(data) {
							return amt_numberic(data);
						}
					}]
				}]
			},{
				text : "무상",
				columns: [{
					text : "가상계좌",
					columns: [{
						text : "수량",
						dataIndex : 'AS_14_ITEM11_CNT',
						width : 50,
						align : 'right',
						sortable : false
					},{
						text : "금액",
						dataIndex : 'AS_14_ITEM11_AMT',
						width : 80,
						align : 'right',
						sortable : false,
						renderer: function(data) {
							return amt_numberic(data);
						}
					}]
				},{
					text : "고객센터-카드",
					columns: [{
						text : "수량",
						dataIndex : 'AS_14_ITEM12_CNT',
						width : 50,
						align : 'right',
						sortable : false
					},{
						text : "금액",
						dataIndex : 'AS_14_ITEM12_AMT',
						width : 80,
						align : 'right',
						sortable : false,
						renderer: function(data) {
							return amt_numberic(data);
						}
					}]
				},{
					text : "찾서-현금",
					columns: [{
						text : "수량",
						dataIndex : 'AS_14_ITEM14_CNT',
						width : 50,
						align : 'right',
						sortable : false
					},{
						text : "금액",
						dataIndex : 'AS_14_ITEM14_AMT',
						width : 80,
						align : 'right',
						sortable : false,
						renderer: function(data) {
							return amt_numberic(data);
						}
					}]
				},{
					text : "찾서-카드",
					columns: [{
						text : "수량",
						dataIndex : 'AS_14_ITEM15_CNT',
						width : 50,
						align : 'right',
						sortable : false
					},{
						text : "금액",
						dataIndex : 'AS_14_ITEM15_AMT',
						width : 80,
						align : 'right',
						sortable : false,
						renderer: function(data) {
							return amt_numberic(data);
						}
					}]
				}]
			},{
				text : "합계",
				columns: [{
					text : "수량",
					dataIndex : 'AS_14_CNT_AMT',
					width : 50,
					align : 'right',
					sortable : false
				},{
					text : "금액",
					dataIndex : 'AS_14_TOT_AMT',
					width : 80,
					align : 'right',
					sortable : false,
					renderer: function(data) {
						return amt_numberic(data);
					}
				}]
			}]
		}, {
			text : "찾서",
			columns: [{				
					text : "유상",
					columns: [{
						text : "찾서-현금",
						columns: [{
							text : "수량",
							dataIndex : 'AS_12_ITEM04_CNT',
							width : 50,
							align : 'right',
							sortable : false
						},{
							text : "금액",
							dataIndex : 'AS_12_ITEM04_AMT',
							width : 80,
							align : 'right',
							sortable : false,
							renderer: function(data) {
								return amt_numberic(data);
							}
						}]
					},{
						text : "찾서-카드",
						columns: [{
							text : "수량",
							dataIndex : 'AS_12_ITEM05_CNT',
							width : 50,
							align : 'right',
							sortable : false
						},{
							text : "금액",
							dataIndex : 'AS_12_ITEM05_AMT',
							width : 80,
							align : 'right',
							sortable : false,
							renderer: function(data) {
								return amt_numberic(data);
							}
						}]
					}]
				},{
					text : "무상",
					columns: [{
						text : "찾서-현금",
						columns: [{
							text : "수량",
							dataIndex : 'AS_12_ITEM14_CNT',
							width : 50,
							align : 'right',
							sortable : false
						},{
							text : "금액",
							dataIndex : 'AS_12_ITEM14_AMT',
							width : 80,
							align : 'right',
							sortable : false,
							renderer: function(data) {
								return amt_numberic(data);
							}
						}]
					},{
						text : "찾서-카드",
						columns: [{
							text : "수량",
							dataIndex : 'AS_12_ITEM15_CNT',
							width : 50,
							align : 'right',
							sortable : false
						},{
							text : "금액",
							dataIndex : 'AS_12_ITEM15_AMT',
							width : 80,
							align : 'right',
							sortable : false,
							renderer: function(data) {
								return amt_numberic(data);
							}
						}]
					}]
				},{
					text : "합계",
					columns: [{
						text : "수량",
						dataIndex : 'AS_12_CNT_AMT',
						width : 50,
						align : 'right',
						sortable : false
					},{
						text : "금액",
						dataIndex : 'AS_12_TOT_AMT',
						width : 80,
						align : 'right',
						sortable : false,
						renderer: function(data) {
							return amt_numberic(data);
						}
					}]
				}]
		}, {
			text : "내방",
			columns: [{				
				text : "유상",
				columns: [{
					text : "가상계좌",
					columns: [{
						text : "수량",
						dataIndex : 'AS_18_ITEM01_CNT',
						width : 50,
						align : 'right',
						sortable : false
					},{
						text : "금액",
						dataIndex : 'AS_18_ITEM01_AMT',
						width : 80,
						align : 'right',
						sortable : false,
						renderer: function(data) {
							return amt_numberic(data);
						}
					}]
				},{
					text : "고객센터-카드",
					columns: [{
						text : "수량",
						dataIndex : 'AS_18_ITEM02_CNT',
						width : 50,
						align : 'right',
						sortable : false
					},{
						text : "금액",
						dataIndex : 'AS_18_ITEM02_AMT',
						width : 80,
						align : 'right',
						sortable : false,
						renderer: function(data) {
							return amt_numberic(data);
						}
					}]
				},{
					text : "찾서-현금",
					columns: [{
						text : "수량",
						dataIndex : 'AS_18_ITEM04_CNT',
						width : 50,
						align : 'right',
						sortable : false
					},{
						text : "금액",
						dataIndex : 'AS_18_ITEM04_AMT',
						width : 80,
						align : 'right',
						sortable : false,
						renderer: function(data) {
							return amt_numberic(data);
						}
					}]
				},{
					text : "찾서-카드",
					columns: [{
						text : "수량",
						dataIndex : 'AS_18_ITEM05_CNT',
						width : 50,
						align : 'right',
						sortable : false
					},{
						text : "금액",
						dataIndex : 'AS_18_ITEM05_AMT',
						width : 80,
						align : 'right',
						sortable : false,
						renderer: function(data) {
							return amt_numberic(data);
						}
					}]
				}]
			},{
				text : "무상",
				columns: [{
					text : "가상계좌",
					columns: [{
						text : "수량",
						dataIndex : 'AS_18_ITEM11_CNT',
						width : 50,
						align : 'right',
						sortable : false
					},{
						text : "금액",
						dataIndex : 'AS_18_ITEM11_AMT',
						width : 80,
						align : 'right',
						sortable : false,
						renderer: function(data) {
							return amt_numberic(data);
						}
					}]
				},{
					text : "고객센터-카드",
					columns: [{
						text : "수량",
						dataIndex : 'AS_18_ITEM12_CNT',
						width : 50,
						align : 'right',
						sortable : false
					},{
						text : "금액",
						dataIndex : 'AS_18_ITEM12_AMT',
						width : 80,
						align : 'right',
						sortable : false,
						renderer: function(data) {
							return amt_numberic(data);
						}
					}]
				},{
					text : "찾서-현금",
					columns: [{
						text : "수량",
						dataIndex : 'AS_18_ITEM14_CNT',
						width : 50,
						align : 'right',
						sortable : false
					},{
						text : "금액",
						dataIndex : 'AS_18_ITEM14_AMT',
						width : 80,
						align : 'right',
						sortable : false,
						renderer: function(data) {
							return amt_numberic(data);
						}
					}]
				},{
					text : "찾서-카드",
					columns: [{
						text : "수량",
						dataIndex : 'AS_18_ITEM15_CNT',
						width : 50,
						align : 'right',
						sortable : false
					},{
						text : "금액",
						dataIndex : 'AS_18_ITEM15_AMT',
						width : 80,
						align : 'right',
						sortable : false,
						renderer: function(data) {
							return amt_numberic(data);
						}
					}]
				}]
			},{
				text : "합계",
				columns: [{
					text : "수량",
					dataIndex : 'AS_18_CNT_AMT',
					width : 50,
					align : 'right',
					sortable : false
				},{
					text : "금액",
					dataIndex : 'AS_18_TOT_AMT',
					width : 80,
					align : 'right',
					sortable : false,
					renderer: function(data) {
						return amt_numberic(data);
					}
				}]
			}]
		}];
    
	
	var siteStore = Ext.create('Ext.data.Store', {
	    fields: ['code', 'name'],
	    data : [
	        {"code":"", "name":"전체"},    
	        {"code":"1", "name":"한경희생활과학"},
	        {"code":"2", "name":"리빙(뷰티)"},
	        {"code":"3", "name":"카페이탈리아"},
	        {"code":"4", "name":"홈케어"},
	        {"code":"5", "name":"브랜드대여"},
	        {"code":"6", "name":"사은품"}
	    ]
	}); 
    
    var comboSite = Ext.create('Ext.form.ComboBox', {
        store: siteStore,
        id: 'site',
        name: 'site',
        fieldLabel: '사이트',
        width: 200,
        labelWidth: 60,
        queryMode: 'local',
        displayField: 'name',
        valueField: 'code',        
        margin: '0 0 0 10',
        emptyText: '사이트구분',
        value: '1'
    });
    
    var dateDivStore = Ext.create('Ext.data.ArrayStore', {
	    fields: [{ name: 'code' },{ name: 'code_nm' }],
	    data: [['payment_dt','결제일자'],['insert_dt', '접수일자']]
	});
    
    var comboDate = Ext.create('Ext.form.ComboBox', {
    	store: dateDivStore,
        name: 'date_div', 
        fieldLabel: '기간검색',
        width: 160,
        labelWidth: 60,
        displayField: 'code_nm',
        valueField: 'code',
        emptyText: '선택',
        editable: false,
        margin: '0 0 0 10',
        value: 'payment_dt'
    });

    var searchForm = Ext.create('Ext.form.Panel', {		
    	id: 'searchForm',
    	bodyPadding: 5,
    	layout: {
	        type: 'vbox',       // Arrange child items vertically
	        align: 'stretch'    // Each takes up full width
	    },
	    items: [
	        {
	        	border: 0,
				layout: {
					type: 'hbox',  
					align: 'stretch',
					padding: '0 5 0 5'
				},      
				items: [
					{
					    width: 16,
					    height: 16,
					    xtype: 'image',
					    margin: '0 5 0 5',
					    imgCls: 'icon-mn004'				        
					},
					comboSite,
					comboDate,					
					{
			        	width: 120,
				        xtype: 'datefield',
				        name: 'sdate',		
				        format: 'Ymd',
				        submitFormat: 'Ymd',
				        submitValue: true,
				        value: toDate,
				        margin: '0 0 0 5',
			    		emptyText: '접수일(시작)',
			    		listeners:  {
			                specialkey: function (f,e) {    
			                     if (e.getKey() == e.ENTER) {
			                    	 reload();
			                    }
			                }
			            }
			        },
			        {
			        	width: 120,
				        xtype: 'datefield',
				        name: 'edate',		
				        format: 'Ymd',
				        submitFormat: 'Ymd',
				        submitValue: true,
				        value: toDate,
				        margin: '0 0 0 5',
			    		emptyText: '접수일(종료)',
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
			            text: '오늘',
			            margin: '0 0 0 5',
			        	handler: function() {
			        		setFormDate('today');
			        	}
			        },
			        {
			            xtype: 'button',
			            text: '주간',
			            margin: '0 0 0 5',
			            handler: function() {
			        		setFormDate('week');
			        	}
			        },
			        {
			            xtype: 'button',
			            text: '월간',
			            margin: '0 0 0 5',
			            handler: function() {
			        		setFormDate('month');
			        	}
			        },
			        {
			            xtype: 'button',
			            iconCls: 'icon-search',
			            margin: '0 0 0 5',
			        	handler: reload
			        },{
				    	xtype: 'button',
				    	text: '엑셀다운로드',
				    	align:'right',
				    	style:'text-align:right',		    	
				    	iconCls: 'icon-excel',
				    	margin: '0 0 0 5px',
				    	handler: function(){
				    		download();
				    	}
				    }
			     ]
	        }
	    ]
	});
    
	Ext.create('Ext.panel.Panel', {
		id:'Content',
	    title: name,
	    flex: 1,
	    height: FRAME_CONTENT_HEIGHT,
	    renderTo: Ext.getBody(),
	    layout: {
	        type: 'vbox',       // Arrange child items vertically
	        align: 'stretch',    // Each takes up full width
	        padding: 5
	    },
	    items: [
	        searchForm,
	    {
	        xtype: 'splitter'   // A splitter between the two child items
	    },		
	    {               // Results grid specified as a config object with an xtype of 'grid'
	        xtype: 'grid',
	        columns: columns,// One header just for show. There's no data,
	        store: store, // A dummy empty data store
	        flex: 1,                                       // Use 1/3 of Container's height (hint to Box layout)
	        id: 'calllog_grid',
	        name: 'calllog_grid'
	    }]
	});
	
	// form reload
	function reload() {
		
		var form = Ext.getCmp('searchForm').getForm();
		
		var sdate = form.findField("sdate");
		var edate = form.findField("edate");
						
		if(sdate.getSubmitValue() == "" 
			&& edate.getSubmitValue() == "") {				
			
			Ext.Msg.alert('Notice', '날짜 입력은 필수입니다!');
			return;			
		}
		
		if((sdate.getSubmitValue() == "" && edate.getSubmitValue() != "") || 
				(sdate.getSubmitValue() != "" && edate.getSubmitValue() == "")) {
			Ext.Msg.alert('Notice', '기간검색은 시작일자와 종료일자 모두 입력해 주세요!');
			return;
		}
		
		store.getProxy().extraParams = form.getValues();
		store.loadPage(1);
	}
	
	// form date
	function setFormDate(flag) {
		
		var form = Ext.getCmp('searchForm').getForm();
		
		var toDate = Ext.Date.format(new Date(),'Ymd');
		
		if(flag == "today") { // 오늘
			
			form.findField("sdate").setValue(toDate);
			form.findField("edate").setValue(toDate);
			
		} else if (flag == "week") { // 주간
			form.findField("sdate").setValue(getWeekDay());			
			form.findField("edate").setValue(toDate);
		} else if (flag == "month") { // 월간
			form.findField("sdate").setValue(getMonthDay());
			form.findField("edate").setValue(toDate);
		} else { //공백
			form.findField("sdate").setValue("");
			form.findField("edate").setValue("");
		}
	}
    
});

function amt_numberic(str){
	if(str != "0"){
		return "￦ "+Number(str).toLocaleString().split(".")[0];
	}else{
		return "0";
	}
}

function download() {
	
	Ext.getBody().mask('파일 다운로드 중...');
	
	Ext.Ajax.request({
		url: COMMON_URL + '/ajaxPrdASReportDown',
		success: function(result, request) {
			Ext.getBody().unmask();
			var obj = Ext.decode(result.responseText);
			// console.log(obj);
			location.href = COMMON_URL + "/common/FileDown.jsp?fileName="+obj.filename+"&fileDir="+obj.filepath;
		},
		failure: function(result, request) {
			Ext.getBody().unmask();        							 
			Ext.Msg.alert('Error', '다운로드 중 오류가 발생하였습니다.');	        							 
		},
		params : Ext.getCmp('searchForm').getForm().getValues(),  
		timeout: TIMEOUT_SEC
	});
}