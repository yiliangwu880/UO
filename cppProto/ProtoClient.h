//game client --> game server通讯

#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#pragma pack(push)
#pragma pack(1)
namespace proto {

	//约定前 uint16_t 必须为 消息号id.
	struct login_cs
	{
		const uint16_t id = 1;
		string name;
		string psw;
	};

	//先定义参数信息，以后再具体实现, 域的顺序 和 遗漏，都会初始化的时候检查出来
#define PROTO_CLIENT \
	DB_CLASS_NAME(login_cs)\
	DB_FIELD(id)\
	DB_FIELD(name)\
	DB_FIELD(psw)\
	DB_CLASS_END\
\

}



#pragma pack(pop)
