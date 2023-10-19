#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <climits>
using namespace std;

 int maxValue = 0;
 int minValue = 0;
 double avg = 0;

struct Array {
  int n = 0;
  int arr[100];  

  void fillArray(int argc, char* argv[]) {
    int i = 0;
    while (i < argc) {
        if (int x = atoi(argv[i])) {
            arr[n++] = x;
        }
        i++;
    }
  }
};

void *trungBinhCong(void *arr) {
    Array *arr1 = (Array *)arr;
    double avgTmp = 0;
    for(int i = 0; i < arr1->n; i++) {
            avgTmp += arr1->arr[i];
    }
    avgTmp /= arr1->n;
    avg = avgTmp;
}
void *findMax(void *arr) {
    Array *arr1 = (Array *)arr;
    int maxTmp = arr1->arr[0];
    for(int i = 0; i < arr1->n; i++) {
        if (maxTmp < arr1->arr[i]) {
            maxTmp = arr1->arr[i];
        }
    }
    maxValue = maxTmp;
    
}

void *findMin(void *arr) {
    Array *arr1 = (Array *)arr;
    int minTmp = arr1->arr[0];
    for(int i = 0; i < arr1->n; i++) {
        if (minTmp > arr1->arr[i]) {
            minTmp = arr1->arr[i];
        }
    }
    minValue = minTmp;
}

int main(int argc, char* argv[]) {
    Array arr = Array();
    arr.fillArray(argc, argv);

    pthread_t tid;
    int status; int *pstatus = &status;
    pthread_create(&tid, NULL, trungBinhCong, &arr);
    if (pthread_join(tid, (void**) pstatus) == 0) {
        pthread_create(&tid, NULL, findMax, &arr);
        if (pthread_join(tid, (void**) pstatus) == 0) {
            pthread_create(&tid, NULL, findMin, &arr);
            if (pthread_join(tid, (void**) pstatus) == 0) {
                cout << "Gia tri trung binh: " << avg << endl;
                cout << "Gia tri lon nhat: " << maxValue << endl;
                cout << "Gia tri nho nhat: " << minValue << endl;
            }
        }
        
    }
    return 0;
}
