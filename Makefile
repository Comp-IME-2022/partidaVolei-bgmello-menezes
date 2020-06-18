CC := g++
SRCDIR := src
INCLUDEDIR := ./include
TARGET := bin/jogoDeVolei

SOURCES := $(shell find $(SRCDIR) -type f)

.PHONY: all
all: format build

.PHONY: format
format:	
	clang-format src/* include/* -i

.PHONY: build
build: $(SOURCES)
	mkdir -p bin/
	$(CC) -o $(TARGET) $(SOURCES) -I$(INCLUDEDIR)
