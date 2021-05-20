/*
db table 定义
unordered_map 比较少用，新增的需要定义对应类型的 packMap，UnpackMap 函数

*/

#pragma once

#include <string>
#include <vector>
#include "dbTable.h"
#include "dbStructDef.h"

namespace db
{
	struct Account : public BaseTable
	{
		Account() : BaseTable(1) {}
		std::string name;
		std::string psw;
		std::vector<ActorBrief> vecActor;
	};
	struct Player : public BaseTable
	{
		Player() : BaseTable(2) {}
		uint64_t uin;
		std::string name;
		std::string myblob;
	};

//先定义宏参数信息，以后再具体实现
//域的顺序 和 遗漏，都会初始化的时候检查出来
#define DB_ALL_TABLE_INFO \
	DB_CLASS_NAME(Account)\
	DB_MAIN_KEY(name)\
	DB_FIELD(psw)\
	DB_FIELD(vecActor)\
	DB_CLASS_END\
\
	DB_CLASS_NAME(Player)\
	DB_MAIN_KEY(uin)\
	DB_FIELD(name)\
	DB_FIELD(myblob)\
	DB_CLASS_END\
\


//其中具体实现例子，这里为空实现
#define DB_CLASS_NAME(className)	 
#define DB_MAIN_KEY(fieldName)	 
#define DB_INDEX_KEY(fieldName)	
#define DB_FIELD(fieldName)	 
#define DB_CLASS_END		

	DB_ALL_TABLE_INFO

#undef  DB_CLASS_NAME
#undef  DB_MAIN_KEY
#undef  DB_INDEX_KEY
#undef  DB_FIELD
#undef  DB_CLASS_END



}