#pragma once

#include "config.h"
#include "argparse.h"

#include <stdio.h>
#include <stdarg.h>


extern const char* progName;
extern const char* progVer;

void die(const char* str, ...);
int default_help_cb(struct argparse* self, const struct argparse_option* option);

#define OPT_MYHELP() OPT_BOOLEAN('h', "help", NULL, \
		"show this help message and exit", \
		default_help_cb, 0, OPT_NONEG)
