/*
 * Copyright (c) 2019 Oticon A/S
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ztest.h>
#include <sys/util.h>
#include <string.h>

/**
 * @brief Test of u8_to_dec
 *
 * This test verifies conversion of various input values.
 *
 */
static void test_u8_to_dec(void)
{
	char text[4];
	u8_t len;

	len = u8_to_dec(text, sizeof(text), 0);
	zassert_equal(len, 1, "Length of 0 is not 1");
	zassert_equal(strcmp(text, "0"), 0,
		      "Value=0 is not converted to \"0\"");

	len = u8_to_dec(text, sizeof(text), 1);
	zassert_equal(len, 1, "Length of 1 is not 1");
	zassert_equal(strcmp(text, "1"), 0,
		      "Value=1 is not converted to \"1\"");

	len = u8_to_dec(text, sizeof(text), 11);
	zassert_equal(len, 2, "Length of 11 is not 2");
	zassert_equal(strcmp(text, "11"), 0,
		      "Value=10 is not converted to \"11\"");

	len = u8_to_dec(text, sizeof(text), 100);
	zassert_equal(len, 3, "Length of 100 is not 3");
	zassert_equal(strcmp(text, "100"), 0,
		      "Value=100 is not converted to \"100\"");

	len = u8_to_dec(text, sizeof(text), 101);
	zassert_equal(len, 3, "Length of 101 is not 3");
	zassert_equal(strcmp(text, "101"), 0,
		      "Value=101 is not converted to \"101\"");

	len = u8_to_dec(text, sizeof(text), 255);
	zassert_equal(len, 3, "Length of 255 is not 3");
	zassert_equal(strcmp(text, "255"), 0,
		      "Value=255 is not converted to \"255\"");

	memset(text, 0, sizeof(text));
	len = u8_to_dec(text, 2, 123);
	zassert_equal(len, 2,
		      "Length of converted value using 2 byte buffer isn't 2");
	zassert_equal(
		strcmp(text, "12"), 0,
		"Value=123 is not converted to \"12\" using 2-byte buffer");

	memset(text, 0, sizeof(text));
	len = u8_to_dec(text, 1, 123);
	zassert_equal(len, 1,
		      "Length of converted value using 1 byte buffer isn't 1");
	zassert_equal(
		strcmp(text, "1"), 0,
		"Value=123 is not converted to \"1\" using 1-byte buffer");

	memset(text, 0, sizeof(text));
	len = u8_to_dec(text, 0, 123);
	zassert_equal(len, 0,
		      "Length of converted value using 0 byte buffer isn't 0");
}

#define TEST_DEFINE_1 1
#define TEST_DEFINE_0 0

void test_COND_CODE_1(void)
{
	/* Test validates that expected code has been injected. Failure would
	 * be seen in compilation (lack of variable or ununsed variable.
	 */
	COND_CODE_1(1, (u32_t x0 = 1;), (u32_t y0;))
	zassert_true((x0 == 1), NULL);

	COND_CODE_1(NOT_EXISTING_DEFINE, (u32_t x1 = 1;), (u32_t y1 = 1;))
	zassert_true((y1 == 1), NULL);

	COND_CODE_1(TEST_DEFINE_1, (u32_t x2 = 1;), (u32_t y2 = 1;))
	zassert_true((x2 == 1), NULL);

	COND_CODE_1(2, (u32_t x3 = 1;), (u32_t y3 = 1;))
	zassert_true((y3 == 1), NULL);
}

void test_COND_CODE_0(void)
{
	/* Test validates that expected code has been injected. Failure would
	 * be seen in compilation (lack of variable or ununsed variable.
	 */
	COND_CODE_0(0, (u32_t x0 = 1;), (u32_t y0;))
	zassert_true((x0 == 1), NULL);

	COND_CODE_0(NOT_EXISTING_DEFINE, (u32_t x1 = 1;), (u32_t y1 = 1;))
	zassert_true((y1 == 1), NULL);

	COND_CODE_0(TEST_DEFINE_0, (u32_t x2 = 1;), (u32_t y2 = 1;))
	zassert_true((x2 == 1), NULL);

	COND_CODE_0(2, (u32_t x3 = 1;), (u32_t y3 = 1;))
	zassert_true((y3 == 1), NULL);
}

#undef ZERO
#undef SEVEN
#undef A_BUILD_ERROR
#define ZERO 0
#define SEVEN 7
#define A_BUILD_ERROR (this would be a build error if you used || or &&)

void test_UTIL_OR(void)
{
	zassert_equal(UTIL_OR(SEVEN, A_BUILD_ERROR), 7, NULL);
	zassert_equal(UTIL_OR(7, 0), 7, NULL);
	zassert_equal(UTIL_OR(SEVEN, ZERO), 7, NULL);
	zassert_equal(UTIL_OR(0, 7), 7, NULL);
	zassert_equal(UTIL_OR(ZERO, SEVEN), 7, NULL);
	zassert_equal(UTIL_OR(0, 0), 0, NULL);
	zassert_equal(UTIL_OR(ZERO, ZERO), 0, NULL);
}

void test_UTIL_AND(void)
{
	zassert_equal(UTIL_AND(ZERO, A_BUILD_ERROR), 0, NULL);
	zassert_equal(UTIL_AND(7, 0), 0, NULL);
	zassert_equal(UTIL_AND(SEVEN, ZERO), 0, NULL);
	zassert_equal(UTIL_AND(0, 7), 0, NULL);
	zassert_equal(UTIL_AND(ZERO, SEVEN), 0, NULL);
	zassert_equal(UTIL_AND(0, 0), 0, NULL);
	zassert_equal(UTIL_AND(ZERO, ZERO), 0, NULL);
	zassert_equal(UTIL_AND(7, 7), 7, NULL);
	zassert_equal(UTIL_AND(7, SEVEN), 7, NULL);
	zassert_equal(UTIL_AND(SEVEN, 7), 7, NULL);
	zassert_equal(UTIL_AND(SEVEN, SEVEN), 7, NULL);
}

void test_IF_ENABLED(void)
{
	#define test_IF_ENABLED_FLAG_A 1
	#define test_IF_ENABLED_FLAG_B 0

	IF_ENABLED(test_IF_ENABLED_FLAG_A, (goto skipped;))
	/* location should be skipped if IF_ENABLED macro is correct. */
	zassert_false(true, "location should be skipped");
skipped:
	IF_ENABLED(test_IF_ENABLED_FLAG_B, (zassert_false(true, "");))

	IF_ENABLED(test_IF_ENABLED_FLAG_C, (zassert_false(true, "");))

	zassert_true(true, "");

	#undef test_IF_ENABLED_FLAG_A
	#undef test_IF_ENABLED_FLAG_B
}

void test_UTIL_LISTIFY(void)
{
	int i = 0;

#define INC(x, _)		\
	do {			\
		i += x;		\
	} while (0);

#define DEFINE(x, y) int a##x = x * y;
#define MARK_UNUSED(x, _) ARG_UNUSED(a##x);

	UTIL_LISTIFY(4, DEFINE, 2)
	UTIL_LISTIFY(4, MARK_UNUSED, _)

	UTIL_LISTIFY(4, INC, _)

	zassert_equal(i, 0 + 1 + 2 + 3, NULL);
	zassert_equal(a0, 0, NULL);
	zassert_equal(a1, 2, NULL);
	zassert_equal(a2, 4, NULL);
	zassert_equal(a3, 6, NULL);
}

void test_MACRO_MAP_CAT(void)
{
	int item_a_item_b_item_c_ = 1;

#undef FOO
#define FOO(x) item_##x##_
	zassert_equal(MACRO_MAP_CAT(FOO, a, b, c), 1, "MACRO_MAP_CAT");
#undef FOO
}

static int inc_func(void)
{
	static int a = 1;

	return a++;
}

/* Test checks if @ref Z_MAX and @ref Z_MIN return correct result and perform
 * single evaluation of input arguments.
 */
static void test_z_max_z_min(void)
{
	zassert_equal(Z_MAX(inc_func(), 0), 1, "Unexpected macro result");
	/* Z_MAX should have call inc_func only once */
	zassert_equal(inc_func(), 2, "Unexpected return value");

	zassert_equal(Z_MIN(inc_func(), 2), 2, "Unexpected macro result");
	/* Z_MIN should have call inc_func only once */
	zassert_equal(inc_func(), 4, "Unexpected return value");
}

static void test_FOR_EACH(void)
{
	#define FOR_EACH_MACRO_TEST(arg) *buf++ = arg;

	u8_t array[3] = {0};
	u8_t *buf = array;

	FOR_EACH(FOR_EACH_MACRO_TEST, 1, 2, 3)

	zassert_equal(array[0], 1, "Unexpected value %d", array[0]);
	zassert_equal(array[1], 2, "Unexpected value %d", array[1]);
	zassert_equal(array[2], 3, "Unexpected value %d", array[2]);
}

static void fsum(u32_t incr, u32_t *sum)
{
	*sum = *sum + incr;
}

static void test_FOR_EACH_FIXED_ARG(void)
{
	u32_t sum = 0;

	FOR_EACH_FIXED_ARG(fsum, &sum, 1, 2, 3)

	zassert_equal(sum, 6, "Unexpected value %d", sum);
}

static void test_FOR_EACH_IDX(void)
{
	#define FOR_EACH_IDX_MACRO_TEST(n, arg) u8_t a##n = arg;

	FOR_EACH_IDX(FOR_EACH_IDX_MACRO_TEST, 1, 2, 3)

	zassert_equal(a0, 1, "Unexpected value %d", a0);
	zassert_equal(a1, 2, "Unexpected value %d", a1);
	zassert_equal(a2, 3, "Unexpected value %d", a2);

	#define FOR_EACH_IDX_MACRO_TEST2(n, arg) array[n] = arg;
	u8_t array[32] = {0};

	FOR_EACH_IDX(FOR_EACH_IDX_MACRO_TEST2, 1, 2, 3, 4, 5, 6, 7, 8,
						9, 10, 11, 12, 13, 14, 15);
	for (int i = 0; i < 15; i++) {
		zassert_equal(array[i], i + 1,
				"Unexpected value: %d", array[i]);
	}
	zassert_equal(array[15], 0, "Unexpected value: %d", array[15]);

	#define FOR_EACH_IDX_MACRO_TEST3(n, arg) &a##n,

	u8_t *a[] = {
		FOR_EACH_IDX(FOR_EACH_IDX_MACRO_TEST3, 1, 2, 3)
	};

	zassert_equal(ARRAY_SIZE(a), 3, "Unexpected value:%d", ARRAY_SIZE(a));
}

static void test_FOR_EACH_IDX_FIXED_ARG(void)
{
	#undef FOO
	#define FOO(n, arg, fixed_arg) \
		u8_t fixed_arg##n = arg;

	FOR_EACH_IDX_FIXED_ARG(FOO, a, 1, 2, 3)

	zassert_equal(a0, 1, "Unexpected value %d", a0);
	zassert_equal(a1, 2, "Unexpected value %d", a1);
	zassert_equal(a2, 3, "Unexpected value %d", a2);
}

static void test_IS_EMPTY(void)
{
	#define test_IS_EMPTY_REAL_EMPTY
	#define test_IS_EMPTY_NOT_EMPTY XXX_DO_NOT_REPLACE_XXX
	zassert_true(IS_EMPTY(test_IS_EMPTY_REAL_EMPTY),
		     "Expected to be empty");
	zassert_false(IS_EMPTY(test_IS_EMPTY_NOT_EMPTY),
		      "Expected to be non-empty");
}

static void test_LIST_DROP_EMPTY(void)
{
	/*
	 * The real definition should be:
	 *  #define TEST_BROKEN_LIST ,Henry,,Dorsett,Case,
	 * but checkpatch complains, so below equivalent is defined.
	 */
	#define TEST_BROKEN_LIST EMPTY, Henry, EMPTY, Dorsett, Case,
	#define TEST_FIXED_LIST LIST_DROP_EMPTY(TEST_BROKEN_LIST)
	#define TEST_MKSTR(a) #a,
	static const char *const arr[] = {
		FOR_EACH(TEST_MKSTR, TEST_FIXED_LIST)
	};

	zassert_equal(sizeof(arr) / sizeof(char *), 3,
		      "Failed to cleanup list");
	zassert_equal(strcmp(arr[0], "Henry"), 0, "Failed at 0");
	zassert_equal(strcmp(arr[1], "Dorsett"), 0, "Failed at 1");
	zassert_equal(strcmp(arr[2], "Case"), 0, "Failed at 0");
}

void test_main(void)
{
	ztest_test_suite(test_lib_sys_util_tests,
			 ztest_unit_test(test_u8_to_dec),
			 ztest_unit_test(test_COND_CODE_1),
			 ztest_unit_test(test_COND_CODE_0),
			 ztest_unit_test(test_UTIL_OR),
			 ztest_unit_test(test_UTIL_AND),
			 ztest_unit_test(test_IF_ENABLED),
			 ztest_unit_test(test_UTIL_LISTIFY),
			 ztest_unit_test(test_MACRO_MAP_CAT),
			 ztest_unit_test(test_z_max_z_min),
			 ztest_unit_test(test_FOR_EACH),
			 ztest_unit_test(test_FOR_EACH_FIXED_ARG),
			 ztest_unit_test(test_FOR_EACH_IDX),
			 ztest_unit_test(test_FOR_EACH_IDX_FIXED_ARG),
			 ztest_unit_test(test_IS_EMPTY),
			 ztest_unit_test(test_LIST_DROP_EMPTY)
	);

	ztest_run_test_suite(test_lib_sys_util_tests);
}
