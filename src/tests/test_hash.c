#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/hash.h"
#define ASSERT_EQ(val1, val2)                                                                                      \
	do {                                                                                                       \
		if ((val1) != (val2)) {                                                                            \
			fprintf(stderr, "ASSERT_EQ failed: %s != %s (%s:%d)\n", #val1, #val2, __FILE__, __LINE__); \
		}                                                                                                  \
	} while (0)

static inline test_hash_string(void) {
	const char *test_str = "hello";
	uint32_t hash = hash_string(test_str, strlen(test_str));
	// Precomputed hash value for "hello"
	const uint32_t expected_hash = 0x4f9f2cab;
	ASSERT_EQ(hash, expected_hash);
}
/* ===============================
   Test Runner
   =============================== */
int main(void) {
	printf("Running hash_string tests...\n");
	test_hash_string();
	printf("All hash tests passed\n");
	return 0;
}