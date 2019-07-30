#pragma once

#include "CQMsgSend.h"

/*
��������Ϣ(Type=4)

subtype		�����ͣ�Ŀǰ�̶�Ϊ1
msgId	��ϢID
fromDiscuss	��Դ������
fromQQ		��ԴQQ��
msg			��Ϣ����
font		����

���ӳ�����ڿ�Q���̡߳��б����ã���ע��ʹ�ö������Ҫ��ʼ��(CoInitialize,CoUninitialize)
�������ʹ���»��߿�ͷ��Ҫ�ĳ�˫�»���
���ط���ֵ,��Ϣ��������,������Ȳ�������
*/
#define EVE_DiscussMsg_EX(Name)																	\
	void Name(CQ::EVEDiscussMsg & eve);															\
	EVE_DiscussMsg(Name)																		\
	{																							\
		CQ::EVEDiscussMsg tep(subType, msgId, fromDiscuss, fromQQ, msg, font);					\
		Name(tep);\
		return tep._EVEret;																		\
	}																							\
	void Name(CQ::EVEDiscussMsg & eve)


namespace CQ
{
	struct EVEDiscussMsg : EVEMsg
	{
		long long fromDiscuss; //�������

		EVEDiscussMsg(int subType, int msgId, long long fromDiscuss, long long fromQQ, const char* msg, int font);

		bool leave() const; //�˳�������

		// ͨ�� EVEMsg �̳�
		msg sendMsg() const override;
		int sendMsg(const char*) const override;
		int sendMsg(const std::string&) const override;
	};
}
