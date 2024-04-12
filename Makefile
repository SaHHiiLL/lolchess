
CC=clang++
OUT_DIR=target
CFLAGS=-g
build: 
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -o $(OUT_DIR)/lolchess src/*.cpp -lraylib -lGL -lm -lpthread -ldl -lrt 
