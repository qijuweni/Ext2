#include "gtest/gtest.h"
#include "CLFreeInodeManager.h"

TEST(FreeInodeManager, inode)
{

char dataMap[1024] = {0};
             dataMap[0] = 1 + 8; ////////0号没有用，root占1号
              dataMap[0] = dataMap[0] + 4;
	CLFreeInodeManager *pb = new CLFreeInodeManager(dataMap, 1024 * 8, 3);
	EXPECT_EQ(1, pb->FindFitInode());	
	EXPECT_EQ(4, pb->FindFitInode());
	EXPECT_EQ(5, pb->FindFitInode());
	EXPECT_EQ(6, pb->FindFitInode());
	EXPECT_EQ(7, pb->FindFitInode());
	EXPECT_TRUE(pb->ResetInode(2));
	EXPECT_EQ(2, pb->FindFitInode());
	EXPECT_EQ(8, pb->FindFitInode());
	 EXPECT_TRUE(pb->ResetInode(4));
	EXPECT_EQ(4, pb->FindFitInode());
	EXPECT_EQ(9, pb->FindFitInode());
	delete pb;
};
