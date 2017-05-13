#include "functions.h"
#include "unity.h"

void setUp(void)
{
}
void tearDown(void)
{
}
void test_add( void )
{
	int stage = 1;
	float score = 0;
	int new_stage = 0;

	// Test 1
	score = 9;
	new_stage = get_stage(stage, score);
	if (new_stage != 1)
		return -1;

	// Test 2
	score = 10;
	new_stage = get_stage(stage, score);
	if (new_stage != 2)
		return -1;

	return 0;
}
