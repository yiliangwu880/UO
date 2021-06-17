
#include "AccountMgr.h"

using namespace proto;
using namespace acc;

Account::Account(const string &name)
	:m_Verify(*this)
	, m_AccData(*this, name)
	, m_FirstSn(*this)
	, m_AccSn(*this)
{
}


const std::string & Account::Name() const
{
	return m_AccData.Name();
}

void Account::Send(Packet &packet)
{
	m_AccSn.Send(packet);
}


