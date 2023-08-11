#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
int main(int argc, char * argv)
{	
	char * startDirectory;
	int maxDepth = -1;
	int found = 0;
}
int walkDirectory(char * dir, int curDepth, int maxDepth)
{	
	if (curDepth > maxDepth) {
		return;
	}
	curDepth++;
	DIR *dir = opendir(dir);
	if (dir == NULL) {
		printf("error");
	}


}
