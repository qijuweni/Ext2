//������typedef����define���������򶼲�����չ������ļ�����ʹ��ͬһ������Ĳ�ͬ�ļ���Ҳ���ܻ���ʹ�á�

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
