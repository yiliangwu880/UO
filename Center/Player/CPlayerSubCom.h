#pragma once

class CPlayer;
class CPlayerSubCom
{
public:
	CPlayer &m_owner;
public:
	CPlayerSubCom(CPlayer &owner);
};

