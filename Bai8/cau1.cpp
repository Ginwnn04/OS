#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
using namespace std;

int fac(int n) {
    int f = 1;
    for(int i = 1; i <= n; i++) {
        f *= i;
    }
    return f;
}

int main(int argc, char const *argv[]) {
    int fp1[2], fp2[2];
    if (argc < 2) {
        cout << "Thieu doi so" << endl;
        return 1;
    }
    if (pipe(fp1) == 0 && pipe(fp2) == 0) {
        int pid = fork();
        if (pid < 0) {
            cout << "Fork failed" << endl;
        }
        else if(pid == 0) {
            close(fp1[1]);
            int n;
            read(fp1[0], &n, sizeof(int));
            int f = fac(n);
            close(fp2[0]);
            write(fp2[1], &f, sizeof(int));
        }
        else {
            close(fp1[0]);
            int n = atoi(argv[1]);
            write(fp1[1], &n, sizeof(int));
            close(fp2[1]);
            int f = 0;
            read(fp2[0], &f, sizeof(int));
            cout << n << "! = " << f << endl;
        }
    }
    else {
        cout << "Pipe failed" << endl;
    }

}
