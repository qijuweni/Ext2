#include "gtest/gtest.h"
#include "CLFileDev.h"

TEST(Dev, FileDev)
{
	CLFileDev *pf = new CLFileDev;
	pf->InitDev();
	pf->OpenDev();
	char a[1024] = "qadasghqueqrhqelrghlkekqhlkjhqerter";
	pf->WriteFromRamToDevice(a, 1024, 1024);
	char b[1024] = {0};
	pf->ReadFromDeviceToRam(b, 1024, 1024);
	EXPECT_STREQ(a, b);
	char c[1024] = {0};
	pf->Clear(1024, 1024);
	char d[1024];
	pf->ReadFromDeviceToRam(d, 1024, 1024);
	EXPECT_STREQ(c, d);
	delete pf;
};
