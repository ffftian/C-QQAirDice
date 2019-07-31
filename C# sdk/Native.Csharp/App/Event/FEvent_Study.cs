using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Native.Csharp.App.EventArgs;
using Native.Csharp.App.Interface;
using System.IO;
using System.Linq;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace Native.Csharp.App.Event
{
    class FEvent_Study : IReceiveGroupMessage
    {
        static public JObject JsonData;
        static string MeassgePath;


        static public void JsonDataInit()//整理
        {
            MeassgePath = AppDomain.CurrentDomain.BaseDirectory + ("Save/Meassge.json");
            if (File.Exists(MeassgePath))
            {
                StreamReader reader = File.OpenText(MeassgePath);
                    JsonData = (JObject)JToken.ReadFrom(new JsonTextReader(reader));
               
                reader.Close();
            }
            else
            {
                JsonData = new JObject();
            }
        }
        static public void JsonDataSave()
        {
            System.IO.Directory.CreateDirectory(AppDomain.CurrentDomain.BaseDirectory + ("Save"));
            File.WriteAllText(MeassgePath, JsonData.ToString());
        }

        public void ReceiveGroupMessage(object sender, CqGroupMessageEventArgs e)
        {
            回复群友话语(e);
            记录群友话语(e);
        }

        public void 记录群友话语(CqGroupMessageEventArgs e)
        {
           // string filePath = AppDomain.CurrentDomain.BaseDirectory + ("Meassge.json");
            if (e.Message.StartsWith("/录入话语"))
            {
                var S1 = e.Message.IndexOf("问:");
                var S2 = e.Message.IndexOf("答:");
                var S3 = e.Message.LastIndexOf(" ");


                if (S2 - S1 - 4 > -1)//处理只写问答暴毙
                {
                    var SP1 = e.Message.Substring(S1 + 2, S2 - S1-2);//切割问,获得问的话语//SP1是key
                    SP1 = SP1.Trim();



                    var SP2 = e.Message.Substring(S2 + 2);//sb2是答
                    SP2 = SP2.Trim();

                    if (JsonData.ContainsKey(SP1))
                    {
                        JsonData[SP1] = SP2;
                    }
                    else
                    {
                        JsonData.Add(SP1, SP2);
                    }
                    Common.CqApi.SendGroupMessage(e.FromGroup, "问:" + SP1 + "\n答:" + SP2 + "\n是吗?我明白了");
                }
                else
                {
                    Common.CqApi.SendGroupMessage(e.FromGroup, "命令不正确");
                }

            }

        }

        public void 回复群友话语(CqGroupMessageEventArgs e)
        {
            if (JsonData.ContainsKey(e.Message))
            {
                Common.CqApi.SendGroupMessage(e.FromGroup, JsonData[e.Message].ToString());
            }
        }
    }
}

