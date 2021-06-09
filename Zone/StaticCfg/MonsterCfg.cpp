#include "GCfg.h"

MonsterCfgMgr::MonsterCfgMgr()
	:m_MonsterCfg({
	{
		1,
		{ 1,
			"The Abyssal Infernal",
			0,0,0,0,
			//damType
			{
				{ResistanceType::Physical,1,2},
			},
			//res
			{
				{ResistanceType::Physical,1,2},
			},
			//skill
			{
				{SkillName::Healing,1000,1200},
				{SkillName::Fishing,1000,1200},
			},
		}
	},

			{1, { 1 }}
		})

{}

