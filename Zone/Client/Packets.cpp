#include "Packets.h"
#include "Player.h"

//c#适配
#define base Packet
#define uint uint32
#define byte uint8_t


LoginConfirm::LoginConfirm(Actor &actor)
	: base(0x1B, 37)
{
	ActorBase &m = actor.m_ActorBase;
	const DbActorBase &d = m.GetData();
	m_Stream.Write(m.GetId());
	m_Stream.Write(0);
	m_Stream.Write((short)d.body);
	m_Stream.Write((short)d.x);
	m_Stream.Write((short)d.y);
	m_Stream.Write((short)d.z);
	m_Stream.Write((byte)d.dir);
	m_Stream.Write((byte)0);
	m_Stream.Write(-1);

	//Map map = m.Map;

	//if (map == null || map == Map.Internal)
	//{
	//	map = m.LogoutMap;
	//}

	m_Stream.Write((short)0);
	m_Stream.Write((short)0);
	m_Stream.Write((short)(6144));//m_Stream.Write((short)(map == null ? 6144 : map.Width));
	m_Stream.Write((short)(4096));//m_Stream.Write((short)(map == null ? 4096 : map.Height));

	m_Stream.Fill();
}
