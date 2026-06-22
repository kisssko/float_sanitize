
#include <stdint.h>

#include "float_san.h"


// Universal float sanitize using IEEE-754 delta signed addition
float sanitize_float(float x, int mask_bits)
{
	uint32_t tail_mask = ((1U << mask_bits) - 1U);
	uint32_t round_bit = (1U << (mask_bits - 1U));
	uint32_t carry_bit = (1U << mask_bits);

	float_uint_t data, delta;
	data.f = x;

	delta.i = data.i & 0xFF800000U;

	delta.i |= ((data.i & round_bit) >> (mask_bits - 1)) * carry_bit;

	data.f += delta.f;
	data.i &= ~tail_mask;

	return data.f;
}

// Universal double sanitize using IEEE-754 delta signed addition
double sanitize_double(double x, int mask_bits)
{
	uint64_t tail_mask = ((1ULL << mask_bits) - 1ULL);
	uint64_t round_bit = (1ULL << (mask_bits - 1ULL));
	uint64_t carry_bit = (1ULL << mask_bits);

	double_uint_t data, delta;
	data.d = x;

	delta.i = data.i & 0xFFF0000000000000ULL;

	// Branchless перенос бита округления в carry_bit
	delta.i |= ((data.i & round_bit) >> (mask_bits - 1)) * carry_bit;

	data.d += delta.d;
	data.i &= ~tail_mask;

	return data.d;
}

