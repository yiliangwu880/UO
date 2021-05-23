#pragma once

#include <vector>
#include <map>
#include <functional>
#include "com.h"

using namespace std;
struct ActionEffect
{
	//actions[0],actions[1]参数必须为 ：
	//ActionFun action;
	//ActionChgFun chgFun; 
	//或者
	//ActionActorFun action;
	//ActionActorChgFun chgFun;
	vector<any> actions;

	//其他配置
	vector<any> anys;
};

//战斗主动释放的技能效果
struct BattleActSkillCfg 
{
	int id;
	vector<ActionEffect> vecAe;
};

vector < BattleActSkillCfg > allBattleActSkillCfg= {
{1, 
	{//ActionEffect
		{Action::EarthQuake,ActionChg::EarthQuakeLv}, { 3000,"提示" }}
		/*ActionEffect2*/,
		/*ActionEffect3*/
	}
},//也可以多个行动效果 {1, {ActionSkill::EarthQuake,.。}，  {ActionSkill::EarthQuake2, 。。}}

{ 2, {{Action::HaSiKaDebuff}, { 3000,"提示" }}} },
{ 3, {{Action::CreateState<State1>,, ActionChg::Lv0} { 3000,"提示" }}} }, //action通用，只创建State,吧配置传过去
{ 5, {{Action::AddBuf}, { 1/*buffid*/,1/*buffLv*/,}, ActionChg::Lv1}} },//通用加不用buffiD
{ 6, {{Action::GuFaBig, ActionChg::Lv0}, {1}}},//古法大，吸血，双方加buff
{ 7, {{Action::CreateMonster, ActionChg::Lv0}, {1}}},//召唤物
};

//施加buff时，增加的State
struct BuffCfg
{
	int id;
	bool isGood; //false indicate debuff
	vector<ActionEffect> vecAe;
};

vector < BuffCfg > allBuffCfg = {
	//多个效果例子
//{1, {{Action::CreateState<State1>, { 3000,"提示" }, ActionChg::Lv0}}, {Action::CreateState<State2>, { 3000,"提示" }, ActionChg::Lv0}}}}
{BuffId::TriggerXixue, true,{{ Action::CreateState<StateTriggerXixue>, { 3000,"提示" }, ActionChg::Lv0 }}},//古法大，吸血，自己buf
{BuffId::TargetXixue, false, {{ Action::CreateState<StateTargetXixue>, { 3000,"提示" }, ActionChg::Lv0 }}},//古法大，吸血，目标buf
};

//被动技能，加载或者升级技能时，更新State
struct PassiveSkillCfg
{
	int id;
	vector<ActionEffect> vecAe;
};

vector < PassiveSkillCfg > allPassiveSkillCfg = {
{1, {{ Action::UpdatePassive<StateTriggerXixue>, { 3000,"提示" }, PassiveChg::Lv0 }}},
{2, {{ Action::UpdatePassive<StateTargetXixue>, { 3000,"提示" }, PassiveChg::Lv0 }}},
};


//vector<any> anys = {3000,"提示" };
////用法参考
////any Int = 69,		//初始化的时候，把 typeinfo相关内容动态赋值，等_Cast的时候会检查是否合法。
////	Double = 8.8,	//浮点型
////	CStr = "hello",			//字符数组
////	Str = string("center!");		//string类
////vector<any> anys = { Int,Double,CStr,Str };	//可直接放入序列容器中
//////set < any > any_set{ Int,Double,CStr,Str };	//Error:不能直接放入关联容器内,需要提供operator<，但 any 很难比较
////cout << *Int._Cast<int>() << endl;	//T* _Cast<typenampe T>():返回any对象的"值"，但需要一个模板参数确定对象值的类型
////cout << *Double._Cast<double>() << endl;
////cout << *CStr._Cast<char const *>() << endl;