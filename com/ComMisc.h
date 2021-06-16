/*
	杂项
*/

#pragma once

template<class Owner>
class SubCom
{
public:
	Owner &m_owner;
public:
	SubCom(Owner &owner)
		:m_owner(owner)
	{

	}
};

struct Core
{
	static const bool T2A = true;
	static const bool UOR = true;
	static const bool UOTD = true;
	static const bool LBR = true;
	static const bool AOS = true;
	static const bool SE = true;
	static const bool ML = true;
	static const bool SA = true;
	static const bool HS = true;
	static const bool TOL = true;
	static const bool EJ = true;
};