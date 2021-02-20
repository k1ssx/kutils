#include "common.h"

#include <stdio.h>
#include <stdlib.h>

#include "argparse.h"

void die(const char* str, ...) {
	va_list arg;
	va_start(arg, str);
	vfprintf(stderr,str, arg);
	va_end(arg);
	exit(1);
}


int default_help_cb(struct argparse* self, const struct argparse_option *option) {
	(void)option;
	printf("kutils v%s\n", VERSION);
	printf("%s - v%s\n", progName , progVer);
	printf("%s\n\n", COPYRIGHT_STR);
	argparse_usage(self);
	exit(0);
}
