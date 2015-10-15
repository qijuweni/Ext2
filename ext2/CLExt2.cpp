#include "CLExt2.h"
#include "CLFileDev.h"
#include <iostream>
#include <string.h>
#include<stdlib.h>
#include "CLFreeInodeManager.h"
#include "CLFreeBlocksManager.h"
#include "CLFileCtl.h"
#include "CLExchangeBase.h"
#include "SInode.h"
#include "SDirect.h"

using namespace std;

#define  FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define  DIR_MODE (S_IRUSR | S_IRGRP | S_IROTH)


CLExt2::CLExt2()
{

};

CLExt2::~CLExt2()
{

};

bool CLExt2::Mkfs(CLDevice *Dev)
{
	if(Dev->InitDev() == false)
		return false;
	Dev->OpenDev();
	int posDev = 0;
	s_superblock ss;
	InitSuperblock(&ss);
	Dev->WriteFromRamToDevice(&ss, sizeof(s_superblock), posDev);
	posDev = sizeof(s_superblock);

	s_groupDescription sg;
	InitGroupDescription(&sg);
	Dev->WriteFromRamToDevice(&sg, sizeof(s_groupDescription), posDev);
	posDev += sizeof(s_groupDescription);

	char inodeMap[1024] = {0};
	 inodeMap[0] = 1 + 2;
	 inodeMap[0] = inodeMap[0] + 4;	 
	 Dev->WriteFromRamToDevice(&inodeMap, sizeof(inodeMap), posDev);
	 posDev += sizeof(inodeMap);

	  char dataMap[1024] = {0};
	  dataMap[0] = 1 + 2; ////////0号没有用，root占1号
	  dataMap[0] = dataMap[0] + 4;
	  Dev->WriteFromRamToDevice(&dataMap, sizeof(dataMap), posDev);
	  posDev += sizeof(dataMap);

	  s_inode rootInode;
	  InitInode(&rootInode,DIR_MODE, 0, 0, 2 * sizeof(s_direct), DIRECT, 3);
	  rootInode.dataBlocks[0] = 1;
	  Dev->WriteFromRamToDevice(&rootInode, sizeof(rootInode), posDev + sizeof(s_inode));
	  posDev += (2 * sizeof(s_inode));

	  s_inode chridRootInode;
	  InitInode(&chridRootInode, DIR_MODE, 0, 0, sizeof(s_direct), DIRECT, 1);
	  chridRootInode.dataBlocks[0] = 2;
	  Dev->WriteFromRamToDevice(&chridRootInode, sizeof(s_inode), posDev);
	  posDev += sizeof(s_inode);

	  s_direct rootDir1;
	  rootDir1.name[0] = 'q';
	  rootDir1.name[1] = 'i';
	  rootDir1.name[2] = 0;
	  rootDir1.ino = 2;

	  s_direct rootDir2;
	  rootDir2.name[0] = '.';
	  rootDir2.name[1] = 0;
	  rootDir2.ino = 1;

	  posDev = sg.beginDataBlockIndex * sizeof(t_block) + sizeof(t_block);
	  Dev->WriteFromRamToDevice(&rootDir1, sizeof(s_direct), posDev);
	  posDev += sizeof(s_inode);
	  Dev->WriteFromRamToDevice(&rootDir2, sizeof(s_direct), posDev);

	  rootDir2.ino = 2;
	  posDev = (sg.beginDataBlockIndex + 2) * sizeof(t_block);
	  Dev->WriteFromRamToDevice(&rootDir2, sizeof(t_block), posDev);
	  posDev += sizeof(s_direct);

	  rootDir1.name[0] = '.';
	  rootDir1.name[1] = '.';
	  rootDir1.ino = 1;
	  Dev->WriteFromRamToDevice(&rootDir1, sizeof(t_block), posDev);

	  return true;
};

void CLExt2::InitSuperblock(s_superblock * pSuperblock)
{    
	pSuperblock->blockNum = 1024 * 7 - 4 - 256;
	pSuperblock->inodeNum = 1024 * 2 ; 
	pSuperblock->blockSize = 1024;
	pSuperblock->inodeSize = 128;
	pSuperblock->restBlockNum = pSuperblock->blockNum;
	pSuperblock->restInodeNum = pSuperblock->inodeNum;
};  

/*int CLExt2::FindNameINode(char *name, int inode)
{
	if(m_pinodes[inode].type != DIRECT)
		return -1;

	int ptrBlockIndexsOfInode[MAX_DATABLOCKS_ININODE];
	int numBlocks = findBlockIndexofInode(inode, ptrBlockIndexsOfInode);

	block ptrDataBlock;
	for(int i = 0; i < numBlocks; i++)
	{
		takeDataBlock(&ptrDataBlock, ptrBlockIndexsOfInode[i]);

		s_direct *ptrDirents = (s_direct*)ptrDataBlock;

		for(int i = 0; i < (int)(sizeof(block)/sizeof(s_direct)); i++)
		{
			//      cout<<ptrDirents[i].name<<"  AND  "<<ptrDirents[i].ino<<endl;
			      if(ptrDirents[i].name[0] == 0)
				      break;
			      if(strcmp(name, ptrDirents[i].name) == 0)
				      return ptrDirents[i].ino;
		}
	}
       	cout<<"findNameINode   wrong"<<endl;

	return -1;
};

int CLExt2::findBlockIndexofInode(int inode, int ptrBlockIndexs[MAX_DATABLOCKS_ININODE])/////ok
{
	int i = 0;

	while(m_pinodes[inode].dataBlocks[i] != -1)
	{
		ptrBlockIndexs[i] = m_pinodes[inode].dataBlocks[i];
		i++;
	}

	return i;
};

int CLExt2::takeDataBlock(block *ptrDataBlock, int indexData)
{
	int beginDataBlockIndex = m_pgd->beginDataBlockIndex;

	m_pDevice->ReadFromDeviceToRam(ptrDataBlock, sizeof(block), (beginDataBlockIndex + indexData) * sizeof(block));

	return 0;
};*/

bool CLExt2::InitFileSys(CLDevice *pDevice)
{
	if(!pDevice->OpenDev())
		return false;

	m_pss = (s_superblock*)malloc(sizeof(s_superblock));

	if(!m_pss)
		cout<<"malloc\n"<<endl;

	pDevice->ReadFromDeviceToRam(m_pss, sizeof(s_superblock), 0);

	int pos = sizeof(s_superblock);

	m_pgd = (s_groupDescription*)malloc(sizeof(s_groupDescription));

	if(!m_pgd)
		cout<<"malloc\n"<<endl;

	pDevice->ReadFromDeviceToRam(m_pgd, sizeof(s_groupDescription), pos);
	pos += sizeof(s_groupDescription);

	char *pinodemap = (char*)malloc(sizeof(t_block));

	if(!pinodemap)
		cout<<"malloc\n"<<endl;

	pDevice->ReadFromDeviceToRam(pinodemap, sizeof(t_block), pos);
	pos += sizeof(t_block);
	m_pFreeInodeManager = new CLFreeInodeManager(pinodemap, m_pss->inodeNum, m_pss->restInodeNum);

	char *pdatamap = (char*)malloc(sizeof(t_block));

	if(!pdatamap)
		cout<<"malloc\n"<<endl;

	pDevice->ReadFromDeviceToRam(pdatamap, sizeof(t_block), pos);
	pos += sizeof(t_block);
	CLFreeBlocksManager *pFreeBlockManager = new CLFreeBlocksManager(pdatamap, m_pss->blockNum, m_pss->restBlockNum);
 
	CLFileCtl::m_pFreeBlockManager = pFreeBlockManager;
	m_pExchangeBase = new CLExchangeBase(pDevice, m_pgd->beginInodeBlockIndex, m_pgd->beginDataBlockIndex);
	CLFileCtl::m_pExchangeBase = m_pExchangeBase;

	return true;
};

/*int CLExt2::findLastDirInodeIndex(const char *path, char buf[MAX_NAMELENGTH])
{
	if(!path)
		return -1;
	const char *tmpptr = path;
	int pathLength;
	int nowDirInodeIndex;
	if(*tmpptr == '/' && ((pathLength = strlen(path)) != 0) )//strlen
	{
		nowDirInodeIndex = 1;
		tmpptr++;
	}
	else
		return -1;

	int j = 0;
	while(1)
	{
		if(*tmpptr == '/')
		{
			buf[j] = 0;
			nowDirInodeIndex = findNameINode(buf, nowDirInodeIndex);

			if(nowDirInodeIndex == -1)
				return -1;

			while(j != 0)
			{
				buf[--j] = 0;
			}
			tmpptr++;
		}
	  	else if(*tmpptr == '\0')
		{
			buf[j] = 0;
			break;
		}
		else
		{
			buf[j] = *tmpptr;
			tmpptr++;
			if(++j >= MAX_NAMELENGTH)
				cout<<"MAX_NAMELENGTH"<<endl;
		}

	}
	return nowDirInodeIndex;
};
*/
void CLExt2::InitGroupDescription(s_groupDescription *pSuperDescription)
{ 
	pSuperDescription->beginInodeBlockIndex = 4;
	pSuperDescription->beginDataBlockIndex = 260;
	pSuperDescription->beginBlockIndex = 0;
	pSuperDescription->endBlockIndex = 1024 * 7 - 1;
};
/*
int CLExt2::findFitInode()
{
	int inodeNums = (m_pgd->beginDataBlockIndex - m_pgd->beginInodeBlockIndex) * sizeof(block) / sizeof(s_inode);
	int mod, index, i;
	char cmp = 1;
	for(i = 0; i < inodeNums ;i++)
	{
		mod = i % 8;
		
		if(mod == 0)
		{
			index = i/8;
			cmp = 1;
		}
		else
			cmp = cmp<<1;

		if(!(m_pinodemap[index] & cmp))
		{
			 m_pinodemap[index] |= cmp;
			 return i;
		}
	}
	cout<<"findFitInode flase"<<endl;
	return -1;
		
}

int CLExt2::findFitDataBlock()
{
	int inodeNums = m_pss->blockNum;
	int mod, index, i;
	char cmp = 1;

	for(i = 0; i < inodeNums ;i++)
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
			 return i;
		 }

	}
	cout<<"findFitDataBlock false"<<endl;

	return -1;
}*/

bool CLExt2::InitInode(s_inode *ptrInode,  mode_t mode, uid_t uid, gid_t gid, off_t size, int type, int links)
{
	ptrInode->size = size;
	ptrInode->links = links;
	ptrInode->mode = mode;
	ptrInode->type = type;
	ptrInode->gid = gid;
	ptrInode->uid = uid;

	for(int i = 1; i < MAX_DATABLOCKS_ININODE; i++)
		 ptrInode->dataBlocks[i] = -1;

	 return true;
};

/*bool CLExt2::addDirent(s_direct dirent, int inodeIndex)
{
	int ptrBlockIndexsOfInode[MAX_DATABLOCKS_ININODE];
	int numBlocks = findBlockIndexofInode(inodeIndex, ptrBlockIndexsOfInode);

	if(numBlocks == 0)
	{
		cout<<"addDirent findBlockIndexofInode = 0"<<endl;
		return false;
	}
	int dataSize = m_pinodes[inodeIndex].size;
	int dataBlockIndex = dataSize/sizeof(block);
	int blockExistSize = dataSize%sizeof(block);
	int beginDataBlockIndex = m_pgd->beginDataBlockIndex;
	int sizeRead = sizeof(block);

	m_pDevice->WriteFromRamToDevice(&dirent, sizeof(s_direct), (beginDataBlockIndex + ptrBlockIndexsOfInode[dataBlockIndex]) * sizeRead + blockExistSize);
	m_pinodes[inodeIndex].size += sizeof(s_direct);

	return true;
}

int CLExt2::createFile(char *name, mode_t mode, int type, int parentInode)
{
	int inodeIndex = findFitInode();
	
	if(inodeIndex == -1)
		return -1;
	if(!initInode(&m_pinodes[inodeIndex], mode, 0, 0, 0, type, 1))
		return -1;

	s_direct dirent = { {0}, -1};
	strcpy(dirent.name, name);
	dirent.ino = inodeIndex;

	if(!addDirent(dirent, parentInode))
		return -1;
	
	if(type == DIRECT)
	{
		s_direct dirent1 = { {0}, -1};
		strcpy(dirent1.name, ".");
		dirent1.ino = inodeIndex;
		if(!addDirent(dirent1, inodeIndex))
			return -1;
		m_pinodes[inodeIndex].links++;
		
		strcpy(dirent1.name, "..");
		dirent1.ino = parentInode;
		if(!addDirent(dirent1, inodeIndex))
			return -1;
		m_pinodes[parentInode].links++;
	}
	return inodeIndex ;
}
*/
int CLExt2::Create(const char *path, mode_t mode)
{
	/*char buf[MAX_NAMELENGTH] = {0};
	int nowDirInodeIndex;
	if((nowDirInodeIndex = findLastDirInodeIndex(path, buf)) == -1)
	{
		cout<<"create false"<<endl;
		return -1;
	}

	int indexFileInode = -1;
	if((indexFileInode = createFile(buf, mode, REGULAR ,nowDirInodeIndex)) == -1)
		return -1;
        s_FileTableItem *pTmpFileTableItem = NULL;
	int fd = findFitFD(&pTmpFileTableItem);
	pTmpFileTableItem->pInode = &m_pinodes[indexFileInode];
	pTmpFileTableItem->pos = 0;
//	pTmpFileTableItem->status ;
   	return fd;*/
	return 0;
};

int CLExt2::Mkdir(const char *path, mode_t mode)
{
/*	char buf[MAX_NAMELENGTH] = {0};
	int nowDirInodeIndex;
	if((nowDirInodeIndex = findLastDirInodeIndex(path, buf)) == -1)
	{
		cout<<"create false"<<endl;
		return -1;
	}

	int indexFileInode = -1;
	if((indexFileInode = createFile(buf, mode, DIRECT ,nowDirInodeIndex)) == -1)
		return -1;
*/   	return 0;
};

/*size_t CLExt2::myread(int fd, void *buf, int nbytes)
{                {
                        if(fd < 0)
                                return -1; 
                        int *tmp = fdMap[fd];
                        if(tmp[0] < 0)
                                return -1; 
    
                        int fileSize = c_pinodes[tmp[0]].size;    
                        if(tmp[1] >= fileSize)
                        {   
                                cout<<"pos"<<tmp[1]<<"size"<<fileSize<<endl;
                                return 0;
                        }   
                        int ptrBlockIndexsOfInode[MAX_DATABLOCKS_ININODE];
                        int numBlocks = findBlockIndexofInode(tmp[0], ptrBlockIndexsOfInode);
                        //cout<<numBlocks<<endl;
    
                        if(numBlocks == 0)
                        {   
                                cout<<"myread findBlockIndexofInode = 0"<<endl;
                                return -1; 
                        }   
cout<<tmp[1]<<endl;
                        int dataBlockIndex = tmp[1]/sizeof(block);
                        int pos = tmp[1] % sizeof(block);

                        block datablock = {0};
                        char *tmpPos = (char*)datablock;
                        int bufPos = 0;

                        if(takeDataBlock(&datablock, ptrBlockIndexsOfInode[dataBlockIndex]) == -1)
                                return -1;

if(nbytes <= sizeof(block) - pos)
                        {
                                memcpy(buf, tmpPos + pos, nbytes);
                                bufPos = nbytes;
                        }
                        else
                        {
                                memcpy(buf, tmpPos + pos, sizeof(block) - pos);
                                nbytes -= (sizeof(block) - pos);
                                 bufPos = sizeof(block) - pos;

                                while(++dataBlockIndex < numBlocks)
                                {
                                        block datablock1 = {0};
                                        if(takeDataBlock(&datablock1, ptrBlockIndexsOfInode[dataBlockIndex])== -1)
                                                return -1;
                                        if(nbytes <= sizeof(block))
                                        {
                                                strncpy((char*)buf + bufPos, datablock1, nbytes);
                                                bufPos += nbytes;
                                                break;
                                        }
                                        else
                                        {
                                                strncpy((char*)buf + bufPos, datablock1, sizeof(block));
                                                bufPos += sizeof(block);
                                                nbytes -= sizeof(block);
                                        }
                                }
                        }
                        cout<<bufPos<<endl;
                        tmp[1] += bufPos; return bufPos;
                }*/
int CLExt2::Open(const char *path, int aflag, mode_t mode)
{	
	/*char buf[MAX_NAMELENGTH] = {0};
	int nowDirInodeIndex;
	if((nowDirInodeIndex = findLastDirInodeIndex(path, buf)) == -1) 
	{   
		cout<<"open false"<<endl;
		return -1; 
	}	

	int indexFileInode;

	if((indexFileInode = findNameINode(buf, nowDirInodeIndex)) == -1)
	{
		if(aflag & O_CREAT)
		{
			if((indexFileInode = createFile(buf, mode, REGULAR ,nowDirInodeIndex)) == -1)
				return -1;				
		}
		else
			return -1;
	}
	
	s_FileTableItem *pTmpFileTableItem = NULL;
	int fd = findFitFD(&pTmpFileTableItem);

	if(fd == -1)
		return -1;

	pTmpFileTableItem->pos = 0;
	pTmpFileTableItem->status = aflag;               ///////////////////
	pTmpFileTableItem->pInode = &m_pinodes[indexFileInode];

	return fd;*/
	return 0;
};
