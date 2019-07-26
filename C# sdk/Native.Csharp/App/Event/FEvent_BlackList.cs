//using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Native.Csharp.App.EventArgs;
using Native.Csharp.App.Interface;
using System.IO;
using System.Linq;
using Native.Csharp.Sdk.Cqp.Enum;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;

namespace Native.Csharp.App.Event
{
   public class FEvent_BlackList : IReceiveGroupMessage
    {
        public  static JObject BlackData;
        static string dataPath;
        //JArray jArray;
        static public void JsonDataInit()
        {
            dataPath = AppDomain.CurrentDomain.BaseDirectory + ("BlackList.json");
            StreamReader reader = File.OpenText(dataPath);
            try
            {
                BlackData = (JObject)JToken.ReadFrom(new JsonTextReader(reader));
            }
            catch
            {
                BlackData = new JObject();
            }
            reader.Close();
        }
        static public void JsonDataSave()
        {
            File.WriteAllText(dataPath, BlackData.ToString());
        }



        public void ReceiveGroupMessage(object sender, CqGroupMessageEventArgs e)
        {
            AddBlack(e);



        }
        public void AddBlack(CqGroupMessageEventArgs e)
        {
            if (e.Message.StartsWith(".黑名单"))
            {
                if (Common.CqApi.GetMemberInfo(e.FromGroup, e.FromQQ).PermitType == PermitType.Holder)
                {

                    if (e.Message.Contains("/"))
                    {
                        var QQ = e.Message.Split('/')[1];


                        if (Common.CqApi.GetMemberInfo(e.FromGroup, long.Parse(QQ)) != null)
                        {
                            BlackData.Add(e.Message.Split('/')[1], "");
                            Common.CqApi.SendGroupMessage(e.FromGroup, "已将:" + Common.CqApi.GetMemberInfo(e.FromGroup, long.Parse(QQ)).Nick + "加入黑名单");
                        }
                        else
                        {
                            Common.CqApi.SendGroupMessage(e.FromGroup, "查无此人");
                        }
                        //   Common.CqApi.SendGroupMessage(e.FromGroup, "已获取/");

                    }
                }
                else
                {
                    Common.CqApi.SendGroupMessage(e.FromGroup, "不,我不听你的话，我不贴");
                }
                //   Common.CqApi.SendGroupMessage(e.FromGroup, "已获取群主");
            }
        }
           // Common.CqApi.SendGroupMessage(e.FromGroup, Common.CqApi.GetMemberInfo(e.FromGroup, e.FromQQ).PermitType.ToString());

        } 
        
    }

