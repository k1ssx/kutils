#include "common.h"

#include <stdio.h>
#include <stdlib.h>


const char* progName = "arch";
const char* progVer = "1.0.0";

static const char* const usage[] = {
	"arch",
	NULL
};


int main(int argc, const char** argv) {
	struct argparse_option options[] = {
		OPT_MYHELP(),
		OPT_END()
	};
	struct argparse argp;
	argparse_init(&argp, options, usage, 0);
	argparse_describe(&argp, "Prints the architecture of the machine", NULL);
	argc = argparse_parse(&argp, argc, argv);
	/* Program goes here.
	 */
	return 0;
}
