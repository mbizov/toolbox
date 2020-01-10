#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <Windows.h>

#include "errors.h"

#define MAX_FILES 0xff /* i don't care anymore */

/* data structure to hold settings and operands */
typedef struct _list_opts {
	bool detailed_list; /* print more info about files */
	bool no_skip; /* do not skip files with hidden attribute */
	bool no_skip2; /* do not skip implied . and .. */
	bool single; /* not a dir/wildcard (ignored) */
	char *file; /* file/dir paths and wildcards */
} list_opts_t;

/* formats the attributes in a line format like ls -l */
void FormatAttributes(DWORD dwFileAttributes);

/* dump information about a file according to the settings structure */
int DumpFileInfo(WIN32_FIND_DATA fd, list_opts_t *lo);

/*
print items in a directory or a single file
calls DumpFileInfo
*/
int ListFiles(list_opts_t *lo);

#endif
