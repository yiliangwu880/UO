#pragma once

#include <vector>
#include <map>
#include <functional>
#include "com.h"

using namespace std;
struct ActionEffect
{
	//actions[0],actions[1]��������Ϊ ��
	//ActionFun action;
	//ActionChgFun chgFun; 
	//����
	//ActionActorFun action;
	//ActionActorChgFun chgFun;
	vector<any> actions;

	//��������
	vector<any> anys;
};

//ս�������ͷŵļ���Ч��
struct BattleActSkillCfg 
{
	int id;
	vector<ActionEffect> vecAe;
};

vector < BattleActSkillCfg > allBattleActSkillCfg= {
{1, 
	{//ActionEffect
		{Action::EarthQuake,ActionChg::EarthQuakeLv}, { 3000,"��ʾ" }}
		/*ActionEffect2*/,
		/*ActionEffect3*/
	}
},//Ҳ���Զ���ж�Ч�� {1, {ActionSkill::EarthQuake,.��}��  {ActionSkill::EarthQuake2, ����}}

{ 2, {{Action::HaSiKaDebuff}, { 3000,"��ʾ" }}} },
{ 3, {{Action::CreateState<State1>,, ActionChg::Lv0} { 3000,"��ʾ" }}} }, //actionͨ�ã�ֻ����State,�����ô���ȥ
{ 5, {{Action::AddBuf}, { 1/*buffid*/,1/*buffLv*/,}, ActionChg::Lv1}} },//ͨ�üӲ���buffiD
{ 6, {{Action::GuFaBig, ActionChg::Lv0}, {1}}},//�ŷ�����Ѫ��˫����buff
{ 7, {{Action::CreateMonster, ActionChg::Lv0}, {1}}},//�ٻ���
};

//ʩ��buffʱ�����ӵ�State
struct BuffCfg
{
	int id;
	bool isGood; //false indicate debuff
	vector<ActionEffect> vecAe;
};

vector < BuffCfg > allBuffCfg = {
	//���Ч������
//{1, {{Action::CreateState<State1>, { 3000,"��ʾ" }, ActionChg::Lv0}}, {Action::CreateState<State2>, { 3000,"��ʾ" }, ActionChg::Lv0}}}}
{BuffId::TriggerXixue, true,{{ Action::CreateState<StateTriggerXixue>, { 3000,"��ʾ" }, ActionChg::Lv0 }}},//�ŷ�����Ѫ���Լ�buf
{BuffId::TargetXixue, false, {{ Action::CreateState<StateTargetXixue>, { 3000,"��ʾ" }, ActionChg::Lv0 }}},//�ŷ�����Ѫ��Ŀ��buf
};

//�������ܣ����ػ�����������ʱ������State
struct PassiveSkillCfg
{
	int id;
	vector<ActionEffect> vecAe;
};

vector < PassiveSkillCfg > allPassiveSkillCfg = {
{1, {{ Action::UpdatePassive<StateTriggerXixue>, { 3000,"��ʾ" }, PassiveChg::Lv0 }}},
{2, {{ Action::UpdatePassive<StateTargetXixue>, { 3000,"��ʾ" }, PassiveChg::Lv0 }}},
};


//vector<any> anys = {3000,"��ʾ" };
////�÷��ο�
////any Int = 69,		//��ʼ����ʱ�򣬰� typeinfo������ݶ�̬��ֵ����_Cast��ʱ������Ƿ�Ϸ���
////	Double = 8.8,	//������
////	CStr = "hello",			//�ַ�����
////	Str = string("center!");		//string��
////vector<any> anys = { Int,Double,CStr,Str };	//��ֱ�ӷ�������������
//////set < any > any_set{ Int,Double,CStr,Str };	//Error:����ֱ�ӷ������������,��Ҫ�ṩoperator<���� any ���ѱȽ�
////cout << *Int._Cast<int>() << endl;	//T* _Cast<typenampe T>():����any�����"ֵ"������Ҫһ��ģ�����ȷ������ֵ������
////cout << *Double._Cast<double>() << endl;
////cout << *CStr._Cast<char const *>() << endl;