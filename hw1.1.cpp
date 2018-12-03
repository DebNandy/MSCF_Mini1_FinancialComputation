
// File: hw1.1.cpp
// Author(s): PALLAV RAJ & DEBAJYOTI NANDY & AVINASH SHRIVASTAVA

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	//for (int i(1); i <= 1000000; ++i) { // 1 million times
	/*
	part 1.a
	The loop goes uptil i=14 and then crashes
	*/
	
	watch

	for (int i(1); i <= 10; ++i) { // 1 million times
        int *pi =     // "array" of int
             new int[10000000];     // 10 million ints
        double *pd =  // "array" of double
             new double[10000000];  // 10 million doubles
        char *pc =    // "array" of char
             new char[10000000];    // 10 million chars

        cout << "i: " << setw(7) << i << '\n';

        // ... but no delete[] statements!
        // Memory leak!
		delete pc;
		delete pd;
		delete pi;
		
		/*
		part 1.b
		delete added

		*/
    }

	int *partc = new int(-123);
	cout << "address of object : " <<partc << "\n";
	//cout << "address of object : " << &partc << "\n";
	cout << "value of object : " << *partc << "\n";

	delete partc;
	
	/*
	part 1.c
	address of object : 006599D8
	value of object : -123

	*/

	cout << "after delete, address of object : " << partc << "\n";
	
	int x=1234;
	partc = &x; 

	cout << "after re-init, address of object : " << partc << "\n";
	cout << "after re-init, value of object : " << *partc << "\n";


	watch

	/*
	part 1.d
	after delete, address of object : 00008123
	if delete again, it corrupts the program
	after re-initialisation of pointer,
	address = 0093FE08
	value = 1234

	*/

	
	/* part 1.e
	Since delete[] is not used, program eventually runs out of heap memory at i=2

	*/
	
	/* part 1.f
	delete[] is used, now no error is thrown

	*/

	/* part 1.g
	used ' separator for readability, code works fine
	for (int i(0); i < 1'000; ++i) {

	*/
		

    for (int i(0); i < 100; ++i) {
        cout << "before allocation " << i << "\n";
        char *pc = new char[500000000];
        cout << "after allocation -- ";
        if (pc == nullptr)
            cout << "new returned nullptr\n";
        else
            cout << "new did NOT return nullptr\n";
		delete[] pc;
    }
    

	cin.get(); //To stop the window from closing
	return 0;
}

