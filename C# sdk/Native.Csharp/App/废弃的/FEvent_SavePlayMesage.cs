using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Native.Csharp.App.EventArgs;
using Native.Csharp.App.Interface;
using System.IO;

namespace Native.Csharp.App.Event
{



    class FEvent_SavePlayMesage : IReceiveGroupMessage
    {
         bool 录入 = false;
        // string FileName;//文件名称
         long FromGroup;//读取的群
         string filePath;//当前开启文件

        public void ReceiveGroupMessage(object sender, CqGroupMessageEventArgs e)
        {
            SaveMesage(e);
        }

        //开始录入，录入文本名称
        public void SaveMesage(CqGroupMessageEventArgs e)
        {
            string Message = e.Message;
            if (Message.StartsWith(".录入开始")&& 录入==false)
            {
                try
                { 
                    if (Message.Contains("/"))
                    {
                        var SP = Message.Split('/');
                        FromGroup = e.FromGroup;
                        录入 = true;
                        filePath = AppDomain.CurrentDomain.BaseDirectory+SP[1] + ".txt";
                        //   fs = new FileStream(path + SP[1]+".txt", FileMode.OpenOrCreate, FileAccess.Write);
                        //sw = new StreamWriter(fs); // 创建写入流
                        Common.CqApi.SendGroupMessage(e.FromGroup, "录入已开始");
                        Common.CqApi.SendGroupMessage(e.FromGroup, "当前path位置" + filePath);
                        Common.CqApi.SendGroupMessage(e.FromGroup, "当前保存群位置" + FromGroup);
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
           // Common.CqApi.SendGroupMessage(e.FromGroup, "当前群位置" + e.FromGroup);
           // Common.CqApi.SendGroupMessage(e.FromGroup, "当前保存的群位置" + FromGroup);
            if (录入 == true && FromGroup == e.FromGroup)
            {
                if (!e.Message.StartsWith(".录入开始")&& !e.Message.StartsWith(".录入结束"))
                {
                   // Common.CqApi.SendGroupMessage(e.FromGroup,"当前path位置"+ filePath);
                    var QQID = Common.CqApi.GetMemberInfo(e.FromGroup, e.FromQQ).Nick;
                   // sw.Write(QQID + "\n");
                   // sw.Write(e.Message + "\n"); // 写入Hello World

                    //将待写的入数据从字符串转换为字节数组  
                    Encoding encoder = Encoding.UTF8;
                    byte[] bytes = encoder.GetBytes(QQID+ "\n"+e.Message+ "\n");
                    FileStream fs = File.OpenWrite(filePath);
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
                     录入 = false;
                  //  sw.Close();
                    //fs.Dispose();

                    Common.CqApi.SendGroupMessage(e.FromGroup, "录入已结束");
                }
                catch(Exception ee)
                {
                    Common.CqApi.SendGroupMessage(e.FromGroup, ee.ToString());
                }
                // goto loop;
            }
        }


    }
}
