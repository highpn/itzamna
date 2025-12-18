#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../math/vec3.h"
#define NORMALIZE_TOL 1e-3f
#define EPSILON 1e-6f

/* ===============================
   Test Macros
   =============================== */
#define ASSERT_NEAR(a, b, tol)                                                                     \
	do {                                                                                       \
		if (fabsf((a) - (b)) > (tol)) {                                                    \
			fprintf(stderr, "ASSERT_NEAR failed: %s=%f %s=%f tol=%f (%s:%d)\n",        \
			        #a, (float)(a), #b, (float)(b), (float)(tol), __FILE__, __LINE__); \
			exit(1);                                                                   \
		}                                                                                  \
	} while (0)

#define ASSERT_TRUE(cond)                                                                               \
	do {                                                                                            \
		if (!(cond)) {                                                                          \
			fprintf(stderr, "ASSERT_TRUE failed: %s (%s:%d)\n", #cond, __FILE__, __LINE__); \
			exit(1);                                                                        \
		}                                                                                       \
	} while (0)

/* ===============================
   Tests normalize function
   =============================== */

static void test_vec3_normalize_direction(void) {
	vec3_t v = {2.0f, 0.0f, 0.0f};
	vec3_t n = vec3_normalize(v);

	ASSERT_NEAR(n.x, 1.0f, 1e-2f);
	ASSERT_NEAR(n.y, 0.0f, 1e-6f);
	ASSERT_NEAR(n.z, 0.0f, 1e-6f);
}

static void test_vec3_normalize_unit_vector(void) {
	vec3_t v = {0.0f, 1.0f, 0.0f};
	vec3_t n = vec3_normalize(v);

	ASSERT_NEAR(n.x, 0.0f, 1e-6f);
	ASSERT_NEAR(n.y, 1.0f, 1e-2f);
	ASSERT_NEAR(n.z, 0.0f, 1e-2f);
}

static void test_vec3_normalize_zero_vector(void) {
	vec3_t v = {0.0f, 0.0f, 0.0f};
	vec3_t n = vec3_normalize(v);

	/* zero vector stays zero */
	ASSERT_NEAR(n.x, 0.0f, 1e-6f);
	ASSERT_NEAR(n.y, 0.0f, 1e-6f);
	ASSERT_NEAR(n.z, 0.0f, 1e-6f);
}

static void test_vec3_normalize_no_nan(void) {
	vec3_t v = {1.0f, 2.0f, 3.0f};
	vec3_t n = vec3_normalize(v);

	ASSERT_TRUE(isfinite(n.x));
	ASSERT_TRUE(isfinite(n.y));
	ASSERT_TRUE(isfinite(n.z));
}

static void test_vec3_normalize_vector(void) {
	vec3_t v = {1.0f, 2.0f, 3.0f};
	vec3_t n = vec3_normalize(v);

	ASSERT_NEAR(n.x, 0.267261f, 1e-3f);
	ASSERT_NEAR(n.y, 0.534522f, 1e-3f);
	ASSERT_NEAR(n.z, 0.801784f, 1e-3f);
	ASSERT_TRUE(isfinite(n.y));
	ASSERT_TRUE(isfinite(n.z));
}
/* ===============================
   Test vec3 addition
   ===============================
*/
static void test_vec3_add_sub(void) {
	vec3_t a = {1, 2, 3};
	vec3_t b = {4, 5, 6};

	vec3_t c = vec3_add(a, b);
	ASSERT_NEAR(c.x, 5, EPSILON);
	ASSERT_NEAR(c.y, 7, EPSILON);
	ASSERT_NEAR(c.z, 9, EPSILON);

	vec3_t d = vec3_sub(c, a);
	ASSERT_NEAR(d.x, 4, EPSILON);
	ASSERT_NEAR(d.y, 5, EPSILON);
	ASSERT_NEAR(d.z, 6, EPSILON);
}
/* ===============================
   Test vec3 scaling
   ===============================
*/
static void test_vec3_scale(void) {
	vec3_t v = {1, -2, 3};
	vec3_t s = vec3_scale(v, 2.5f);

	ASSERT_NEAR(s.x, 2.5f, EPSILON);
	ASSERT_NEAR(s.y, -5.0f, EPSILON);
	ASSERT_NEAR(s.z, 7.5f, EPSILON);
}
/* ===============================
   Test vec3 dot and cross product
   ===============================
*/
static void test_vec3_dot_cross(void) {
	vec3_t a = {1, 0, 0};
	vec3_t b = {0, 1, 0};

	float dot = vec3_dot(a, b);
	ASSERT_NEAR(dot, 0.0f, EPSILON);

	vec3_t c = vec3_cross(a, b);
	ASSERT_NEAR(c.x, 0.0f, EPSILON);
	ASSERT_NEAR(c.y, 0.0f, EPSILON);
	ASSERT_NEAR(c.z, 1.0f, EPSILON);
}
/* ===============================
   Test vec3 length and normalize
   ===============================
*/
static void test_vec3_length_normalize(void) {
	vec3_t v = {1, 2, 3};
	float len = vec3_inv_length(v);
	ASSERT_NEAR(len, 1.0f / sqrtf(14.0f), NORMALIZE_TOL);

	vec3_t n = vec3_normalize(v);
	float len2 = vec3_dot(n, n);
	ASSERT_NEAR(len2, 1.0f, NORMALIZE_TOL);
	ASSERT_TRUE(isfinite(n.x));
	ASSERT_TRUE(isfinite(n.y));
	ASSERT_TRUE(isfinite(n.z));
}

static void test_vec3_normalize_edge_cases(void) {
	// Zero vector
	vec3_t zero = {0, 0, 0};
	vec3_t n0 = vec3_normalize(zero);
	ASSERT_NEAR(n0.x, 0.0f, EPSILON);
	ASSERT_NEAR(n0.y, 0.0f, EPSILON);
	ASSERT_NEAR(n0.z, 0.0f, EPSILON);

	// Already unit vector
	vec3_t u = {0, 1, 0};
	vec3_t n1 = vec3_normalize(u);
	ASSERT_NEAR(n1.x, 0.0f, EPSILON);
	ASSERT_NEAR(n1.y, 1.0f, 1E-2f);
	ASSERT_NEAR(n1.z, 0.0f, EPSILON);
}
/* ===============================
   Test Runner
   =============================== */
int main(void) {
	printf("Running vec3_normalize tests...\n");

	test_vec3_normalize_direction();
	test_vec3_normalize_unit_vector();
	test_vec3_normalize_zero_vector();
	test_vec3_normalize_no_nan();
	test_vec3_normalize_vector();
	test_vec3_add_sub();
	test_vec3_scale();
	test_vec3_dot_cross();
	test_vec3_length_normalize();
	test_vec3_normalize_edge_cases();
	printf("All vec3 tests passed\n");
	return 0;
}