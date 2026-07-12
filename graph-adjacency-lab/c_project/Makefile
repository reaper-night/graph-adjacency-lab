CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
SRCDIR = src
INCDIR = include
BINDIR = bin
BUILDDIR = build

SRCS = $(SRCDIR)/main.c $(SRCDIR)/logger.c $(SRCDIR)/utils.c $(SRCDIR)/sort.c
OBJS = $(BUILDDIR)/main.o $(BUILDDIR)/logger.o $(BUILDDIR)/utils.o $(BUILDDIR)/sort.o
TARGET = $(BINDIR)/app

.PHONY: all debug release clean test

all: release

debug: CFLAGS += -DDEBUG
debug: $(TARGET)

release: CFLAGS += -O2
release: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(BINDIR)

test: debug
	./$(TARGET)
	gcc -Wall -I$(INCDIR) -o tests/test_utils tests/test_utils.c $(SRCDIR)/utils.c
	./tests/test_utils