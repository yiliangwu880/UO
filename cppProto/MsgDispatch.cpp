#include "MsgDispatch.h"



void MsgMgr::Check()
{
	using namespace proto;
#pragma pack(push)
#pragma pack(1)

#define DB_CLASS_NAME(className) \
	struct Check_##className \
	{\
		using CheckType = className;\

#define DB_FIELD(fieldName)	\
		decltype(CheckType::fieldName) fieldName;\

#define DB_CLASS_END\
	};\

		ALL_STRUCT_INFO

#undef  DB_CLASS_NAME
#undef  DB_FIELD
#undef  DB_CLASS_END

#define DB_CLASS_NAME(className) \
	  if(sizeof(Check_##className) != sizeof(Check_##className::CheckType))\
	  {\
			L_ERROR(#className" miss field define!");\
			L_ASSERT(false);\
	  }\

#define DB_FIELD(fieldName)	
#define DB_CLASS_END

			ALL_STRUCT_INFO

#undef  DB_CLASS_NAME
#undef  DB_FIELD
#undef  DB_CLASS_END



#define DB_CLASS_NAME(className) \
	{\
		className t;\
		size_t lastOffset = 0; \

#define DB_FIELD(fieldName)	\
	{\
		size_t offset = (size_t)&(((decltype(t) *)(nullptr))->fieldName);\
		if(lastOffset > offset)\
		{\
			L_ERROR("field "#fieldName" define order is error");\
			L_ASSERT(false);\
		}\
		lastOffset = offset;\
	}\

#define DB_CLASS_END\
	}\

			ALL_STRUCT_INFO

#undef  DB_CLASS_NAME
#undef  DB_FIELD
#undef  DB_CLASS_END

#pragma pack(pop)
}




