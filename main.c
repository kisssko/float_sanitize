#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "float_san.h"
#include "float_san_test.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	int f_mask_bits = 8;
	int d_mask_bits = 12;

	FloatTestCase f_tests[] =
	{
		{ "F-CS1", "Accumulation (0.1 + 0.1 + 0.1)", 0.3f, get_f_case1() },
		{ "F-CS2", "Loss of significance (10-9.8)", 0.2f, get_f_case2() },
		{ "F-CS3", "Inverse operation (1/3 * 3)", 1.0f, get_f_case3() },
		{ "F-CS4", "Loop accumulation (0.1 * 10)", 1.0f, get_f_case4() },
		{ "F-CS5", "Large numbers (Epsilon-crit)", 123456.0f, get_f_case5() }
	};

	int f_num_tests = sizeof(f_tests) / sizeof(f_tests[0]);
	int f_raw_passed = 0, f_sanit_passed = 0;

	printf("=== IEEE-754 FLOAT SANITIZE TEST REPORT (MASK_BITS: %d) ===\n", f_mask_bits);
	putchar('\n');
	puts("ID    | Description                        | Standard      |"
		 " Calculated    | Raw ==   | Sanit == | Raw HEX (Std vs Calc)");
	puts("------------------------------------------------------------"
		 "-----------------------------------------------------------");

	for (int i = 0; i < f_num_tests; i++)
	{
		float std_san = sanitize_float(f_tests[i].standard, f_mask_bits);
		float calc_san = sanitize_float(f_tests[i].calculated, f_mask_bits);

		bool raw_equal = (f_tests[i].standard == f_tests[i].calculated);
		bool sanitized_equal = (std_san == calc_san);

		if (raw_equal)
			f_raw_passed++;
		if (sanitized_equal)
			f_sanit_passed++;

		float_uint_t u_std, u_calc;
		u_std.f = f_tests[i].standard;
		u_calc.f = f_tests[i].calculated;

		printf("%-5s | %-34s | %-13.6f | %-13.6f | %-8s | %-8s | %08X vs %08X\n",
		f_tests[i].id, f_tests[i].description, f_tests[i].standard, f_tests[i].calculated,
		raw_equal ? "PASSED" : "FAILED", sanitized_equal ? "PASSED" : "FAILED",
		u_std.i, u_calc.i);
	}
	puts("------------------------------------------------------------"
		 "-----------------------------------------------------------");
	puts("SUMMARY (FLOAT):");
	printf("  Raw global match without sanitize: %d/%d\n", f_raw_passed, f_num_tests);
	printf("  Match WITH sanitize algorithm:     %d/%d\n", f_sanit_passed, f_num_tests);
	puts("------------------------------------------------------------"
		 "-----------------------------------------------------------");
	putchar('\n');

	DoubleTestCase d_tests[] = {
		{ "D-CS1", "Accumulation (0.1 + 0.1 + 0.1)", 0.3, get_d_case1() },
		{ "D-CS2", "Loss of significance (10-9.8)", 0.2, get_d_case2() },
		{ "D-CS3", "Inverse operation (1/3 * 3)", 1.0, get_d_case3() },
		{ "D-CS4", "Loop accumulation (0.1 * 10)", 1.0, d_get_case4() },
		{ "D-CS5", "Large numbers (Epsilon-crit)", 123456.0, get_d_case5() }
	};

	int d_num_tests = sizeof(d_tests) / sizeof(d_tests[0]);
	int d_raw_passed = 0, d_sanit_passed = 0;

	printf("=== IEEE-754 DOUBLE SANITIZE TEST REPORT (MASK_BITS: %d) ===\n",
		d_mask_bits);
	putchar('\n');
	puts("ID    | Description                        | Standard      |"
		" Calculated    | Raw ==   | Sanit == | Raw HEX (Std vs Calc)");
	puts("------------------------------------------------------------"
		 "-----------------------------------------------------------");

	for (int i = 0; i < d_num_tests; i++)
	{
		double std_san = sanitize_double(d_tests[i].standard, d_mask_bits);
		double calc_san = sanitize_double(d_tests[i].calculated, d_mask_bits);

		bool raw_equal = (d_tests[i].standard == d_tests[i].calculated);
		bool sanitized_equal = (std_san == calc_san);

		if (raw_equal)
			d_raw_passed++;
		if (sanitized_equal)
			d_sanit_passed++;

		double_uint_t u_std, u_calc;
		u_std.d = d_tests[i].standard;
		u_calc.d = d_tests[i].calculated;

		printf("%-5s | %-34s | %-13.6f | %-13.6f | %-8s | %-8s | %016llX vs %016llX\n",
		d_tests[i].id, d_tests[i].description, d_tests[i].standard, d_tests[i].calculated,
		raw_equal ? "PASSED" : "FAILED", sanitized_equal ? "PASSED" : "FAILED",
		(uint64_t)u_std.i, (uint64_t)u_calc.i);
	}
	puts("------------------------------------------------------------"
		 "-----------------------------------------------------------");
	puts("SUMMARY (DOUBLE):");
	printf("  Raw global match without sanitize: %d/%d\n", d_raw_passed, d_num_tests);
	printf("  Match WITH sanitize algorithm:     %d/%d\n", d_sanit_passed, d_num_tests);
	puts("------------------------------------------------------------"
		 "-----------------------------------------------------------");

	return 0;
}

