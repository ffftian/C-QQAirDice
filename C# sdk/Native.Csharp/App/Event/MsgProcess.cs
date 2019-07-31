using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;


namespace Native.Csharp.App.Event
{
    public enum msgtype { Private, Group, Discuss };

    /// <summary>
    /// Type=21 在线状态消息, 事件接口
    /// </summary>
   

    public class MsgProcess
    {
        




        static Dictionary<long, GroupStruct> GroupDict = new Dictionary<long, GroupStruct>();//关于群的设置 
        static Dictionary<long, List<int>> RemoteDict = new Dictionary<long, List<int>>();//关于遥控骰子的预留，防止很多人用遥控

        public long QQ;
        public long fromGroup;
        public string Message;
        public msgtype msgtype;
        public int stringNumber = 0;

        //GroupInt


        public MsgProcess(string Message, long QQ, long Group, msgtype msgtype)
        {
            this.QQ = QQ;
            this.fromGroup = Group;
            this.Message = Message;
            this.msgtype = msgtype;
            Main();
        }
        public MsgProcess(string Message, long QQ, msgtype msgtype)
        {
            this.QQ = QQ;
            fromGroup = 0;
            this.Message = Message;
            this.msgtype = msgtype;
            Main();
        }

        void 发送消息(string SendMessage)
        {
                if (msgtype == msgtype.Group)//群
                {
                    Common.CqApi.SendGroupMessage(fromGroup, SendMessage);
                }
                else if (msgtype == msgtype.Discuss)//讨论组
                {
                    Common.CqApi.SendDiscussMessage(fromGroup, SendMessage);
                }
                else if (msgtype == msgtype.Private)//私聊
                {
                    Common.CqApi.SendPrivateMessage(QQ, SendMessage);
                }
            
        }
        void 发送私聊消息(string SendMessage)
        {
            Common.CqApi.SendPrivateMessage(QQ, SendMessage);
        }

        string 获取昵称()
        {
            return/* fromGroup==0?*/ Common.CqApi.GetQQInfo(QQ).Nick;/* :  Common.CqApi.GetMemberInfo(fromGroup, QQ).Nick;*/
        }

        void Main()
        {
            if (Message.StartsWith("/help"))
            {/*
                string 说明 = "丛雨就是我啦，现在拥有的功能有:\n" +
                    "教丛雨说话:.录入话语 问: 答: \n" +
                    "让丛雨录跑团记录:.录入开始 /名称 录入结束\n" +
                    "投点使用/r 也可开启传统投点模式";*/
                发送消息(Global.GlobalMsg["help"]);
            }
            if (Message.StartsWith(".jrrp"))
            {
                发送消息( "别jrrp了，来教我说话吧，指令：/录入话语 问: 答:");
            }
            #region 投点相关
            if (Message.StartsWith("/rd"))//百面投点
            {
                if (RemoteDict.ContainsKey(QQ) == false)
                {
                    int rd = 0;
                    发送消息(获取昵称() + "的D100投出:" + SingleDice("1d100", ref rd));
                }
                else
                {
                    int rd = 0;
                    发送消息("由于"+Message.Substring(3)+ 获取昵称() + "的D100投出:" + 子遥控骰子读取("1d100", ref rd));
                }
            }
            if (Regex.IsMatch(Message, @"^/r[+-]?([0-9]+d[0-9]+)"))//一般匹配正则,关于自定义投点
            {
                if (RemoteDict.ContainsKey(QQ) == false)
                {
                    发送消息(获取昵称() + Dice(Message).Substring(2));
                }
                else
                {
                    发送消息(获取昵称() + 遥控骰子读取(Message).Substring(2));
                    //发送消息(获取昵称() + Dice(Message).Substring(2));
                }
            }
            if (Message.StartsWith("/rhd"))//私聊丢点
            {
                int rd=0;
                发送消息(获取昵称 ()+"进行了一次暗骰");
                发送私聊消息(获取昵称() + "的D100投出:" + SingleDice("1d100", ref rd));
            }
            if (Message.StartsWith("/rp"))//惩罚丢点
            {
                int value = DiceRamdom.random.Next(0, 10);//1-10
                int Punishment = DiceRamdom.random.Next(0, 10);//只会0-9
                int Punishment2 = DiceRamdom.random.Next(0, 10);//只会0-9
                                                         //  string valueS = value.ToString();

               // value += Punishment> Punishment2? Punishment*10 : Punishment2 * 10;
                if(value==0&& Punishment==0|| Punishment2==0)
                {
                    //大失败
                    发送消息(获取昵称() + "投出了P=" + (value + Punishment * 10) + "惩罚骰=" + Punishment2 + "结果:" + (100)+"是的大失败了!");
                }
                else
                {
                    发送消息(获取昵称() + "投出了P=" + (value + Punishment * 10) + "惩罚骰=" + Punishment2 + "结果:" + (value + (Punishment > Punishment2 ? Punishment * 10 : Punishment2 * 10)));
                }
            }
            if (Message.StartsWith("/rb"))//奖励丢点
            {
                int value = DiceRamdom.random.Next(0, 10);//1-10
                int Punishment = DiceRamdom.random.Next(0, 10);//只会0-9
                int Punishment2 = DiceRamdom.random.Next(0, 10);//只会0-9
                                                                //  string valueS = value.ToString();

                // value += Punishment> Punishment2? Punishment*10 : Punishment2 * 10;
                if (value == 0 && Punishment == 0 && Punishment2 == 0)
                {
                    //大失败
                    发送消息(获取昵称() + "投出了B=" + (value + Punishment * 10) + "奖励骰=" + Punishment2 + "结果:" + (100) + "是的大失败了，奖励骰还大失败，是俏!");
                }
                else
                {
                    发送消息(获取昵称() + "投出了B=" + (value + Punishment * 10) + "奖励骰=" + Punishment2 + "结果:" + (value + (Punishment < Punishment2 ? Punishment * 10 : Punishment2 * 10)));
                }
            }


            //[技能名称（可忽略）][技能数值][玩家附带的话]
            //[技能名称任意，但任意必须包含数字][技能数值][玩家附带的话]
            if (Message.StartsWith("/ra"))//面向解决设计
                {
                String strReply = "";

                // String a = Message.Replace(" ", "");
                if (!Regex.IsMatch(Message.Substring(3), @"\w+"))
                {
                    发送消息("指令不正确");
                    return;
                }
               MatchCollection Skill= Regex.Matches(Message.Substring(3), @"\w+");//匹配技能名称
               
               int intSkillVal = RDConstant.FindSkill(Skill[0].Value);//技能值
               if(Skill.Count>1)
                {
                   
                   var T = Regex.Match(Skill[1].Value, @"[0-9]+");//进行获取是否为自定义技能//可能是数字
                    if (T.Length != 0)
                    {
                        intSkillVal = int.Parse(Skill[1].Value);
                    } 
                    else
                    {
                        发送消息("指令不正确未知的数字");
                        return;
                    }
                    
                }
               else if(intSkillVal==0)
                {
                    发送消息("指令不正确，未知的技能属性");
                    return;
                }
                int intD100Res = DiceRamdom.Roll(0, 100);
                if (intD100Res <= 5 && intD100Res <= intSkillVal) strReply += Global.GlobalMsg["strCriticalSuccess"];
                else if (intD100Res > 95) strReply += Global.GlobalMsg["strFumble"];
                else if (intD100Res <= intSkillVal / 5) strReply += Global.GlobalMsg["strExtremeSuccess"];
                else if (intD100Res <= intSkillVal / 2) strReply += Global.GlobalMsg["strHardSuccess"];
                else if (intD100Res <= intSkillVal) strReply += Global.GlobalMsg["strSuccess"];
                else strReply += Global.GlobalMsg["strFailure"];

                发送消息(获取昵称() + "进行" + Skill[0].Value + "鉴定:D100=" + intD100Res + "/" + intSkillVal + strReply);

                //  var 数值 = Regex.Match(a, @"\u4e00-\u9fa5+");

                //string strSkillName

                //tring strReply = 获取昵称() + "进行" + strSkillName + "检定: D100=" + to_string(intD100Res) + "/" +
                //to_string(intSkillVal) + " ";


                }

            
            if (Regex.IsMatch(Message, @"(?<=^/遥控骰子\=)[0-9]+"))//遥控大法好//等于号之前被当正则符号处理了//接受到至少1位才进入
            {
                遥控骰子(Message,QQ);
                string g = "";
                 RemoteDict[QQ].ForEach(O => { g += O+","; });
                Common.CqApi.SendPrivateMessage(QQ, "已记录在案了哦,现有骰子队列:" + g   );
            }
              if (Regex.IsMatch(Message , @"(?<=/)[0-9]+(?=遥控骰子\=)"))//带指明的遥控
              {
                var Taget = long.Parse(Regex.Match(Message, @"(?<=/)[0-9]+(?=遥控骰子\=)").Value);
                遥控骰子(Message, Taget);
                string g = "";
                RemoteDict[Taget].ForEach(O => { g += O + ","; });
                Common.CqApi.SendPrivateMessage(QQ, "已修改他人的命运,现有骰子队列:" + g);
            }


            #endregion
            #region
             // if(Message.StartsWith("/开启"))

            #endregion

            CLR();
            MyTest();
        }
        void MyTest()
        {
            if(QQ==790947404)
            {
              ///  string a=Message;
               // CLRDice.CLRRD.RollDice(ref Message, 790947404);
               // 发送消息(Message);

            }
        }




        void CLR()
        {

            String QQCLRMsg = 获取昵称();
            if (Regex.IsMatch(Message, @"(?<=^/coc)"))//COC7相关
            {
                var t = Regex.Match(Message, @"(?<=^/coc)[0-9]+");
                if(t.Length==0)
                {
                    CLRDice.CLRRD.CLRCOC7(ref QQCLRMsg,1);
                    发送消息(QQCLRMsg);
                }
                else if (t.Length < 3)
                {
                    CLRDice.CLRRD.CLRCOC7(ref QQCLRMsg, int.Parse(t.Value));
                    发送消息(QQCLRMsg);
                }
                else
                {
                    发送消息("你投的太多啦！会撑啦");
                }
            }
            if (Regex.IsMatch(Message, @"(?<=^/dnd)"))//COC7相关
            {
                var t = Regex.Match(Message, @"(?<=^/dnd)[0-9]+");
                if (t.Length == 0)
                {
                    CLRDice.CLRRD.CLRDND(ref QQCLRMsg, 1);
                    发送消息(QQCLRMsg);
                }
                else if (t.Length < 3)
                {
                    CLRDice.CLRRD.CLRDND(ref QQCLRMsg, int.Parse(t.Value));
                    发送消息(QQCLRMsg);
                }
                else
                {
                    发送消息("你投的太多啦！会撑啦");
                }
            }




                if (Message.StartsWith("/疯狂症状"))//疯狂症状
            {
                CLRDice.CLRRD.CLRLongInsane(ref QQCLRMsg);
                发送消息(QQCLRMsg);
            }
            if (Message.StartsWith("/临时疯狂"))//临时疯狂
            {
                CLRDice.CLRRD.CLRTempInsane(ref QQCLRMsg);
                发送消息(QQCLRMsg);
            }
        }


       public  string Dice(string Message)//不提供处理/r符号/
        {
            string ReturnMessage = "";
            int I = 0;
            MatchCollection numList = Regex.Matches(Message, @"[+-]?([0-9]+d[0-9]+)|([+-]?[0-9]+)");
            if (numList.Count > 1000)
            {
                return "你投的太多了！";
            }
            for (int a = 0; a < numList.Count; a++)
            {
                var t = SingleDice(numList[a].Value, ref I);
                ReturnMessage += a + 1 < numList.Count ? t + "+" : t;
            }
            return Message + "投出:" + ReturnMessage + "总值:" + I;
        }


        //public int RollDice(int a)

       private  string SingleDice(string SingleMessage, ref int intValue)
        {
            string ReturnMessage = "";
            MatchCollection numList = Regex.Matches(SingleMessage, @"[+-]?[0-9]+");
            if (numList.Count == 1)
            {
                var T = numList[0].Value;
                if (numList[0].Value[0]=='+')
                {
                    T =   numList[0].Value.Substring(1);
                }
                intValue += int.Parse(T);
                ReturnMessage += "(" + T+ ")";
                return ReturnMessage;

            }
                int Time = int.Parse(numList[0].Value);
                int Size = int.Parse(numList[1].Value);
                if (Time < 0)//不优雅的处理方式
                {
                    Time = -Time;
                    Size = -Size;
                }
                var ts = System.DateTime.Now.Subtract(DateTime.Parse("1970-1-1"));
                int diffMilliseconds = Convert.ToInt32(ts.TotalSeconds + intValue);
                System.Random random = new Random(diffMilliseconds);//获取真-随机数（个屁）
                for (int a = 0; a < Time; a++)
                {
                    int Temp = Size >= 0 ? random.Next(0 + 1, Size + 1) : random.Next(Size, 0);
                    intValue += Temp;
                    ReturnMessage += Temp > 0 && a + 1 < Time ? Temp.ToString() + "+" : Temp.ToString();
                }
            ReturnMessage = "(" + ReturnMessage + ")";
            return ReturnMessage;
        }


        private List<int> 遥控骰子(string Message,long targetQQ)
        {
            MatchCollection matchs = Regex.Matches(Message, @"((?<=遥控骰子=)|(?<=,))[0-9]+");//反正之前判断过，为符合人工操作骰子
            List<int> RemoteValue = new List<int>();

            foreach (Match match in matchs)
            {
                RemoteValue.Add(int.Parse(match.Value));
            }
            if (!RemoteDict.ContainsKey(targetQQ))
            {
                RemoteDict.Add(targetQQ, RemoteValue);
            }
            else
            {
                RemoteDict[targetQQ].AddRange(RemoteValue);
            }

            return RemoteDict[targetQQ];
        }
            string  遥控骰子读取(string Message)
            {
                string ReturnMessage = "";
                int I = 0;
                MatchCollection numList = Regex.Matches(Message, @"[+-]?([0-9]+d[0-9]+)");
                if (numList.Count > 1000)
                {
                    return "你投的太多了！";
                }
                for (int a = 0; a < numList.Count; a++)
                {
                    var t = 子遥控骰子读取(numList[a].Value, ref I);
                    ReturnMessage += a + 1 < numList.Count ? t + "+" : t;
                }
                return Message + "投出:" + ReturnMessage + "总值:" + I;
            }
        private string 子遥控骰子读取(string SingleMessage, ref int intValue)
        {
            string ReturnMessage = "";
            MatchCollection numList = Regex.Matches(SingleMessage, @"[+-]?[0-9]+");
            int Time = int.Parse(numList[0].Value);
            int Size = int.Parse(numList[1].Value);
            if (Time < 0)//不优雅的处理方式
            {
                Time = -Time;
                Size = -Size;
            }
            var ts = System.DateTime.Now.Subtract(DateTime.Parse("1970-1-1"));
            int diffMilliseconds = Convert.ToInt32(ts.TotalSeconds + intValue);
            System.Random random = new Random(diffMilliseconds);//获取真-随机数（个屁）
            for (int a = 0; a < Time; a++)
            {
                int Temp =0;
                if (RemoteDict[QQ].Count != 0)
                {
                    Temp = RemoteDict[QQ][0];
                    RemoteDict[QQ].RemoveAt(0);//用过就报销
                }
                else
                {
                    Temp = Size >= 0 ? random.Next(0 + 1, Size + 1) : random.Next(Size, 0);
                }

                intValue += Temp;
                ReturnMessage += Temp > 0 && a + 1 < Time ? Temp.ToString() + "+" : Temp.ToString();
            }
            ReturnMessage = "(" + ReturnMessage + ")";
            return ReturnMessage;
        }
    }
}
