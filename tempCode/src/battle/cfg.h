#pragma once

#include <vector>
#include <map>
#include <functional>
#include "com.h"

using namespace std;
struct ActEffect
{
	//actions[0],actions[1]��������Ϊ ��
	//ActFun action;
	//ActChgFun chgFun; 
	//����
	//ActActorFun action;
	//ActActorChgFun chgFun;
	vector<any> actions;

	//��������
	vector<any> anys;
};

//ս�������ͷŵļ���Ч��
struct BattleActSkillCfg 
{
	int id;
	vector<ActEffect> vecAe;
};

vector < BattleActSkillCfg > allBattleActSkillCfg= {
{1, 
	{//ActEffect
		{Act::EarthQuake,ActChg::EarthQuakeLv}, { 3000,"��ʾ" }}
		/*ActEffect2*/,
		/*ActEffect3*/
	}
},//Ҳ���Զ���ж�Ч�� {1, {ActSkill::EarthQuake,.��}��  {ActSkill::EarthQuake2, ����}}

{ 2, {{Act::HaSiKaDebuff}, { 3000,"��ʾ" }}} },
{ 3, {{Act::CreateState<State1>,, ActChg::Lv0} { 3000,"��ʾ" }}} }, //actionͨ�ã�ֻ����State,�����ô���ȥ
{ 5, {{Act::AddBuf}, { 1/*buffid*/,1/*buffLv*/,}, ActChg::Lv1}} },//ͨ�üӲ���buffiD
{ 6, {{Act::GuFaBig, ActChg::Lv0}, {1}}},//�ŷ�����Ѫ��˫����buff
{ 7, {{Act::CreateMonster, ActChg::Lv0}, {1}}},//�ٻ���
};

//ʩ��buffʱ�����ӵ�State
struct BuffCfg
{
	int id;
	bool isGood; //false indicate debuff
	vector<ActEffect> vecAe;
};

vector < BuffCfg > allBuffCfg = {
	//���Ч������
//{1, {{Act::CreateState<State1>, { 3000,"��ʾ" }, ActChg::Lv0}}, {Act::CreateState<State2>, { 3000,"��ʾ" }, ActChg::Lv0}}}}
{BuffId::TriggerXixue, true,{{ Act::CreateState<StateTriggerXixue>, { 3000,"��ʾ" }, ActChg::Lv0 }}},//�ŷ�����Ѫ���Լ�buf
{BuffId::TargetXixue, false, {{ Act::CreateState<StateTargetXixue>, { 3000,"��ʾ" }, ActChg::Lv0 }}},//�ŷ�����Ѫ��Ŀ��buf
};

//�������ܣ����ػ�����������ʱ������State
struct PassiveSkillCfg
{
	int id;
	vector<ActEffect> vecAe;
};

vector < PassiveSkillCfg > allPassiveSkillCfg = {
{1, {{ Act::UpdatePassive<StateTriggerXixue>, { 3000,"��ʾ" }, PassiveChg::Lv0 }}},
{2, {{ Act::UpdatePassive<StateTargetXixue>, { 3000,"��ʾ" }, PassiveChg::Lv0 }}},
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