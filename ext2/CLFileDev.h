#include "CLDevice.h"

typedef char t_block[1024];

class CLFileDev:public CLDevice
{
public:
	CLFileDev();
	virtual ~CLFileDev();
	virtual int WriteFromRamToDevice(void *ram, int size, int DevOffset);
	virtual int ReadFromDeviceToRam(void *ram,int size, int DevOffset);
        virtual int Clear(int size, int DevOffset);
	virtual bool InitDev();
	virtual bool OpenDev();
private:
	int m_Fd;
	void * m_pBase;
};
