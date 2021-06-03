#include "AccountSubCom.h"
#include "dbTableDef.h"

//核心组件，先随便命名
class AccData : public AccountSubCom
{
	static const int MAX_ACTOR = 4;

	DbAccount m_data;
public:
	AccData(Account &owner, CStr &name);

	void LoadDb(const DbAccount &data);
	CStr &Name() const;
	CStr &Psw() const;
	void CreateAccount(CStr &psw);


	static void OnDbLoad(bool ret, const DbAccount &data, any para);
	static void OnInsert(bool ret, const DbPlayer &data, any para);
	static void OnSelect(bool ret, const DbPlayer &data, any para);
private:

	static void CreateActor(const acc::Session &sn);
	static void SelectActor(const acc::Session &sn);
};