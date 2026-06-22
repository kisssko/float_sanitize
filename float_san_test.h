#ifndef __FLOAT_SAN_TEST_H__
#define __FLOAT_SAN_TEST_H__

typedef struct
{
	const char * id;
	const char * description;
	float standard;
	float calculated;
} FloatTestCase;

typedef struct
{
	const char * id;
	const char * description;
	double standard;
	double calculated;
} DoubleTestCase;


float get_f_case1(void);
float get_f_case2(void);
float get_f_case3(void);
float get_f_case4(void);
float get_f_case5(void);

double get_d_case1(void);
double get_d_case2(void);
double get_d_case3(void);
double d_get_case4(void);
double get_d_case5(void);

#endif
