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
	struct DbEquips 
	{
		int i;
	};
	struct DbActor //monster ,npc, playeractor com use
	{
		int str;
		int dex;
		int intl;
		int female;
		uint8_t race;
		
		uint16_t hue;
		int16_t hairVal;
		int16_t hairHue;
		int16_t hairValf;
		int16_t hairHuef;
		DbEquips equips;
	};


//先定义宏参数信息，以后再具体实现
//域的顺序 和 遗漏，都会初始化的时候检查出来
#define DB_ALL_STRUCT_INFO \
	DB_CLASS_NAME(ActorBrief)\
	DB_FIELD(uin)\
	DB_FIELD(name)\
	DB_CLASS_END\
\
	DB_CLASS_NAME(DbActor)\
	DB_FIELD(str)\
	DB_FIELD(dex)\
	DB_FIELD(intl)\
	DB_FIELD(female)\
	DB_FIELD(race)\
	DB_FIELD(hue)\
	DB_FIELD(hairVal)\
	DB_FIELD(hairHue)\
	DB_FIELD(hairValf)\
	DB_FIELD(hairHuef)\
	DB_FIELD(equips)\
	DB_CLASS_END\
\





}