#pragma once

#include <vector>
#include <map>
#include <functional>
#include <memory>

public enum ActionType
{
	Wander,
	Combat,
	Guard,
	Flee,
	Backoff,
	Interact
}

class BaseSpeedAi
{

};
class BaseActionAi
{

};
class BaseSkillAi
{

};

//�����ϳ�����AI��
//ÿ�������״̬��ģʽ
//���������ϵ�״̬�ϲ�����״̬�������� ��1ս��״̬�����������ܡ����� 2����״̬���ͷţ��ȴ�������  ��Ҫ�ϲ�
class Ai
{
	Actor &m_actor;
	BaseSkillAi m_SkillAi;
	BaseActionAi m_ActionAi;
	BaseSpeedAi m_SpeedAi;
public:

	//��������
	void OnTimer()
	{
		case state, do Action;
		Think();
	}
	//�ⲿ����
	void OnTalk()
	{
		case state, do speech something;
	}
};