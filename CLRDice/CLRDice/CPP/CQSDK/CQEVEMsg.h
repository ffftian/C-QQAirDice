#pragma once
#include "CQEVEBasic.h"

#include <string>
#include <map>

namespace CQ
{
	// ����
	struct Font final
	{
		const char* Name{};
		int Size{},
		    Color{},
		    /*���壺1 б�壺2 �»��ߣ�4*/
		    Style{},
		    Bubble{};

		explicit Font(int);
	};

	//������Ϣ
	class regexMsg final
	{
		//��Ϣ
		std::map<std::string, std::string> regexMap{};
	public:
		regexMsg(const std::string& msg);
		std::string get(const std::string&);
		std::string operator [](const std::string&);
	};

	class msg;

	//��Ϣ�¼�����
	struct EVEMsg : EVE
	{
		//������
		int subType;
		//��ϢID
		int msgId;
		//��ԴQQ
		long long fromQQ;
		//��Ϣ
		std::string message;
		//����
		Font font;

		EVEMsg(int subType, int msgId, long long fromQQ, std::string message, int font);

		//��ʵ�û�
		bool isUser() const;
		//�Ƿ���ϵͳ�û�
		bool isSystem() const;

		virtual int sendMsg(const char*) const = 0;
		virtual int sendMsg(const std::string&) const = 0;
		virtual msg sendMsg() const = 0;
	};
}
