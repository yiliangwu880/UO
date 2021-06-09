#pragma once
#include "ActorSubCom.h"



class ActorBase : public ActorSubCom<ActorBase>
{
	uint16 m_str = 0;
	uint16 m_dex = 0;
	uint16 m_intl = 0;
	uint16 m_x = 0, m_y = 0, m_z = 0;
	bool m_female = false;
	uint8_t m_race = 0;
	Point3D m_pos; 
	uint32 m_hp = 0;

public:
	ActorBase(Actor &actor);
	void InitMonster(const MonsterInit &data);
	const Point3D &GetPos() { return m_pos; };
	void SetPos(const Point3D &pos) { m_pos = pos;};

private:
	void OnLoad(DbPlayer &data);
	void OnSave(DbPlayer &data);
};