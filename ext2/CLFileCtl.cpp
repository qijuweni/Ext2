#include "CLFileBlockTable.h"
#include "CLFileCtl.h"
#include <stdlib.h>
#include "string.h"


CLFileCtl::CLFileCtl()
{

};

CLFileCtl::~CLFileCtl()
{

};

int CLFileCtl::copy(void *buf, int size, bool readOrWrite)
{//          0 READ
	int tmpSize = size;
	int blockPos = m_pos % sizeof(t_block);
	int restBufSize = sizeof(t_block) - blockPos;
	int bufPos = 0;
	int *psrcPos;
	int *pdesPos;
	void *psrc;
	void *pdes;

	if(readOrWrite == 0)
	{
		psrc = (void*)(&m_blockBuf);
		psrcPos = &blockPos;
		pdes = buf;
		pdesPos = &bufPos;
	}
	{
		psrc = buf;	
		psrcPos = &bufPos;		
		pdes = (void*)(&m_blockBuf);	
		pdesPos = &blockPos;
	}
	if(tmpSize <= restBufSize)	
	{	
		memcpy((void*)((char*)pdes + (*pdesPos)), (void*)((char*)psrc + (*psrcPos)), tmpSize);
		if(readOrWrite == 1)		
			m_changeFlag = 1;
		return tmpSize;
	}

	memcpy((void*)((char*)pdes + (*pdesPos)), (void*)((char*)psrc + (*psrcPos)), restBufSize);
	if(readOrWrite == 1)	
		m_changeFlag = 1;
	SetPos(m_pos + restBufSize);	
	tmpSize -= restBufSize;
	bufPos += restBufSize ;
	blockPos = 0;
	restBufSize = sizeof(t_block);

	while(tmpSize > 0)
	{	
		if(tmpSize <= (int)sizeof(t_block))
		{ 		
			memcpy((void*)((char*)pdes + (*pdesPos)), (void*)((char*)psrc + (*psrcPos)), tmpSize);						if(readOrWrite == 1)			
				m_changeFlag = 1;		
			return size;	
		}
		else
		{ 			
			memcpy((void*)((char*)pdes + (*pdesPos)), (void*)((char*)psrc + (*psrcPos)), restBufSize);						if(readOrWrite == 1)
					m_changeFlag = 1;
			SetPos(m_pos + restBufSize);		
			tmpSize -= restBufSize;	
			bufPos += restBufSize ;
		}
	}
	return -1;
}
bool CLFileCtl::SetPos(int pos)
{
	if(pos/sizeof(t_block) != m_pos/sizeof(t_block))
	{
		if(m_changeFlag == 1)
		{
			Flush();//			
		}

		m_bufBlockTableIndex = m_pos/sizeof(t_block);

		if(!m_pBlockTable->getBlock(m_bufBlockTableIndex , &m_blockBuf))
			clearBuf();
	}
	
	m_pos = pos;

	return true;
};

bool CLFileCtl::Flush()
{
/*	if(m_pBlockTable->setBlock(m_bufBlockTableIndex, &m_blockBuf)) // =1 chenggong
	{
		m_changeFlag = 0;
		return true;
	}
	else
*/		return false;

};

bool CLFileCtl::ClearBuf()
{
	memset(&m_blockBuf, 0, sizeof(t_block));
	return true;	
};
