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
	world

INCLUDE_DIRS := $(SRC_DIRS)
INC := $(addprefix -I,$(INCLUDE_DIRS))

BUILD_DIR := build
BIN_DIR   := $(BUILD_DIR)/bin
OBJ_DIR   := $(BUILD_DIR)/obj

ENGINE := $(BIN_DIR)/engine

# ===============================
# Platform Detection
# ===============================
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	PLATFORM_SRC := platform/linux.c
	LIBS := -lm -lpthread
endif

ifeq ($(OS),Windows_NT)
	PLATFORM_SRC := platform/windows.c
	LIBS := -luser32 -lgdi32
endif

# ===============================
# Source Files
# ===============================
SRC := \
	$(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c)) \
	$(PLATFORM_SRC)

OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

# ===============================
# Default Target
# ===============================
.PHONY: all
all: $(ENGINE)

# ===============================
# Build Engine
# ===============================
$(ENGINE): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIBS)
	@echo "Built engine: $@"

# ===============================
# Compile Objects
# ===============================
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# ===============================
# Tools
# ===============================
TOOLS := \
	mapcompiler \
	texturepacker

.PHONY: tools
tools: $(TOOLS)

mapcompiler:
	$(CC) $(CFLAGS) $(INC) \
		tools/mapcompiler/*.c \
		-o $(BIN_DIR)/mapcompiler

texturepacker:
	$(CC) $(CFLAGS) $(INC) \
		tools/texturepacker/*.c \
		-o $(BIN_DIR)/texturepacker

# ===============================
# Tests
# ===============================
TESTS := \
	test_bsp \
	test_collision

.PHONY: tests
tests: $(TESTS)

test_bsp:
	$(CC) $(CFLAGS) $(INC) \
		tests/test_bsp.c \
		world/bsp.c math/plane.c util/array.c \
		-o $(BIN_DIR)/test_bsp

test_collision:
	$(CC) $(CFLAGS) $(INC) \
		tests/test_collision.c \
		world/collision.c math/plane.c \
		-o $(BIN_DIR)/test_collision

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
