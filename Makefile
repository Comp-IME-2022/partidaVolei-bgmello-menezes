.PHONY: all
all: format build

.PHONY: format
format:	
	clang-format src/* include/* -i

.PHONY: build
build: src/main.cpp src/Partida.cpp src/Time.cpp src/Jogador.cpp
	mkdir -p bin/
	cd src/
	g++ -o bin/jogoDeVolei src/main.cpp src/Partida.cpp src/Time.cpp src/Jogador.cpp -I./include
