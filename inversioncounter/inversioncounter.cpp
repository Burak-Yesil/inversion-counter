/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Burak Yesil
 * Version     : 1.0
 * Date        : 10-29-2021
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long numInversions = 0;

    for(int i = 0; i < length; i++){
        for(int j = i; j < length; j++){
            if(array[i] > array[j]){
                numInversions++;
            }
        }
    }
    return numInversions;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    vector <int> scratch;
    scratch.reserve(length);
    return mergesort(array, &scratch[0] , 0, length-1);
}


static long mergesort(int array[], int scratch[], int low, int high) {
    /** Applies merge sort to inputed array and also 
    return the number of inversions in original array. **/
    long numInversions = 0;

    if(low < high){
        int mid = low + (high - low )/2;
        numInversions += mergesort(array, scratch, low, mid);
        numInversions += mergesort(array, scratch, mid+1, high);
        int L = low;
        int H = mid+1;

        for (int i = low; i<=high; i++){
            if (L<=mid && ((H>high) || (array[L]<= array[H]))){
                scratch[i] = array[L];
                L++;
            }

            else{
                scratch[i] = array[H];
                numInversions += (mid -L +1);
                H++;
            }
        }
        for (int j = low; j <= high; j++){
            array[j] = scratch[j];
        }
    }

    return numInversions;
}






int main(int argc, char *argv[]) {
    // TODO: parse command-line argument

    // checking if slow is an argument
    bool is_slow = false;

    if(argc == 2 && string(argv[1]) == "slow") is_slow = true;
    
    else if(argc == 2) {
    cerr << "Error: Unrecognized option '" << string(argv[1]) << "'." << endl;
    return 1;
    }

    else if(argc > 2) {
    cerr << "Usage: ./inversioncounter [slow]" << endl;
    return 1;
    } 
    
   



    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

  if(values.size() == 0) {
    cerr << "Error: Sequence of integers not received." << endl;
    return 1;
  }
  // Uses short hand if else to decide which inversion counter to use
  cout << "Number of inversions: " << (is_slow ? count_inversions_slow(values.data(), values.size()) : count_inversions_fast(values.data(), values.size())) << endl;
  

return 0;
}
