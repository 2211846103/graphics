PROJECT := graphics

BUILD_DIR := build

INCLUDE_DIR := include
SRC_DIR := src
LIB_DIR := libs

INCLUDE := $(wildcard $(INCLUDE_DIR)/*.hpp)
SRC := $(wildcard $(SRC_DIR)/*.cpp)
LIBS :=  $(basename $(wildcard *.dll))

install: clean compile

clean:
	rm -rf $(BUILD_DIR)
	mkdir $(BUILD_DIR)

compile: $(SRC)
	g++ $(SRC) -I ./$(INCLUDE_DIR) -L ./$(LIB_DIR) -lglfw3 -o $(BUILD_DIR)/$(PROJECT)