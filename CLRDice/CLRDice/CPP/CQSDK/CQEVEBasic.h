#pragma once

#include "CQconstant.h"

namespace CQ
{
	// �¼�����
	struct EVE
	{
		//������Ϣ���κζ���
		//���֮ǰ��������Ϣ,���ｫ���·��б�����Ϣ
		void message_ignore();
		//���ر�����Ϣ
		void message_block();

		int _EVEret = Msg_Ignored;

		virtual ~EVE()
		{
		}
	};
}
