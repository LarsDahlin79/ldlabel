

EXE=ldlabel

all: $(EXE)

CC=gcc
CFLAGS=-Wall -Werror -g -ansi -std=c99
SRC_DIR=../source
INC_DIR=-I../include -I../unittest
OBJ=main.o ldlabel.o utils.o graphics.o freetype.o zint_interface.o variables.o sysvar.o test_zint.o test_main.o test_utils.o test_bitmap.o test_graphics.o test_freetype.o test_variables.o test_sys_var.o test_ldlabel.o
TEST_DIR=../unittest
BITMAP=/usr/local/lib/libbitmap.so

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -lfreetype -lm -lzint -L/usr/local/lib -o $@ -lbitmap $(OBJ)

main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) $(INC_DIR) -c -o $@ $^

ldlabel.o: $(SRC_DIR)/ldlabel.c
	$(CC) $(CFLAGS) $(INC_DIR) -c -o $@ $^

utils.o: $(SRC_DIR)/utils.c
	$(CC) $(CFLAGS) $(INC_DIR) -c -o $@ $^

graphics.o: $(SRC_DIR)/graphics.c
	$(CC) $(CFLAGS) $(INC_DIR) -c -o $@ $^

freetype.o: $(SRC_DIR)/freetype.c
	$(CC) $(CFLAGS) $(INC_DIR) -I/usr/include/freetype2/ -c -o $@ $^

zint_interface.o: $(SRC_DIR)/zint_interface.c
	$(CC) $(CFLAGS) $(INC_DIR) -c -o $@ $^

variables.o: $(SRC_DIR)/variables.c
	$(CC) $(CFLAGS) $(INC_DIR) -c -o $@ $^

sysvar.o: $(SRC_DIR)/sysvar.c
	$(CC) $(CFLAGS) $(INC_DIR) -c -o $@ $^

test_bitmap.o: $(TEST_DIR)/test_bitmap.c
	$(CC) $(CFLAGS) $(INC_DIR) -c -o $@ $^ -lbitmap

test_zint.o: $(TEST_DIR)/test_zint.c
	$(CC) $(CFLAGS) $(INC_DIR) -c -o $@ $^

test_utils.o: $(TEST_DIR)/test_utils.c
	$(CC) $(CFLAGS) $(INC_DIR) -c -o $@ $^

test_graphics.o: $(TEST_DIR)/test_graphics.c
	$(CC) $(CFLAGS) $(INC_DIR) -c -o $@ $^

test_freetype.o: $(TEST_DIR)/test_freetype.c
	$(CC) $(CFLAGS) $(INC_DIR) -c -o $@ $^

test_variables.o: $(TEST_DIR)/test_variables.c
	$(CC) $(CFLAGS) $(INC_DIR) -c -o $@ $^ 

test_sys_var.o: $(TEST_DIR)/test_sysvar.c
	$(CC) $(CFLAGS) $(INC_DIR) -c -o $@ $^ 

test_ldlabel.o: $(TEST_DIR)/test_ldlabel.c
	$(CC) $(CFLAGS) $(INC_DIR) -c -o $@ $^ 

test_main.o: $(TEST_DIR)/test_main.c
	$(CC) $(CFLAGS) $(INC_DIR) -c -o $@ $^

.PHONY: clean

clean:
	rm *.o $(EXE) *.bmp
