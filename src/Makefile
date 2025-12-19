# ===============================
# Compiler & Flags
# ===============================
CC      := gcc
CSTD    := -std=c11
WARN    := -Wall -Wextra -Wpedantic
OPT     := -O2
DEBUG   := -g
CFLAGS  := $(CSTD) $(WARN) $(OPT) $(DEBUG)

# ===============================
# Directories
# ===============================
SRC_DIRS := \
	core \
	graphics \
	audio \
	math \
	platform \
	runtime \
	util \
	world \
	graph

INC := $(addprefix -I,$(SRC_DIRS))
INC += -I/usr/include/SDL3

BUILD_DIR := build
BIN_DIR   := $(BUILD_DIR)/bin
OBJ_DIR   := $(BUILD_DIR)/obj
LIB_DIR   := $(BUILD_DIR)/lib

ENGINE := $(BIN_DIR)/engine
ENGINE_LIB := $(LIB_DIR)/libengine.a

# ===============================
# Platform Detection
# ===============================
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	PLATFORM_SRC := platform/linux.c
	LIBS := -lSDL3 -lm -lpthread -ldl -lasound
endif

ifeq ($(OS),Windows_NT)
	PLATFORM_SRC := platform/windows.c
	LIBS := -luser32 -lgdi32
endif

# ===============================
# Source Files
# ===============================
SRC := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c)) \
       $(PLATFORM_SRC)

OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

# ===============================
# Default Target
# ===============================
.PHONY: all
all: $(ENGINE)

# ===============================
# Build Engine Static Library
# ===============================
$(ENGINE_LIB): $(OBJ)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $(OBJ)
	@echo "Built engine library: $@"

# ===============================
# Build Engine Executable
# ===============================
$(ENGINE): $(ENGINE_LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(ENGINE_LIB) $(LIBS)
	@echo "Built engine: $@"

# ===============================
# Compile Objects
# ===============================
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# ===============================
# Clean
# ===============================
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	echo "Cleaned build directory"

# ===============================
# Run
# ===============================
.PHONY: run
run: $(ENGINE)
	./$(ENGINE)