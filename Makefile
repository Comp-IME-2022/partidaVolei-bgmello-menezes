CC := g++
SRCDIR := src
INCLUDEDIR := include
BINDIR := bin
TARGET := $(BINDIR)/jogoDeVolei

SOURCES := $(shell find $(SRCDIR) -type f | grep -v main.cpp)

.PHONY: all
all: format build

.PHONY: format
format:	
	clang-format $(SRCDIR)/* $(INCLUDEDIR)/* -i

.PHONY: build
build: $(SOURCES)
	mkdir -p bin/
	$(CC) -o $(TARGET) $(SOURCES) $(SRCDIR)/main.cpp -I$(INCLUDEDIR)
