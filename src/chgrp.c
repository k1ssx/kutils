#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <grp.h>

const char* progName = "arch";
const char* progVer = "1.0.0";

static const char* const usage[] = {
	"chgrp [-RhLHPv]... GROUP FILE...",
	NULL
};


int main(int argc, const char** argv) {
	int recurse = 0;
	int no_deref = 0;
	int traverse_symlinks = 0;
	int traverse_cmd_symlinks = 0;
	int no_traverse = 0;
	int verbose = 0;
	struct argparse_option options[] = {
		OPT_MYHELP(),
		OPT_BOOLEAN('R', NULL, &recurse, "Recurse"),
		OPT_BOOLEAN('h', NULL, &no_deref, "Affect symlinks instead of targets"),
		OPT_BOOLEAN('L', NULL, &traverse_symlinks, "Traverse all symlinks to directories"),
		OPT_BOOLEAN('H', NULL, &traverse_cmd_symlinks, "Traverse symlinks on command line"),
		OPT_BOOLEAN('P', NULL, &no_traverse, "Don't traverse symlinks (default)"),
		OPT_BOOLEAN('v', NULL, &verbose, "Verbose output"),
		OPT_END()
	};
	struct argparse argp;
	argparse_init(&argp, options, usage, 0);
	argparse_describe(&argp, "Prints the architecture of the machine", NULL);
	argc = argparse_parse(&argp, argc, argv);
	/* Program goes here. */
	if(argc < 2) {
		argparse_usage(&argp);
		die("Not enough arguments.\n");
	}
	else {
		bool integer_convert = true;
		int gid = strtol(argv[0], NULL, 0);
		if(gid == 0 && strcmp(argv[0], "0") != 0) {
			//Failed integer conversion.
			integer_convert = false;
		}
		if(integer_convert == false) {
			errno = 0;
			struct group* grp = getgrnam(argv[0]);
			if(grp == NULL) {
				die("Failed to get gid: %s\n", strerror(errno));			
			}
			gid = grp->gr_gid;
		}
		if(verbose)
			fprintf(stderr, "GID: %d\n", gid); 
		
	}



	

	return 0;
}
