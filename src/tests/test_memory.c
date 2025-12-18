#include "../util/memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT_EQ(val1, val2)                                                                                      \
	do {                                                                                                       \
		if ((val1) != (val2)) {                                                                            \
			fprintf(stderr, "ASSERT_EQ failed: %s != %s (%s:%d)\n", #val1, #val2, __FILE__, __LINE__); \
			exit(1);                                                                                   \
		}                                                                                                  \
	} while (0)

#define ASSERT_TRUE(cond)                                                                               \
	do {                                                                                            \
		if (!(cond)) {                                                                          \
			fprintf(stderr, "ASSERT_TRUE failed: %s (%s:%d)\n", #cond, __FILE__, __LINE__); \
			exit(1);                                                                        \
		}                                                                                       \
	} while (0)

static void test_arena_init_and_alloc(void) {
	uint8_t memory[1024];
	Arena arena;
	arena_init(&arena, memory, sizeof(memory));
	void *ptr1 = arena_alloc(&arena, 128, 16);
	ASSERT_TRUE(ptr1 != NULL);
	void *ptr2 = arena_alloc(&arena, 256, 32);
	ASSERT_TRUE(ptr2 != NULL);
	ASSERT_TRUE((size_t)ptr1 % 16 == 0);
	ASSERT_TRUE((size_t)ptr2 % 32 == 0);
}
static void test_arena_out_of_memory(void) {
	uint8_t memory[256];
	Arena arena;
	arena_init(&arena, memory, sizeof(memory));
	void *ptr = arena_alloc(&arena, 512, 16);
	ASSERT_TRUE(ptr == NULL);
}
static void test_arena_reset(void) {
	uint8_t memory[512];
	Arena arena;
	arena_init(&arena, memory, sizeof(memory));
	void *ptr1 = arena_alloc(&arena, 256, 16);
	ASSERT_TRUE(ptr1 != NULL);
	arena_reset(&arena);
	void *ptr2 = arena_alloc(&arena, 256, 16);
	ASSERT_TRUE(ptr2 != NULL);
	ASSERT_EQ(ptr1, ptr2);
}
int main(void) {
	printf("Running arena memory tests...\n");
	test_arena_init_and_alloc();
	test_arena_out_of_memory();
	test_arena_reset();
	printf("All memory tests passed\n");
	return 0;
}