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

int main(){
    default_random_engine e(time(NULL));
    uniform_int_distribution<int> u(0, 100);
    int test[21];
    for(int i = 0; i < 20; i++)
        test[i + 1] = u(e);
    for(int i = 1; i <= 20; i++)
        cout << test[i] << " ";
    cout << endl;
    insert_sort(test, 20);
    for(int i = 1; i <= 20; i++)
        cout << test[i] << " ";
    cout << endl;
    return 0;
}