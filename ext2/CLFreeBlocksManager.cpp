#include <iostream>
#include "CLFreeBlocksManager.h"

using namespace std;

CLFreeBlocksManager::CLFreeBlocksManager(char * pdatamap, int BlockNums, int nowBlockNums)
{
	m_BlockNums = BlockNums;
	m_pdatamap = pdatamap;
	m_nowBlockNums = nowBlockNums;
};

CLFreeBlocksManager::~CLFreeBlocksManager()
{

};

int CLFreeBlocksManager::FindFitDataBlock()
{
	int mod, index, i;
	char cmp = 1;

	for(i = 0; i < m_BlockNums ; i++)
	{
		mod = i % 8;
		if(mod == 0)
		{
			index = i / 8;		
			cmp = 1;
		}		
		else
			cmp = cmp<<1;

		if(!(m_pdatamap[index] & cmp))
		{
			m_pdatamap[index] |= cmp;
			m_nowBlockNums--;
			return i;
		}
	}
	cout<<"findFitDataBlock false"<<endl;
	return -1;
};

bool CLFreeBlocksManager::ResetBlock(int blockIndex)
{
	if(blockIndex < 0 || blockIndex >= m_BlockNums)
		return false;

	int index = blockIndex / 8;
	int mod = blockIndex % 8;
	int cmp = 1;

	while(mod > 0)
	{
		cmp = cmp << 1;
		--mod;
	}

	cmp = ~cmp;
	m_pdatamap[index] = m_pdatamap[index] & cmp;
	m_nowBlockNums++;
	return true;
};
