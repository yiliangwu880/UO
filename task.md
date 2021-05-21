
#整体
整体服务器框架：
标准appMgr
创建每个进程项目

zone跨服协调。

#game com
	多索引map. mainkey, 次要key可以未缺省值，查找不到。
#acc
	继续完善创建角色流程
	转发client消息 从 cmd, msg. 改为 msg

#db
	请求响应带唯一会话id,利用这个，请求可以直接传入回调函数，写lambda处理响应。
	sid 超时处理。用全局定时器轮询判断，比每次请求走注册，删除timer 效率高。

