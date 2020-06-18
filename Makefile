CC := g++
SRCDIR := src
TESTDIR := test
INCLUDEDIR := include
BINDIR := bin
TARGET := $(BINDIR)/jogoDeVolei

SOURCES := $(shell find $(SRCDIR) -type f | grep -v main.cpp)

.PHONY: all
all: format test build

.PHONY: test
test: $(SOURCES)
	mkdir -p bin/
	$(CC) -o $(BINDIR)/test $(SOURCES) $(TESTDIR)/test.cpp -I$(INCLUDEDIR)

.PHONY: format
format:	
	clang-format $(SRCDIR)/* $(INCLUDEDIR)/* $(TESTDIR)/* -i

.PHONY: build
build: $(SOURCES)
	mkdir -p bin/
	$(CC) -o $(TARGET) $(SOURCES) $(SRCDIR)/main.cpp -I$(INCLUDEDIR)
