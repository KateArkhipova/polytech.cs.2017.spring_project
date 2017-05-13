
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
}