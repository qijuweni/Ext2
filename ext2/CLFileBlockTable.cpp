#include "CLFileBlockTable.h"

#define ONEDIR_MAXINDEX 11
#define TWODIR_MAXINDEX 13

CLFreeBlocksManager *CLFileBlockTable::m_pFreeBlockManager = 0;

int CLFileBlockTable::GetBlockIndex(int blockTableIndex, int *pBlockIndex)
{
	int iBlockIndex = 0;
	if(blockTableIndex <= ONEDIR_MAXINDEX)
	{
		if((iBlockIndex = m_pTable[blockTableIndex] == -1)
		{
			
		}
	}
};
