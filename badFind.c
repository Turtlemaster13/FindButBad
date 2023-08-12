#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>


void walkDirectory(char *dir, int curDepth, int maxDepth, char * searchString)
{	
	printf("Searching for %s in %s\n", searchString, dir);

	struct stat statPath;
	if (curDepth > maxDepth) {
		return;
	}
	curDepth++;

	// Open the local directory and look for the file

	DIR *openDir = opendir(dir);
	if (openDir == NULL) {
		printf("error");
	}
	struct dirent *entry;
	while ((entry = readdir(openDir)) != NULL) {
		printf("%s\n", entry->d_name);
		if (strncmp(entry->d_name, searchString, strlen(searchString))== 0){
			printf("found file : [%s/%s]\n", dir, searchString);
			exit(0);
		}
	}

	// Find local directories and search those
	rewinddir(openDir);
	struct dirent *entry2;
	while ((entry2 = readdir(openDir)) != NULL) {
		printf("checking [%s] - %i\n", entry2->d_name, strncmp(entry2->d_name, "..", strlen("..")));
		if ( strncmp(entry2->d_name, "..", strlen("..")) == 0  || strncmp(entry2->d_name, ".", strlen("."))== 0){
			continue;
		}else{
			char cwd[500];
			getcwd(cwd, sizeof(cwd));
			stat(entry2->d_name, &statPath);

			char checkPath[1024];
			sprintf(checkPath, "%s/%s", dir, entry2->d_name);
			stat(checkPath, &statPath);

			if (S_ISDIR(statPath.st_mode)){
				return walkDirectory(checkPath, curDepth, maxDepth, searchString);
			} else {
			}
		}
	}
	closedir(openDir);
}



int main(int argc, char ** argv)
{	
	char * startDirectory;
	int maxDepth = 3;
	int found = 0;
	walkDirectory(argv[2], 1, maxDepth, argv[1]);
	return 0;
}
