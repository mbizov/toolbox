#include "list.h"

char *FormatAttributes(DWORD dwFileAttributes) {
	char formatted[12];
	if (dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) strcat(formatted, "a");
	else strcat(formatted, "-");
	
	if (dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED) strcat(formatted, "c");
	else strcat(formatted, "-");
	
	if (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) strcat(formatted, "d");
	else strcat(formatted, "-");
	
	if (dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED) strcat(formatted, "e");
	else strcat(formatted, "-");
	
	if (dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) strcat(formatted, "h");
	else strcat(formatted, "-");
	
	fi (dwFileAttributes & FILE_ATTRIBUTE_NORMAL) strcat(formatted, "n");
	else strcat(formatted, "-");
}

int DumpFileInfo(WIN32_FIND_DATA fd, list_opts_t *lo) {
	if (!lo->detailed_list) {
		printf("%s\n", fd.cFileName);
	}
	
	return ERROR_NONE;
}

int ListFiles(list_opts_t *lo) {
	WIN32_FIND_DATA fd; /* file finder data structure */
	HANDLE finder = INVALID_HANDLE_VALUE; /* handle for FindFirstFile and FindNextFile */
	
	
	finder = FindFirstFile(lo->file, &fd);
	
	/*printf("detailed_list = %d\n", lo->detailed_list);
	printf("no_skip = %d\n", lo->no_skip);
	printf("no_skip2 = %d\n", lo->no_skip2);
	printf("single = %d\n", lo->single);
	printf("file = %s\n", lo->file);*/
	
	do {
		DumpFileInfo(fd, lo);
	} while(FindNextFile(finder, &fd) != 0);
	
	return ERROR_NONE;
}
