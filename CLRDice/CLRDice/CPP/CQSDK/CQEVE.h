/*
CoolQ SDK for VS2017
Api Version 9.10
Written by MukiPy2001 & Thanks for the help of orzFly and Coxxs
*/
#pragma once
#ifdef _MSC_VER
#define CQEVENT(ReturnType, Name, Size) __pragma(comment(linker, "/EXPORT:" #Name "=_" #Name "@" #Size))\
	extern "C" __declspec(dllexport) ReturnType __stdcall Name
#else
#define CQEVENT(ReturnType, Name, Size)\
	extern "C" __attribute__((dllexport)) ReturnType __attribute__((__stdcall__)) Name
#endif /*_MSC_VER*/
/*
����Ӧ�õ�ApiVer��Appid������󽫲������
*/
#define MUST_AppInfo CQEVENT(const char*, AppInfo, 0)()

/*
����Ӧ�õ�ApiVer��Appid������󽫲������
*/
#define MUST_AppInfo_RETURN(CQAPPID) MUST_AppInfo{return CQAPIVERTEXT "," CQAPPID;}

/*
������ʧЧ,��ʹ�� getAuthCode(); ֱ�ӻ�ȡ, �˺�����CQAPI.h��

Ӧ��AuthCode����

�뱣�� AuthCode ,��ֵ�ǵ���CQAPI��ƾ֤

�벻Ҫ�ڱ����������������
*/
//#define MUST_Initialize CQEVENT(int, Initialize, 4)(int AuthCode)


///////////////////////////////// �¼� ������� /////////////////////////////////
//extern "C" __declspec(dllexport) void __stdcall Int32(int a){}//@4
//extern "C" __declspec(dllexport) void __stdcall Char(const char* a){}//@4
//extern "C" __declspec(dllexport) void __stdcall Int64(long long a){}//@8

/*
��Q����(Type=1001)

���ӳ�����ڿ�Q�����̡߳��б����á�
���۱�Ӧ���Ƿ����ã������������ڿ�Q������ִ��һ�Σ���������ִ�в����ʼ�����롣
����ؾ��췵�ر��ӳ��򣬷���Ῠס��������Լ�������ļ��ء�
��̶����� 0

�������ʹ���»��߿�ͷ��Ҫ�ĳ�˫�»���
*/
#define EVE_Startup(Name) CQEVENT(int, Name, 0)()

/*
��Q�˳�(Type=1002)

���ӳ�����ڿ�Q�����̡߳��б����á�
���۱�Ӧ���Ƿ����ã������������ڿ�Q�˳�ǰִ��һ�Σ���������ִ�в���رմ��롣
������������Ϻ󣬿�Q���ܿ�رգ��벻Ҫ��ͨ���̵߳ȷ�ʽִ����������

�������ʹ���»��߿�ͷ��Ҫ�ĳ�˫�»���
���ط���ֵ,��Ϣ��������,������Ȳ�������
*/
#define EVE_Exit(Name) CQEVENT(int, Name, 0)()

/*
Ӧ���ѱ�����(Type=1003)

��Ӧ�ñ����ú󣬽��յ����¼���
�����Q����ʱӦ���ѱ����ã����� EVE_Startup(Type=1001,��Q����) �����ú󣬱�����Ҳ��������һ�Ρ�
��Ǳ�Ҫ����������������ش��ڡ���������Ӳ˵������û��ֶ��򿪴��ڣ�

�������ʹ���»��߿�ͷ��Ҫ�ĳ�˫�»���
���ط���ֵ,��Ϣ��������,������Ȳ�������
*/
#define EVE_Enable(Name) CQEVENT(int, Name, 0)()

/*
Ӧ�ý���ͣ��(Type=1004)

��Ӧ�ñ�ͣ��ǰ�����յ����¼���
�����Q����ʱӦ���ѱ�ͣ�ã��򱾺��������᡿�����á�
���۱�Ӧ���Ƿ����ã���Q�ر�ǰ�������������᡿�����á�

�������ʹ���»��߿�ͷ��Ҫ�ĳ�˫�»���
���ط���ֵ,��Ϣ��������,������Ȳ�������
*/
#define EVE_Disable(Name) CQEVENT(int, Name, 0)()

/*
˽����Ϣ(Type=21)

�˺����������²���
subType		�����ͣ�11/���Ժ��� 1/��������״̬ 2/����Ⱥ 3/����������
msgId		��ϢID
fromQQ		��ԴQQ
msg			��Ϣ����
font		����

���ӳ�����ڿ�Q���̡߳��б����ã���ע��ʹ�ö������Ҫ��ʼ��(CoInitialize,CoUninitialize)
�������ʹ���»��߿�ͷ��Ҫ�ĳ�˫�»���
���ط���ֵ,��Ϣ��������,������Ȳ�������
*/
#define EVE_PrivateMsg(Name) CQEVENT(int, Name, 24)(int subType, int msgId, long long fromQQ, const char* msg, int font)

/*
Ⱥ��Ϣ(Type=2)

subType		�����ͣ�Ŀǰ�̶�Ϊ1
msgId		��ϢID
fromGroup	��ԴȺ��
fromQQ		��ԴQQ��
fromAnonymous ��Դ������
msg			��Ϣ����
font		����

�����Ϣ����������,fromQQ �̶�Ϊ 80000000,��ʹ�ù��߽� fromAnonymous ת��Ϊ ��������Ϣ

���ӳ�����ڿ�Q���̡߳��б����ã���ע��ʹ�ö������Ҫ��ʼ��(CoInitialize,CoUninitialize)
�������ʹ���»��߿�ͷ��Ҫ�ĳ�˫�»���
���ط���ֵ,��Ϣ��������,������Ȳ�������
*/
#define EVE_GroupMsg(Name) CQEVENT(int, Name, 36)(int subType, int msgId, long long fromGroup, long long fromQQ, const char* fromAnonymous, const char* msg, int font)

/*
��������Ϣ(Type=4)

subtype		�����ͣ�Ŀǰ�̶�Ϊ1
msgId		��ϢID
fromDiscuss	��Դ������
fromQQ		��ԴQQ��
msg			��Ϣ����
font		����

���ӳ�����ڿ�Q���̡߳��б����ã���ע��ʹ�ö������Ҫ��ʼ��(CoInitialize,CoUninitialize)
�������ʹ���»��߿�ͷ��Ҫ�ĳ�˫�»���
���ط���ֵ,��Ϣ��������,������Ȳ�������
*/
#define EVE_DiscussMsg(Name) CQEVENT(int, Name, 32)(int subType, int msgId, long long fromDiscuss, long long fromQQ, const char* msg, int font)

/*
Ⱥ�ļ��ϴ��¼�(Type=11)

subType �����ͣ�Ŀǰ�̶�Ϊ1
sendTime ����ʱ��(ʱ���)
fromGroup ��ԴȺ��
fromQQ ��ԴQQ��
file �ϴ��ļ���Ϣ,ʹ�� <����_ת��_�ı���Ⱥ�ļ�> ��������ת��Ϊ��Ч����,���༭

���ӳ�����ڿ�Q���̡߳��б����ã���ע��ʹ�ö������Ҫ��ʼ��(CoInitialize,CoUninitialize)
�������ʹ���»��߿�ͷ��Ҫ�ĳ�˫�»���
���ط���ֵ,��Ϣ��������,������Ȳ�������
*/
#define EVE_GroupUpload(Name) CQEVENT(int, Name, 28)(int subType, int sendTime, long long fromGroup,long long fromQQ, const char* file)
/*��ǿ�İ汾,������
#define EVE_GroupUpload_EX(Name) CQEVENT(int, Name, 28)(int subType, int sendTime, long long fromGroup,long long fromQQ, const char* file)\
{\
int Name(int subType, int sendTime, long long fromGroup,long long fromQQ, File file);\
return Name(subType,sendTime,fromGroup,fromQQ,ToFile(file));\
}\
int Name(int subType, int sendTime, long long fromGroup,long long fromQQ, File file)
*/

/*
Ⱥ�¼�-����Ա�䶯(Type=101)

subtype			�����ͣ�1/��ȡ������Ա 2/�����ù���Ա
sendTime ����ʱ��(ʱ���)
fromGroup		��ԴȺ��
beingOperateQQ	������QQ

���ӳ�����ڿ�Q���̡߳��б����ã���ע��ʹ�ö������Ҫ��ʼ��(CoInitialize,CoUninitialize)
�������ʹ���»��߿�ͷ��Ҫ�ĳ�˫�»���
���ط���ֵ,��Ϣ��������,������Ȳ�������
*/
#define EVE_System_GroupAdmin(Name) CQEVENT(int, Name, 24)(int subType, int msgId, long long fromGroup, long long beingOperateQQ)

/*
Ⱥ�¼�-Ⱥ��Ա����(Type=102)

subtype		�����ͣ�1/ȺԱ�뿪 2/ȺԱ���� 3/�Լ�(����¼��)����
sendTime ����ʱ��(ʱ���)
fromGroup	��ԴȺ��
fromQQ		������QQ(��������Ϊ2��3ʱ����)
beingOperateQQ ������QQ

���ӳ�����ڿ�Q���̡߳��б����ã���ע��ʹ�ö������Ҫ��ʼ��(CoInitialize,CoUninitialize)
�������ʹ���»��߿�ͷ��Ҫ�ĳ�˫�»���
���ط���ֵ,��Ϣ��������,������Ȳ�������
*/
#define EVE_System_GroupMemberDecrease(Name) CQEVENT(int, Name, 32)(int subType, int msgId, long long fromGroup, long long fromQQ, long long beingOperateQQ)

/*
Ⱥ�¼�-Ⱥ��Ա����(Type=103)

subtype �����ͣ�1/����Ա��ͬ�� 2/����Ա����
sendTime ����ʱ��(ʱ���)
fromGroup ��ԴȺ��
fromQQ ������QQ(������ԱQQ)
beingOperateQQ ������QQ(����Ⱥ��QQ)

���ӳ�����ڿ�Q���̡߳��б����ã���ע��ʹ�ö������Ҫ��ʼ��(CoInitialize,CoUninitialize)
�������ʹ���»��߿�ͷ��Ҫ�ĳ�˫�»���
���ط���ֵ,��Ϣ��������,������Ȳ�������
*/
#define EVE_System_GroupMemberIncrease(Name) CQEVENT(int, Name, 32)(int subType, int msgId, long long fromGroup, long long fromQQ, long long beingOperateQQ)

/*
�����¼�-���������(Type=201)

subtype �����ͣ�Ŀǰ�̶�Ϊ1
sendTime ����ʱ��(ʱ���)
fromQQ ��ԴQQ

���ӳ�����ڿ�Q���̡߳��б����ã���ע��ʹ�ö������Ҫ��ʼ��(CoInitialize,CoUninitialize)
�������ʹ���»��߿�ͷ��Ҫ�ĳ�˫�»���
���ط���ֵ,��Ϣ��������,������Ȳ�������
*/
#define EVE_Friend_Add(Name) CQEVENT(int, Name, 16)(int subType, int msgId, long long fromQQ)

/*
����-�������(Type=301)

subtype �����ͣ�Ŀǰ�̶�Ϊ1
sendTime ����ʱ��(ʱ���)
fromQQ ��ԴQQ
msg ����
responseFlag ������ʶ(����������)

�ú���������� (responseFlag, #����_ͨ��)

���ӳ�����ڿ�Q���̡߳��б����ã���ע��ʹ�ö������Ҫ��ʼ��(CoInitialize,CoUninitialize)
�������ʹ���»��߿�ͷ��Ҫ�ĳ�˫�»���
���ط���ֵ,��Ϣ��������,������Ȳ�������
*/
#define EVE_Request_AddFriend(Name) CQEVENT(int, Name, 24)(int subType, int msgId, long long fromQQ, const char* msg, const char* responseFlag)

/*
����-Ⱥ���(Type=302)

subtype �����ͣ�1/����������Ⱥ 2/�Լ�(����¼��)������Ⱥ
sendTime ����ʱ��(ʱ���)
fromGroup ��ԴȺ��
fromQQ ��ԴQQ
msg ����
responseFlag ������ʶ(����������)

��� subtype �� 1
��Ⱥ������� (responseFlag, #����_Ⱥ���, #����_ͨ��)
��� subtype �� 2
��Ⱥ������� (responseFlag, #����_Ⱥ����, #����_ͨ��)

���ӳ�����ڿ�Q���̡߳��б����ã���ע��ʹ�ö������Ҫ��ʼ��(CoInitialize,CoUninitialize)
�������ʹ���»��߿�ͷ��Ҫ�ĳ�˫�»���
���ط���ֵ,��Ϣ��������,������Ȳ�������
*/
#define EVE_Request_AddGroup(Name) CQEVENT(int, Name, 32)(int subType, int sendTime, long long fromGroup, long long fromQQ, const char* msg, const char* responseFlag)

/*
�˵�

���� .json �ļ������ò˵���Ŀ��������
�����ʹ�ò˵������� .json ���˴�ɾ�����ò˵�
�������ʹ���»��߿�ͷ��Ҫ�ĳ�˫�»���
���ط���ֵ,��Ϣ��������,������Ȳ�������
*/
#define EVE_Menu(Name) CQEVENT(int, Name, 0)()

/*
������

��ʹ��EX�汾
emmm,��ΪһЩԭ��,��������ʱ������...

���ӳ�����ڿ�Q���̡߳��б����ã���ע��ʹ�ö������Ҫ��ʼ��(CoInitialize,CoUninitialize)��
�������ʹ���»��߿�ͷ��Ҫ�ĳ�˫�»���
*/
#define EVE_Status(Name) CQEVENT(const char*, Name, 0)()
