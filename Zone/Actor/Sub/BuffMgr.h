#pragma once
#include "ActorSubCom.h"




class Buff
{
	Actor &m_Actor;
	lc::Timer m_tm; //cd
	BuffId m_buffId = BuffId::None;//map cfg,  map StateId m_StateId;
	uint16 m_lv = 0;
	const BuffCfg *m_cfg = nullptr;

public:
	Buff(Actor &actor);
	void Init(BuffId id, uint16 lv);
	void OnTimerOut();
	uint16 GetLv()const { return m_lv; }
	const BuffCfg *Cfg() const { return m_cfg; }
};

class BuffMgr : public ActorSubCom<BuffMgr>
{
	std::map<BuffId, shared_ptr<Buff>> m_id2buff; //优先安全，不考虑效率，不用new
public:
	BuffMgr(Actor &actor);
	bool AddBuff(BuffId id, uint16 lv, Actor &trigger, Actor &target);
	void Del(BuffId id);

private:

};