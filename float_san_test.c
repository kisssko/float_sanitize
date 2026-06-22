
#include <stdint.h>

#include "float_san_test.h"

float get_f_case1(void)
{
	volatile float start = 0.1f, step = 0.1f;
	return start + step + step;
}
float get_f_case2(void)
{
	volatile float a = 10.0f, b = 9.8f;
	return a - b;
}
float get_f_case3(void)
{
	volatile float a = 1.0f, b = 3.0f;
	return (a / b) * b;
}
float get_f_case4(void)
{
	volatile float sum = 0.0f, step = 0.1f;
	for (int i = 0; i < 10; i++)
		sum += step;
	return sum;
}
float get_f_case5(void)
{
	volatile float base = 123456.0f, step1 = 0.1f, step2 = 0.2f;
	return base + step1 + step1 - step2;
}

double get_d_case1(void)
{
	volatile double start = 0.1, step = 0.1;
	return start + step + step;
}
double get_d_case2(void)
{
	volatile double a = 10.0, b = 9.8;
	return a - b;
}
double get_d_case3(void)
{
	volatile double a = 1.0, b = 3.0;
	return (a / b) * b;
}
double d_get_case4(void)
{
	volatile double sum = 0.0, step = 0.1;
	for (int i = 0; i < 10; i++)
		sum += step;
	return sum;
}
double get_d_case5(void)
{
	volatile double base = 123456.0, step1 = 0.1, step2 = 0.2;
	return base + step1 + step1 - step2;
}

