/*
 *  _______     ________    ________    ________    __
 * |   __  \   |__    __|  |   _____|  |   _____|  |  |
 * |  |  |  |     |  |     |  |        |  |_____   |  |
 * |  |  |  |     |  |     |  |        |   _____|  |__|
 * |  |__|  |   __|  |__   |  |_____   |  |_____    __
 * |_______/   |________|  |________|  |________|  |__|
 *
 * Dice! QQ Dice Robot for TRPG
 * Copyright (C) 2018 w4123���
 *
 * This program is free software: you can redistribute it and/or modify it under the terms
 * of the GNU Affero General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License along with this
 * program. If not, see <http://www.gnu.org/licenses/>.
 */
//#include "CQEVE_ALL.h"
//#include "CQTools.h"
#include <cctype>
#include <sstream>
#include "RD.h"
#include "RDConstant.h"
using namespace std;
//using namespace CQ;
/*
inline void init(string& msg)
{
	msg_decode(msg);
}
*/
inline void init2(string& msg)
{
	for (int i = 0; i != msg.length(); i++)
	{
		if (msg[i] < 0)
		{
			if ((msg[i] & 0xff) == 0xa1 && (msg[i + 1] & 0xff) == 0xa1)
			{
				msg[i] = 0x20;
				msg.erase(msg.begin() + i + 1);
			}
			else if ((msg[i] & 0xff) == 0xa3 && (msg[i + 1] & 0xff) >= 0xa1 && (msg[i + 1] & 0xff) <= 0xfe)
			{
				msg[i] = msg[i + 1] - 0x80;
				msg.erase(msg.begin() + i + 1);
			}
			else
			{
				i++;
			}
		}
	}

	while (isspace(static_cast<unsigned char>(msg[0])))
		msg.erase(msg.begin());
	while (!msg.empty() && isspace(static_cast<unsigned char>(msg[msg.length() - 1])))
		msg.erase(msg.end() - 1);
	if (msg.substr(0, 2) == "��")
	{
		msg.erase(msg.begin());
		msg[0] = '.';
	}
	if (msg[0] == '!')
		msg[0] = '.';
}

 inline void COC7D(string& strMAns)
{
	RD rd3D6("3D6");
	RD rd2D6p6("2D6+6");
	strMAns += "����������:";
	strMAns += '\n';
	strMAns += "����STR=3D6*5=";
	rd3D6.Roll();
	const int STR = rd3D6.intTotal * 5;

	strMAns += to_string(STR) + "/" + to_string(STR / 2) + "/" + to_string(STR / 5);
	strMAns += '\n';
	strMAns += "����CON=3D6*5=";
	rd3D6.Roll();
	const int CON = rd3D6.intTotal * 5;

	strMAns += to_string(CON) + "/" + to_string(CON / 2) + "/" + to_string(CON / 5);
	strMAns += '\n';
	strMAns += "����SIZ=(2D6+6)*5=";
	rd2D6p6.Roll();
	const int SIZ = rd2D6p6.intTotal * 5;

	strMAns += to_string(SIZ) + "/" + to_string(SIZ / 2) + "/" + to_string(SIZ / 5);
	strMAns += '\n';
	strMAns += "����DEX=3D6*5=";
	rd3D6.Roll();
	const int DEX = rd3D6.intTotal * 5;

	strMAns += to_string(DEX) + "/" + to_string(DEX / 2) + "/" + to_string(DEX / 5);
	strMAns += '\n';
	strMAns += "��òAPP=3D6*5=";
	rd3D6.Roll();
	const int APP = rd3D6.intTotal * 5;

	strMAns += to_string(APP) + "/" + to_string(APP / 2) + "/" + to_string(APP / 5);
	strMAns += '\n';
	strMAns += "����INT=(2D6+6)*5=";
	rd2D6p6.Roll();
	const int INT = rd2D6p6.intTotal * 5;

	strMAns += to_string(INT) + "/" + to_string(INT / 2) + "/" + to_string(INT / 5);
	strMAns += '\n';
	strMAns += "��־POW=3D6*5=";
	rd3D6.Roll();
	const int POW = rd3D6.intTotal * 5;

	strMAns += to_string(POW) + "/" + to_string(POW / 2) + "/" + to_string(POW / 5);
	strMAns += '\n';
	strMAns += "����EDU=(2D6+6)*5=";
	rd2D6p6.Roll();
	const int EDU = rd2D6p6.intTotal * 5;

	strMAns += to_string(EDU) + "/" + to_string(EDU / 2) + "/" + to_string(EDU / 5);
	strMAns += '\n';
	strMAns += "����LUCK=3D6*5=";
	rd3D6.Roll();
	const int LUCK = rd3D6.intTotal * 5;
	strMAns += to_string(LUCK);

	strMAns += '\n';
	strMAns += "����:" + to_string(STR + CON + SIZ + APP + POW + EDU + DEX + INT + LUCK);

	strMAns += "\n����SAN=POW=";
	const int SAN = POW;
	strMAns += to_string(SAN);
	strMAns += "\n����ֵHP=(SIZ+CON)/10=";
	const int HP = (SIZ + CON) / 10;
	strMAns += to_string(HP);
	strMAns += "\nħ��ֵMP=POW/5=";
	const int MP = POW / 5;
	strMAns += to_string(MP);
	string DB;
	int build;
	if (STR + SIZ >= 2 && STR + SIZ <= 64)
	{
		DB = "-2";
		build = -2;
	}
	else if (STR + SIZ >= 65 && STR + SIZ <= 84)
	{
		DB = "-1";
		build = -1;
	}
	else if (STR + SIZ >= 85 && STR + SIZ <= 124)
	{
		DB = "0";
		build = 0;
	}
	else if (STR + SIZ >= 125 && STR + SIZ <= 164)
	{
		DB = "1D4";
		build = 1;
	}
	else if (STR + SIZ >= 165 && STR + SIZ <= 204)
	{
		DB = "1d6";
		build = 2;
	}
	else
	{
		DB = "�������!";
		build = -10;
	}
	strMAns += "\n�˺�����DB=" + DB + "\n���=" + (build == -10 ? "�������" : to_string(build));
	int MOV;
	if (DEX < SIZ && STR < SIZ)
		MOV = 7;
	else if (DEX > SIZ && STR > SIZ)
		MOV = 9;
	else
		MOV = 8;
	strMAns += "\n�ƶ���MOV=" + to_string(MOV);
}

 inline void COC6D(string& strMAns)
{
	RD rd3D6("3D6");
	RD rd2D6p6("2D6+6");
	RD rd3D6p3("3D6+3");
	strMAns += "����������:";
	strMAns += '\n';
	strMAns += "����STR=3D6=";
	rd3D6.Roll();
	const int STR = rd3D6.intTotal;

	strMAns += to_string(STR);
	strMAns += '\n';
	strMAns += "����CON=3D6=";
	rd3D6.Roll();
	const int CON = rd3D6.intTotal;

	strMAns += to_string(CON);
	strMAns += '\n';
	strMAns += "����SIZ=2D6+6=";
	rd2D6p6.Roll();
	const int SIZ = rd2D6p6.intTotal;

	strMAns += to_string(SIZ);
	strMAns += '\n';
	strMAns += "����DEX=3D6=";
	rd3D6.Roll();
	const int DEX = rd3D6.intTotal;

	strMAns += to_string(DEX);
	strMAns += '\n';
	strMAns += "��òAPP=3D6=";
	rd3D6.Roll();
	const int APP = rd3D6.intTotal;

	strMAns += to_string(APP);
	strMAns += '\n';
	strMAns += "����INT=2D6+6=";
	rd2D6p6.Roll();
	const int INT = rd2D6p6.intTotal;

	strMAns += to_string(INT);
	strMAns += '\n';
	strMAns += "��־POW=3D6=";
	rd3D6.Roll();
	const int POW = rd3D6.intTotal;

	strMAns += to_string(POW);
	strMAns += '\n';
	strMAns += "����EDU=3D6+3=";
	rd3D6p3.Roll();
	const int EDU = rd3D6p3.intTotal;

	strMAns += to_string(EDU);
	strMAns += '\n';
	strMAns += "����:" + to_string(STR + CON + SIZ + APP + POW + EDU + DEX + INT);
	const int SAN = POW * 5;
	const int IDEA = INT * 5;
	const int LUCK = POW * 5;
	const int KNOW = EDU * 5;
	const int HP = static_cast<int>(ceil(static_cast<double>(CON + SIZ) / 2.0));
	const int MP = POW;
	strMAns += "\n����SAN=POW*5=" + to_string(SAN) + "\n���IDEA=INT*5=" + to_string(IDEA) + "\n����LUCK=POW*5=" +
		to_string(LUCK) + "\n֪ʶKNOW=EDU*5=" + to_string(KNOW);
	strMAns += "\n����ֵHP=(CON+SIZ)/2=" + to_string(HP) + "\nħ��ֵMP=POW=" + to_string(MP);
	strMAns += "\n�˺�����DB=";
	string DB;
	if (STR + SIZ >= 2 && STR + SIZ <= 12)
	{
		DB = "-1D6";
	}
	else if (STR + SIZ >= 13 && STR + SIZ <= 16)
	{
		DB = "-1D4";
	}
	else if (STR + SIZ >= 17 && STR + SIZ <= 24)
	{
		DB = "0";
	}
	else if (STR + SIZ >= 25 && STR + SIZ <= 32)
	{
		DB = "1D4";
	}
	else if (STR + SIZ >= 33 && STR + SIZ <= 40)
	{
		DB = "1D6";
	}
	else
	{
		DB = "�������!";
	}
	strMAns += DB;
}

 inline void COC7(string& strMAns, int intNum)
{
	strMAns += "����������:";
	string strProperty[] = {"����", "����", "����", "����", "��ò", "����", "��־", "����", "����"};
	string strRoll[] = {"3D6", "3D6", "2D6+6", "3D6", "3D6", "2D6+6", "3D6", "2D6+6", "3D6"};
	int intAllTotal = 0;
	while (intNum--)
	{
		strMAns += '\n';
		for (int i = 0; i != 9; i++)
		{
			RD rdCOC(strRoll[i]);
			rdCOC.Roll();
			strMAns += strProperty[i] + ":" + to_string(rdCOC.intTotal * 5) + " ";
			intAllTotal += rdCOC.intTotal * 5;
		}
		strMAns += "����:" + to_string(intAllTotal);
		intAllTotal = 0;
	}
}

 inline void COC6(string& strMAns, int intNum)
{
	strMAns += "����������:";
	string strProperty[] = {"����", "����", "����", "����", "��ò", "����", "��־", "����"};
	string strRoll[] = {"3D6", "3D6", "2D6+6", "3D6", "3D6", "2D6+6", "3D6", "3D6+3"};
	const bool boolAddSpace = intNum != 1;
	int intAllTotal = 0;
	while (intNum--)
	{
		strMAns += '\n';
		for (int i = 0; i != 8; i++)
		{
			RD rdCOC(strRoll[i]);
			rdCOC.Roll();
			strMAns += strProperty[i] + ":" + to_string(rdCOC.intTotal) + " ";
			if (boolAddSpace && rdCOC.intTotal < 10)
				strMAns += "  ";
			intAllTotal += rdCOC.intTotal;
		}
		strMAns += "����:" + to_string(intAllTotal);
		intAllTotal = 0;
	}
}

  inline void DND(string& strOutput, int intNum)
{
	strOutput += "��Ӣ������:";
	RD rdDND("4D6K3");
	string strDNDName[6] = {"����", "����", "����", "����", "��֪", "����"};
	const bool boolAddSpace = intNum != 1;
	int intAllTotal = 0;
	while (intNum--)
	{
		strOutput += "\n";
		for (int i = 0; i <= 5; i++)
		{
			rdDND.Roll();
			strOutput += strDNDName[i] + ":" + to_string(rdDND.intTotal) + " ";
			if (rdDND.intTotal < 10 && boolAddSpace)
				strOutput += "  ";
			intAllTotal += rdDND.intTotal;
		}
		strOutput += "����:" + to_string(intAllTotal);
		intAllTotal = 0;
	}
}

 inline void TempInsane(string& strAns)
{
	const int intSymRes = Randint(1, 10);
	std::string strTI = "1D10=" + to_string(intSymRes) + "\n֢״: " + TempInsanity[intSymRes];
	if (intSymRes == 9)
	{
		const int intDetailSymRes = Randint(1, 100);
		strTI = format(strTI, {
			"1D10=" + to_string(Randint(1, 10)), "1D100=" + to_string(intDetailSymRes), strFear[intDetailSymRes]
		});
	}
	else if (intSymRes == 10)
	{
		const int intDetailSymRes = Randint(1, 100);
		strTI = format(strTI, {
			"1D10=" + to_string(Randint(1, 10)), "1D100=" + to_string(intDetailSymRes), strPanic[intDetailSymRes]
		});
	}
	else
	{
		strTI = format(strTI, {"1D10=" + to_string(Randint(1, 10))});
	}
	strAns += strTI;
}

 inline void LongInsane(string& strAns)
{
	const int intSymRes = Randint(1, 10);
	std::string strLI = "1D10=" + to_string(intSymRes) + "\n֢״: " + LongInsanity[intSymRes];
	if (intSymRes == 9)
	{
		const int intDetailSymRes = Randint(1, 100);
		strLI = format(strLI, {
			"1D10=" + to_string(Randint(1, 10)), "1D100=" + to_string(intDetailSymRes), strFear[intDetailSymRes]
		});
	}
	else if (intSymRes == 10)
	{
		const int intDetailSymRes = Randint(1, 100);
		strLI = format(strLI, {
			"1D10=" + to_string(Randint(1, 10)), "1D100=" + to_string(intDetailSymRes), strPanic[intDetailSymRes]
		});
	}
	else
	{
		strLI = format(strLI, {"1D10=" + to_string(Randint(1, 10))});
	}
	strAns += strLI;
}

  inline void RD::COC7D(std::string &strMAns)
{
	RD rd3D6("3D6");
	RD rd2D6p6("2D6+6");
	strMAns += "����������:";
	strMAns += '\n';
	strMAns += "����STR=3D6*5=";
	rd3D6.Roll();
	const int STR = rd3D6.intTotal * 5;

	strMAns += to_string(STR) + "/" + to_string(STR / 2) + "/" + to_string(STR / 5);
	strMAns += '\n';
	strMAns += "����CON=3D6*5=";
	rd3D6.Roll();
	const int CON = rd3D6.intTotal * 5;

	strMAns += to_string(CON) + "/" + to_string(CON / 2) + "/" + to_string(CON / 5);
	strMAns += '\n';
	strMAns += "����SIZ=(2D6+6)*5=";
	rd2D6p6.Roll();
	const int SIZ = rd2D6p6.intTotal * 5;

	strMAns += to_string(SIZ) + "/" + to_string(SIZ / 2) + "/" + to_string(SIZ / 5);
	strMAns += '\n';
	strMAns += "����DEX=3D6*5=";
	rd3D6.Roll();
	const int DEX = rd3D6.intTotal * 5;

	strMAns += to_string(DEX) + "/" + to_string(DEX / 2) + "/" + to_string(DEX / 5);
	strMAns += '\n';
	strMAns += "��òAPP=3D6*5=";
	rd3D6.Roll();
	const int APP = rd3D6.intTotal * 5;

	strMAns += to_string(APP) + "/" + to_string(APP / 2) + "/" + to_string(APP / 5);
	strMAns += '\n';
	strMAns += "����INT=(2D6+6)*5=";
	rd2D6p6.Roll();
	const int INT = rd2D6p6.intTotal * 5;

	strMAns += to_string(INT) + "/" + to_string(INT / 2) + "/" + to_string(INT / 5);
	strMAns += '\n';
	strMAns += "��־POW=3D6*5=";
	rd3D6.Roll();
	const int POW = rd3D6.intTotal * 5;

	strMAns += to_string(POW) + "/" + to_string(POW / 2) + "/" + to_string(POW / 5);
	strMAns += '\n';
	strMAns += "����EDU=(2D6+6)*5=";
	rd2D6p6.Roll();
	const int EDU = rd2D6p6.intTotal * 5;

	strMAns += to_string(EDU) + "/" + to_string(EDU / 2) + "/" + to_string(EDU / 5);
	strMAns += '\n';
	strMAns += "����LUCK=3D6*5=";
	rd3D6.Roll();
	const int LUCK = rd3D6.intTotal * 5;
	strMAns += to_string(LUCK);

	strMAns += '\n';
	strMAns += "����:" + to_string(STR + CON + SIZ + APP + POW + EDU + DEX + INT + LUCK);

	strMAns += "\n����SAN=POW=";
	const int SAN = POW;
	strMAns += to_string(SAN);
	strMAns += "\n����ֵHP=(SIZ+CON)/10=";
	const int HP = (SIZ + CON) / 10;
	strMAns += to_string(HP);
	strMAns += "\nħ��ֵMP=POW/5=";
	const int MP = POW / 5;
	strMAns += to_string(MP);
	string DB;
	int build;
	if (STR + SIZ >= 2 && STR + SIZ <= 64)
	{
		DB = "-2";
		build = -2;
	}
	else if (STR + SIZ >= 65 && STR + SIZ <= 84)
	{
		DB = "-1";
		build = -1;
	}
	else if (STR + SIZ >= 85 && STR + SIZ <= 124)
	{
		DB = "0";
		build = 0;
	}
	else if (STR + SIZ >= 125 && STR + SIZ <= 164)
	{
		DB = "1D4";
		build = 1;
	}
	else if (STR + SIZ >= 165 && STR + SIZ <= 204)
	{
		DB = "1d6";
		build = 2;
	}
	else
	{
		DB = "�������!";
		build = -10;
	}
	strMAns += "\n�˺�����DB=" + DB + "\n���=" + (build == -10 ? "�������" : to_string(build));
	int MOV;
	if (DEX < SIZ && STR < SIZ)
		MOV = 7;
	else if (DEX > SIZ && STR > SIZ)
		MOV = 9;
	else
		MOV = 8;
	strMAns += "\n�ƶ���MOV=" + to_string(MOV);
}

  string *RD::GGGB(std::string * stg)
{
	  *stg = "114514";

	return stg;
}
  string RD :: VV()
  {
	  return "11111";
  }

  namespace CLRDice
  {
	  static public ref class RD
	  {
	  private:
		 static void MarshalString(String ^s, string& os) {
			  using namespace Runtime::InteropServices;
			  const char* chars =
				  (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			  os = chars;
			  Marshal::FreeHGlobal(IntPtr((void*)chars));
		  }
	  public:
		 static void  CLRCOC7(String ^%NetS, int Number)
		  {
			  string Cstring;
			  MarshalString(NetS, Cstring);
			  COC7(Cstring, Number);
			  NetS = gcnew String(Cstring.c_str());
		  }
		 static void  CLRCOC7D(String ^%NetS)
		 {
			 string Cstring;
			 MarshalString(NetS, Cstring);
			 COC7D(Cstring);
			 NetS = gcnew String(Cstring.c_str());
		 }
		 static void CLRDND(String ^%NetS, int Number)
		 {
			 string Cstring;
			 MarshalString(NetS, Cstring);
			 DND(Cstring, Number);
			 NetS = gcnew String(Cstring.c_str());
		 }
		 static void CLRLongInsane(String ^%NetS)
		 {
			 string Cstring;
			 MarshalString(NetS, Cstring);
			 LongInsane(Cstring);
			 NetS = gcnew String(Cstring.c_str());
		 }
		 static void CLRTempInsane(String ^%NetS)
		 {
			 string Cstring;
			 MarshalString(NetS, Cstring);
			 TempInsane(Cstring);
			 NetS = gcnew String(Cstring.c_str());
		 }
	  };
  }

  /*
	  void  CLRTemp(String ^% NetS)
	  {

		  // std::string str = "Hello";

		 // string Cstring = new char[NetS->Length];

		  //MarshalString(NetS, Cstring);

		  //COC7(Cstring, Number);


		  string a = new char[1000];
		  nei(a);
		  NetS = gcnew String(a.c_str());

	  }
	   void nei(string &cS)
	  {
		   cS = "11145141";

	  }
	  */
/*
inline std::string RD::Text(std::string *stg)
{
	*stg = "2356";
	return *stg;
}
*/


