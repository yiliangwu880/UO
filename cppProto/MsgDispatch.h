//最新代码，以 https://gitee.com/yiliangwu880/CppProto.git 项目为准。
#pragma once
#include "ProtoInclude.h"

struct MsgMgr
{
	static void Check();
};

template<class Connecter>
class MsgDispatch
{	//管理center消息派发
	//记录处理接收消息 的信息
	struct MsgData
	{
		void *unpackFun = nullptr;	    //解包函数  bool Unpack(T &t, CPointChar &cur, size_t &len)
		void *msgFun = nullptr;		//处理消息函数	 void(*fun)(Connecter &con, const MsgType &msg)
		char *(*createFun)() = nullptr;		//消息对象 分配函数  
		void(*freeFun)(char *) = nullptr;	    //消息对象 释放函数 
	};

	std::unordered_map<uint16_t, MsgData> m_id2MsgData; //proto 消息ID 2 回调
public:
	static MsgDispatch& Ins()
	{
		static MsgDispatch ins;
		return ins;
	}
	//注册 proto消息回调
	template<class MsgType>
	void RegMsgHandler(void(*fun)(Connecter &con, const MsgType &msg));

	void Dispatch(Connecter &con, const char *msg, size_t len);
};


template<class Connecter>
template<class MsgType>
void MsgDispatch< Connecter>::RegMsgHandler(void(*fun)(Connecter &con, const MsgType &msg))
{
	MsgType msg;
	if (m_id2MsgData.find(msg.id) != m_id2MsgData.end())
	{
		L_ERROR("repeated reg");
		return;
	}
	MsgData &d = m_id2MsgData[msg.id];
	d.msgFun = (void *)fun;
	d.unpackFun = (void *)proto::Unpack<MsgType>;
	d.createFun = (decltype(d.createFun))proto::CreateFun<MsgType>;
	d.freeFun = (decltype(d.freeFun))proto::FreeFun<MsgType>;
}

template<class Connecter>
void MsgDispatch<Connecter>::Dispatch(Connecter &con, const char *msg, size_t len)
{
	using ComMsgFun = void(Connecter &con, const char &); //消息回调函数的抽象。 
	using ComUnpackFun = bool(char &, proto::CPointChar &, size_t &);//消息解析函数的抽象。 

	uint16_t msgId = *(const uint16_t *)msg; //约定协议前 uint16_t 为 cmdId. 
	auto it = m_id2MsgData.find(msgId);
	if (it == m_id2MsgData.end())
	{
		L_ERROR("unknow cmdId %d", msgId);
		return;
	}
	MsgData &msgData = it->second;
	ComMsgFun *fun = (ComMsgFun *)msgData.msgFun;
	ComUnpackFun *unpack = (ComUnpackFun *)msgData.unpackFun;
	char *msgType = msgData.createFun();
	if (unpack(*msgType, msg, len))
	{
		if (0 == len)
		{
			(*fun)(con, *msgType);
		}
		else//还有内容未解包
		{
			L_ERROR("have unknow bytes unpack %d", len);
		}
	}
	else
	{
		L_ERROR("unpack fail, cmdId=%d", msgId);
	}
	msgData.freeFun(msgType);

}


