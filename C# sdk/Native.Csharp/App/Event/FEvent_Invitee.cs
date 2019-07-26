using Native.Csharp.App.EventArgs;
using Native.Csharp.App.Interface;
using Native.Csharp.Sdk.Cqp.Enum;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Native.Csharp.App.Event
{
    public class FEvent_Invite : IReceiveAddGroupBeInvitee
    {
        public void ReceiveAddGroupBeInvitee(object sender, CqAddGroupRequestEventArgs e)
        {

            Common.CqApi.SetGroupAddRequest(e.ResponseFlag, RequestType.GroupInvitation, ResponseType.PASS, "丛雨已经通过申请");


        }
    }
}
