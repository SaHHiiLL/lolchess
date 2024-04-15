
CC=clang++
OUT_DIR=target
CFLAGS=-g  -lm -ldl -lrt -lpthread -Wall
RAYLIB_PATH=-g3 ./lib/raylib/src/libraylib.a

build: pre
	$(CC) -o $(OUT_DIR)/lolchess src/*.cpp $(RAYLIB_PATH) $(CFLAGS)

pre:
	mkdir -p $(OUT_DIR)

## TODO add a step to build raylib here
dep: pre
	unzip resourcees/lila-public-piece.zip -d ./target
	python3 resourcees/convert.py

trash:
	trash target

