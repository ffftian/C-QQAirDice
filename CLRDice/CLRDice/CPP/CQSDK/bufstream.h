#pragma once
#include <string>

namespace CQ
{
	class CQstream
	{
	protected:
		std::string buf;
	public:
		virtual void clear();

		//�ַ���
		virtual CQstream& append(const std::string& s);
		virtual CQstream& operator <<(const std::string& s);
		//
		virtual CQstream& append(const char* c);
		virtual CQstream& operator <<(const char* c);

		//����
		virtual CQstream& append(const int& i);
		virtual CQstream& operator <<(const int& i);
		virtual CQstream& append(const std::size_t& i);
		virtual CQstream& operator <<(const std::size_t& i);

		//������(Q��ʲô��)
		virtual CQstream& append(const long long& l);
		virtual CQstream& operator <<(const long long& l);


		//������Ʒ�
		virtual CQstream& operator <<(void (*control)(CQstream&));
		virtual void send() = 0;
		virtual void flush();

		virtual ~CQstream();
	};

	//���Ͳ����������
	void send(CQstream& log);
	//ֻ����,����������,�´η���ʱ�������ظ�����
	void flush(CQstream& log);
	void endl(CQstream& log);
}
