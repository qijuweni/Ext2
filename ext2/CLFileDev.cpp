#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include "CLFileDev.h"

#define  NUM_BLOCK 1024 * 7
#define  FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define  PATHNAME_DEV_BY_FILE "/home/qijunwei/fileSys/Dpan"

using namespace std;

bool CLFileDev::InitDev()
{
	cout<<"CLFileDev create"<<endl;
	int Fd = open(PATHNAME_DEV_BY_FILE, O_RDWR | O_CREAT | O_TRUNC, FILE_MODE);
	if(Fd == -1)
		cout<<"CLFileDev失败\n"<<endl;

	t_block sizeofSystem[NUM_BLOCK] = {{0}};
	int tes;
	
	if((tes = write(Fd, sizeofSystem, sizeof(t_block) * NUM_BLOCK)) != -1)
	{
		#ifdef TESTDEV
			cout<<"开辟空间success   "<<tes<<endl;
		#endif
	}
	else
	{
		cout<<"开辟空间失败"<<endl;
		return false;
	}
	//	char a[10] = "qijunwei";
	//	pBase = mmap(0, sizeof(block) * NUM_BLOCK, PROT_WRITE|PROT_READ, MAP_SHARED, m_Fd, 0);
	//	memcpy(pBase, a, 10);
	//	cout<<"memcpy success"<<endl;
	close(Fd);
	return true;
};

bool CLFileDev::OpenDev()
{
	m_Fd = open(PATHNAME_DEV_BY_FILE, O_RDWR , FILE_MODE); 
	if(m_Fd != -1)
	{
		m_pBase = mmap(0, sizeof(t_block) * NUM_BLOCK, PROT_WRITE|PROT_READ, MAP_SHARED, m_Fd, 0);
		return true;
	}
	else 
		return false;
};

CLFileDev::CLFileDev()
{

};

CLFileDev::~CLFileDev()
{

};

int CLFileDev::ReadFromDeviceToRam(void *ram,int size, int DevOffset)
{

	memcpy(ram, (char*)m_pBase + DevOffset, size);
	return 0;

};

int CLFileDev::WriteFromRamToDevice(void *ram, int size, int DevOffset)
{

	memcpy((char*)m_pBase + DevOffset, ram, size);
	return 0;
}

int CLFileDev::Clear(int size, int DevOffset)
{
	memset((char*)m_pBase + DevOffset, '\0', size);
	return 0;
};
