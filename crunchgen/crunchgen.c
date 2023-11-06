#define _GNU_SOURCE

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#ifndef EXECNAME
#define EXECNAME "crunchgen"
#endif

struct stub {
	char *name;
	int (*f)();
};

extern struct stub entry_points[];

char *progname;

void usage() {
	int columns = 0, len;
	struct stub *ep;

	(void) printf("Usage: %s <prog> <args> ..., where <prog> is one of:\n", EXECNAME);
	for(ep = entry_points; ep->name != NULL; ++ep) {
		len = strlen(ep->name) + 1;
		if(columns + len < 80) columns += len;
		else {
			(void) putchar('\n');
			columns = len;
		}
		(void) printf(" %s", ep->name);
	}
	(void) putchar('\n');
}

int crunched_main(int argc, char *argv[], char **envp) {
	bool notcompiled = strcmp(EXECNAME, progname) != 0;
	if(notcompiled) (void) fprintf(stderr, "%s: %s not compiled in\n", EXECNAME, progname);
	usage();
	return notcompiled ? 1 : 0;
}

int main(int argc, char *argv[], char **envp) {
	struct stub *ep;

	if(strcmp(EXECNAME, program_invocation_short_name) != 0) progname = program_invocation_short_name;
	else {
		if(argc == 1) {
			usage();
			return 1;
		}
		progname = argv[1];
		argc -= 1;
		++argv;
	}

	for(ep = entry_points; ep->name != NULL; ep++) {
		if(strcmp(progname, ep->name) == 0) {
			break;
		}
	}

	if(ep->name) return ep->f(argc, argv, envp);
	return crunched_main(argc, argv, envp);
}

#include"entry_points.h"
