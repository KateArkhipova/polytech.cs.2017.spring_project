#include <stdio.h>
#include "functions.h"

int test_get_speed()
{
	int stage = 10;
	float speed = get_speed(stage);
	if (speed != 2)
		return -1;
	
	return 0;
}

int test_get_stage()
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

int test_get_rest_time()
{
	int rest_time = 179;
    int enemies_spawn = 0;
    if (get_rest_time(rest_time,enemies_spawn) != 180)
    	return -1;

    rest_time = 181;
    if (get_rest_time(rest_time,enemies_spawn) != 181)
    	return -1;

    return 0;
} 


int main()
{
	if (test_get_speed() < 0)
	{
		printf("Test get_speed() failed!\n");
		return -1;
	}
	if (test_get_stage() < 0)
	{
		printf("Test get_stage() failed!\n");
		return -1;
	}
	if (test_get_rest_time()< 0)
	{
		printf("Test get_rest_time() failed!\n");
		return -1;
	}
	
	printf("All tests passed!\n");

	return 0;
}
