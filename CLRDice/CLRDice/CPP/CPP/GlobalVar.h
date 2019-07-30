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
#pragma once
#ifndef DICE_GLOBAL_VAR
#define DICE_GLOBAL_VAR
#include"../CQSDK/CQLogger.h"
//#include "CQLogger.h"
#include <map>

// �汾��Ϣ
extern const unsigned short Dice_Build;
extern const std::string Dice_Ver_Without_Build;
extern const std::string DiceRequestHeader;
extern const std::string Dice_Ver;
extern const std::string Dice_Short_Ver;
extern const std::string Dice_Full_Ver;

// Ӧ���Ƿ�����
extern bool Enabled;

// ��Ϣ�����߳��Ƿ���������
extern bool msgSendThreadRunning;

// ȫ�ֿ�QLogger
extern CQ::logger DiceLogger;

// �ظ���Ϣ, �����ݿ���ͨ��CustomMsg�����޸Ķ������޸�Դ����
extern std::map<const std::string, std::string> GlobalMsg;
#endif /*DICE_GLOBAL_VAR*/
