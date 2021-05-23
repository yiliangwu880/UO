
# 跨服切换场景
## 我的设计
	设定环境，多服务器多场景，网络稳定。宕机或者网络断开重连不考虑。全部重启解决。
## center player
	state: 
		WaitEnterZone:    
				//加载完, 请求zone 登录player.				--ReqLoginZone_sc
				//接收 zone 登录player 成功， 进入 Playing		--RspLoginZone_cs

		Playing,
				//enter:正常转发 消息. 设置zoneId
				//接收 预定，转发目标zone.						--ReqZoneReserve
				//接收 响应预定，转发源zone, 成功预定进入 Moving。--RspZoneReserve

		Moving, //enter:缓存 send to zone消息
				//收到zone 转换 zone， 转发目标zone 。进入Playing	--ReqTranZone

## zone Player
	state: 
		None   : //接收 ReqZoneReserve,成功创建WaitTranIn，失败通知center --RspZoneReserve
				//接收 登录player，创建 Playing

		WaitTranIn:  //接收 ReqTranZone， 请求acc恢复,请求acc 缓存, 进入Playing.  --MsgReqCacheMsg

		Playing: 
				//请求acc 缓存，请求 center 预定位置,进入WaitReserve。		--MsgReqCacheMsg， ReqZoneReserve

		WaitReserve: (防止重复请求预定)
				// 接收响应 acc缓存, center 预定都ok， 请求 转换zone. 删除自己。 --RspZoneReserve，MsgRspCacheMsg，ReqTranZone
					(保证 删除后，不会收到 Player 的业务请求)
				//接收center 预定失败，进入Playing.				--RspZoneReserve