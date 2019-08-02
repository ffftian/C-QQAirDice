using Native.Csharp.App.EventArgs;
using Native.Csharp.App.Interface;
using System;
using System.Text.RegularExpressions;

namespace Native.Csharp.App.Event
{
    public class FEvent_Dice : IReceiveGroupMessage, IReceiveDiscussMessage, IReceiveALLPrivateMessage
    {
        delegate void VoidAction();
        FEvent_SavePlayMesagePro savePlayMesagePro = new FEvent_SavePlayMesagePro();//记录跑团pro版
        FEvent_Study fEvent_Study = new FEvent_Study();//记录傻吊群友说话
        FEvent_BlackList fEvent_BlackList = new FEvent_BlackList();//黑名单


        public void ReceiveGroupMessage(object sender, CqGroupMessageEventArgs e)
        {
            try
            {
                if (FEvent_BlackList.BlackData[e.FromQQ.ToString()] != null)
                {
                    return;
                }
                MsgProcess msg = new MsgProcess(e.Message, e.FromQQ, e.FromGroup, msgtype.Group);
                //savePlayMesagePro.ReceiveGroupMessage(sender, e);
                //fEvent_Study.ReceiveGroupMessage(sender, e);
                //fEvent_BlackList.ReceiveGroupMessage(sender, e);
            }
            catch(Exception exception)
            {
                Common.CqApi.SendPrivateMessage(790947404, exception.Message);
            }

        }
        public void ReceiveALLPrivateMessage(object sender, CqPrivateMessageEventArgs e)
        {
            if (FEvent_BlackList.BlackData[e.FromQQ.ToString()] != null)
            {
                return;
            }
            MsgProcess msg = new MsgProcess(e.Message, e.FromQQ, msgtype.Private);
        }

        public void ReceiveDiscussMessage(object sender, CqDiscussMessageEventArgs e)
        {
            MsgProcess msg = new MsgProcess(e.Message,e.FromQQ, e.FromDiscuss, msgtype.Discuss);
        }

        /*
        public void ReceiveGroupPrivateMessage(object sender, CqPrivateMessageEventArgs e)
        {
            FEventMsgProcess msg = new FEventMsgProcess(e.Message, e.FromQQ, msgtype.Private);
            //savePlayMesagePro.ReceiveGroupPrivateMessage(sender, e);
        }

        public void ReceiveFriendMessage(object sender, CqPrivateMessageEventArgs e)
        {
//            Common.CqApi.SendPrivateMessage(790947404, e.Message);


            FEventMsgProcess msg = new FEventMsgProcess(e.Message, e.FromQQ, msgtype.Private);
        }
        */

        //public void ReceiveOnlineStatusMessage(object sender, CqPrivateMessageEventArgs e)
        //{
        //    FEventMsgProcess msg = new FEventMsgProcess(e.Message, e.FromQQ, msgtype.Private);
        //}



        //public void ReceiveGroupPrivateMessage(object sender, CqPrivateMessageEventArgs e)
        //{
        //    FEventMsgProcess msg = new FEventMsgProcess(e.Message, e.FromQQ, msgtype.Private);
        //}
    }
}

