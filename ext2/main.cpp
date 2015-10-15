#include <iostream>
#include "CLFdManager.h"
#include "CLFreeInodeManager.h"
#include "CLFreeBlocksManager.h"
#include "CLFileDev.h"
#include "gtest/gtest.h"
#include "CLExt2.h"
#include "CLExchangeBase.h"
#include "CLFileCtl.h"

using namespace std;

int main (int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
/*	CLFdManager fdm;
	int t = 0;
	for(int i = 0; i<10; i++)
	{
		t = fdm.FindFitFdAndSetFd(&t);
//		if(t == 4)
//			fdm.Close(t);
		cout<< t<<endl;
	};
	fdm.Close(3);
	fdm.Close(5);
	fdm.Close(6);
	
	for(int i = 0; i<10; i++)
	{
		t = fdm.FindFitFdAndSetFd(&t);
//		if(t == 4)
//			fdm.Close(t);
		cout<< t<<endl;
	
	}
	int inodemap = 245 + 256;
	int numinode = 32;
	CLFreeInodeManager inodemanager((char*)&inodemap, numinode);
	inodemanager.ResetInode(2);
        inodemanager.ResetInode(8);
	for(int i = 0; i<7;i++)
	{
		numinode = inodemanager.FindFitInode();
		cout<<numinode<<endl;

	}
	
	int blockmap = 245 + 256;
	int numblock = 32;
	CLFreeBlocksManager blockmanager((char*)&blockmap, numblock);
	blockmanager.ResetBlock(2);
        blockmanager.ResetBlock(8);
	for(int i = 0; i<7;i++)
	{
		numblock = blockmanager.FindFitDataBlock();
		cout<<numblock<<endl;
	}


	CLFileDev fdv;
	fdv.InitDev();
	fdv.OpenDev();
	char a[10] = "qijuwnei";
	char b[10];
	fdv.WriteFromRamToDevice(a, 10 , 0);
	fdv.ReadFromDeviceToRam(b, 10 ,0);
	cout<<b[0]<<b[1]<<b[2]<<b[5]<<b[9]<<endl;*/
//	CLExt2 c;
//	CLDevice *pd = new CLFileDev;
//	c.Mkfs(pd);
//	c.InitFileSys(pd);

//	return 0;
};
