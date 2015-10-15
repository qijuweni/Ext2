#include <iostream>
#include "CLFreeInodeManager.h"

using namespace std;

CLFreeInodeManager::CLFreeInodeManager(char *pInodemap, int inodeNums, int nowInodeNums)
{
	m_InodeNums = inodeNums;
	m_pInodemap = pInodemap;
	m_nowInodeNums = nowInodeNums;
};

CLFreeInodeManager::~CLFreeInodeManager()
{

};

int CLFreeInodeManager::FindFitInode()
{
	int mod, index, i;
	char cmp = 1;
	//cout<<inodeNums<< "     issdsadfasf  "<<c_pinodemap[1]<<endl;
	for(i = 0; i < m_InodeNums ;i++)
	{
		mod = i % 8;
		if(mod == 0)
		{
			index = i / 8;		
			cmp = 1;
		}		
		else
			cmp = cmp<<1;

		if(!(m_pInodemap[index] & cmp))
		{
			m_pInodemap[index] |= cmp;
			m_nowInodeNums--;
			return i;
		}
	}
	cout<<"findFitInode flase"<<endl;
	
	return -1;
};

bool CLFreeInodeManager::ResetInode(int inodeIndex)
{
	if(inodeIndex < 0 || inodeIndex >= m_InodeNums)
		return false;

	int index = inodeIndex / 8;
	int mod = inodeIndex % 8;
	char cmp = 1;

	while(mod > 0)
	{
		cmp = cmp << 1;
		--mod;
	}

	cmp = ~cmp;
	m_pInodemap[index] = m_pInodemap[index] & cmp;
	//cout<<(int)(*m_pInodemap)<<endl;
	m_nowInodeNums++;
	return true;
};
