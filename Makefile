
CC=clang++
OUT_DIR=target
CFLAGS=-g  -lm -ldl -lrt -lpthread


build: pre
	$(CC) -o $(OUT_DIR)/lolchess src/*.cpp -g3 ./lib/raylib/src/libraylib.a $(CFLAGS)

debug:
	$(CC) -o $(OUT_DIR)/lolchess src/main.cpp src/chess2.cpp -g3 ./lib/raylib/src/libraylib.a $(CFLAGS)

pre:
	mkdir -p $(OUT_DIR)

dep: pre
	unzip resourcees/lila-public-piece.zip -d ./target
	python3 resourcees/convert.py

trash:
	trash target

