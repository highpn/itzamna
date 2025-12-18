
#include "../util/array.h"
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
static void test_array_init_and_push(void) {
	Array array;
	array_init(&array, sizeof(int));

	for (int i = 0; i < 20; i++) {
		array_push(&array, &i);
	}

	ASSERT_EQ(array.count, 20);
	for (size_t i = 0; i < array.count; i++) {
		int *value = (int *)array_get(&array, i);
		ASSERT_EQ(*value, (int)i);
	}
	// Test pop
	array_pop(&array); // Test pop
	ASSERT_EQ(array.count, 19);
	ASSERT_EQ(*(int *)array_get(&array, 18), 18);
	ASSERT_EQ(array.capacity, 32);
	// Free array
	array_free(&array);
	ASSERT_EQ(array.data, NULL); // Ensure data is NULL after free
	ASSERT_EQ(array.count, 0);
	ASSERT_EQ(array.capacity, 0);
}
int main(void) {
	printf("Running dynamic array tests...\n");
	test_array_init_and_push();
	printf("All dynamic array tests passed\n");
	return 0;
}