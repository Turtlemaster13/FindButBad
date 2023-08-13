#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>


void walkDirectory(char *dir, int curDepth, int maxDepth, char * searchString)
{	
	struct stat statPath;
	if (curDepth > maxDepth) {
		return;
	}
	curDepth++;

	// Open the local directory and look for the file
	DIR *openDir = opendir(dir);
	if (openDir == NULL) {
		printf("error");
		return;
	}
	struct dirent *entry;
	while ((entry = readdir(openDir)) != NULL) {
		if ( strncmp(entry->d_name, "..", strlen("..")) == 0  || strncmp(entry->d_name, ".", strlen("."))== 0){
			continue;
		}
		if (strncmp(entry->d_name, searchString, strlen(searchString)) == 0){
			printf("found file : [%s/%s]\n", dir, searchString);
			closedir(openDir);
			exit(0);
		}
	}

	// Find local directories and search those
	rewinddir(openDir);
	while ((entry = readdir(openDir)) != NULL) {
		if ( strncmp(entry->d_name, "..", strlen("..")) == 0  || strncmp(entry->d_name, ".", strlen("."))== 0){
			continue;
		}
		char cwd[128];
		getcwd(cwd, sizeof(cwd));
		char checkPath[512];
		if (strcmp(dir, "/") == 0){
			sprintf(checkPath, "%s%s", dir, entry->d_name);
		} else {
			sprintf(checkPath, "%s/%s", dir, entry->d_name);
		}
		stat(checkPath, &statPath);
		if (S_ISDIR(statPath.st_mode)){
			printf("checking [%s, %s]\n", dir, entry->d_name);
			walkDirectory(checkPath, curDepth, maxDepth, searchString);
		
		}
	}
	closedir(openDir);
	return;
}



int main(int argc, char ** argv)
{	
	char * startDirectory;
	int maxDepth = 6;
	int found = 0;
	if (strncmp(argv[1], "--help", strlen("--help")) == 0){
		printf("----finds a file----\narg[1]: start directory\narg[2]: the file to find\n");
	} else {
		walkDirectory(argv[1], 1, maxDepth, argv[2]);
	}
	return 0;
}
