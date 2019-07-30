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
#include "CQLogger.h"
#include "GlobalVar.h"
#include <map>

bool Enabled = false;

bool msgSendThreadRunning = false;

CQ::logger DiceLogger("Dice!");

/*
 * �汾��Ϣ
 * �����޸�Dice_Build, Dice_Ver_Without_Build��DiceRequestHeader�Լ�Dice_Ver����
 * ���޸�Dice_Short_Ver��Dice_Full_Ver�����Դﵽ�汾�Զ���
 */
const unsigned short Dice_Build = 524;
const std::string Dice_Ver_Without_Build = "2.3.8";
const std::string DiceRequestHeader = "Dice/" + Dice_Ver_Without_Build;
const std::string Dice_Ver = Dice_Ver_Without_Build + "(" + std::to_string(Dice_Build) + ")";
const std::string Dice_Short_Ver = "Dice! by ��� Version " + Dice_Ver;
#ifdef __clang__

#ifdef _MSC_VER
const std::string Dice_Full_Ver = Dice_Short_Ver + " [CLANG " + __clang_version__ + " MSVC " + std::to_string(_MSC_FULL_VER) + " " + __DATE__ + " " + __TIME__ + "]";
#elif defined(__GNUC__)
const std::string Dice_Full_Ver = Dice_Short_Ver + " [CLANG " + __clang_version__ + " GNUC " + std::to_string(__GNUC__) + "." + std::to_string(__GNUC_MINOR__) + "." + std::to_string(__GNUC_PATCHLEVEL__) + " " + __DATE__ + " " + __TIME__ + "]";
#else
const std::string Dice_Full_Ver = Dice_Short_Ver + " [CLANG " + __clang_version__ + " UNKNOWN]"
#endif /*_MSC_VER*/

#else

#ifdef _MSC_VER
const std::string Dice_Full_Ver = Dice_Short_Ver + " [MSVC " + std::to_string(_MSC_FULL_VER) + " " + __DATE__ + " " + __TIME__ + "]";
#elif defined(__GNUC__)
const std::string Dice_Full_Ver = Dice_Short_Ver + " [GNUC " + std::to_string(__GNUC__) + "." + std::to_string(__GNUC_MINOR__) + "." + std::to_string(__GNUC_PATCHLEVEL__) + " " + __DATE__ + " " + __TIME__ + "]";
#else
const std::string Dice_Full_Ver = Dice_Short_Ver + " [UNKNOWN COMPILER]"
#endif /*_MSC_VER*/

#endif /*__clang__*/

std::map<const std::string, std::string> GlobalMsg
{
	{"strNameNumTooBig", "������������!������1-10֮�������!"},
	{"strNameNumCannotBeZero", "������������Ϊ��!������1-10֮�������!"},
	{"strSetInvalid", "��Ч��Ĭ����!������1-99999֮�������!"},
	{"strSetTooBig", "Ĭ��������!������1-99999֮�������!"},
	{"strSetCannotBeZero", "Ĭ��������Ϊ��!������1-99999֮�������!"},
	{"strCharacterCannotBeZero", "�������ɴ�������Ϊ��!������1-10֮�������!"},
	{"strCharacterTooBig", "�������ɴ�������!������1-10֮�������!"},
	{"strCharacterInvalid", "�������ɴ�����Ч!������1-10֮�������!"},
	{"strSCInvalid", "SC���ʽ���벻��ȷ,��ʽΪ�ɹ���San/ʧ�ܿ�San,��1/1d6!"},
	{"strSanInvalid", "Sanֵ���벻��ȷ,������1-99��Χ�ڵ�����!"},
	{"strEnValInvalid", "����ֵ���������벻��ȷ,������1-99��Χ�ڵ�����!"},
	{"strNameDelErr", "û����������,�޷�ɾ��!"},
	{"strValueErr", "�������ʽ�������!"},
	{"strInputErr", "������������ʽ�������!"},
	{"strUnknownErr", "������δ֪����!"},
	{"strUnableToGetErrorMsg", "�޷���ȡ������Ϣ!"},
	{"strDiceTooBigErr", "���ﱻ���ӳ���������û��"},
	{"strRequestRetCodeErr", "���ʷ�����ʱ���ִ���! HTTP״̬��: {0}"},
	{"strRequestNoResponse", "������δ�����κ���Ϣ"},
	{"strTypeTooBigErr", "��!�������������ж�������~1...2..."},
	{"strZeroTypeErr", "����...!!ʱ����(���ﱻ���Ӳ�����ʱ���ѷ������)"},
	{"strAddDiceValErr", "������Ҫ�����������ӵ�ʲôʱ����~(��������ȷ�ļ�������:5-10֮�ڵ�����)"},
	{"strZeroDiceErr", "��?�ҵ�������?"},
	{"strRollTimeExceeded", "�������������������������!"},
	{"strRollTimeErr", "�쳣����������"},
	{"strWelcomeMsgClearedNotice", "�������Ⱥ����Ⱥ��ӭ��"},
	{"strWelcomeMsgIsEmptyErr", "����:û��������Ⱥ��ӭ�ʣ����ʧ��"},
	{"strWelcomeMsgUpdatedNotice", "�Ѹ��±�Ⱥ����Ⱥ��ӭ��"},
	{"strPermissionDeniedErr", "����:�˲�����ҪȺ�������ԱȨ��"},
	{"strNameTooLongErr", "����:���ƹ���(���Ϊ50Ӣ���ַ�)"},
	{"strUnknownPropErr", "����:���Բ�����"},
	{"strEmptyWWDiceErr", "��ʽ����:��ȷ��ʽΪ.w(w)XaY!����X��1, 5��Y��10"},
	{"strPropErr", "������������������Ŷ~"},
	{"strSetPropSuccess", "�������óɹ�"},
	{"strPropCleared", "�������������"},
	{"strRuleErr", "�������ݻ�ȡʧ��,������Ϣ:\n"},
	{"strRulesFailedErr", "����ʧ��,�޷��������ݿ�"},
	{"strPropDeleted", "����ɾ���ɹ�"},
	{"strPropNotFound", "����:���Բ�����"},
	{"strRuleNotFound", "δ�ҵ���Ӧ�Ĺ�����Ϣ"},
	{"strProp", "{0}��{1}����ֵΪ{2}"},
	{"strStErr", "��ʽ����:��ο������ĵ���ȡ.st�����ʹ�÷���"},
	{"strRulesFormatErr", "��ʽ����:��ȷ��ʽΪ.rules[��������:]������Ŀ ��.rules COC7:����"},
	{"strJrrp", "{0}�������Ʒֵ��: {1}"},
	{"strJrrpErr", "JRRP��ȡʧ��! ������Ϣ: \n{0}"},
	{"strFumble", "��ʧ��"},
	{"strFailure", "ʧ��"},
	{"strSuccess", "�ɹ�"},
	{"strHardSuccess", "���ѳɹ�"},
	{"strExtremeSuccess", "���ѳɹ�"},
	{"strCriticalSuccess", "��ɹ�"},
	{"strInitListClearedNotice", "�ɹ�����ȹ���¼!"},
	{"strInitListIsEmptyErr", "����: �ȹ��б�Ϊ��!"},
	{"strCommandNotAvailableErr", "����: �����������Ⱥ/��������ʹ��"},
	{"strSuccessfullyEnabledNotice", "�ɹ�������������!"},
	{"strAlreadyEnabledErr", "���������Ѿ����ڿ���״̬!"},
	{"strSuccessfullyDisabledNotice", "�ɹ��رձ�������!"},
	{"strAlreadyDisabledErr", "���������Ѿ����ڹر�״̬!"},
	{"strObCommandSuccessfullyEnabledNotice", "�ɹ��ڱ�Ⱥ/�������������Թ�ģʽ!"},
	{"strObCommandAlreadyEnabledErr", "����: �ڱ�Ⱥ/�������Թ�ģʽ�Ѿ�������!"},
	{"strObCommandSuccessfullyDisabledNotice", "�ɹ��ڱ�Ⱥ/�������н����Թ�ģʽ!"},
	{"strObCommandAlreadyDisabledErr", "����: �ڱ�Ⱥ/�������Թ�ģʽ�Ѿ�������!"},
	{"strObCommandDisabledErr", "����Ա���ڱ�Ⱥ/�������н����Թ�ģʽ!"},
	{"strObListClearedNotice", "�ɹ�ɾ�������Թ���!"},
	{"strJrrpCommandSuccessfullyEnabledNotice", "�ɹ��ڱ�Ⱥ/������������.jrrp����!"},
	{"strJrrpCommandAlreadyEnabledErr", "����: �ڱ�Ⱥ/��������.jrrp�����Ѿ�������!"},
	{"strJrrpCommandSuccessfullyDisabledNotice", "�ɹ��ڱ�Ⱥ/�������н���.jrrp����!"},
	{"strJrrpCommandAlreadyDisabledErr", "����: �ڱ�Ⱥ/��������.jrrp�����Ѿ�������!"},
	{"strJrrpCommandDisabledErr", "����Ա���ڴ�Ⱥ/�������н���.jrrp����!"},
	{"strHelpCommandSuccessfullyEnabledNotice", "�ɹ��ڱ�Ⱥ/������������.help����!"},
	{"strHelpCommandAlreadyEnabledErr", "����: �ڱ�Ⱥ/��������.help�����Ѿ�������!"},
	{"strHelpCommandSuccessfullyDisabledNotice", "�ɹ��ڱ�Ⱥ/�������н���.help����!"},
	{"strHelpCommandAlreadyDisabledErr", "����: �ڱ�Ⱥ/��������.help�����Ѿ�������!"},
	{"strHelpCommandDisabledErr", "����Ա���ڴ�Ⱥ/�������н���.help����!"},
	{"strHelpMsg" , Dice_Short_Ver + "\n" +
	R"(��ʹ��!dismiss [������QQ��]�����û������Զ���Ⱥ�������飡
���ż�¼��ɫ��: https://logpainter.kokona.tech
<ͨ������>
.r [�������ʽ*] [ԭ��]			��ͨ����
.rs	[�������ʽ*] [ԭ��]			�����
.w/ww XaY						����
.set [1-99999֮�������]			����Ĭ����
.sc SC���ʽ** [Sanֵ]			�Զ�Sancheck
.en [������] [����ֵ]			��ǿ�춨/Ļ��ɳ�
.coc7/6 [����]					COC7/6��������
.dnd [����]					DND��������
.coc7/6d					��ϸ��COC7/6��������
.ti/li					�����-��ʱ/�ܽ�֢״
.st [del/clr/show] [������] [����ֵ]		���￨����
.rc/ra [������] [����ֵ]		���ܼ춨(������/����)
.jrrp [on/off]				������Ʒ�춨
.name [cn/jp/en] [����]			�����������
.rules [��������:]������Ŀ		�����ѯ
.n [����]					����/ɾ��ȫ���ǳ�
.nnn [cn/jp/en]				��������ǳ�
.rh [�������ʽ*] [ԭ��]			����,���˽�ķ���
.help						��ʾ����
<����Ⱥ/��������>
.nn [����]					����/ɾ���ǳ�
.ri [��ֵ] [�ǳ�]			DnD�ȹ�����
.init [clr]					DnD�ȹ��鿴/���
.bot [on/off] [������QQ��]		�����˿�����ر�
.ob [exit/list/clr/on/off]			�Թ�ģʽ
.welcome ��ӭ��Ϣ				Ⱥ��ӭ��ʾ
*COC7�ͷ���ΪP+����,������ΪB+����
 ֧��ʹ��K��ȡ�ϴ�ļ�������
 ֧��ʹ�� ����#���ʽ ���ж�������
**SC���ʽΪ �ɹ���San/ʧ�ܿ�San,��:1/1d6
�������/bug����/�鿴Դ�������QQȺ941980833��624807593(����)"}
};