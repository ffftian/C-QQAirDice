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
            {
                string 说明 = "丛雨就是我啦，现在拥有的功能有:\n" +
                    "教丛雨说话:.录入话语 问: 答: \n" +
                    "让丛雨录跑团记录:.录入开始 /名称 录入结束\n" +
                    "投点使用/r 也可开启传统投点模式";
                发送消息(说明);
            }
            if (Message.StartsWith(".jrrp"))
            {
                发送消息( "别jrrp了，来教我说话吧，指令：.录入话语 问: 答:");
            }
            #region 投点相关
            if (Message.StartsWith("/rd"))//公开丢点
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
            if (Regex.IsMatch(Message, @"^/r[+-]?([0-9]+d[0-9]+)"))//一般匹配正则,关于投点
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
            CLR();
        }
        void CLR()
        {

            String QQCLRMsg = 获取昵称();
            if (Regex.IsMatch(Message, @"(?<=^/coc7)[0-9]+"))//COC7相关
            {
                var t = Regex.Match(Message, @"(?<=^/coc7)[0-9]+");
                if (t.Length < 3)
                {
                    CLRDice.RD.CLRCOC7(ref QQCLRMsg, int.Parse(t.Value));
                    发送消息(QQCLRMsg);
                }
                else
                {
                    发送消息("你投的太多啦！会撑啦");
                }
            }

            if (Message.StartsWith("/疯狂症状"))//疯狂症状
            {
                CLRDice.RD.CLRLongInsane(ref QQCLRMsg);
                发送消息(QQCLRMsg);
            }
            if (Message.StartsWith("/临时疯狂"))//临时疯狂
            {
                CLRDice.RD.CLRTempInsane(ref QQCLRMsg);
                发送消息(QQCLRMsg);
            }
        }



       public  string Dice(string Message)//不提供处理/r符号/复用性yes
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
                var t = SingleDice(numList[a].Value, ref I);
                ReturnMessage += a + 1 < numList.Count ? t + "+" : t;
            }
            return Message + "投出:" + ReturnMessage + "总值:" + I;
        }
       private  string SingleDice(string SingleMessage, ref int intValue)
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
                int Temp = Size >= 0 ? random.Next(0+1, Size+1) : random.Next(Size, 0);
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
