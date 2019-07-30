#pragma once
#include <string>
#include "CQEVEBasic.h"

namespace CQ
{
	struct EVERequest : EVE
	{
		int sendTime; // ����ʱ��(ʱ���)
		long long fromQQ; // ��ԴQQ
		const char* msg; // ����
		const char* responseFlag; // ������ʶ(����������)

		EVERequest(int sendTime, long long fromQQ, const char* msg, const char* responseFlag);
		virtual void pass(const std::string& msg) const = 0; //ͨ��������
		virtual void fail(const std::string& msg) const = 0; //�ܾ�������
	};
}
