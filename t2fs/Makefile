#
# Makefile ESQUELETO
#
# DEVE ter uma regra "all" para geração da biblioteca
# regra "clean" para remover todos os objetos gerados.
#
# NECESSARIO adaptar este esqueleto de makefile para suas necessidades.
#
# 

CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src


all: 
	libt2fs.a

libt2fs.a:
	ar crs libt2fs.a ./t2fs.o $(LIB_DIR)apidisk.o $(LIB_DIR)bitmap2.o
	rm -rf ./t2fs.o
	mv libt2fs.a $(LIB_DIR)

t2fs.o:
	gcc -g -c $(SRC_DIR)/t2fs.c -Iinclude -Wall

clean:
	rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/*.o $(SRC_DIR)/*~ $(INC_DIR)/*~ *~


