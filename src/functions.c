#include "functions.h"

float get_speed(int stage)
{
	return (10 + stage) / 10.0;
}

int get_stage(int stage, float score)
{
	if (score == stage * 10)
		return stage + 1;
	else
		return stage;
}

int get_rest_time(int rest_time, int enemies_spawn) {
	if(rest_time<180 && enemies_spawn == 0){
		return rest_time+1;
	}
	return rest_time;
}