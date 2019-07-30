using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Native.Csharp.App.Event
{
   static class DiceRamdom
    {
       public static Random random = new Random(DateTime.Now.Day+DateTime.Now.Minute+DateTime.Now.Millisecond);


    }
}
