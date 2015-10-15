#include <unistd.h>
#include <fcntl.h>
//#include "CLDevice.h"

#define  MAX_FD_NUM 50
//#define  MAX_NAMELENGTH 12
#define  REGULAR 10
#define  DIRECT 11
#define  MAX_OPEN_FILES  100

class CLDevice;

struct s_superblock
{
  	int blockNum;
	int inodeNum;
	int blockSize;
	int inodeSize;
	int restBlockNum;
	int restInodeNum;
	int restspace[250];
};

struct s_groupDescription
{
	int beginBlockIndex;
	int endBlockIndex;
	int beginInodeBlockIndex;
	int beginDataBlockIndex;
	int rest[252];
};
	
 struct s_stat
{
	mode_t mode;
	int inodeIndex;
	int links;
	uid_t uid;
	gid_t gid;
	off_t size;
	int type;
};

struct s_direct;
//{
//	char name[MAX_NAMELENGTH];
//	int  ino;
//};

typedef char t_block[1024];
class CLFreeInodeManager;
class CLExchangeBase;
class CLFileCtlTable;
class CLFdManager;

struct s_inode;

class CLExt2
{
public:
	CLExt2();
	~CLExt2();
	bool Mkfs(CLDevice *Dev);
	bool InitFileSys(CLDevice *Dev);
	

	//int createFile(char *name, mode_t mode, int type, int parentInode);
	
	int Create(const char *path, mode_t mode);
	int Mkdir(const char *pathname, mode_t mode);
	int Open(const char *path, int aflag, mode_t mode = 0);
	//ssize_t Read(int fd, void *buf, int nbytes);
	
private:
	bool InitInode(s_inode *ptrInode,  mode_t mode, uid_t uid, gid_t gid, off_t size, int type, int links);

	void InitSuperblock(s_superblock *pSuperblock);
	void InitGroupDescription(s_groupDescription *pSuperDescription);
private:
	 s_superblock *m_pss;
	 s_groupDescription *m_pgd;

	 CLFreeInodeManager *m_pFreeInodeManager;
	 CLFdManager *m_pFdManager;
	 CLExchangeBase *m_pExchangeBase;
	// CLFileCtlTable *m_pCtlTable; 
};
