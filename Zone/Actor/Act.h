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


using ActFun = void (*)(const vector<any> &, Actor &trigger, UnionTarget &target);
//调整 ActFun 的输入参数.
//@ActLv 通常表示技能等级，buff等级等
using ChgActParaFun = vector<any> (*)(const vector<any> &, uint32 ActLv, Actor  &actor, UnionTarget &target);

namespace ChgAct
{
	vector<any> EarthQuakeLv(const vector<any> &cfg, uint32 ActLv, Actor &trigger, UnionTarget &target);
	vector<any> Lv0(const vector<any> &cfg, uint32 ActLv, Actor &trigger, UnionTarget &target);

}
namespace Act
{
	void EarthQuake(const vector<any> &cfg, Actor &trigger, UnionTarget &target);
	inline void Act1(const vector<any> &cfg, Actor &trigger, UnionTarget &target) {};
	inline void Act2(const vector<any> &cfg, Actor &trigger, UnionTarget &target) {};
}
