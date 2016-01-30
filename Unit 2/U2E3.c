#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

void main()
{
	int intMin = INT_MIN;
	int intMax = INT_MAX;
	float floatMin = FLT_MIN;
	float floatMax = FLT_MAX;
	long longMin = LONG_MIN;
	long longMax = LONG_MAX;
	long long llMin = LLONG_MIN;
	long long llMax = LLONG_MAX;
	short shortMin = SHRT_MIN;
	short shortMax = SHRT_MAX;
	double doubleMin = DBL_MIN;
	double doubleMax = DBL_MAX;
	long double lDoubleMin = LDBL_MIN;
	long double lDoubleMax = LDBL_MAX;
	
	printf("IntMin: %d \n",intMin - 1);
	printf("IntMax: %d \n",intMax + 1);
	
	// same goes for the other data types
}
