class CLFreeBlocksManager
{
public:
	CLFreeBlocksManager(char * pdatamap, int BlockNums, int nowBlockNums);
	virtual ~CLFreeBlocksManager();
	int FindFitDataBlock();
	bool ResetBlock(int blockIndex);
private:
	char *m_pdatamap;
	int m_BlockNums;
	int m_nowBlockNums;
};
