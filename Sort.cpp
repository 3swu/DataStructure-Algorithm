#include <iostream>
#include <random>
#include <ctime>

using namespace std;

void insert_sort(int a[], int n){
    int i, j;
    for(i = 2; i <= n; i++)
        if(a[i] < a[i - 1]){
            a[0] = a[i];
            for(j = i - 1; a[0] < a[j]; --j)
                a[j + 1] = a[j];
            a[j + 1] = a[0];
        }
}

//采用步长为 n / 2， 并且递推折半
void shell_sort(int a[], int n){
    int dk, i, j;
    for(dk = n / 2; dk >= 1; dk /= 2)
        for(i = dk + 1; i <= n; ++i)
            if(a[i] < a[i - dk]){
                a[0] = a[i];
                for(j = i - dk; j > 0 && a[0] < a[j]; j -= dk)
                    a[j + dk] = a[j];
                a[j + dk] = a[0];
            }
}

int partition(int a[], int low, int high){
    a[0] = a[low];
    while(low < high){
        while(low < high && a[high] >= a[0])
            --high;
        a[low] = a[high];
        while(low < high && a[low] <= a[0])
            ++low;
        a[high] = a[low];
    }
    a[low] = a[0];
    return low;
}

void quick_sort(int a[], int low, int high){
    if(low < high){
        int pivotloc = partition(a, low, high);
        quick_sort(a, low, pivotloc - 1);
        quick_sort(a, pivotloc + 1, high);
    }
}

int main(){
    default_random_engine e(time(NULL));
    uniform_int_distribution<int> u(0, 100);
    int test[21];
    for(int i = 0; i < 20; i++)
        test[i + 1] = u(e);
    for(int i = 1; i <= 20; i++)
        cout << test[i] << " ";
    cout << endl;
    // insert_sort(test, 20);
    // shell_sort(test, 20);
    quick_sort(test, 1, 20);
    for(int i = 1; i <= 20; i++)
        cout << test[i] << " ";
    cout << endl;
    return 0;
}