CFLAGS ?= -O2 -g -ggdb
LDFLAGS ?=

BASIC_CFLAGS = -Wall -Wextra -fPIC
BASIC_LDFLAGS =

ALL_CFLAGS = $(BASIC_CFLAGS) $(CFLAGS)
ALL_LDFLAGS = $(BASIC_LDFLAGS) $(LDFLAGS)

CC = gcc
MKDIR = mkdir -p
BIN_DIR = bin


.PHONY: all
all : arch base64 basename chgrp

COMMON_OBJS := src/argparse.o src/common.o src/fts.o


$(COMMON_OBJS) $(OBJS): %.o : %.c
	$(CC) -o $*.o -c $(ALL_CFLAGS) $<

.PHONY: arch
arch: $(BIN_DIR)/arch 

$(BIN_DIR)/arch : src/arch.o $(COMMON_OBJS) | $(BIN_DIR)
	$(CC) $(ALL_CFLAGS) -o $@ $^

.PHONY: base64
arch: $(BIN_DIR)/base64

$(BIN_DIR)/base64 : src/base64.o $(COMMON_OBJS) | $(BIN_DIR)
	$(CC) $(ALL_CFLAGS) -o $@ $^

.PHONY: basename
arch: $(BIN_DIR)/basename

$(BIN_DIR)/basename : src/basename.o $(COMMON_OBJS) | $(BIN_DIR)
	$(CC) $(ALL_CFLAGS) -o $@ $^

$(BIN_DIR) :
	$(MKDIR) $(BIN_DIR)

.PHONY: chgrp
chgrp: $(BIN_DIR)/chgrp

$(BIN_DIR)/chgrp: src/chgrp.o $(COMMON_OBJS) | $(BIN_DIR)
	$(CC) $(ALL_CFLAGS) -o $@ $^

.PHONY: clean

clean : 
	rm -f src/*.o
	rm -rf bin/
