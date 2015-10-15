
struct s_Inode;
struct s_Dirent;
typedef char t_block[1024];

class CLFileBlockTable;
class CLExt2;
class CLFreeBlocksManager;
class CLExchangeBase;

class CLFileCtl
{
public:
	CLFileCtl();
	virtual ~CLFileCtl();
	bool SetPos(int pos);
	virtual int FindNameInode(s_Inode *pInode, char *name) = 0;
	virtual int Read(void *buf, int size) = 0;
	virtual int Write(void *buf, int size) = 0;
        virtual int AddDirent(s_Dirent *pDirent) = 0;
	bool Flush();
	bool ClearBuf();
	
	friend class CLExt2;

protected:
	int Copy(void *buf, int size, bool readOrWrite);
	int m_bufBlockTableIndex;
	int m_changeFlag;
	t_block m_blockBuf;
	int m_status;
	int m_pid;
	int m_count;
	char *m_name;
	s_Inode *m_pInode;
	int m_pos;
	static CLExchangeBase *m_pExchangeBase;
	static CLFreeBlocksManager *m_pFreeBlockManager;
	CLFileBlockTable * m_pBlockTable;
};
