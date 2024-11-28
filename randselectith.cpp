// Question 2. Write a program to find the ith smallest element of an array using Randomized Select.  


#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

// Swap function to replace the missing swap
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(int *a, int p, int q) {
    int x = a[p];
    int i = p;
    for (int j = p + 1; j <= q; j++) {
        if (a[j] <= x) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i], a[p]);
    return i;
}

int random_generator(int p, int q) {
    return p + rand() % (q - p + 1);
}

int randomised_select(int *a, int p, int q, int i) {
    // Base case: if there's only one element
    if (p == q) {
        return a[p];
    }

    int r = random_generator(p, q);    // Generate a random index
    swap(a[p], a[r]);                  // Swap the first element with the random element
    
    int m = partition(a, p, q);        // Partition the array and get pivot index
    
    int k = m - p + 1;                 // Rank of the pivot element
    
    if (i == k) {
        return a[m];                   // Found the ith smallest element
    }
    else if (i < k) {
        return randomised_select(a, p, m - 1, i);  // Search in the left subarray
    }
    else {
        return randomised_select(a, m + 1, q, i - k);  // Search in the right subarray
    }
}

int main() {
    srand(time(NULL));

    int size, i;
    cout << "Enter the size of the array: ";
    cin >> size;

    int* a = new int[size];
    
    cout << "Enter the elements of the array: ";
    for (int j = 0; j < size; j++) {
        cin >> a[j];
    }

    cout << "Enter the value of i (for the ith smallest element): ";
    cin >> i;

    // Find and print the ith smallest element
    int result = randomised_select(a, 0, size - 1, i);
    cout << "The " << i << "th smallest element is: " << result << endl;

    delete[] a;
    return 0;
}
