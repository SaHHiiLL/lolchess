
CC=clang++
OUT_DIR=target
CFLAGS=-g  -lm -ldl -lrt -lpthread

pre:
	mkdir -p $(OUT_DIR)

build: pre
	$(CC) -o $(OUT_DIR)/lolchess src/*.cpp -g3 ./raylib/src/libraylib.a $(CFLAGS)

dep: pre
	unzip resourcees/lila-public-piece.zip -d ./target
	python3 resourcees/convert.py

trash:
	trash target

