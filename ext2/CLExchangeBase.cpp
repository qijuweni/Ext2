#include "CLExchangeBase.h"
#include "CLDevice.h"
#include "SInode.h"

CLExchangeBase::CLExchangeBase(CLDevice *pDev, int InodesBeginBlockIndex, int BlocksBeginBlockIndex)
{
	m_pDev = pDev;
	m_InodesBeginBlockIndex = InodesBeginBlockIndex;
	m_BlocksBeginBlockIndex = BlocksBeginBlockIndex;
};

CLExchangeBase::~CLExchangeBase()
{

};

bool CLExchangeBase::ReadBlock(t_block pblock, int indexBlock)
{
	m_pDev->ReadFromDeviceToRam((pblock) ,sizeof(t_block),(m_BlocksBeginBlockIndex + indexBlock) * sizeof(t_block));
	return true;
};

bool CLExchangeBase::WriteBlock(t_block pblock, int indexBlock)
{	
	m_pDev->WriteFromRamToDevice(pblock,sizeof(t_block),(m_BlocksBeginBlockIndex + indexBlock) * sizeof(t_block));
	return true;
};

bool CLExchangeBase::ReadInode(s_inode *pInode, int indexInode)
{
	m_pDev->ReadFromDeviceToRam(pInode, sizeof(s_inode), m_InodesBeginBlockIndex * sizeof(t_block) + sizeof(s_inode)*indexInode);
	return true;
};

bool CLExchangeBase::WriteInode(s_inode *pInode, int indexInode)
{
	m_pDev->WriteFromRamToDevice(pInode, sizeof(s_inode), m_InodesBeginBlockIndex * sizeof(t_block) + sizeof(s_inode)*indexInode);
	return true;
};
