
//this file is build by CppCfg Tool
//don't modify by manual
#pragma once
#include <string>
#include <array>
#include "SimpleCfg.h"

struct comCfg
{
	struct S_access
	{
		std::string ex_ip;
		uint16_t ex_port;
		std::string inner_ip;
		uint16_t inner_port;
	};
	struct S_center
	{
		std::string ip;
		uint16_t port;
	};
	struct S_zone
	{
		std::vector<uint16_t> allSvrId;
	};


	////////////////////////define member list////////////////////////
	S_access access;
	S_center center;
	S_zone zone;

	////////////////////////method list////////////////////////
	//load or reload cfg file .
	bool LoadFile(const char *file_name=nullptr)
	{
		//default load original cfg file name
		if (nullptr == file_name)
		{
			file_name = "../comCfg.txt";
		}
		SimpleCfg js;
		if (!js.ParseFile(file_name))
		{
			return false;
		}
		return Assign(js);
	}

private:
	template<typename Array>
	inline size_t ArrayLen(const Array &array)
	{
		return sizeof(array) / sizeof(array[0]);
	}
	//initialize or reload cfg content.
	bool Assign(const nlohmann::json &js)
	{
		try
		{

			access.ex_ip = js["access"]["ex_ip"];
			access.ex_port = js["access"]["ex_port"];
			access.inner_ip = js["access"]["inner_ip"];
			access.inner_port = js["access"]["inner_port"];
			center.ip = js["center"]["ip"];
			center.port = js["center"]["port"];
			for (size_t i = 0; i < js["zone"]["allSvrId"].size(); ++i)
			{
				zone.allSvrId.push_back(js["zone"]["allSvrId"][i]);
			}


			return true;
		}
		catch (...)
		{
			//if fail, pls check if your cfg fomart is legal.
			return false;
		}
	}
};
