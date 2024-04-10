# Compiler
CC = g++

# Flags
WARNING_CXXFLAG = -Wall -Wextra -Werror
DEBUG_CXXFLAG   = -fshort-wchar -g
CXXFLAGS = $(DEBUG_CXXFLAG) $(WARNING_CXXFLAG)

# Directory
SRC_PATH = src
SRC_BODY = body
BIN_PATH = bin
OBJ_PATH = $(BIN_PATH)/output

# Main file
MAIN = $(SRC_PATH)/main.cpp
MAIN_OBJ = $(call SRC_TO_OBJ, $(MAIN))
MAIN_OUT = $(call SRC_TO_BIN, $(MAIN))

# Functions
BIN_FUNC =$(BIN_PATH)/$(patsubst $(SRC_PATH)/%.cpp,%,$1)
SRC_TO_BIN =$(foreach f, $1,$(call BIN_FUNC, $f))
OBJ_FUNC =$(OBJ_PATH)/$(patsubst $(SRC_PATH)/%.cpp,%.o,$1)
SRC_TO_OBJ =$(foreach f, $1,$(call OBJ_FUNC, $f))

# All Object
ALL_SRC = $(wildcard $(SRC_PATH)/*/$(SRC_BODY)/*.cpp)
ALL_OBJ = $(call SRC_TO_OBJ, $(ALL_SRC))

.PHONY: all clean run build compile recompile

all: build run

build: $(MAIN_OUT)

run:
	$(MAIN_OUT)

clean:
	rm -rf $(BIN_PATH)/output/*.o $(MAIN_OUT)

recompile: clean all

%.run: %/driver
	$(BIN_PATH)/driver

%/driver: $(ALL_OBJ) $(OBJ_PATH)/%/$(SRC_TEST)/driver.o
	$(CC) $(CXXFLAGS) -o $(BIN_PATH)/driver $(foreach f, $^,$(OBJ_PATH)/$(notdir $f))

$(MAIN_OUT): $(ALL_OBJ) $(MAIN_OBJ)
	$(CC) $(CXXFLAGS) -o $@ $(foreach f, $^,$(OBJ_PATH)/$(notdir $f))