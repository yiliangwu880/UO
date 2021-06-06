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

