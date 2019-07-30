#pragma once
#include "CQface.h"

#include <string>
#include <vector>
#include <map>
#include <memory>
//#include <shared_mutex>

namespace CQ {
	//cq��Ϣ����
	struct OneCodeMsg { size_t key, keylen = 0, value = 0; OneCodeMsg(size_t key); };
	//һ��cq��Ϣ������ͨ��Ϣ
	struct CodeMsg : std::vector<OneCodeMsg> { public: bool isCode; size_t key, keylen = 0; CodeMsg(bool isCode, size_t key); };

	class CodeMsgs;
	struct CodeMsgsFor {
		CodeMsgs&t;
		size_t pos;
		CQ::CodeMsgs&operator*();
		CQ::CodeMsgsFor&operator++();
		bool operator!=(CQ::CodeMsgsFor&);
		CodeMsgsFor(CodeMsgs&t, int pos);
	};
	//��Ϣ����
	class CodeMsgs {
		std::vector<CodeMsg> msglist;
		std::string txt;
		size_t thismsg=0;//ָ��
		void decod();//����
		bool find(std::string &s,int);
		bool is(std::string &s, int);
	public:
		CodeMsgs(std::string);

		//char* at(int);

		//��λ��ָ����
		CQ::CodeMsgs&operator[](size_t);
		CQ::CodeMsgs&operator++(int);
		CQ::CodeMsgs&operator++();
		CQ::CodeMsgs&operator--(int);
		CQ::CodeMsgs&operator--();
		CQ::CodeMsgs&operator-(size_t);
		CQ::CodeMsgs&operator+(size_t);
		//����ָ�뵱ǰλ��
		int pos();
		
		//�ӵ�ǰλ�ÿ�ʼ����ָ��cq��
		//�������,��λ��ָ����
		//���򷵻�null,���Ҳ����ƶ�ָ��
		bool find(std::string s);

		//�ӵ�ǰλ�ÿ�ʼ��������ָ��cq��
		//�������,��λ��ָ����
		//���򷵻�null,���Ҳ����ƶ�ָ��
		bool lastfind(std::string);


		//�ж��Ƿ���CQ��
		bool isCQcode();

		//�ж��Ƿ�Ϊָ��CQ��
		bool is(std::string);

		//�����CQ��,����CQ������
		//�������,������Ϣ
		std::string get();

		//�����CQ��,���ؼ���Ӧ��ֵ
		//����Ҳ�����,�򷵻ؿ��ַ�
		//�������,���ؿ��ַ�
		std::string get(std::string key);
		std::vector<std::string> keys();
		
		CQ::CodeMsgsFor begin();
		CQ::CodeMsgsFor end();

		void debug();

	};

	struct code {
		//[CQ:image,file={1}] - �����Զ���ͼƬ
		//�ļ��� ��QĿ¼\data\image\ Ϊ����
		static std::string image(std::string fileurl);

		//[CQ:record,file={1},magic={2}] - ��������
		//�ļ��� ��QĿ¼\data\record\ Ϊ����
		static std::string record(std::string fileurl, bool magic);

		//[CQ:face,id={1}] - QQ����
		static std::string face(int faceid);

		//[CQ:face,id={1}] - QQ����
		//static std::string face(CQ::face face);

		//[CQ:at,qq={1}] - @ĳ��
		static std::string at(long long QQ);

		//[CQ:effect,type=art,id=2003,content=С��] - ħ������
		static std::string effect(std::string type, int id, std::string content);

		//[CQ:sign,title=ɹ�Ҹ�,image=http://pub.idqqimg.com/pc/misc/files/20170825/cc9103d0db0b4dcbb7a17554d227f4d7.jpg] - ǩ��

		//[CQ:hb, title = ��ϲ����] - ���(ֻ����,���ܷ�)

		//[CQ:shake, id = 1] - ��һ��(ԭ���ڶ�������֧�ֺ�����Ϣʹ��)

		//[CQ:sface,id={1}] - С����

		//[CQ:bface,id={1}] - ԭ������

		//[CQ:emoji,id={1}] - emoji����

		//[CQ:rps,type={1}] - ���Ͳ�ȭħ������
		//���Ͳ�֧���Զ���type
		//1 Ϊ ʯͷ
		//2 Ϊ ����
		//3 Ϊ ��

		//[CQ:dice,type={1}] - ����������ħ������
		//���Ͳ�֧���Զ���type
		//typeΪ���ӵ���

		//[CQ:anonymous,ignore={1}] - ��������Ϣ(��֧��Ⱥ��Ϣʹ��)
		//��������Ϣ�ͷ
		//ignoreΪtrueʱ,�������ʧ����תΪ��ͨ��Ϣ

		//[CQ:music,type={1},id={2}] - ��������
		//typeΪ����ƽ̨,֧��qq��163��xiami
		//id��Ϊ����id

		//[CQ:music,type=custom,url={1},audio={2},title={3},content={4},image={5}] - ���������Զ������
		//urlΪ��������,������������������ҳ�棨���������ҳ��
		//audioΪ��Ƶ���ӣ���mp3���ӣ�
		//titleΪ���ֵı��⣬����12������
		//contentΪ���ֵļ�飬����30�����ڡ��ò����ɱ�����
		//imageΪ���ֵķ���ͼƬ���ӡ�������Ϊ�ջ򱻺��ԣ�����ʾĬ��ͼƬ
		//!�����Զ������ֻ����Ϊ������һ����Ϣ����

		//[CQ:share,url={1},title={2},content={3},image={4}] - �������ӷ���
		//urlΪ�������ӡ�
		//titleΪ����ı��⣬����12�����ڡ�
		//contentΪ����ļ�飬����30�����ڡ��ò����ɱ����ԡ�
		//imageΪ�����ͼƬ���ӡ�������Ϊ�ջ򱻺��ԣ�����ʾĬ��ͼƬ��
		//!���ӷ���ֻ����Ϊ������һ����Ϣ����

	};
}