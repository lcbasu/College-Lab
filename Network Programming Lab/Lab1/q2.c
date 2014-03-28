#include <stdio.h>
#include <dirent.h>

/*

 DT_UNKNOWN       0
 DT_FIFO          1
 DT_CHR           2
 DT_DIR           4
 DT_BLK           6
 DT_REG           8
 DT_LNK          10
 DT_SOCK         12
 DT_WHT          14

*/

int main()
{
	DIR *dirLoc;
	struct dirent *directoryEntry;

	dirLoc = opendir("/");
	if(dirLoc)
	{
		directoryEntry = readdir(dirLoc);
		while(directoryEntry != 0)
		{
			printf("Name\t:%s", directoryEntry->d_name);
			printf("\nType\t:%d\n", directoryEntry->d_type);
			directoryEntry = readdir(dirLoc);
		}
		closedir(dirLoc);
	}
	return 0;
}