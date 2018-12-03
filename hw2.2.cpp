
// File: hw2.2.cpp
// Author(s):
// DEBAJYOTI NANDY
// AVINASH SHRIVASTAVA
// PALLAV RAJ
// MSCF, Pittsburgh

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	const double pi(3.1415926535897932);
	const double *ppi{ &pi };

	cout << fixed << setprecision(15);

	cout << "pi:    " << pi << '\n';
	cout << "&pi:   " << &pi << '\n';
	cout << "ppi:   " << ppi << '\n';
	cout << "*ppi:  " << *ppi << '\n';

	/* code for part (b)
	const double e;
	*/
	// Above didnot compile and the error says const object must be initialized

	/* code for part (c)*/
	const double e(2.7182818284590452);
	cout << "e:     " << e << '\n';


	/* code for part (d)
	double *pe(&e);  // pe points to e
	*/
	//Compilation error says const double * cannot be initialized to double *


	/* code for part (e)*/
	double *pe((double *)&e);  // force pe to point to e
	cout << "pe:    " << pe << '\n';    // address of e
	cout << "*pe:   " << *pe << '\n';   // value of e


										/* code for part (f)*/
	*pe = pi;		// change e to pi?
	cout << "*pe:   " << *pe << '\n';   // is e now pi?
										// Yes, visual studio C++ updated this to value of pi


										/* code for part (g)*/
	cout << "e:     " << e << '\n';    // is e now pi?	Ans. No
	cout << "&e:    " << &e << '\n';   // address of e
	cout << "pe:    " << pe << '\n';   // same as address of e? Ans. Yes
	cout << "*pe:   " << *pe << '\n';  // value of e?	Ans. No
	// Although &e and pe have the same value, meaning pe is pointing towards e, 
	// but the value of e and *pe are not the same. e is stil 2.71... but *pe is 3.14...

									   /* Overall Output
									   pi:    3.141592653589793
									   &pi : 00E5FBF0
									   ppi : 00E5FBF0
									   *ppi : 3.141592653589793
									   e : 2.718281828459045
									   pe : 00E5FBD4
									   *pe : 2.718281828459045
									   *pe : 3.141592653589793
									   e : 2.718281828459045
									   &e : 00E5FBD4
									   pe : 00E5FBD4
									   *pe : 3.141592653589793
									   */
	return 0;
}

