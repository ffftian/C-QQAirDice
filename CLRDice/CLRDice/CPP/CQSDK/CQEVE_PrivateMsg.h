#pragma once
#include "CQMsgSend.h"

/*
˽����Ϣ(Type=21)

�˺����������²���
subType		�����ͣ�11/���Ժ��� 1/��������״̬ 2/����Ⱥ 3/����������
msgId	��ϢID
fromQQ		��ԴQQ
msg			��Ϣ����
font		����

���ӳ�����ڿ�Q���̡߳��б����ã���ע��ʹ�ö������Ҫ��ʼ��(CoInitialize,CoUninitialize)
�������ʹ���»��߿�ͷ��Ҫ�ĳ�˫�»���
���ط���ֵ,��Ϣ��������,������Ȳ�������
*/
#define EVE_PrivateMsg_EX(Name)																	\
	void Name(CQ::EVEPrivateMsg & eve);															\
	EVE_PrivateMsg(Name)																		\
	{																							\
		CQ::EVEPrivateMsg tep(subType, msgId, fromQQ, msg, font); \
		Name(tep); \
		return tep._EVEret;																		\
	}																							\
	void Name(CQ::EVEPrivateMsg & eve)


namespace CQ
{
	struct EVEPrivateMsg final : EVEMsg
	{
		EVEPrivateMsg(int subType, int msgId, long long fromQQ, const char* msg, int font);

		//���Ժ���
		bool fromPrivate() const;

		//��������״̬
		bool fromOnlineStatus() const;

		//����Ⱥ��ʱ
		bool fromGroup() const;

		//������������ʱ
		bool fromDiscuss() const;

		// ͨ�� EVEMsg �̳�
		msg sendMsg() const override;

		int sendMsg(const char*) const override;

		int sendMsg(const std::string&) const override;
	};
}
