#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

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
    double avg = 0;
    for(int i = 0; i < arr1->n; i++) {
            avg += arr1->arr[i];
    }
    avg /= arr1->n;
    cout << "Trung binh cong la: " << avg << endl;
}
void *findMax(void *arr) {
    Array *arr1 = (Array *)arr;
    int max = arr1->arr[0];
    for(int i = 0; i < arr1->n; i++) {
            if (max < arr1->arr[i]) {
                max = arr1->arr[i];
            }
    }
    cout << "Gia tri lon nhat la: " << max << endl;
}

void *findMin(void *arr) {
    Array *arr1 = (Array *)arr;
    int min = arr1->arr[0];
    for(int i = 0; i < arr1->n; i++) {
            if (min > arr1->arr[i]) {
                min = arr1->arr[i];
            }
    }
    cout << "Gia tri nho nhat la: " << min << endl;
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
            sleep(2);
        }
    }
    return 0;
}
