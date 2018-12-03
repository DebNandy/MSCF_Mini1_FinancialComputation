//
//  HW3.1
//  Authors:
//	DEBAJYOTI NANDY
//  AVINASH SHRIVASTAVA
//	PALLAV RAJ

#include <iostream>
using namespace std;

int add(char c1, char c2)
{
    return c1+c2;
}

int add(int i1, int i2)
{
    return i1+i2;
}

double add(double x1, double x2)
{
    return x1+x2;
}

double add(double x1, double x2, double x3)
{
    return x1 + x2 + x3;
}

int add(int i1, int i2, int i3, int i4)
{
    return i1 + i2 + i3 + i4;
}

void swap(int *pi, int *pj) {
    *pi = *pi - *pj;
    *pj = *pi + *pj;
    *pi = *pj - *pi;

}

void swap(double *px, double *py) {
    *px = *px - *py;
    *py = *px + *py;
    *px = *py - *px;

}

void swap(int& ri, int& rj) {
    ri = ri - rj;
    rj = ri + rj;
    ri = rj - ri;

}

void swap(double& rx, double& ry) {
    rx = rx - ry;
    ry = rx + ry;
    rx = ry - rx;

}

char max_of(char c1, char c2) {
    return c1>c2 ? c1 : c2;
}

int max_of(int i1, int i2) {
    return i1>i2 ? i1 : i2;
}

double max_of(double d1, double d2) {
    return d1>d2 ? d1 : d2;
}

int main()
{
    // part (a)
    cout << "hello, world\n";
    
     // part (b)
     cout << fixed;  // display decimal point for double
     cout << add('a', '\n') << '\n';
     cout << add(5, 9) << '\n';
//     cout << add('A', 32) << '\n';
//     cout << add(9, 3.3) << '\n'; // this won't work since there's no function to add one double and one int
     cout << add(3.5, 4.2) << '\n';
     cout << add(1.1, 2.2, 3.3) << '\n';
     cout << add(1, 2, 3, 4) << '\n';
//     cout << add(5, 4, 3, 2, 1) << '\n'; // won't work since no function which takes 5 arguments
     cout << add(1, 2, 3) << '\n';
     cout << add(1.1, 2.2, 3.3, 4.4) << '\n';
     cout << add('A', 2.2, 1) << '\n';
    
     // part (c)
     int i(7), j(13);
     double x(3.14), y(2.18);
     
     cout << "before swap: i: " << i << ", j: " << j << '\n';
     swap(&i, &j);    // pass pointers
     cout << "after swap:  i: " << i << ", j: " << j << '\n';
     
     cout << "before swap: i: " << i << ", j: " << j << '\n';
     swap(i, j);      // pass references
     cout << "after swap:  i: " << i << ", j: " << j << '\n';
     
     cout << "before swap: x: " << x << ", y: " << y << '\n';
     swap(&x, &y);    // pass pointers
     cout << "after swap:  x: " << x << ", y: " << y << '\n';
     
     cout << "before swap: x: " << x << ", y: " << y << '\n';
     swap(x, y);      // pass references
     cout << "after swap:  x: " << x << ", y: " << y << '\n';

     // part (d)
     cout << "max_of('a', 'b'): " << max_of('a', 'b') << '\n';
     cout << "max_of(-4, 8):    " << max_of(-4, 8) << '\n';
     cout << "max_of(2.2, 3.3): " << max_of(2.2, 3.3) << '\n';
}

