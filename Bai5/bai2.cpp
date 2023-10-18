#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
using namespace std;


bool isPrime(int x) {
    if (x < 2)
        return false;
    for(int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0)
            return false;
    }
    return true;
}



void *listPrime(void *n) {
    int *n1 = (int *)n;
    
    for(int i = 2; i <= *n1; i++) {
        if (isPrime(i)) {
            cout << i << " ";
        }
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    if (int n = atoi(argv[1])) {
        pthread_t tid;
        int status; int *pstatus = &status;
        pthread_create(&tid, NULL, listPrime, &n);
        if (pthread_join(tid, (void**) pstatus) == 0) {
            return 0;
        }
    }
    else {
        cout << "Nhap doi so khong hop le" << endl;
    }
    return 0;
}
