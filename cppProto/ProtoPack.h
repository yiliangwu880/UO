#pragma once
#include "log_def.h"

namespace proto
{
	using PointChar = char*;
	using CPointChar = const char*;

	//@cur [in]打包到内存地址，[out]第一个未使用的内存地址（下个变量打包的内存地址）。
	//@len [in]cur 有效长度，[out]打包后，cur未使用字节长度
	template<class T>
	inline bool Pack(const T &t, PointChar &cur, size_t &len)
	{
		L_ERROR("pack unknow. type name = %s", typeid(T).name());
		return false;
	}
	//@cur [in]解包来源内存地址，[out]第一个未解包的内存地址（下个变量解包的内存地址）。
	//@len [in]cur有效长度，[out]解包后，cur未使用字节长度
	template<class T>
	inline bool Unpack(T &t, CPointChar &cur, size_t &len)
	{
		L_ERROR("unpack unknow. type name = %s", typeid(T).name());
		return false;
	}
	//解包消息ID用，例如 const uint16_t id = 1; 
	template<>
	inline bool Unpack<const uint16_t>(const uint16_t &v, CPointChar &cur, size_t &len)
	{
		L_COND(len >= sizeof(v), false);
		uint16_t unpackV = *(uint16_t*)cur;
		cur += sizeof(v);
		len -= sizeof(v);
		L_COND(v == unpackV, false); //解包内容和对象不符合。  消息ID不一样
		return true;
	}


#define EASY_CODE(T)\
	template<>\
	inline bool Pack<T>(const T &v, PointChar &cur, size_t &len)\
	{\
		L_COND(len >= sizeof(v), false);\
		*(T*)cur = v;\
		cur += sizeof(v);\
		len -= sizeof(v);\
		return true;\
	}\

	EASY_CODE(bool)
	EASY_CODE(int32_t)
	EASY_CODE(uint32_t)
	EASY_CODE(int64_t)
	EASY_CODE(uint64_t)
	EASY_CODE(double)
	EASY_CODE(int16_t)
	EASY_CODE(uint16_t)
	EASY_CODE(int8_t)
	EASY_CODE(uint8_t)
#undef  EASY_CODE

#define EASY_CODE(T)\
	template<>\
	inline bool Unpack<T>(T &v, CPointChar &cur, size_t &len)\
	{\
		L_COND(len >= sizeof(v), false);\
		v = *(T*)cur;\
		cur += sizeof(v);\
		len -= sizeof(v);\
		return true;\
	}\

		EASY_CODE(bool)
		EASY_CODE(int32_t)
		EASY_CODE(uint32_t)
		EASY_CODE(int64_t)
		EASY_CODE(uint64_t)
		EASY_CODE(double)
		EASY_CODE(int16_t)
		EASY_CODE(uint16_t)
		EASY_CODE(int8_t)
		EASY_CODE(uint8_t)
#undef  EASY_CODE

	template<>
	inline bool Pack<std::string>(const std::string &v, PointChar &cur, size_t &len)
	{
		uint32_t strLen = v.length();
		L_COND(Pack(strLen, cur, len), false);
		L_COND(len >= v.length(), false);
		memcpy(cur, v.c_str(), v.length());
		cur += v.length();
		len -= v.length();
		return true;
	}
	template<>
	inline bool Unpack<std::string>(std::string &v, CPointChar &cur, size_t &len)
	{
		uint32_t strLen;
		L_COND(Unpack(strLen, cur, len), false);
		L_COND(len >= strLen, false);
		v.assign(cur, strLen);
		cur += strLen;
		len -= strLen;
		return true;
	}

	template<class Vec>
	inline bool PackVector(const Vec &v, PointChar &cur, size_t &len)
	{
		uint32_t vecLen = v.size();
		L_COND(Pack(vecLen, cur, len), false);
		for (const auto &vt : v)
		{
			L_COND(Pack(vt, cur, len), false);
		}
		return true;
	}

	template<class Vec>
	inline bool UnpackVector(Vec &v, CPointChar &cur, size_t &len)
	{
		uint32_t vecLen;
		L_COND(Unpack(vecLen, cur, len), false);
		v.resize(vecLen);
		for (uint32_t i = 0; i < vecLen; i++)
		{
			L_COND(Unpack(v[i], cur, len), false);
		}
		return true;
	}

	template<class Map>
	inline bool PackMap(const Map &v, PointChar &cur, size_t &len)
	{
		uint32_t cntLen = v.size();
		L_COND(Pack(cntLen, cur, len), false);
		for (const auto &vt : v)
		{
			L_COND(Pack(vt.first, cur, len), false);
			L_COND(Pack(vt.second, cur, len), false);
		}
		return true;
	}

	template<class Map>
	inline bool UnpackMap(Map &v, CPointChar &cur, size_t &len)
	{
		uint32_t cntLen;
		L_COND(Unpack(cntLen, cur, len), false);
		for (uint32_t i = 0; i < cntLen; i++)
		{
			typename Map::key_type k;
			typename Map::mapped_type value;
			L_COND(Unpack(k, cur, len), false);
			L_COND(Unpack(value, cur, len), false);
			v.insert(std::make_pair(k, value));
		}
		return true;
	}
	///////////////////////vector////////////////////////////
	//定义所有vector<xx>  
	//觉得理论上不应该每种vector<xx>都定义，应该有方法会静态识别vector类型，并调用PackVector函数，不需要这里得定义。
	//但还没研究出方法，先用宏吧所有情况实现一遍
#define EASY_CODE(T)\
	template<>\
	inline bool Pack<std::vector<T>>(const std::vector<T> &v, PointChar &cur, size_t &len)\
	{\
		return PackVector(v, cur, len);\
	}\
	template<>\
	inline bool Unpack<std::vector<T>>(std::vector<T> &v, CPointChar &cur, size_t &len)\
	{\
		return UnpackVector(v, cur, len);\
	}\

	EASY_CODE(int32_t)
		EASY_CODE(uint32_t)
		EASY_CODE(int64_t)
		EASY_CODE(uint64_t)
		EASY_CODE(double)
		EASY_CODE(int16_t)
		EASY_CODE(uint16_t)
		EASY_CODE(int8_t)
		EASY_CODE(uint8_t)

		//任意vector<struct>
#define DB_CLASS_NAME(className) EASY_CODE(className)
#define DB_FIELD(fieldName)
#define DB_CLASS_END

		ALL_STRUCT_INFO

#undef  DB_CLASS_NAME
#undef  DB_FIELD
#undef  DB_CLASS_END

#undef  EASY_CODE

		///////////////////////unordered_map////////////////////////////
					//定义所有unordered_map<xx>
#define EASY_CODE(K,T)\
	template<>\
	inline bool Pack<std::unordered_map<K,T>>(const std::unordered_map<K,T> &v, PointChar &cur, size_t &len)\
	{\
		return PackMap(v, cur, len);\
	}\
	template<>\
	inline bool Unpack<std::unordered_map<K,T>>(std::unordered_map<K,T> &v, CPointChar &cur, size_t &len)\
	{\
		return UnpackMap(v, cur, len);\
	}\

			//实际情况少量使用，需要再扩展
		EASY_CODE(uint32_t, uint32_t)
		EASY_CODE(uint32_t, uint64_t)
		EASY_CODE(uint64_t, uint64_t)

#define DB_CLASS_NAME(className) EASY_CODE(uint64_t, className)
#define DB_FIELD(fieldName)
#define DB_CLASS_END

		ALL_STRUCT_INFO

#undef  DB_CLASS_NAME
#undef  DB_FIELD
#undef  DB_CLASS_END

#define DB_CLASS_NAME(className) EASY_CODE(uint32_t, className)
#define DB_FIELD(fieldName)
#define DB_CLASS_END

		ALL_STRUCT_INFO

#undef  DB_CLASS_NAME
#undef  DB_FIELD
#undef  DB_CLASS_END

#undef  EASY_CODE

		///////////////////////自定义结构体////////////////////////////

#define DB_CLASS_NAME(className)\
	template<>\
	inline bool Pack<className>(const className &v, PointChar &cur, size_t &len)\
	{\

#define DB_FIELD(fieldName)\
	L_COND(Pack(v.fieldName, cur, len), false);\

#define DB_CLASS_END\
		return true;\
	}\

		ALL_STRUCT_INFO

#undef  DB_CLASS_NAME
#undef  DB_FIELD
#undef  DB_CLASS_END



#define DB_CLASS_NAME(className)\
	template<>\
	inline bool Unpack<className>(className &v, CPointChar &cur, size_t &len)\
	{\

#define DB_FIELD(fieldName)\
	L_COND(Unpack(v.fieldName, cur, len), false);\

#define DB_CLASS_END\
		return true;\
	}\

		ALL_STRUCT_INFO

#undef  DB_CLASS_NAME
#undef  DB_FIELD
#undef  DB_CLASS_END



	///////////////////////分配 释放 函数////////////////////////////
		template<class T>
	inline char * CreateFun()
	{
		L_ERROR("CreateFun unknow. type name = %s", typeid(T).name());
		return nullptr;
	}

	template<class T>
	inline void FreeFun(char *p)
	{
		L_ERROR("CreateFun unknow. type name = %s", typeid(T).name());
	}
#define DB_CLASS_NAME(className)\
	template<>\
	inline char *CreateFun<className>()\
	{\
		return (char *)(new className());\
	}\

#define DB_FIELD(fieldName)
#define DB_CLASS_END

	ALL_STRUCT_INFO

#undef  DB_CLASS_NAME
#undef  DB_FIELD
#undef  DB_CLASS_END

#define DB_CLASS_NAME(className)\
	template<>\
	inline void FreeFun<className>(char *p)\
	{\
		return delete (className *)p;\
	}\

#define DB_FIELD(fieldName)
#define DB_CLASS_END

		ALL_STRUCT_INFO

#undef  DB_CLASS_NAME
#undef  DB_FIELD
#undef  DB_CLASS_END

}