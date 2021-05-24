
# 跨服切换场景
## 我的设计
	设定环境，多服务器多场景，网络稳定。宕机或者网络断开重连不考虑。全部重启解决。
## center player
	state: 
		Playing,
				//enter:正常转发 消息. 设置zoneId
				//接收 预定，转发目标zone.						--ReqZoneReserve
				//接收 响应预定，转发源zone, 成功预定进入 Moving。--RspZoneReserve

		Moving, //enter:缓存 send to zone消息
				//收到zone 转换 zone， 转发目标zone 。进入Playing	--ReqTranZone

## zone Player
	state: 
		None   : //接收 ReqZoneReserve,成功创建WaitTranIn，失败通知center --RspZoneReserve
				
		Playing: 
				//请求acc 缓存，请求 center 预定位置,进入WaitReserve。		--MsgReqCacheMsg， ReqZoneReserve

		WaitTranIn:  //接收 ReqTranZone， 请求acc恢复,请求acc 缓存, 进入Playing.  --MsgReqCacheMsg


		WaitReserve: (防止重复请求预定)
				// 接收响应 acc缓存, center 预定都ok， 请求 转换zone. 删除自己。 --RspZoneReserve，MsgRspCacheMsg，ReqTranZone
					(保证 删除后，不会收到 Player 的业务请求)
				//接收center 预定失败，进入Playing.				--RspZoneReserve

#登录流程
## center player
	state:
		None:
			请求登录，读db,创建player. 进入WaitLogin

		WaitLogin:
			请求登录，拒绝。
			请求zone 登录player.							--ReqLoginZone_sc
			接收 zone 登录player 成功， 进入 LoginOk		--RspLoginZone_cs

		LoginOk: 不区分在线离线状态
			请求重登录，请求zone 重登录， 进入 WaitReLogin	--ReqReLoginZone_sc

		WaitReLogin: 
			接收 zone 重登录player 成功， 进入 LoginOk		--RspReLoginZone_cs
			
## zone Player
	state: 
		None   : 
				接收 登录，创建 player，进入LoginOk  --ReqLoginZone_sc RspLoginZone_cs

		LoginOk:
				接收 重登录，替换session 	--ReqReLoginZone_sc RspReLoginZone_cs
				当 session 删除，进入 OffLine

		OffLine:
				接收 登录，进入LoginOk  --ReqLoginZone_sc RspLoginZone_cs
				离线超时，del player.