/*
db table 嵌套的 struct 定义
*/

#pragma once

#include <string>
#include <vector>
#include <array>
#include "dbTable.h"
#include "AttrDef.h"

namespace db
{

	struct ActorBrief  
	{
		uint64_t uin;
		std::string name;
	};

	struct DbAttr 
	{
		Attr type;
		int32_t v;
	};

	//武器，装备，穿戴物
	struct dbEquip 
	{
		uint16_t id;
		std::string name;//独特名
		//其他可变属性
		std::vector<DbAttr> attrs;
	};

	struct DbEquips 
	{
		//主副手武器
		dbEquip primary;
		dbEquip second;
		std::vector<dbEquip> vecDress;//武器外穿戴物
	};

	struct DbActorBase 
	{
		uint16_t str = 0;
		uint16_t dex = 0;
		uint16_t intl = 0;

		uint16_t x = 0, y = 0, z = 0;

		bool female = false;
		uint8_t race = 0;

	};

	struct DbPlayerBase
	{
		uint16_t hue = 0;
		int16_t hairVal = 0;
		int16_t hairHue = 0;
		int16_t hairValf = 0;
		int16_t hairHuef = 0;
		uint32_t sceneId = 0;
	};

	struct DbActor //monster ,npc, playeractor com use
	{
		DbActorBase actorBase;
		DbPlayerBase playerBase;
		DbEquips equips;
	};


//	
//先定义宏参数信息，以后再具体实现
//域的顺序 和 遗漏，都会初始化的时候检查出来
#define DB_ALL_STRUCT_INFO \
	DB_CLASS_NAME(ActorBrief)\
	DB_FIELD(uin)\
	DB_FIELD(name)\
	DB_CLASS_END\
\
	DB_CLASS_NAME(DbAttr)\
	DB_FIELD(type)\
	DB_FIELD(v)\
	DB_CLASS_END\
\
	DB_CLASS_NAME(dbEquip)\
	DB_FIELD(id)\
	DB_FIELD(name)\
	DB_FIELD(attrs)\
	DB_CLASS_END\
\
	DB_CLASS_NAME(DbEquips)\
	DB_FIELD(primary)\
	DB_FIELD(second)\
	DB_FIELD(vecDress)\
	DB_CLASS_END\
\
	DB_CLASS_NAME(DbActorBase)\
	DB_FIELD(str)\
	DB_FIELD(dex)\
	DB_FIELD(intl)\
	DB_FIELD(x)\
	DB_FIELD(y)\
	DB_FIELD(z)\
	DB_FIELD(female)\
	DB_FIELD(race)\
	DB_CLASS_END\
\
	DB_CLASS_NAME(DbPlayerBase)\
	DB_FIELD(hue)\
	DB_FIELD(hairVal)\
	DB_FIELD(hairHue)\
	DB_FIELD(hairValf)\
	DB_FIELD(hairHuef)\
	DB_FIELD(sceneId)\
	DB_CLASS_END\
\
	DB_CLASS_NAME(DbActor)\
	DB_FIELD(actorBase)\
	DB_FIELD(playerBase)\
	DB_FIELD(equips)\
	DB_CLASS_END\
\





}