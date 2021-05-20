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
	struct RspZoneOk_cs
	{
		const uint16_t id = 51;
		uint16 svrId;
	};


}
#pragma pack(pop)
