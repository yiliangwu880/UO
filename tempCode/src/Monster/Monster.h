/*
��ͬ��������ϱ�����̳в��̫�ർ�µĸ����� ��
*/
#pragma once

#include <vector>
#include <map>
#include <functional>
#include "com.h"
#include "cfg.h"

class Monster
{
public:
	//int show; ���
	//Drop dropCfg;
	Actor m_actor;//ս�������������
public:

	//ĳ����������λ�ô���������Ӱ������������
	void  PosAction()
	{
		int x, y;
		get all SceneEntity;
		for (SceneEntity &v: all)
		{
			Actor actor = v.getActor;
			do(m_actor, actor);
		}
	}

private:
};
