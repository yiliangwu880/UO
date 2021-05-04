#pragma once

#include <vector>
#include <map>
#include <functional>
#include "com.h"

using namespace std;
struct ActionEffect
{
	ActionFun action;
	vector<any> anys;
	ActionChgFun chgFun; //调整anys方法 ，比如根据技能等级，释放者，目标状体，调整 anys具体值。
};

struct SkillCfg 
{
	int id;
	vector<ActionEffect> vecAe;
};

vector < SkillCfg > allSkillCfg= {
	{1, 
		{{Action::EarthQuake, { 3000,"提示" }, ActionChg::EarthQuakeLv}, /*ActionEffect2*/, /*ActionEffect3*/}
	},//也可以多个行动效果 {1, {ActionSkill::EarthQuake,.。}，  {ActionSkill::EarthQuake2, 。。}}

	{2, {{Action::HaSiKaDebuff, { 3000,"提示" }}}},
	{3, {{Action::CreateState<State1>, { 3000,"提示" }, ActionChg::Lv0}}}, //action通用，只创建State,吧配置传过去
	{4, {{Action::AddBuf, { 1/*buffid*/,1/*buffLv*/,}, ActionChg::Lv1}}},//通用加不用buffiD
	{4, {{Action::GuFaBig, {1}, ActionChg::Lv0}},//古法大，吸血，双方加buff
};

struct BuffCfg
{
	int id;
	vector<ActionEffect> vecAe;
};

vector < BuffCfg > allBuffCfg = {
	//多个效果例子
//{1, {{Action::CreateState<State1>, { 3000,"提示" }, ActionChg::Lv0}}, {Action::CreateState<State2>, { 3000,"提示" }, ActionChg::Lv0}}}}
{BuffId::TriggerXixue, {{ Action::CreateState<StateTriggerXixue>, { 3000,"提示" }, ActionChg::Lv0 }}},//古法大，吸血，自己buf
{BuffId::TargetXixue, {{ Action::CreateState<StateTargetXixue>, { 3000,"提示" }, ActionChg::Lv0 }}},//古法大，吸血，目标buf


//vector<any> anys = {3000,"提示" };
////用法参考
////any Int = 69,		//初始化的时候，把 typeinfo相关内容动态赋值，等_Cast的时候会检查是否合法。
////	Double = 8.8,	//浮点型
////	CStr = "hello",			//字符数组
////	Str = string("world!");		//string类
////vector<any> anys = { Int,Double,CStr,Str };	//可直接放入序列容器中
//////set < any > any_set{ Int,Double,CStr,Str };	//Error:不能直接放入关联容器内,需要提供operator<，但 any 很难比较
////cout << *Int._Cast<int>() << endl;	//T* _Cast<typenampe T>():返回any对象的"值"，但需要一个模板参数确定对象值的类型
////cout << *Double._Cast<double>() << endl;
////cout << *CStr._Cast<char const *>() << endl;