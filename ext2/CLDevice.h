
#ifndef CLDevice_H
#define CLDevice_H

#define TESTDEV

class CLDevice
{
public:
	CLDevice();
	virtual ~CLDevice();
	virtual int WriteFromRamToDevice(void *ram, int size, int DevOffset) = 0;
	virtual int ReadFromDeviceToRam(void *ram,int size, int DevOffset) = 0;
	virtual bool InitDev() = 0;
	virtual bool OpenDev() = 0;
	virtual int Clear(int size, int DevOffset) = 0;
};

#endif
