PROJECT := graphics

BUILD_DIR := build

INCLUDE_DIR := include
SRC_DIR := src
LIB_DIR := libs

LIBS_ARGS :=  $(basename -l$(wildcard *.dll))

INCLUDE := -I$(INCLUDE_DIR)
SRC := $(wildcard $(SRC_DIR)/*.cpp)
LIBS := -L$(LIB_DIR)

install: clean compile

clean:
	rm -rf $(BUILD_DIR)
	mkdir $(BUILD_DIR)

compile: $(SRC)
	g++ $(SRC) $(INCLUDE) $(LIBS) $(LIBS_ARGS) -o $(BUILD_DIR)/$(PROJECT)