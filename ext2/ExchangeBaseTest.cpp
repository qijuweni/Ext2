#include "gtest/gtest.h"
#include "CLExchangeBase.h"
#include "CLFileDev.h"
#include "SInode.h"

TEST(Exchangebase,test)
{
	CLFileDev * pf = new CLFileDev;
	pf->InitDev();
	pf->OpenDev();
	CLExchangeBase *pe = new CLExchangeBase(pf, 6, 7);
	t_block a = "qijunweilkjhgfdsa";
	pe->WriteBlock(a, 8);
	t_block b = "123456789qwertyuiop";
	pe->WriteBlock(b, 9);
	t_block c;
	t_block d;
	pe->ReadBlock(c, 8);
	pe->ReadBlock(d,9);
	EXPECT_STREQ(c, a);
	EXPECT_STREQ(d,b);
	s_inode s,q,w;
        s.uid = q.uid = 1;
	s.gid = q.gid = 2;
	s.mode = q.mode = 3;
	s.links = q.links = 4;
	s.type = q.type =5;
	pe->WriteInode(&s, 5);		
	pe->ReadInode(&w, 5);
	EXPECT_EQ(q.uid,w.uid);

	EXPECT_EQ(q.gid,w.gid);
	EXPECT_EQ(q.links,w.links);
	EXPECT_EQ(q.mode,w.mode);
	EXPECT_EQ(q.type,w.type);
}
