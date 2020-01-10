#define _MBCS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <Windows.h>
#include <getopt.h>

#include "errors.h"
#include "list.h"

/*
TODO:
colour support
directory listing without wildcards
sorting

fix attribute formatting in list.c

*/

void help(char **argv) {
	printf("usage: %s [-aAlh] dir...\n", argv[0]);
	printf("list files in a directory\n");
	printf("  -a\tdo not skip hidden files\n");
	printf("  -A\tdo not skip anything except . and ..\n");
	printf("  -l\tlong (detailed format)\n");
	printf("  -h\tprint help message\n");
	return;
}

int main(int argc, char **argv) {
	list_opts_t lo;
	
	/* default settings */
	lo.detailed_list = false;
	lo.no_skip = false;
	lo.no_skip2 = false;
	lo.single = false;
	lo.file = "*";
	
	
	/* parse command line args */
	int c;
	opterr = 0; /* supress built-in warnings */
	while ((c = getopt(argc, argv, "hlaA")) != EOF) {
		switch (c) {
			case 'h':
				help(argv);
				return ERROR_NONE;
			case 'l':
				lo.detailed_list = true;
				break;
			case 'a':
				lo.no_skip2 = true;
				break;
			case 'A':
				lo.no_skip = true;
				break;
			default:
				printf("error: invalid option '-%c'.\ntry '%s -h' for more information.\n", optopt, argv[0]);
				return ERROR_ARGS;
		}
	}
	
	/*0      1  2  3 4 5 6*/
	/*a.exe -a -b -c 1 2 3*/
	
	if (optind != argc) {
		for (int i = optind; i < argc; i++) {
			lo.file = argv[i];
			ListFiles(&lo);
		}
	} else {
		ListFiles(&lo);
	}
}
