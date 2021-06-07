#pragma once
#include "Scene/Aoi/Aoi.h"

class Scene : public Noncopyable
{
	union
	{
		uint32 id;
		struct
		{
			uint16 fbId; //副本id, 0 start
			uint16 mapId;//
		};
	};

public:
	Aoi::Scene m_aoi;

public:
	void Init();

};