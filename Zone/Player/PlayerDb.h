#pragma once
#include "BaseData.h"



class PlayerDb : public PlayerSubCom
{
	lc::Timer m_tm;
	DbPlayer m_data;

public:
	PlayerDb(Player &owner)
		:PlayerSubCom(owner)
	{
	}
	void OnLoad(const DbPlayer &data);
	void OnSave();
	const DbPlayer &GetData() { return m_data; }
	//for Player subcom class call
	DbPlayer &GetDataWritable() { return m_data; }
};
