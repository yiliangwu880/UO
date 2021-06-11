#pragma once
#include "Scene/Aoi/Aoi.h"

union SceneId
{
	uint32 id=0;
	struct
	{
		uint16 mapId;//
		uint16 fbId; //副本id, 0 表示世界地图，不会销毁
	};
	SceneId() {}
	SceneId(uint16 mapId, uint16 fbId)
	{
		this->mapId = mapId;
		this->fbId = fbId;
	}
};
class Scene : public Noncopyable
{
public:
	SceneId m_SceneId;

private:

public:
	Aoi::Scene m_aoi;

public:
	Scene(SceneId sceneId);
	void Init();
	void Init(uint16 mapId);
	uint32 GetId() const { return m_SceneId.id; }
	operator uint32() const { return m_SceneId.id; }

};