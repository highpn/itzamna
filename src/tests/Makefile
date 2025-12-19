CC := gcc

CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -O0 -g
INCLUDES:= -I../include

# Path to your engine build output
ENGINE_LIB := ../build/lib/libengine.a
LDFLAGS    := $(ENGINE_LIB)

TEST_SRC   := $(wildcard test_*.c)
TEST_BINS  := $(patsubst %.c,%,$(TEST_SRC))

.PHONY: all run clean run-tests

all: $(TEST_BINS) run-tests

%: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@ $(ENGINE_LIB)

run: all
	@for t in $(TEST_BINS); do \
		echo "Running $$t"; \
		./$$t || exit 1; \
	done
	@echo All tests passed.
clean:
	rm -f $(TEST_BINS)


