// Question 1. Write a program to sort the elements of an array using Randomized Quick Sort (the program should report the number of comparisons).
[DECREASING ORDER]



#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

int comparison_count = 0;

int partition(int *a, int p, int q) {
    int x = a[p];
    int i = p;
    for(int j = p+1; j <= q; j++) {
        comparison_count++; // Increment the comparison count for each comparison made
        if(a[j] >= x) { // Changed from <= to >=
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i], a[p]);   // Swap the pivot to its correct position
    return i;           // Return the partition index
}

int random_generator(int p, int q) {
    return p + rand() % (q - p + 1);
}

void randomised_quicksort(int *a, int p, int q) {
    if(p < q) {
        int r = random_generator(p, q);
        cout << "Randomly chosen pivot: " << a[r] << endl;
        swap(a[p], a[r]);
        int m = partition(a, p, q);
        randomised_quicksort(a, p, m-1);
        randomised_quicksort(a, m+1, q);
    }
}

int main() {
    srand(time(NULL));    // Seed the random number generator
    int size;
    cout << "Enter the size of array: ";
    cin >> size;
    
    int *a = new int[size];
    
    cout << "Enter the array elements: " << endl;
    for(int i = 0; i < size; i++) {
        cin >> a[i];
    }
    
    randomised_quicksort(a, 0, size-1);
    
    cout << "Array sorted in decreasing order: ";
    for(int i = 0; i < size; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    
    cout << "Number of comparisons: " << comparison_count << endl;
    
    delete[] a; // Deallocate memory
    return 0;
}

