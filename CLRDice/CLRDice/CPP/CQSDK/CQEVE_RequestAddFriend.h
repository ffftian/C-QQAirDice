#pragma once
#include <string>
#include "CQEVERequest.h"

/*
����-�������(Type=301)

subtype �����ͣ�Ŀǰ�̶�Ϊ1
sendTime ����ʱ��(ʱ���)
fromQQ ��ԴQQ
msg ����
responseFlag ������ʶ(����������)

�ú���������� (responseFlag, #����_ͨ��)

���ӳ�����ڿ�Q���̡߳��б����ã���ע��ʹ�ö������Ҫ��ʼ��(CoInitialize,CoUninitialize)
�������ʹ���»��߿�ͷ��Ҫ�ĳ�˫�»���
���ط���ֵ,��Ϣ��������,������Ȳ�������
*/
#define EVE_Request_AddFriend_EX(Name) \
	void Name(CQ::EVERequestAddFriend & eve);\
	EVE_Request_AddFriend(Name)\
	{\
		CQ::EVERequestAddFriend tep(subType, sendTime, fromGroup, fromQQ, msg, responseFlag);\
		Name(tep);\
		return tep._EVEret;\
	}\
	void Name(CQ::EVERequestAddFriend & eve)

namespace CQ
{
	struct EVERequestAddFriend final : EVERequest
	{
		//������
		//1:�̶�Ϊ1
		int subType;
		long long fromGroup; // ��ԴȺ��
		EVERequestAddFriend(int subType, int sendTime, long long fromQQ, const char* msg, const char* responseFlag);
		void pass(const std::string& msg = "") const override; //ͨ��������
		void fail(const std::string& msg = "�����ڲ�����ĳЩҪ�󱻾ܾ�!") const override; //�ܾ�������
	};
}
