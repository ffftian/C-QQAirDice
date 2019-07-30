/*
 *  _______     ________    ________    ________    __
 * |   __  \   |__    __|  |   _____|  |   _____|  |  |
 * |  |  |  |     |  |     |  |        |  |_____   |  |
 * |  |  |  |     |  |     |  |        |   _____|  |__|
 * |  |__|  |   __|  |__   |  |_____   |  |_____    __
 * |_______/   |________|  |________|  |________|  |__|
 *
 * Dice! QQ Dice Robot for TRPG
 * Copyright (C) 2018-2019 w4123���
 *
 * This program is free software: you can redistribute it and/or modify it under the terms
 * of the GNU Affero General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License along with this
 * program. If not, see <http://www.gnu.org/licenses/>.
 */
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
#include <fstream>
#include "CQEVE_ALL.h"
#include "EncodingConvert.h"
#include "DiceNetwork.h"
#include "GlobalVar.h"

#ifdef _MSC_VER
#pragma comment(lib, "user32.lib")
#endif

EVE_Menu(eventMenu)
{
	std::string ver;
	if (!Network::GET("api.kokona.tech", "/getVer", 5555, ver))
	{
		MessageBoxA(nullptr, ("������ʱ��������: \n" + ver).c_str(), "Dice!���´���", MB_OK | MB_ICONWARNING);
		return -1;
	}

	ver = UTF8toGBK(ver);
	const std::string serverBuild = ver.substr(ver.find('(') + 1, ver.find(')') - ver.find('(') - 1);
	if (Dice_Build >= stoi(serverBuild))
	{
		MessageBoxA(nullptr, "������ʹ�õ�Dice!��Ϊ���°汾!", "Dice!����", MB_OK | MB_ICONINFORMATION);
		return 0;
	}

	const std::string updateNotice = "�����°汾! \n\n��ǰ�汾: " + Dice_Ver + "\n�°汾: " + ver + "\n\n����: �������ʹ�õ�Dice!Ϊ�޸İ�, �˸��»Ὣ�串��Ϊԭ��!\n���ȷ������ʼ����, ȡ����ȡ������";
	
	if (MessageBoxA(nullptr, updateNotice.c_str(), "Dice!����", MB_OKCANCEL | MB_ICONINFORMATION) != IDOK)
	{
		MessageBoxA(nullptr, "������ȡ��", "Dice!����", MB_OK | MB_ICONINFORMATION);
		return 0;
	}

	char buffer[MAX_PATH];
	const DWORD length = GetModuleFileNameA(nullptr, buffer, sizeof buffer);

	if (length == MAX_PATH || length == 0)
	{
		MessageBoxA(nullptr, "·����ȡʧ��!", "Dice!���´���", MB_OK | MB_ICONERROR);
		return -1;
	}

	std::string filePath(buffer, length);
	filePath = filePath.substr(0, filePath.find_last_of("\\")) + "\\app\\com.w4123.dice.cpk";
	
	std::string fileContent;
	if (!Network::GET("api.kokona.tech", "/getDice", 5555, fileContent))
	{
		MessageBoxA(nullptr, ("�°汾�ļ�����ʧ��! ������������״̬! ������Ϣ: " + fileContent).c_str(), "Dice!���´���", MB_OK | MB_ICONERROR);
		return -1;
	}
	
	std::ofstream streamUpdate(filePath, std::ios::trunc | std::ios::binary | std::ios::out);
	if (!streamUpdate)
	{
		MessageBoxA(nullptr, "�ļ���ʧ��!", "Dice!���´���", MB_OK | MB_ICONERROR);
		return -1;
	}

	streamUpdate << fileContent;
	streamUpdate.close();
	MessageBoxA(nullptr, "Dice!�Ѹ���, ������������Q!", "Dice!����", MB_OK | MB_ICONINFORMATION);
	return 0;
}

