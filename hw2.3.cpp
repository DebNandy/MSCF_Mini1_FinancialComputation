
// File: hw2.3.cpp
// Author(s):
// DEBAJYOTI NANDY
// AVINASH SHRIVASTAVA
// PALLAV RAJ
// MSCF, Pittsburgh

#include <iostream>
using namespace std;

/* original code from lecture notes */
void put_int_bits(unsigned i)
{
	if (i == 0) {   // stopping condition
		cout << 0;  // leading 0 bit
	}
	else {
		put_int_bits(i / 2);  // hard task
		cout << i % 2;        // easy task
	}
}

/* improved version from part (b) */
void put_int_n_bits(unsigned i, unsigned n)
{
	if (n) {
		put_int_n_bits(i / 2, n - 1);  // hard task
		cout << i % 2;                 // easy task
	}
}

void put_int_bits_v2(unsigned i)
{
	// assume 8 bits per byte
	const size_t bits_per_int = sizeof(int) * 8;
	put_int_n_bits(i, bits_per_int);
}

/* function definition for part (d), from lecture notes */
void put_rev_str_it(char *s) {  // iterative version
	char *end(s);               // start at beginning,
	int num = 0;
	while (*end++)              // then find the end
		num++;					// fixed the calculation of num
	while (num)
		cout << s[--num];       // display in reverse
								// fixed the iterator decrement
}

void put_rev_str_rc(char *s) {  // recursive version
	if (*s) {                   // if there is a char
		put_rev_str_rc(s + 1);    // put trailing chars
		cout << *s;             // then current char
	}
}
void put_int_commas_helper(int n, int count, bool is_negative)
{
	if (n == 0)
	{
		if (is_negative)
			cout << '-';
		return;
	}
	else
	{
		put_int_commas_helper(n / 10, count + 1, is_negative);
		cout << abs(n % 10);
		if (count % 3 == 0 && count != 0)
			cout << ',';
	};

}
void put_int_with_commas(int n)
{
	put_int_commas_helper(n, 0, n<0);
}

int main()
{
	put_int_bits(0);    // 0
	cout << "\n";
	put_int_bits(7);    // 0111
	cout << "\n";
	put_int_bits(1234); // 010011010010
	cout << "\n";
	put_int_bits(-1);   // 011111111111111111111111111111111
	cout << "\n";

	/* code for part (b)*/
	put_int_bits_v2(0);    // 0
	cout << "\n";
	put_int_bits_v2(7);    // 0111
	cout << "\n";
	put_int_bits_v2(1234); // 010011010010
	cout << "\n";
	put_int_bits_v2(-1);   // 011111111111111111111111111111111
	cout << "\n";


	/* code for part (c)*/
	put_int_with_commas(0); cout << '\n';
	put_int_with_commas(1); cout << '\n';
	put_int_with_commas(12); cout << '\n';
	put_int_with_commas(123); cout << '\n';
	put_int_with_commas(1234); cout << '\n';
	put_int_with_commas(12345); cout << '\n';
	put_int_with_commas(123456); cout << '\n';
	put_int_with_commas(1234567); cout << '\n';
	put_int_with_commas(12345678); cout << '\n';
	put_int_with_commas(123456789); cout << '\n';
	put_int_with_commas(1234567890); cout << '\n';
	put_int_with_commas(INT_MAX); cout << '\n';
	put_int_with_commas(-1); cout << '\n';
	put_int_with_commas(-12); cout << '\n';
	put_int_with_commas(-123); cout << '\n';
	put_int_with_commas(-1234); cout << '\n';
	put_int_with_commas(-12345); cout << '\n';
	put_int_with_commas(-123456); cout << '\n';
	put_int_with_commas(-1234567); cout << '\n';
	put_int_with_commas(-12345678); cout << '\n';
	put_int_with_commas(-123456789); cout << '\n';
	put_int_with_commas(-1234567890); cout << '\n';
	put_int_with_commas(INT_MIN); cout << '\n';


	/* code for part (d)*/
	char hello[] = "Hello World!";

	put_rev_str_it(hello);
	cout << "\n";

	put_rev_str_rc(hello);
	cout << "\n";

	return 0;
}

