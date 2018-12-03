
// File: hw5.1.cpp
// Authors:
// Debajyoti Nandy
// Pallav Raj
// Avinash Shrivastava

#include <iostream>
#include <vector>
#include <algorithm>     // for minmax_element()
#include <cstdlib>       // for rand()
#include <ctime>         // for time()
using namespace std;

void selection_sort(vector<int>& v)
{
   int k(0);         // next slot for sorted value
   for ( ; k < v.size(); ++k) {
      int low_i(k);  // index of lowest remaining value
      for (int j(k); j < v.size(); ++j) {  // nested! O(N^2)
         if (v[j] < v[low_i])
            low_i = j;
      }
      // now, swap the lowest remaining value into slot k
      int temp(v[k]);
      v[k] = v[low_i];
      v[low_i] = temp;
   }
}

void insertion_sort(vector<int>& v)
{
   int k(1);           // next step
   for ( ; k < v.size(); ++k) {
      int temp(v[k]);
      int j(k-1);      // highest index of sorted portion
      for ( ; j >= 0 && v[j] > temp; --j) { // nest! O(N^2)
         v[j+1] = v[j];  // shift v[j-1] to v[j]
      }
      // now, put temp into correct slot
      v[j+1] = temp;
   }
}

void bubble_sort(vector<int>& v)
{
   for (int k(0); k < v.size(); ++k) {        // iteration
      for (int j(0); j < v.size()-1; ++j) {   // nest! O(N^2)
         if (v[j] > v[j+1]) {
            int temp(v[j]);
            v[j] = v[j+1];
            v[j+1] = temp;
         }
      }
   }
}

// "optimized" bubble sort
void bubble_sort_op(vector<int>& v)
{
   for (int k(0); k < v.size(); ++k) {    // iteration
      size_t up_limit = v.size()-k-1;     // 1st optimization
      size_t nswaps(0);                   // 2nd optimization
      for (int j(0); j < up_limit; ++j) { // nest! O(N^2)
         if (v[j] > v[j+1]) {
            nswaps += 1;
            int temp(v[j]);
            v[j] = v[j+1];
            v[j+1] = temp;
         }
      }
      if (nswaps == 0)  // sorted -- we are DONE!
         return;
   }
}

// quicksort components
int partition(int a[], int size)
{
    if (size <= 0) return -1;    // empty array
    swap(a[0], a[rand()%size]);  // to optimize
    int pivot(a[0]);
    int j(0);    // index for <= pivot
    int k(1);    // index for > pivot OR untested
    for ( ; k < size; ++k)       // test each array element
        if (a[k] <= pivot)       // ... against the pivot
            swap(a[++j], a[k]);  // call by reference
    swap(a[0], a[j]);            // pivot is in correct place!
    return j;
}

void quicksort_array_help(int a[], int size)
{
    if (size == 0) return;           // empty array
    int p_index = partition(a, size);
    if (p_index >= 0) {
       quicksort_array_help(a, p_index);
       quicksort_array_help(a + p_index + 1,
                                 size - p_index - 1);
    }
}

void quicksort(vector<int>& vi)
{
    // treat vector<int> as array-of-size int
    quicksort_array_help(&vi[0], vi.size());

}

void merge_sort(vector<int>& vi)
{
    if (vi.size() <= 1) return;  // nothing to do!

    // split vi into a front half and a back half
    vector<int> vft(&vi[0], &vi[0]+vi.size()/2);
    vector<int> vbk(&vi[0]+vi.size()/2, &vi[0]+vi.size());

    merge_sort(vft);     // sort the front half
    merge_sort(vbk);     // sort the back half

    // merge the sorted front and back into vi
    // notice that vi.size() == vft.size() + vbk.size()
    int ift(0), ibk(0);  // front, back half indexes
    for (int i(0); i < vi.size(); ++i) {  // vi index
        // if front is used up, get the back value
        if (ift >= vft.size()) vi[i] = vbk[ibk++];
        // else if back is used up, get the front value
        else if (ibk >= vbk.size()) vi[i] = vft[ift++];
        // else, get the lesser of the front and back values
        else vi[i] = vft[ift] < vbk[ibk]
                      ? vft[ift++] : vbk[ibk++];
    }
}

void counting_sort(vector<int>& vi)
{
    if (vi.size() <= 1) return;   // nothing to do!

    auto mn_mx = minmax_element(vi.begin(), vi.end());
    int min = *mn_mx.first;       // min value
    int max = *mn_mx.second;      // max value
    int M = max - min + 1;        // count vector size

    vector<int> counts(M);        // vector of M 0s
    for (int i(0); i < vi.size(); ++i)
        counts[vi[i] - min] += 1; // increment value counts

    int k(0);        // subscript in vi
    for (int i(0); i < counts.size(); ++i) {
        // there are counts[i] occurrences of i + Min
        // in vector vi
        for (int j(0); j < counts[i]; ++j) {
            vi[k++] = i + min;  // post-increment subscript k
        }
    }
}


int main()
{
	vector<int> vi{ 9, 10, 3, 1, 7, 8, 2, 6, 4, 5 };
	cout << "unsorted vector:  ";
	for (int i(0); i < 10; ++i)
		cout << vi[i] << ' ';
	cout << '\n';

	vector<int> vis(vi);
	selection_sort(vis);
	cout << "selection sort:   ";
	for (int i(0); i < 10; ++i)
		cout << vis[i] << ' ';
	cout << '\n';

	vector<int> vii(vi);
	insertion_sort(vii);
	cout << "insertion sort:   ";
	for (int i(0); i < 10; ++i)
		cout << vii[i] << ' ';
	cout << '\n';

	vector<int> vib(vi);
	bubble_sort(vib);
	cout << "bubble sort:      ";
	for (int i(0); i < 10; ++i)
		cout << vib[i] << ' ';
	cout << '\n';

	vector<int> vio(vi);
	bubble_sort_op(vio);
	cout << "bubble sort (op): ";
	for (int i(0); i < 10; ++i)
		cout << vio[i] << ' ';
	cout << '\n';

	vector<int> viq(vi);
	quicksort(viq);
	cout << "quicksort:        ";
	for (int i(0); i < 10; ++i)
		cout << viq[i] << ' ';
	cout << '\n';

	vector<int> vim(vi);
	merge_sort(vim);
	cout << "merge sort:       ";
	for (int i(0); i < 10; ++i)
		cout << vim[i] << ' ';
	cout << '\n';

	vector<int> vic(vi);
	counting_sort(vic);
	cout << "counting sort:    ";
	for (int i(0); i < 10; ++i)
		cout << vic[i] << ' ';
	cout << '\n';

	// sort algorithm timing tests
	cout << "\nTIMING TESTS:\n\n";
	int n_values = 10'000;
	vector<int> vi_test;
	for (int i(0); i < n_values; ++i)
		vi_test.push_back(rand());

	vector<int> vis_test(vi_test);
	time_t sstart = time(0);
	selection_sort(vis_test);
	time_t sstop = time(0);

	vector<int> vii_test(vi_test);
	time_t istart = time(0);
	insertion_sort(vii_test);
	time_t istop = time(0);

	vector<int> vib_test(vi_test);
	time_t bstart = time(0);
	bubble_sort(vib_test);
	time_t bstop = time(0);

	vector<int> vip_test(vi_test);
	time_t pstart = time(0);
	bubble_sort_op(vip_test);
	time_t pstop = time(0);

	vector<int> viq_test(vi_test);
	time_t qstart = time(0);
	quicksort(viq_test);
	time_t qstop = time(0);

	vector<int> vim_test(vi_test);
	time_t mstart = time(0);
	merge_sort(vim_test);
	time_t mstop = time(0);

	vector<int> vic_test(vi_test);
	time_t cstart = time(0);
	counting_sort(vic_test);
	time_t cstop = time(0);

	cout << "selection_sort of " << n_values
	     << " values took " << (sstop - sstart) << " seconds\n";
	cout << "insertion_sort of " << n_values
		<< " values took " << (istop - istart) << " seconds\n";
	cout << "bubble_sort of " << n_values
		<< " values took " << (bstop - bstart) << " seconds\n";
	cout << "bubble_sort_op of " << n_values
		<< " values took " << (pstop - pstart) << " seconds\n";
	cout << "quicksort of " << n_values
		<< " values took " << (qstop - qstart) << " seconds\n";
	cout << "merge_sort of " << n_values
		<< " values took " << (mstop - mstart) << " seconds\n";
	cout << "counting_sort of " << n_values
		<< " values took " << (cstop - cstart) << " seconds\n";

	/*
	|--------------------------------------------------------------------------------|
	|  Time      | n_values | n_values| n_values| n_values|n_values|n_values|n_values|
	| (seconds)  |  10,000  | 20,000  | 40,000  | 80,000  |160,000 |320,000 |640,000 |
	|--------------------------------------------------------------------------------|
	|selection   |    22    |   88    |   380   |         |		   |        |        |
	|insertion   |    13    |   52    |   220   |		  |		   |        |        |
	|bubble      |    62    |  241    |         |		  |        |        |        |
	|bubble(opt) |    34    |  135    |         |		  |		   |        |        |
	|quick       |     0    |    0    |     0   |    0	  |    0   |    0   |    1   |
	|merge       |     0    |    1    |     1   |    2	  |    4   |    8   |   17   |
	|counting    |     0    |    0    |     0   |    0    |    1   |    1   |    1   |
	|--------------------------------------------------------------------------------|
	*/

	/*
	comment #1: For selection, insertion, bubble and bubble_optimized sort, we can 
	observe that the time to finish the sort grows by a factor of 4 when the size 
	increases by a factor of 2, which shows that the time complexity of these sorting
	algorithm is proportional to N^2 which is expected. 

	comment #2: Also, we can observe bubble sort takes almost twice much time than
	bubble_optimized sort which is also expected as the performed optimizations is 
	expected to reduce the runtime by half

	comment #3: time complexity of mergesort shows a linear relation with the growth 
	of size where the runtime doubles with doubling of size. This is attributed to the
	fact that log(N) is almost like a constant for the ranges of N we are dealing with
	in this exercise.

	comment #4: quick and counting sort perform very well with almost no increase in 
	runtime during the range of the array size. This shows that quick sort and counting 
	sort behave almost linearly with the actual runtime also being very low. This probably
	is because for quicksort and counting sort, there is not much additional memory usage
	and thus the overhead cost of accessing extra memory (like in merge sort) is absent.
	counting sort uses O(M) extra memory which doesn't grow in the exercise, whereas 
	mergesort uses O(N) extra memory which is also linear in array size
	*/

}

