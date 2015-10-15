#include <iostream>
//#include "CLFileCtl.h"
#include "CLFdManager.h"

using namespace std;

CLFdManager::CLFdManager()
{
	for(int i = 0; i <  MAX_NUMS_FD; i++)
		m_FileCtlTab[i] = NULL;
};

CLFdManager::~CLFdManager()
{

};

int CLFdManager::Close(int fd)
{
	if(fd >= MAX_NUMS_FD)
		return -1;
	
//	m_FileCtlTab[fd]

	m_FileCtlTab[fd] = NULL;
	return 0;
};

int CLFdManager::FindFitFdAndSetFd(int 	 *pFileCtl)
{
	if(pFileCtl == NULL)
			return -1;

	for(int i = 0; i <  MAX_NUMS_FD; i++)
	{
		if(m_FileCtlTab[i] == NULL)
		{
			m_FileCtlTab[i] = pFileCtl;
			return i;
		}
	}

		return -1;
};


