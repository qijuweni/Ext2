#include "gtest/gtest.h"
#include "CLFreeBlocksManager.h"

TEST(FreeBlocksManager, block)
{

char dataMap[1024] = {0};
             dataMap[0] = 1 + 2; ////////0号没有用，root占1号
              dataMap[0] = dataMap[0] + 4;
	CLFreeBlocksManager *pb = new CLFreeBlocksManager(dataMap, 1024 * 8, 3);
	EXPECT_EQ(3, pb-> FindFitDataBlock());	
	EXPECT_EQ(4, pb-> FindFitDataBlock());
	EXPECT_EQ(5, pb-> FindFitDataBlock());
	EXPECT_EQ(6, pb-> FindFitDataBlock());
	EXPECT_EQ(7, pb-> FindFitDataBlock());
	EXPECT_TRUE(pb->ResetBlock(6));
	EXPECT_EQ(6, pb-> FindFitDataBlock());
	EXPECT_EQ(8, pb-> FindFitDataBlock());
	 EXPECT_TRUE(pb->ResetBlock(4));
	EXPECT_EQ(4, pb-> FindFitDataBlock());
	EXPECT_EQ(9, pb-> FindFitDataBlock());
	delete pb;
};
