#pragma once
#include <string>
#include "CQEVERequest.h"

/*
����-Ⱥ���(Type=302)

subtype �����ͣ�1/����������Ⱥ 2/�Լ�(����¼��)������Ⱥ
sendTime ����ʱ��(ʱ���)
fromGroup ��ԴȺ��
fromQQ ��ԴQQ
msg ����
responseFlag ������ʶ(����������)

��� subtype �� 1
��Ⱥ������� (responseFlag, #����_Ⱥ���, #����_ͨ��)
��� subtype �� 2
��Ⱥ������� (responseFlag, #����_Ⱥ����, #����_ͨ��)

���ӳ�����ڿ�Q���̡߳��б����ã���ע��ʹ�ö������Ҫ��ʼ��(CoInitialize,CoUninitialize)
�������ʹ���»��߿�ͷ��Ҫ�ĳ�˫�»���
���ط���ֵ,��Ϣ��������,������Ȳ�������
*/
#define EVE_Request_AddGroup_EX(Name) \
	void Name(CQ::EVERequestAddGroup & eve);\
	EVE_Request_AddGroup(Name)\
	{\
		CQ::EVERequestAddGroup tep(subType, sendTime, fromGroup, fromQQ, msg, responseFlag);\
		Name(tep);\
		return tep._EVEret;\
	}\
	void Name(CQ::EVERequestAddGroup & eve)

namespace CQ
{
	struct EVERequestAddGroup final : EVERequest
	{
		//������
		//1:����������Ⱥ
		//2:�Լ�(����¼��)������Ⱥ
		int subType;
		long long fromGroup; // ��ԴȺ��
		EVERequestAddGroup(int subType, int sendTime, long long fromGroup, long long fromQQ, const char* msg,
		                   const char* responseFlag);
		void pass(const std::string& msg = "") const override; //ͨ��������
		void fail(const std::string& msg = "�����ڲ�����ĳЩҪ�󱻾ܾ�!") const override; //�ܾ�������
	};
}
