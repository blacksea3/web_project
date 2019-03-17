
#include "Log.h"
#include <iostream>

Mlog::Mlog(const std::string &name)
{
	_name = name;
	std::cout << "This class Mlog, Mlog: object name:" << _name.c_str() << std::endl;
}

Mlog::~Mlog()
{
	std::cout << "This class Mlog, ~Mlog: object name:" << _name.c_str() << std::endl;
}

//�Ҳ����ҵ�Instance�ĺ�������,�²�Ϊ
//������
//����Mlog������
Mlog* Mlog::Instance()
{
	if (pMlog == NULL)
	{
		pMlog = new Mlog(std::string("111"));
	}
	return pMlog;
}

//debug���
void Mlog::debug_print()
{
	std::cout << "This class Mlog, debug_print: object name:" << _name.c_str() << std::endl;
}

//����
void Mlog::destroy()
{
	if (pMlog != NULL)
	{
		delete pMlog;
		pMlog = NULL;
	}
}

Mlog *Mlog::pMlog = NULL;
