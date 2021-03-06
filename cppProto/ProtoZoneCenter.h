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
	DB_CLASS_NAME(RspZoneOk_sc)\
	DB_FIELD(id)\
	DB_FIELD(svrId)\
	DB_CLASS_END\
\
	DB_CLASS_NAME(ReqLoginZone_sc)\
	DB_FIELD(id)\
	DB_FIELD(cid)\
	DB_FIELD(isCreate)\
	DB_FIELD(playerData)\
	DB_CLASS_END\
\
	DB_CLASS_NAME(RspLoginZone_cs)\
	DB_FIELD(id)\
	DB_FIELD(uin)\
	DB_FIELD(ret)\
	DB_CLASS_END\
\
	DB_CLASS_NAME(ReqReLoginZone_sc)\
	DB_FIELD(id)\
	DB_FIELD(uin)\
	DB_FIELD(cid)\
	DB_CLASS_END\
\
	DB_CLASS_NAME(RspReLoginZone_cs)\
	DB_FIELD(id)\
	DB_FIELD(uin)\
	DB_FIELD(ret)\
	DB_CLASS_END\
\
	DB_CLASS_NAME(ReqZoneReserve)\
	DB_FIELD(id)\
	DB_FIELD(uin)\
	DB_FIELD(srcSvrId)\
	DB_FIELD(dstZoneId)\
	DB_FIELD(sceneId)\
	DB_CLASS_END\
\
	DB_CLASS_NAME(RspZoneReserve)\
	DB_FIELD(id)\
	DB_FIELD(uin)\
	DB_FIELD(srcZoneId)\
	DB_FIELD(ret)\
	DB_CLASS_END\
\
	DB_CLASS_NAME(ReqTranZone)\
	DB_FIELD(id)\
	DB_FIELD(zoneId)\
	DB_FIELD(uin)\
	DB_FIELD(playerData)\
	DB_CLASS_END\

	struct ReqZoneOk_cs
	{
		const uint16_t id = 50;
		uint16 svrId=0;
	};
	//for tmp test, will del
	struct RspZoneOk_sc
	{
		const uint16_t id = 51;
		uint16 svrId=0;
	};

	struct ReqLoginZone_sc
	{
		const uint16_t id = 52;
		uint64 cid = 0;
		bool isCreate = false; //true indicate create player , and first login
		std::string playerData; //DbPlayer pack data
	};
	struct RspLoginZone_cs
	{
		const uint16_t id = 53;
		uint64 uin=0;
		bool ret=false;
	};

	struct ReqReLoginZone_sc
	{
		const uint16_t id = 54;
		uint64 uin=0;
		uint64 cid=0;
	};
	struct RspReLoginZone_cs
	{
		const uint16_t id = 55;
		uint64 uin=0;
		bool ret=false;
	};


	struct ReqZoneReserve
	{
		const uint16_t id = 154;
		uint64 uin=0;
		uint16_t srcSvrId=0;
		uint16_t dstZoneId=0;
		uint32_t sceneId=0;
	};
	struct RspZoneReserve
	{
		const uint16_t id = 155;
		uint64 uin=0;
		uint16_t srcZoneId=0;
		bool ret=false;
	};

	//zone 请求切换 zone, zone , center 之间都可以互相发送
	struct ReqTranZone
	{
		const uint16_t id = 156;
		uint16_t zoneId=0;
		uint64 uin=0;
		std::string playerData; //DbPlayer pack data
	};



}
#pragma pack(pop)
