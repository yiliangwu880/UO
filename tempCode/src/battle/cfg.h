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
	ActionChgFun chgFun; //����anys���� ��������ݼ��ܵȼ����ͷ��ߣ�Ŀ��״�壬���� anys����ֵ��
};

struct SkillCfg 
{
	int id;
	vector<ActionEffect> vecAe;
};

vector < SkillCfg > allSkillCfg= {
	{1, 
		{{Action::EarthQuake, { 3000,"��ʾ" }, ActionChg::EarthQuakeLv}, /*ActionEffect2*/, /*ActionEffect3*/}
	},//Ҳ���Զ���ж�Ч�� {1, {ActionSkill::EarthQuake,.��}��  {ActionSkill::EarthQuake2, ����}}

	{2, {{Action::HaSiKaDebuff, { 3000,"��ʾ" }}}},
	{3, {{Action::CreateState<State1>, { 3000,"��ʾ" }, ActionChg::Lv0}}}, //actionͨ�ã�ֻ����State,�����ô���ȥ
	{4, {{Action::AddBuf, { 1/*buffid*/,1/*buffLv*/,}, ActionChg::Lv1}}},//ͨ�üӲ���buffiD
	{4, {{Action::GuFaBig, {1}, ActionChg::Lv0}},//�ŷ�����Ѫ��˫����buff
};

struct BuffCfg
{
	int id;
	vector<ActionEffect> vecAe;
};

vector < BuffCfg > allBuffCfg = {
	//���Ч������
//{1, {{Action::CreateState<State1>, { 3000,"��ʾ" }, ActionChg::Lv0}}, {Action::CreateState<State2>, { 3000,"��ʾ" }, ActionChg::Lv0}}}}
{BuffId::TriggerXixue, {{ Action::CreateState<StateTriggerXixue>, { 3000,"��ʾ" }, ActionChg::Lv0 }}},//�ŷ�����Ѫ���Լ�buf
{BuffId::TargetXixue, {{ Action::CreateState<StateTargetXixue>, { 3000,"��ʾ" }, ActionChg::Lv0 }}},//�ŷ�����Ѫ��Ŀ��buf


//vector<any> anys = {3000,"��ʾ" };
////�÷��ο�
////any Int = 69,		//��ʼ����ʱ�򣬰� typeinfo������ݶ�̬��ֵ����_Cast��ʱ������Ƿ�Ϸ���
////	Double = 8.8,	//������
////	CStr = "hello",			//�ַ�����
////	Str = string("world!");		//string��
////vector<any> anys = { Int,Double,CStr,Str };	//��ֱ�ӷ�������������
//////set < any > any_set{ Int,Double,CStr,Str };	//Error:����ֱ�ӷ������������,��Ҫ�ṩoperator<���� any ���ѱȽ�
////cout << *Int._Cast<int>() << endl;	//T* _Cast<typenampe T>():����any�����"ֵ"������Ҫһ��ģ�����ȷ������ֵ������
////cout << *Double._Cast<double>() << endl;
////cout << *CStr._Cast<char const *>() << endl;