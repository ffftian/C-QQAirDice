using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Native.Csharp.App.EventArgs;
using Native.Csharp.App.Interface;
using System.IO;
using System.Linq;

namespace Native.Csharp.App.Event
{
    class FEvent_SavePlayMesagePro : IReceiveGroupMessage, IReceiveGroupPrivateMessage
    {
        static Dictionary<long, string> GroupMesageDict = new Dictionary<long, string>();//群号 文件地址
        static Dictionary<long, string> FriendMesageDict = new Dictionary<long, string>();//朋友 文件地址

        public void ReceiveGroupMessage(object sender, CqGroupMessageEventArgs e)
        {
            SaveGroupMesage(e);
        }
        public void ReceiveGroupPrivateMessage(object sender, CqPrivateMessageEventArgs e)
        {
            SaveReceiveGroupPrivateMessage(e);
        }



        public void SaveGroupMesage(CqGroupMessageEventArgs e)
        {
            string Message = e.Message;
            if (Message.StartsWith(".录入开始"))
            {
                try
                {
                    if (Message.Contains("/"))
                    {
                        // var SP = Message.Split('/')[1];
                        string filePath = AppDomain.CurrentDomain.BaseDirectory + Message.Split('/')[1] + ".txt";

                        GroupMesageDict.Add(e.FromGroup, filePath);
                        //   fs = new FileStream(path + SP[1]+".txt", FileMode.OpenOrCreate, FileAccess.Write);
                        //sw = new StreamWriter(fs); // 创建写入流
                        Common.CqApi.SendGroupMessage(e.FromGroup, "录入已开始");
                        Common.CqApi.SendGroupMessage(e.FromGroup, "当前path位置" + filePath);
                        Common.CqApi.SendGroupMessage(e.FromGroup, "当前保存群位置" + e.FromGroup);
                    }
                    else
                    {
                        Common.CqApi.SendGroupMessage(e.FromGroup, "未检测到/指令分割");
                    }
                }
                catch (Exception ee)
                {
                    Common.CqApi.SendGroupMessage(e.FromGroup, ee.ToString());
                }
            }
            if (GroupMesageDict.ContainsKey(e.FromGroup) == true)
            {
                if (!e.Message.StartsWith(".录入开始") && !e.Message.StartsWith(".录入结束"))
                {
                    string value;
                    GroupMesageDict.TryGetValue(e.FromGroup, out value);
                    //将待写的入数据从字符串转换为字节数组
                    var QQID = Common.CqApi.GetMemberInfo(e.FromGroup, e.FromQQ).Nick;
                   // var Time = 

                    Encoding encoder = Encoding.UTF8;
                    byte[] bytes = encoder.GetBytes(QQID + "\n" + e.Message + "\n");
                    FileStream fs = File.OpenWrite(value);
                    //设定书写的开始位置为文件的末尾  
                    fs.Position = fs.Length;
                    //将待写入内容追加到文件末尾  
                    fs.Write(bytes, 0, bytes.Length);
                    fs.Close();
                }
            }
            if (Message.StartsWith(".录入结束"))
            {
                try
                {
                    GroupMesageDict.Remove(e.FromGroup);
                    Common.CqApi.SendGroupMessage(e.FromGroup, "录入已结束");
                }
                catch (Exception ee)
                {
                    Common.CqApi.SendGroupMessage(e.FromGroup, ee.ToString());
                }
            }
        }
        public void SaveReceiveGroupPrivateMessage(CqPrivateMessageEventArgs e)
        {
            string Message = e.Message;
            if (Message.StartsWith(".录入开始"))
            {
                try
                {
                    if (Message.Contains("/"))
                    {
                        // var SP = Message.Split('/')[1];
                        string filePath = AppDomain.CurrentDomain.BaseDirectory + Message.Split('/')[1] + ".txt";

                        if (!FriendMesageDict.ContainsKey(e.FromQQ))
                        {
                            FriendMesageDict.Add(e.FromQQ, filePath);
                            //   fs = new FileStream(path + SP[1]+".txt", FileMode.OpenOrCreate, FileAccess.Write);
                            //sw = new StreamWriter(fs); // 创建写入流
                            Common.CqApi.SendPrivateMessage(e.FromQQ, "录入已开始");
                            Common.CqApi.SendPrivateMessage(e.FromQQ, "当前path位置" + filePath);
                        }
                        else
                        {
                            Common.CqApi.SendGroupMessage(e.FromQQ, "该地址已在录入");
                        }
                    }
                    else
                    {
                        Common.CqApi.SendGroupMessage(e.FromQQ, "未检测到/指令分割");
                    }
                }
                catch (Exception ee)
                {
                    Common.CqApi.SendGroupMessage(e.FromQQ, ee.ToString());
                }
            }
            if (FriendMesageDict.ContainsKey(e.FromQQ) == true)
            {
                if (!e.Message.StartsWith(".录入开始") && !e.Message.StartsWith(".录入结束"))
                {
                    string value;
                    FriendMesageDict.TryGetValue(e.FromQQ, out value);
                    //将待写的入数据从字符串转换为字节数组
                    // var QQID = Common.CqApi.GetMemberInfo(e.FromGroup, e.FromQQ).Nick;
                    var QQID = Common.CqApi.GetQQInfo(e.FromQQ).Nick;
                    var QQMemberID = Common.CqApi.GetMemberInfo(e.FromQQ, Common.CqApi.GetQQInfo(e.FromQQ).Id).Nick;


                    Encoding encoder = Encoding.UTF8;
                    byte[] bytes = encoder.GetBytes(QQID + QQMemberID== ""?"" :'('+ QQMemberID+')' + "\n" + e.Message + "\n");
                    FileStream fs = File.OpenWrite(value);
                    //设定书写的开始位置为文件的末尾  
                    fs.Position = fs.Length;
                    //将待写入内容追加到文件末尾  
                    fs.Write(bytes, 0, bytes.Length);
                    fs.Close();
                }
            }
            if (Message.StartsWith(".录入结束"))
            {
                try
                {
                    FriendMesageDict.Remove(e.FromQQ);
                    Common.CqApi.SendGroupMessage(e.FromQQ, "录入已结束");
                }
                catch (Exception ee)
                {
                    Common.CqApi.SendGroupMessage(e.FromQQ, ee.ToString());
                }
            }

        }


        public void Help(CqPrivateMessageEventArgs e)
        {

        }



    }
}

