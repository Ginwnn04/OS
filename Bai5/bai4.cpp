#include <iostream>
#include <pthread.h>
#include <math.h>
using namespace std;

struct Array {
    int n;
    int arr[100];
};

struct file {
    char* filename;
    Array arr;
    Array arrPrime;
    Array arrPrimeSort;
};

int sumPrime = 0;

bool isPrime(int x) {
    if (x < 2) return false;
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) return false;
    }
    return true;
}

void* readFile(void* arg) {
    file* f = (file*) arg;
    FILE* fi = fopen(f->filename, "r");
    fscanf(fi, "%d", &f->arr.n);
    for (int i = 0; i < f->arr.n; i++) {
        fscanf(fi, "%d", &f->arr.arr[i]);
    }
    for(int i = 0; i < f->arr.n; i++) {
        if (isPrime(f->arr.arr[i])) {
            f->arrPrime.arr[f->arrPrime.n++] = f->arr.arr[i];
            f->arrPrimeSort.arr[f->arrPrimeSort.n++] = f->arr.arr[i];
        }
    }
    fclose(fi);
    return NULL;
}

void* writeFile(void* arg) {
    file* f = (file*) arg;
    FILE* fo = fopen("result", "w");
    fprintf(fo, "So phan tu mang: %d\n", f->arr.n);
    for (int i = 0; i < f->arr.n; i++) {
        fprintf(fo, "%d ", f->arr.arr[i]);
    }
    fprintf(fo, "\n");
    fprintf(fo, "Mang cac so nguyen to: \n");
    for(int i = 0; i < f->arrPrime.n; i++) {
        fprintf(fo, "%d ", f->arrPrime.arr[i]);
    }
    fprintf(fo, "\n");
    fprintf(fo, "Tong cac so nguyen to: %d\n", sumPrime);
    fprintf(fo, "Mang cac so nguyen to da duoc sap xep: \n");
    for(int i = 0; i < f->arrPrimeSort.n; i++) {
        fprintf(fo, "%d ", f->arrPrimeSort.arr[i]);
    }
    fprintf(fo, "\n");
    fclose(fo);
    return NULL;
}

void* sortArrayPrime(void* arg) {
    file* f = (file*) arg;
    for (int i = 0; i < f->arrPrimeSort.n; i++) {
        for (int j = i + 1; j < f->arrPrimeSort.n; j++) {
            if (f->arrPrimeSort.arr[i] > f->arrPrimeSort.arr[j]) {
                int temp = f->arrPrimeSort.arr[i];
                f->arrPrimeSort.arr[i] = f->arrPrimeSort.arr[j];
                f->arrPrimeSort.arr[j] = temp;
            }
        }
    }
    return NULL;
}

void* countSumPrime(void* arg) {
    file* f = (file*) arg;
    for (int i = 0; i < f->arrPrime.n; i++) {
        sumPrime += f->arrPrime.arr[i];
    }
    return NULL;
}

int main(int agrc, char* argv[]) {
    file f = file();
    f.filename = argv[1];
    pthread_t tid;
    int status; int* pstatus = &status;
    pthread_create(&tid, NULL, readFile, &f);
    if (pthread_join(tid, (void**) &pstatus) == 0) {
        pthread_create(&tid, NULL, countSumPrime, &f);
        if (pthread_join(tid, (void**) &pstatus) == 0) {
            pthread_create(&tid, NULL, sortArrayPrime, &f);
            if (pthread_join(tid, (void**) &pstatus) == 0) {
                pthread_create(&tid, NULL, writeFile, &f);
                if (pthread_join(tid, (void**) &pstatus) == 0) {
                    
                }
             }
           
        }
    
    }
    return 0;
}
