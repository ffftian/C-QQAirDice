#pragma once
#include <string>
#include "DiceMsgType.h"
namespace Dice
{
	struct DiceMsg
	{
		// ��Ϣ����
		std::string msg;
		// ȺID, ˽��ʱ�����ó�QQ��
		long long group_id;
		// QQ��
		long long qq_id;
		// ��Ϣ����
		Dice::MsgType msg_type;


		// ����ظ�DiceMsg��
		DiceMsg FormatReplyMsg(std::string reply_msg);

		// �ظ���Ϣ
		void Reply(std::string reply_msg);

		// �������ݵĹ��캯��, string����move��ʱ��ǵ�move
		DiceMsg(std::string msg, long long group_id, long long qq_id, Dice::MsgType msg_type);

		// Ĭ�Ͽչ��캯��
		DiceMsg() = default;
	};
}


