
#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#pragma pack(push)
#pragma pack(1)
namespace proto {

	//�ȶ��������Ϣ���Ժ��پ���ʵ��, ���˳�� �� ��©�������ʼ����ʱ�������
#define PROTO_ALL_PROTO2 \
	DB_CLASS_NAME(test2_sc)\
	DB_FIELD(id)\
	DB_FIELD(ret)\
	DB_FIELD(any)\
	DB_CLASS_END\

	struct test2_sc
	{
		const uint16_t id = 101;
		bool ret;
		std::string any; //������� proto����Ľṹ�壬������� ��̬���������߽� ������
	};



}
#pragma pack(pop)
