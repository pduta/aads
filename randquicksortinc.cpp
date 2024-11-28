// Question 1. Write a program to sort the elements of an array using Randomized Quick Sort (the program should report the number of comparisons).
[INCREASING ORDER]

#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

int comparison_count = 0;

int partition(int *a, int p, int q){
    int x = a[p]; N
    int i=p;
    for(int j=p+1;j<=q;j++){
        comparison_count++; // Increment the comparison count for each comparison made
        if(a[j]<=x){
            i++;
            swap(a[i],a[j]);
        };
    }
    swap(a[i],a[p]);   //we are swapping the elements at index i and that of index p. NOT the index
    return i;          //Now the pivot will be at index i, which before was at index p
}

int random_generator(int p, int q){
    return p + rand()%(q-p+1);
}

void randomised_quicksort(int *a, int p, int q){
    if(p<q){
        int r=random_generator(p,q);
        cout << "Randomly chosen pivot: " << a[r] << endl;
        swap(a[p],a[r]);
        int m=partition(a,p,q);
        randomised_quicksort(a,p,m-1);
        randomised_quicksort(a,m+1,q);
    }
}

int main(){
    srand(time(NULL));    // This will call srand only once in the beginning 

    int size;
    cout<<"Enter the size of array"<<endl;
    cin>>size;
    int *a= new int[size];
    cout<<"Enter the array "<<endl;
    for(int i = 0; i < size; i++){
        cin >> a[i];
    }

    randomised_quicksort(a,0,size-1); //If we entered array of size 5, so the index will be of 4, as it starts with 0
    cout<<"Sorted array : ";
    for(int i=0; i<size; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;

    cout << "Number of comparisons: " << comparison_count << endl;
    delete[] a; // Deallocate memory
    return 0;
}
