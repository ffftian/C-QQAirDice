using Native.Csharp.App.EventArgs;
using Native.Csharp.App.Interface;

namespace Native.Csharp.App.Event
{
    public class Event_GroupMessage : IReceiveGroupMessage
    {
        public void ReceiveGroupMessage(object sender, CqGroupMessageEventArgs e)
        {
            // 将收到的消息发送给来源群, 营造复读机的效果
            Common.CqApi.SendGroupMessage(e.FromGroup, e.Message);
        }
    }
}
