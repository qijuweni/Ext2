
typedef char t_block[1024];
struct s_inode;

class CLDevice;

class CLExchangeBase
{
public:
	CLExchangeBase(CLDevice *pDev, int InodesBeginBlockIndex, int BlocksBeginBlockIndex);
	virtual ~CLExchangeBase();
	bool ReadBlock(t_block pblock, int indexBlock);
	bool WriteBlock(t_block pblock, int indexBlock);
	bool ReadInode(s_inode *pInode, int indexInode);
	bool WriteInode(s_inode *pInode, int indexInode);
private:
	CLDevice *m_pDev;
	int m_InodesBeginBlockIndex;
	int m_BlocksBeginBlockIndex;
};
