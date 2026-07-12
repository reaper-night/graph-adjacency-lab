CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
SRCDIR = src
INCDIR = include
BINDIR = bin
BUILDDIR = build

SRCS = $(SRCDIR)/main.c $(SRCDIR)/graph.c $(SRCDIR)/utils.c
OBJS = $(BUILDDIR)/main.o $(BUILDDIR)/graph.o $(BUILDDIR)/utils.o
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