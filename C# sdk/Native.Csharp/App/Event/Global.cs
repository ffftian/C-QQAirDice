﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Native.Csharp.App.Event
{
    static class Global
    {
        static public Dictionary<string, string> GlobalMsg = new Dictionary<string, string>{
    {"strNameNumTooBig", "生成数量过多!请输入1-10之间的数字!"},
    {"strNameNumCannotBeZero", "生成数量不能为零!请输入1-10之间的数字!"},
    {"strSetInvalid", "无效的默认骰!请输入1-99999之间的数字!"},
    {"strSetTooBig", "默认骰过大!请输入1-99999之间的数字!"},
    {"strSetCannotBeZero", "默认骰不能为零!请输入1-99999之间的数字!"},
    {"strCharacterCannotBeZero", "人物作成次数不能为零!请输入1-10之间的数字!"},
    {"strCharacterTooBig", "人物作成次数过多!请输入1-10之间的数字!"},
    {"strCharacterInvalid", "人物作成次数无效!请输入1-10之间的数字!"},
    {"strSCInvalid", "SC表达式输入不正确,格式为成功扣San/失败扣San,如1/1d6!"},
    {"strSanInvalid", "San值输入不正确,请输入1-99范围内的整数!"},
    {"strEnValInvalid", "技能值或属性输入不正确,请输入1-99范围内的整数!"},
    {"strNameDelErr", "没有设置名称,无法删除!"},
    {"strValueErr", "掷骰表达式输入错误!"},
    {"strInputErr", "命令或掷骰表达式输入错误!"},
    {"strUnknownErr", "发生了未知错误!"},
    {"strUnableToGetErrorMsg", "无法获取错误信息!"},
    {"strDiceTooBigErr", "骰娘被你扔出的骰子淹没了"},
    {"strRequestRetCodeErr", "访问服务器时出现错误! HTTP状态码: {0}"},
    {"strRequestNoResponse", "服务器未返回任何信息"},
    {"strTypeTooBigErr", "哇!让我数数骰子有多少面先~1...2..."},
    {"strZeroTypeErr", "这是...!!时空裂(骰娘被骰子产生的时空裂缝卷走了)"},
    {"strAddDiceValErr", "你这样要让我扔骰子扔到什么时候嘛~(请输入正确的加骰参数:5-10之内的整数)"},
    {"strZeroDiceErr", "咦?我的骰子呢?"},
    {"strRollTimeExceeded", "掷骰轮数超过了最大轮数限制!"},
    {"strRollTimeErr", "异常的掷骰轮数"},
    {"strWelcomeMsgClearedNotice", "已清除本群的入群欢迎词"},
    {"strWelcomeMsgIsEmptyErr", "错误:没有设置入群欢迎词，清除失败"},
    {"strWelcomeMsgUpdatedNotice", "已更新本群的入群欢迎词"},
    {"strPermissionDeniedErr", "错误:此操作需要群主或管理员权限"},
    {"strNameTooLongErr", "错误:名称过长(最多为50英文字符)"},
    {"strUnknownPropErr", "错误:属性不存在"},
    {"strEmptyWWDiceErr", "格式错误:正确格式为.w(w)XaY!其中X≥1, 5≤Y≤10"},
    {"strPropErr", "请认真的输入你的属性哦~"},
    {"strSetPropSuccess", "属性设置成功"},
    {"strPropCleared", "已清除所有属性"},
    {"strRuleErr", "规则数据获取失败,具体信息:\n"},
    {"strRulesFailedErr", "请求失败,无法连接数据库"},
    {"strPropDeleted", "属性删除成功"},
    {"strPropNotFound", "错误:属性不存在"},
    {"strRuleNotFound", "未找到对应的规则信息"},
    {"strProp", "{0}的{1}属性值为{2}"},
    {"strStErr", "格式错误:请参考帮助文档获取.st命令的使用方法"},
    {"strRulesFormatErr", "格式错误:正确格式为.rules[规则名称:]规则条目 如.rules COC7:力量"},
    {"strJrrp", "{0}今天的人品值是: {1}"},
    {"strJrrpErr", "JRRP获取失败! 错误信息: \n{0}"},
    {"strFumble", "大失败"},
    {"strFailure", "失败"},
    {"strSuccess", "成功"},
    {"strHardSuccess", "困难成功"},
    {"strExtremeSuccess", "极难成功"},
    {"strCriticalSuccess", "大成功"},
    {"strInitListClearedNotice", "成功清除先攻记录!"},
    {"strInitListIsEmptyErr", "错误: 先攻列表为空!"},
    {"strCommandNotAvailableErr", "错误: 此命令仅可在群/讨论组中使用"},
    {"strSuccessfullyEnabledNotice", "成功开启本机器人!"},
    {"strAlreadyEnabledErr", "本机器人已经处于开启状态!"},
    {"strSuccessfullyDisabledNotice", "成功关闭本机器人!"},
    {"strAlreadyDisabledErr", "本机器人已经处于关闭状态!"},
    {"strObCommandSuccessfullyEnabledNotice", "成功在本群/讨论组中启用旁观模式!"},
    {"strObCommandAlreadyEnabledErr", "错误: 在本群/讨论组旁观模式已经被启用!"},
    {"strObCommandSuccessfullyDisabledNotice", "成功在本群/讨论组中禁用旁观模式!"},
    {"strObCommandAlreadyDisabledErr", "错误: 在本群/讨论组旁观模式已经被禁用!"},
    {"strObCommandDisabledErr", "管理员已在本群/讨论组中禁用旁观模式!"},
    {"strObListClearedNotice", "成功删除所有旁观者!"},
    {"strJrrpCommandSuccessfullyEnabledNotice", "成功在本群/讨论组中启用.jrrp命令!"},
    {"strJrrpCommandAlreadyEnabledErr", "错误: 在本群/讨论组中.jrrp命令已经被启用!"},
    {"strJrrpCommandSuccessfullyDisabledNotice", "成功在本群/讨论组中禁用.jrrp命令!"},
    {"strJrrpCommandAlreadyDisabledErr", "错误: 在本群/讨论组中.jrrp命令已经被禁用!"},
    {"strJrrpCommandDisabledErr", "管理员已在此群/讨论组中禁用.jrrp命令!"},
    {"strHelpCommandSuccessfullyEnabledNotice", "成功在本群/讨论组中启用.help命令!"},
    {"strHelpCommandAlreadyEnabledErr", "错误: 在本群/讨论组中.help命令已经被启用!"},
    {"strHelpCommandSuccessfullyDisabledNotice", "成功在本群/讨论组中禁用.help命令!"},
    {"strHelpCommandAlreadyDisabledErr", "错误: 在本群/讨论组中.help命令已经被禁用!"},
    {"strHelpCommandDisabledErr", "管理员已在此群/讨论组中禁用.help命令!"},
    {"help",    "投点指令:丢出一个百面骰:/rd\n" +
                "暗骰:/rhd\n"+
                "丢出指定的骰子:/r[次数]d[范畴]\n" +
                "技能鉴定:/ra[技能名称][技能成功率]\n" +
                "投掷COC7版规则属性点指令:/coc[数字or忽略]\n" +
                "随机一个疯狂症状:/临时疯狂\n" +
                "只有群有效指令\n" +
                "教丛雨说话:/录入话语  问:[收到的话]答:[回复的话]\n" +
                "谢谢使用OVO"},
    };
    }
}
