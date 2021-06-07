#pragma once



struct MonsterCfg
{
	struct ResValue
	{
		ResistanceType type;
		uint32 min, max;
	};
	struct SkillValue
	{
		SkillName type;
		uint32 min, max;//[0~1200]
	};

	uint16 id;
	string name;
	uint32 str;
	uint32 dex;
	uint32 intl;
	uint32 dam;


	vector<ResValue> damType;
	vector<ResValue> res;
	vector<SkillValue> skill;

};

struct MonsterCfgMgr : public Singleton<MonsterCfgMgr>
{
	unordered_map<uint16, MonsterCfg> m_MonsterCfg;
	MonsterCfgMgr();
};