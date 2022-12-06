CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -I./inc -I../libmx/inc -I../network/inc -I../cjson/inc

SOURCE_FILES = *.c
OBJECT_FILES = *.o
OBJECT_DIR = ./obj
SOURCE_DIR = ./src

SRC_PATH = $(wildcard $(SOURCE_DIR)/$(SOURCE_FILES))
OUTPUT_FILE = libmodel.a

all: clean obj libmodel

obj:
	if [ ! -d $(OBJECT_DIR) ]; then mkdir $(OBJECT_DIR); fi
	$(CC) $(CFLAGS) -g -c $(SRC_PATH)
	mv $(OBJECT_FILES) $(OBJECT_DIR)

libmodel:
	# $(CC) $(CFLAGS) -o $(OUTPUT_FILE) $(OBJECT_DIR)/$(OBJECT_FILES) # delete -g
	ar -cq $(OUTPUT_FILE) $(OBJECT_DIR)/*.o ../libmx/obj/*.o

uninstall:
	if [ -d $(OBJECT_DIR) ]; then rm -rf $(OBJECT_DIR); fi
	if [ -f $(OUTPUT_FILE) ]; then rm $(OUTPUT_FILE); fi
	if [ -f *.o ]; then rm *.o; fi

clean:
	if [ -d $(OBJECT_DIR) ]; then rm -rf $(OBJECT_DIR); fi

reinstall: uninstall all