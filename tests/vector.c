#include "../src/vector.h"

#include "test.h"

DEFAULT_COMPARE(int)
DEFAULT_TO_STRING(int, "%d")
DefVector(int, NO_FREE(int));

bool test_create() {
	intVector v = intVector_with_capacity(5);
	return EXPECT_EQ(v.size, 0) && EXPECT_EQ(v.capacity, 5);
}

bool test_push_1() {
	intVector v = intVector_with_capacity(5);
	intVector_push(&v, 1);
	intVector_push(&v, 2);
	intVector_push(&v, 3);
	intVector_push(&v, 4);
	intVector_push(&v, 5);
	return EXPECT_ALL(EXPECT_EQ(v.size, 5), EXPECT_EQ(v.capacity, 5), EXPECT_EQ(v.array[0], 1),
					  EXPECT_EQ(v.array[1], 2), EXPECT_EQ(v.array[2], 3), EXPECT_EQ(v.array[3], 4),
					  EXPECT_EQ(v.array[4], 5));
}

bool test_push_2() {
	intVector v = intVector_with_capacity(5);
	intVector_push(&v, 1);
	intVector_push(&v, 2);
	intVector_push(&v, 3);
	intVector_push(&v, 4);
	intVector_push(&v, 5);
	intVector_push(&v, 6);
	return v.size == 6 && v.capacity == 10 && v.array[0] == 1 && v.array[1] == 2 && v.array[2] == 3 &&
		   v.array[3] == 4 && v.array[4] == 5 && v.array[5] == 6;
}

bool test_destroy() {
	intVector v = intVector_with_capacity(5);
	intVector_push(&v, 1);
	intVector_push(&v, 2);
	intVector_push(&v, 3);
	intVector_push(&v, 4);
	intVector_push(&v, 5);
	intVector_destroy(v);
	return true;
}

bool test_remove_and_swap() {
	intVector v = intVector_with_capacity(5);
	intVector_push(&v, 1);
	intVector_push(&v, 2);
	intVector_push(&v, 3);
	intVector_push(&v, 4);
	intVector_push(&v, 5);
	intVector_remove_and_swap(&v, 2);
	return EXPECT_ALL(EXPECT_EQ(v.size, 4), EXPECT_EQ(v.capacity, 5), EXPECT_EQ(v.array[0], 1),
					  EXPECT_EQ(v.array[1], 2), EXPECT_EQ(v.array[2], 5), EXPECT_EQ(v.array[3], 4));
}

int main() {
	Test* tests[] = {
		&(Test){"create",		  test_create		 },
		&(Test){"push_1",		  test_push_1		 },
		&(Test){"push_2",		  test_push_2		 },
		&(Test){"destroy",		   test_destroy		   },
		&(Test){"remove_and_swap", test_remove_and_swap},
		NULL
	};

	return test("Vector", tests);
}
