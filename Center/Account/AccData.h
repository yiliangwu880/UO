#include "AccountSubCom.h"
#include "dbTableDef.h"

//核心组件，先随便命名
class AccData : public AccountSubCom
{

	DbAccount m_data;
public:
	AccData(Account &owner, CStr &name);

	void LoadDb(const DbAccount &data);
	CStr &Name() const;
	CStr &Psw() const;
	void CreateAccount(CStr &psw);
	const std::vector<ActorBrief> &GetActorList();
	void CreatePlayer(const DbPlayer &player);

	static void OnQuery(bool ret, const DbAccount &data, any para);
	static void OnInsert(bool ret, const DbPlayer &data, any para);
	static void OnSelect(bool ret, const DbPlayer &data, any para);
private:

	static void SelectActor(const acc::Session &sn);
};