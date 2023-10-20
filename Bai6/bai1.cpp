#include <iostream>
#include <pthread.h>
using namespace std;

struct Array {
    int arr[100] = {0};
    int n = 0;
};

struct file{
    char* fileName;
    Array arr;
    Array arrLeft;
    Array arrRight;
};

void* readFile(void* f) {
    file* f1 = (file *)f;
    FILE* fp = fopen(f1->fileName, "r");
    while (!feof(fp)) {
        fscanf(fp, "%d", &f1->arr.arr[f1->arr.n++]);
    }
    fclose(fp);
    return NULL;
}

void InterchangeSort(int *arr, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (arr[i] < arr[j]) swap(arr[i], arr[j]);
        }
    }
}

void* splitArr(void* f) {
    file* f1 = (file *)f;
    int n = f1->arr.n;
    int mid = n / 2;
    for (int i = 0; i < mid; i++) {
        f1->arrLeft.arr[f1->arrLeft.n++] = f1->arr.arr[i];
    }
    for (int i = mid; i < n; i++) {
        f1->arrRight.arr[f1->arrRight.n++] = f1->arr.arr[i];
    }
    InterchangeSort(f1->arrLeft.arr, f1->arrLeft.n);
    InterchangeSort(f1->arrRight.arr, f1->arrRight.n);
    return NULL;

}

void* mergeArr(void* f) {
    file* f1 = (file *)f;
    int i = 0, j = 0, k = 0;
    while (i < f1->arrLeft.n && j < f1->arrRight.n) {
        if (f1->arrLeft.arr[i] < f1->arrRight.arr[j]) {
            f1->arr.arr[k++] = f1->arrLeft.arr[i++];
        } else {
            f1->arr.arr[k++] = f1->arrRight.arr[j++];
        }
    }
    while (i < f1->arrLeft.n) {
        f1->arr.arr[k++] = f1->arrLeft.arr[i++];
    }
    while (j < f1->arrRight.n) {
        f1->arr.arr[k++] = f1->arrRight.arr[j++];
    }
    return NULL;

}

int main(int agrc, char* agrv[]) {
    file f = file();
    f.fileName = agrv[1];
    int status; int* pstatus = &status;
    pthread_t tid;
    pthread_create(&tid, NULL, readFile, &f);
    if (pthread_join(tid, (void**)pstatus) == 0) {
        pthread_create(&tid, NULL, splitArr, &f);
        if (pthread_join(tid, (void**)pstatus) == 0) {
            pthread_create(&tid, NULL, mergeArr, &f);
            if (pthread_join(tid, (void**)pstatus) == 0) {
                for(int i = 0; i < f.arr.n; i++) {
                    cout << f.arr.arr[i] << " ";
                }
                cout << endl;
            }
            
        }
    }
    return 0;
}
