#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* progName = "basename";
const char* progVer = "1.0.0";

static const char* const usage[] = {
	"basename string [suffix]",
	NULL
};

void do_basename(const char* string, const char* suffix) {
	if(string == NULL) {
		printf(".\n");
		return;
	}
	size_t sz = strlen(string);
	char strbuf[sz + 1];
	memcpy(&strbuf, string, sz);
	strbuf[sz] = '\0';
	for(size_t i = sz; i > 0; i--) {
		if(string[i] == '/') {
			strbuf[i] = '\0';
			continue;
		}
		else {
			break;
		}
	}
	char* new = strrchr(strbuf, '/');
	if(suffix != NULL) {
		char* suff = strstr(new, suffix);
		if(suff == NULL || strcmp(suff, suffix) != 0) {
			die("Suffix doesn't exist in path.");
		}
		
		size_t index = suff - new;
		new[index] = '\0';
	}
	printf("%s\n", new + 1);
}


int main(int argc, const char** argv) {
	struct argparse_option options[] = {
		OPT_MYHELP(),
		OPT_END()
	};
	struct argparse argp;
	argparse_init(&argp, options, usage, 0);
	argparse_describe(&argp, "Prints the architecture of the machine", NULL);
	argc = argparse_parse(&argp, argc, argv);
	if(argc == 1) {
		do_basename(argv[argc -1], NULL);	
	} else if(argc == 2) {
		do_basename(argv[argc -2], argv[argc -1]);
	} else {

	}
	/* Program goes here.
	 */
	return 0;
}
