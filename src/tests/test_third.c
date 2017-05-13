
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
   
	int rest_time = 179;
    int enemies_spawn = 0;
    if (get_rest_time(rest_time,enemies_spawn) != 180)
    	return -1;

    rest_time = 181;
    if (get_rest_time(rest_time,enemies_spawn) != 181)
    	return -1;

    return 0;
} 

