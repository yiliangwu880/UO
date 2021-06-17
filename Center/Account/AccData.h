#include "AccountSubCom.h"
#include "dbTableDef.h"

//核心组件，先随便命名
class AccData : public AccountSubCom
{

	DbAccount m_data;

public:
	static void OnQuery(bool ret, const DbAccount &data, any para);
	static void OnInsertPlayer(bool ret, const DbPlayer &data, any para);
	static void OnQueryPlayer(bool ret, const DbPlayer &data, any para);
private:

public:
	AccData(Account &owner, CStr &name);

	void LoadDb(const DbAccount &data);
	CStr &Name() const;
	CStr &Psw() const;
	void CreateAccount(CStr &psw);
	const std::vector<ActorBrief> &GetActorList();
	void CreatePlayer(const DbPlayer &player);
	void SelectActor(uint32 idx);

private:
	void LoginPlayerByDb(const DbPlayer &data, bool isCreate);

};