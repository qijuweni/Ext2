#define  MAX_DATABLOCKS_ININODE 15
#include "unistd.h"
#include "fcntl.h"

struct s_inode
{
	mode_t mode;
	uid_t uid;
	gid_t gid;
	off_t size;
	int dataBlocks[MAX_DATABLOCKS_ININODE];
	int type;
	int links;
	int rest[9];
};
