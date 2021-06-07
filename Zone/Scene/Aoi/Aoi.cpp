
#include "Aoi.h"
#include "GridIdxMgr.h"
using namespace std;
using namespace Aoi;

Aoi::Entity::Entity(EntityType type)
	:m_EntityType(type)
{
	
}

Aoi::Entity::~Entity()
{
	if (nullptr != m_scene)
	{
		L_ERROR("can't del entity when not leave scene"); //还没离开 场景，不允许删除对象。 
		//Leave();//不能调用看离开场景。 因为里面触发虚函数OnDelObserver 。 析构函数不能调用 虚函数 ，所以需要用户先离开场景
	}
}

bool Aoi::Entity::Enter(Scene &scene, uint16_t x, uint16_t y)
{
	if (x >= MAP_MAX_POS_X || y >= MAP_MAX_POS_Y)
	{
		L_ERROR("x,y is too big %d %d", x, y);
		return false;
	}
	//必须先离开，才能改位置. 保证scene能找到entity
	if (m_scene)
	{
		m_scene->EntityLeave(*this);
	}

	m_gridIdx = (MAP_SCREEN_X * (y / SCREEN_GRID_HEIGHT) + (x / SCREEN_GRID_WIDTH));
	return scene.EntityEnter(*this);
}

bool Aoi::Entity::Leave()
{
	if (!m_scene)
	{
		return false;
	}
	return m_scene->EntityLeave(*this);
}

void Aoi::Entity::AddObserver(Entity &other)
{
	L_ASSERT(!m_isFreeze);
	m_observers.insert(&other);
	OnAddObserver(other);
}

void Aoi::Entity::DelObserver(Entity &other)
{
	L_ASSERT(!m_isFreeze);
	m_observers.erase(&other);
	OnDelObserver(other);
}


void Aoi::Entity::UpdatePos(uint16_t x, uint16_t y)
{
	if (x >= MAP_MAX_POS_X || y >= MAP_MAX_POS_Y)
	{
		L_ERROR("x,y is too big %d %d", x, y);
		return;
	}
	uint16_t oldIdx = m_gridIdx;
	m_gridIdx = (MAP_SCREEN_X * (y / SCREEN_GRID_HEIGHT) + (x / SCREEN_GRID_WIDTH));

	L_ASSERT(m_gridIdx < MAP_SCREEN_MAX);
	if (oldIdx == m_gridIdx)
	{
		return;
	}
	if (m_scene)
	{
		m_scene->UpdateEntity(*this, oldIdx, m_gridIdx);
	}
}

void Aoi::Entity::ForEachObservers(std::function<void(Entity&)> f)
{
	if (!m_scene)
	{
		return;
	}
	m_scene->Freeze(true);//不让scene改变状态，因为scene 改变会又机会改变 entity 状态
	m_isFreeze = true;
	for (Entity *p : m_observers)
	{
		f(*p);//天知道里面做什么！所以冻结住才安全
	}
	m_isFreeze = false;
	m_scene->Freeze(false);
}

Aoi::Scene::~Scene()
{
	VecEntity vec;
	for (auto &vv : m_idx2grid)
	{
		const Entitys &ar = vv.second.entitys;
		for (auto &v : ar)
		{
			vec.insert(vec.end(), v.begin(), v.end());
		}
	}
	for (Entity *entity : vec)
	{
		EntityLeave(*entity);//里面调用 m_idx2Entitys 删除元素，所以需要复制到vec
	}
}

size_t Aoi::Scene::GetEntityNum()
{
	size_t num = 0;
	for (auto &v : m_idx2grid)
	{
		const Entitys &ar = v.second.entitys;
		for (const VecEntity &vec : ar)
		{
			num += vec.size();
		}
	}
	return num;
}



bool Aoi::Scene::FindAnyPlayer(const Aoi::VecGridIdx &vecGridIdx)
{
	for (const uint16_t &v : vecGridIdx)
	{
		const Grid &grid = m_idx2grid[v];
		const VecEntity &vecEntity = grid.entitys[(size_t)EntityType::Player];
		if (!vecEntity.empty())
		{
			return true;
		}
	}
	return false;
}


void Aoi::Scene::AddObserver(Entity &entity, const VecGridIdx &vecGridIdx)
{
	for (const uint16_t &v : vecGridIdx)
	{
		Grid &grid = m_idx2grid[v];
		bool isActivate = false;//true 表示玩家激活格子
		if (entity.m_EntityType == EntityType::Player && !grid.isActivate)
		{
			isActivate = true;
			grid.isActivate = true;
		}
		for (VecEntity &vecEntity : grid.entitys)
		{
			for (Entity *otherEntity : vecEntity)
			{
				L_ASSERT(otherEntity != &entity);
				otherEntity->AddObserver(entity);
				entity.AddObserver(*otherEntity);
				if (isActivate)
				{
					otherEntity->OnActivate();
				}
			}
		}
	}
}

void Aoi::Scene::DelObserver(Entity &entity, const VecGridIdx &vecGridIdx)
{
	for (const uint16_t &v : vecGridIdx)
	{
		Grid &grid = m_idx2grid[v];
		bool isDeactivate = false;//true 表示玩家导致格子不激活
		if (entity.m_EntityType == EntityType::Player && grid.isActivate && !FindAnyPlayer(vecGridIdx))
		{
			isDeactivate = true;
			grid.isActivate = false;
		}
		for (VecEntity &vecEntity : grid.entitys)
		{
			for (Entity *otherEntity : vecEntity)
			{
				L_ASSERT(otherEntity != &entity);
				otherEntity->DelObserver(entity);
				entity.DelObserver(*otherEntity);
				if (isDeactivate)
				{
					otherEntity->OnDeactivate();
				}
			}
		}
	}
}

bool Aoi::Scene::EntityEnter(Entity &entity)
{
	L_COND(!m_isFreeze, false);
	m_isFreeze = true;
	uint16_t gridIdx = entity.GridIdx();
	const VecGridIdx &ninescreen = GridIdxMgr::Ins().Get9Grid(gridIdx);
	AddObserver(entity, ninescreen);
	m_idx2grid[gridIdx].entitys[(size_t)entity.m_EntityType].push_back(&entity);
	entity.SetScene(this);
	m_isFreeze = false;
	return true;
}

bool Aoi::Scene::EntityLeave(Entity &entity)
{
	L_COND(!m_isFreeze, false);
	if (!entity.GetScene())
	{
		return false;
	}

	m_isFreeze = true;
	uint16_t gridIdx = entity.GridIdx();

	VecEntity &vecEntity = m_idx2grid[gridIdx].entitys[(size_t)entity.m_EntityType];
	SimpleRemoveFromVec(vecEntity, &entity);
	entity.SetScene(nullptr);

	const VecGridIdx &ninescreen = GridIdxMgr::Ins().Get9Grid(gridIdx);
	DelObserver(entity, ninescreen);
	L_ASSERT(entity.m_observers.empty());
	m_isFreeze = false;
	return true;
}

bool Aoi::Scene::UpdateEntity(Entity &entity, uint16_t oldGridIdx, uint16_t newGridIdx)
{
	L_ASSERT(oldGridIdx != newGridIdx);
	L_COND(!m_isFreeze, false);
	L_COND(entity.GetScene(), false);
	m_isFreeze = true;
	if (GridIdxMgr::Ins().checkTwoPosIInNine(oldGridIdx, newGridIdx))
	{
		uint8_t dir = GridIdxMgr::Ins().getScreenDirect(oldGridIdx, newGridIdx);
		{ 
			VecEntity &vecEntity = m_idx2grid[oldGridIdx].entitys[(size_t)entity.m_EntityType];
			SimpleRemoveFromVec(vecEntity, &entity);
			const VecGridIdx &vecGridIdx = GridIdxMgr::Ins().getReverseDirectScreen(oldGridIdx, dir);
			DelObserver(entity, vecGridIdx);
		}
		{
			const VecGridIdx &vecGridIdx = GridIdxMgr::Ins().getDirectScreen(newGridIdx, dir);
			AddObserver(entity, vecGridIdx);
			m_idx2grid[newGridIdx].entitys[(size_t)entity.m_EntityType].push_back(&entity);
		}
	}
	else
	{
		{
			SimpleRemoveFromVec(m_idx2grid[oldGridIdx].entitys[(size_t)entity.m_EntityType], &entity);
			const VecGridIdx &vecGridIdx = GridIdxMgr::Ins().Get9Grid(oldGridIdx);
			DelObserver(entity, vecGridIdx);
		}
		{
			const VecGridIdx &vecGridIdx = GridIdxMgr::Ins().Get9Grid(newGridIdx);
			AddObserver(entity, vecGridIdx);
			m_idx2grid[newGridIdx].entitys[(size_t)entity.m_EntityType].push_back(&entity);
		}
	}

	m_isFreeze = false;
	return true;
}

