class CLFreeInodeManager
{
public:
	CLFreeInodeManager(char *pInodemap, int inodeNums, int nowInodeNums);
	virtual ~CLFreeInodeManager();
	int FindFitInode();
	bool ResetInode(int inodeIndex);
private:
	char *m_pInodemap;
	int m_InodeNums;
	int m_nowInodeNums;
};
