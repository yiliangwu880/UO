#include "GCfg.h"

ActCfgMgr::ActCfgMgr()
	:m_ActCfg({
			{1, { 1, Act::Act1, ChgAct::Lv0 }},
			//{2, { 2, Act::Act1, ChgAct::Lv0, /*技能伤害系数*/{100, 1, "abc"} }},
			//{1, { 1 }},
		})
{}

