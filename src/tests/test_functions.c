#include "unity.h"
#include "functions.h"

void setUp(void)
{
}
void tearDown(void)
{
}
void test_add( void )
{
   
	int stage = 10;
	float speed = get_speed(stage);
	if (speed != 2)
		return -1;
	
	return 0;
}