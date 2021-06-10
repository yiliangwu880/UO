/*
	act动作，使用一些互动的触发。 

	为什么需要 ChgActParaFun?:
	方法1：一种Act效果，用 多种 ActFun 实现不同参数调整方案。
	方法2：一种Act效果，用 一种ActFun 和 多种可复用的 ChgActParaFun 组合来实现不同参数调整方案。
	方法2得益，只需要定义少量的 ActFun 类型.
*/
#pragma once
#include <any>

class Actor;
//联合目标，多选一
struct UnionTarget
{
	Actor *target = nullptr;
	Point3D pos;
};


using ActFun = void (*)(const vector<any> &, Actor &trigger, const UnionTarget &target);
//调整 ActFun 的输入参数.
//@ActLv 通常表示技能等级，buff等级等
using ChgActParaFun = vector<any>(*)(const vector<any> &, uint32 ActLv, Actor  &actor, const UnionTarget &target);
using CheckActFun = bool (*)(const vector<any> &);

namespace ChgAct
{
	vector<any> EarthQuakeLv(const vector<any> &cfg, uint32 ActLv, Actor &trigger, const UnionTarget &target);
	vector<any> Lv0(const vector<any> &cfg, uint32 ActLv, Actor &trigger, const UnionTarget &target);

}
namespace Act
{
	void EarthQuake(const vector<any> &cfg, Actor &trigger, const UnionTarget &target);
	//包含多个 act
	void More(const vector<any> &cfg, Actor &trigger, const UnionTarget &target);
	inline void Act1(const vector<any> &cfg, Actor &trigger, const UnionTarget &target) {};
	inline void Act2(const vector<any> &cfg, Actor &trigger, const UnionTarget &target) {};
}

//单例， 记录每个 ActFun 函数的配置参数合法函数。启服时检测。
REG_MAP_NAME_DECLARE(Act2Check, ActFun, CheckActFun);