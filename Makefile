PROJECT := graphics

BUILD_DIR := build

INCLUDE_DIR := ./include
SRC_DIR := ./src
LIB_DIR := ./lib

LIBS_ARGS := 

INCLUDE := $(INCLUDE_DIR)/*
SRC := $(SRC_DIR)/*
LIBS := $(LIB_DIR)/*

install: clean compile

clean:
	rmdir $(BUILD_DIR)
	mkdir $(BUILD_DIR)

compile: $(SRC)
	g++ $(SRC) -o $(BUILD_DIR)/$(PROJECT)