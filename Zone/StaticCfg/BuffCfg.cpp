#include "GCfg.h"


BuffCfgMgr::BuffCfgMgr()
	:m_BuffCfg({
			{2, { 10, /*BuffState*/{StateId::State1,{100,"ab"}}}},
			{3, { 10, /*BuffState*/{StateId::More,{BuffState{StateId::State1,{100,"ab"}}, BuffState{StateId::StateHSKDeBuffCombine,{100,"ab"}} }}}},
		
		})
{}

void BuffCfgMgr::CheckCfg(bool &ret)
{

}

