
CC=clang++
OUT_DIR=target
CFLAGS=-g

pre:
	mkdir -p $(OUT_DIR)

build: pre
	$(CC) $(CFLAGS) -o $(OUT_DIR)/lolchess src/*.cpp -lraylib -lGL -lm -lpthread -ldl -lrt 

dep: pre
	unzip resourcees/lila-public-piece.zip -d ./target
	python3 resourcees/convert.py

trash:
	trash target

