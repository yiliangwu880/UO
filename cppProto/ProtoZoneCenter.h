//zone --> center 通讯
//id 50-60
#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#pragma pack(push)
#pragma pack(1)
namespace proto {

	//先定义参数信息，以后再具体实现, 域的顺序 和 遗漏，都会初始化的时候检查出来
#define PROTO_ZONE_CENTER \
	DB_CLASS_NAME(ReqZoneOk_cs)\
	DB_FIELD(id)\
	DB_FIELD(svrId)\
	DB_CLASS_END\
\
	DB_CLASS_NAME(RspZoneOk_cs)\
	DB_FIELD(id)\
	DB_FIELD(svrId)\
	DB_CLASS_END\

	struct ReqZoneOk_cs
	{
		const uint16_t id = 50;
		uint16 svrId;
	};
	//for tmp test, will del
	struct RspZoneOk_sc
	{
		const uint16_t id = 51;
		uint16 svrId;
	};

	struct ReqLoginZone_sc
	{
		const uint16_t id = 52;
		uint64 uin;
		std::string playerData; //db::player pack data
	};
	struct RspLoginZone_cs
	{
		const uint16_t id = 53;
		uint64 uin;
		bool ret;
	};


	struct ReqZoneReserve
	{
		const uint16_t id = 54;
		uint64 uin;
		uint16_t srcSvrId;
		uint16_t dstZoneId;
		uint32_t sceneId;
	};
	struct RspZoneReserve
	{
		const uint16_t id = 55;
		uint64 uin;
		uint16_t srcZoneId;
		bool ret;
	};

	//zone 请求切换 zone, zone , center 之间都可以互相发送
	struct ReqTranZone
	{
		const uint16_t id = 56;
		uint16_t zoneId;
		uint64 uin;
		std::string playerData; //db::player pack data
	};



}
#pragma pack(pop)
