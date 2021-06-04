/*
db table 嵌套的 struct 定义
*/

#pragma once

#include <string>
#include <vector>
#include "dbTable.h"

namespace db
{

	struct ActorBrief  
	{
		uint64_t uin;
		std::string name;
	};
	struct DbActorBase
	{
		int str;
		int dex;
		int intl;
		int gender;
		int	race;
	};

//先定义宏参数信息，以后再具体实现
//域的顺序 和 遗漏，都会初始化的时候检查出来
#define DB_ALL_STRUCT_INFO \
	DB_CLASS_NAME(ActorBrief)\
	DB_FIELD(uin)\
	DB_FIELD(name)\
	DB_CLASS_END\
\





}