#include <iostream>
#include <pthread.h>
using namespace std;

struct file {
    int n;
    char* fileName;
};

int sumFactorial = 0;
int factorial = 1;

void* calSum(void* f) {
    file* f1 = (file*) f;
    int n = f1->n;
    for (int i = 1; i < factorial; i++) {
        if (i % 2 == 0) {
            sumFactorial += i;
        }
    }
}

void* calFactorial(void* f) {
    file* f1 = (file*) f;
    int n = f1->n;
    for (int i = 1; i <= n; i++) {
        factorial *= i;
    }
}

void* writeFile(void* f) {
    file* f1 = (file*) f;
    FILE* fp = fopen(f1->fileName, "w");
    fprintf(fp, "%d!= %d\n", f1->n, factorial);
    fprintf(fp, "Sum = %d\n", sumFactorial);
    fclose(fp);
}

int main(int agrc, char* agrv[]) {
    file f = file();
    f.n = atoi(agrv[1]);
    f.fileName = agrv[2];
    int status; int* pstatus = &status;
    pthread_t tid;
    pthread_create(&tid, NULL, calFactorial, &f);
    if (pthread_join(tid, (void**)pstatus) == 0) {
        pthread_create(&tid, NULL, calSum, &f);
        if(pthread_join(tid, (void**)pstatus) == 0) {
            pthread_create(&tid, NULL, writeFile, &f);
            if(pthread_join(tid, (void**)pstatus) == 0) {
                cout << "Da tao xong tap tin " << f.fileName << endl;
            }
        }
    }
}
