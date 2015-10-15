//class CLFileCtl;

#define MAX_NUMS_FD 50

class CLFdManager
{
private:	
	int   *m_FileCtlTab[MAX_NUMS_FD];
public:
	CLFdManager();
	~CLFdManager();
	int FindFitFdAndSetFd(int   *pFileCtl);
	int Close(int fd);
};

