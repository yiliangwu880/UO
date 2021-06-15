/*
来源：https://github.com/yiliangwu880/AOI.git
  9格子算法的 AOI(area of interest)。 
  管理 场景 实体 视野可见
使用方法：
   ) 复制 src/Aoi目录的代码到你的项目
   ）一切扩展接口都在Entity的公共函数 和虚函数中
   ）需要修改GridIdxMgr.h的最大地图长宽，grid长宽来匹配你的项目。

特点：已经保证不引用野对象。
	保证方法：析构函数互相解引用，
			entity gridIdx变化保证调用 Scene::UpdateEntity
			ForEachObservers 遍历的时候，freeze scene ，不让entity gridIdx变化，离开，进入
	不提供阻挡，全场景实体遍历功能，这些不是AOI的任务。

术语：
	单位 point : 场景最小长度单位，也代表entity移动最小距离。地图坐标(x,y)得单位就是point
	单位 grid  : (gridIdx)场景视野划分得grid索引

使用例子：
	class ObserverEntity : public Aoi::Entity
	class Player
	{
		ObserverEntity observer;
		...
	};
	class Scene
	{
		Aoi::Scene aoiScene;
		...
	};
*/
#pragma once
#include <set>

class Actor;
namespace Aoi
{
	class Scene;
	class Entity;
	typedef std::vector<uint16_t> VecGridIdx;

	class Entity
	{
		friend class Scene;
		friend class AoiTest;

		Scene * m_scene = nullptr;
		std::set<Entity *> m_observers; //看见我的entity 集合
		uint16_t m_gridIdx = 0;			//当前所在格子索引
		bool m_isFreeze = false;		//true 表示禁止m_observers变化。 防止野entity或者遍历过程修改容器
		EntityType m_EntityType = EntityType::None;
	public:
		Entity(EntityType type);
		~Entity();
		bool Enter(Scene &scene, uint16_t x, uint16_t y);
		bool Leave();
		void UpdatePos(uint16_t x, uint16_t y); //更新 x,y坐标。 单位为 point
		void ForEachObservers(std::function<void(Entity&)> f);//遍历 看见我的entity集合

	private:
		virtual void OnAddObserver(Entity &other) = 0; //other 看见我
		virtual void OnDelObserver(Entity &other) = 0; //other 看不见我
		virtual void OnActivate() {}; //被玩家激活。 （有任意玩家在附近）
		virtual void OnDeactivate() {};

	private:
		void SetScene(Scene *scene) { m_scene = scene; }
		void AddObserver(Entity &other);//entity看见我
		void DelObserver(Entity &other);//entity看不见我
		uint16_t GridIdx() const { return m_gridIdx; }
		Scene *GetScene() const { return m_scene; }
	};

	using VecEntity = std::vector<Entity *>;
	using Entitys = std::array<std::vector<Entity *>, (size_t)EntityType::Max>;
	struct Grid
	{
		bool isActivate = false;
		Entitys entitys;
	};

	class Scene
	{
		friend class Entity;
		friend class AoiTest;
	

		//map 类型，不用设置地图大小，自动调整需要的内存。 如果数组类型，需要设置地图大小，效率更高
		std::map<uint16_t, Grid> m_idx2grid;//gridIdx 2 entity. 表示一个grid的所有entity

		bool m_isFreeze = false; //true 表示禁止entity gridIdx变化。 防止野entity或者遍历过程修改容器

	public:
		~Scene(); 

	private:
		size_t GetEntityNum(); //for test use
		bool EntityEnter(Entity &entity);
		bool EntityLeave(Entity &entity);
		bool UpdateEntity(Entity &entity, uint16_t oldGridIdx, uint16_t newGridIdx); //entity gridIdx 发生变化
		
		bool Freeze() const { return m_isFreeze; }
		void Freeze(bool val) { m_isFreeze = val; }

		void AddObserver(Entity &entity, const VecGridIdx &vecGridIdx);
		void DelObserver(Entity &entity, const VecGridIdx &vecGridIdx); //entity 和 vecGridIdx 格子所有other entity 互相消失
		bool FindAnyPlayer(const Aoi::VecGridIdx &vecGridIdx);//return true indicate have any Player
	};

	//测试项目用
	class AoiTest
	{
	public:
		static Scene *GetEntityScene(Entity &entity)
		{
			return entity.m_scene;
		}
		static size_t GetEntityNum(Scene &scene) 
		{
			return scene.GetEntityNum();
		}
	};
}