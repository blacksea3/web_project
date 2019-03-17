#pragma once

#include <iostream>

//����Mlog
class Mlog
{
public:
	static Mlog* Instance();

	void debug_print();
	void destroy();

private:
	std::string _name;
	Mlog(const std::string &name);
	~Mlog();
	static Mlog *pMlog;
};
