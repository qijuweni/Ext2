//不管是typedef还是define，其作用域都不会扩展到别的文件，即使是同一个程序的不同文件，也不能互相使用。

#include <iostream>
#include "CLDevice.h"

using namespace std; 

CLDevice::CLDevice()
{
	#ifdef TESTDEV
		cout<<"CLDevice create"<<endl;
	#endif
};

CLDevice::~CLDevice()
{
	#ifdef TESTDEV
		cout<<"CLDevice dis"<<endl;
	#endif
};
