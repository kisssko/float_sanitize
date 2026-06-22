#ifndef __FLOAT_SAN_H__
#define __FLOAT_SAN_H__

float sanitize_float(float x, int mask_bits);
double sanitize_double(double x, int mask_bits);

typedef union
{
	float f;
	uint32_t i;
} float_uint_t;

typedef union
{
	double d;
	uint64_t i;
} double_uint_t;

#endif
