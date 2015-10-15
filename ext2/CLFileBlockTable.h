class CLFreeBlocksManager;
class CLExchangeBase;
typedef char t_block[1024];

class CLFileBlockTable
{
public:
	int GetBlockIndex(int blockTableIndex, int *pBlockIndex);
private:
	static CLExchangeBase *m_pExchangeBase;
	static CLFreeBlocksManager *m_pFreeBlockManager;	
	int *m_pTable;
	int m_numsNowBlock;	
	t_block *m_pSecondDir;
};
