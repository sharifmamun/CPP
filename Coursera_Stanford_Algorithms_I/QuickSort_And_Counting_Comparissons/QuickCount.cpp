/*Santiago Zubieta*/
#include <iostream>
#include <numeric>
#include <fstream>
#include <climits>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <queue>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <deque>
#include <vector>
#include <string>
#include <cstdlib>
#include <cassert>
#include <sstream>
#include <iterator>
#include <algorithm>  

#define MAXN 721

using namespace std;

int arr[100000];
bool DEBUG = false;

void useLastElement(int l, int r){
    // The use of the last element is simply swapping the last with the first
    int temp = arr[l];
    arr[l] = arr[r];
    arr[r] = temp;
}

void useMedianElement(int l, int r) {
    int m = (l + r) / 2;
    // Middle index of the range defined by the l (left) and r (right) bounds
    int low = arr[l];
    // Value at the start of the range
    int mid = arr[m];
    // Value at the middle of the range
    int top = arr[r];
    // Value at the end of the range
    int medianIndex;
    // Index where the median value of those 3 values will be located at
    if(low < mid) {
        if(mid < top) {
            medianIndex = m;
            // The median value is the one at the m (middle) index
        }
        else {
            if(low < top) {
                medianIndex = r;
                // The median value is the one at the r (right) index
            }
            else {
                medianIndex = l;
                // The median value is the one at the l (left) index

            }
        }
    }
    else {
        if(low < top) {
            medianIndex = l;
            // The median value is the one at the l (left) index
        }
        else {
            if(mid < top) {
                medianIndex = r;
                // The median value is the one at the r (right) index
            }
            else {
                medianIndex = m;
                // The median value is the one at the m (middle) index
            }
        }
    }
    // Swap the median-of-three element with the first element for the
    // devised linear scan partitioning algorithm to work.
    int temp = arr[l];
    arr[l] = arr[medianIndex];
    arr[medianIndex] = temp;
}

unsigned int quickCount(int l, int r) {
    if(l >= r){
        return 0;
    }
    // useLastElement(l, r);
    // Use this function if you want to use the last element as the pivot
    useMedianElement(l, r);
    // Use this function if you want to use the median of 3 as the pivot
    // otherwise, it will use the first element of the array. The median
    // of 3 helps tremendously with almost sorted/reverse sorted arrays.  
    int p = arr[l];
    int i = l + 1;
    for(int j = l + 1; j <= r; j++) {
    // This is the linear time algorithm upper bounded by O(n) to partition
    // the array in such a way that the pivot is placed in its rightful pla-
    // ce, and all left elements will be < pivot, and right elements > pivot.
        if(arr[j] < p){
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        }
    }    
    int temp = arr[l];
    arr[l] = arr[i - 1];
    arr[i - 1] = temp;
    // Swap the pivot element with the index indicating the place where the
    // partition of elements < pivot, and > pivot occurs.s
    int m = r - l + 1;
    // m is the amount of elements in this subproblem
    int comp0 = m - 1;
    // m - 1 is the amount of comparissons done in this subproblem
    int comp1 = quickCount(l, i - 2);
    int comp2 = quickCount(i, r);
    // Each of these recursive calls will return the amount of comparissons
    // done in each of the subproblems. Add up the 3 amounts to get total.
    return comp0 + comp1 + comp2;
}

void debugNumbers() {
// These are numbers generated by default just to test, in decreasing order
// from 721 to 1. This allows us to test that a reversed sorted array, will
// have a number of comparissons equal to (n * (n + 1)) / 2, or 259560.
// This also works for a sorted array, because both will always yield a sin-
// gle partition, which will be (n - 1) .. (n - 2) .. (n - 3) in size always.
    for(int i = 0; i < MAXN; i++){
        arr[i] = i;
    }
}

int main() {
    // This is a quickSort which will incidentally count the amount of comp-
    // arissons done inside it to compare how different pivot-picking strat-
    // egies will yield different amount of comparissons / operations.
    int i;
    if(DEBUG) {
        debugNumbers();
        i = MAXN;
    } 
    else {
        int n;
        i = 0;
        // Try running with the given file input
        // ./QuickCount < IntegerArray.txt
        while(cin >> n) {
            arr[i++] = n;
        }
        // With the Given Input, the number of comparissons is as follows:
        // 162085 - Picking first element as pivot
        // 164123 - Picking last element as pivot
        // 138382 - Picking median-of-three element between first, middle, last
    }
    unsigned int comps = quickCount(0, i - 1);
    // The number can be really big, and will never be negative, so its better
    // to use an unsigned integer, to have more storage space for it!
    cout << "Comparissons: " << comps << endl;
}
