#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
using namespace std;

float tinhToan(int a, int b, char op) {
    if (op == '+') {
        return a + b;
    }
    else if (op == '-') {
        return a - b;
    }
    else if (op == '*') {
        return a * b;
    }
    else if (op == '/') {
        return a / (b*1.0);
    }
}

int main(int argc, char const *argv[]) {
    int fp1[2], fp2[2];
    if (argc < 4) {
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
            int n1;
            int n2;
            char op;
            read(fp1[0], &n1, sizeof(int));
            read(fp1[0], &n2, sizeof(int));
            read(fp1[0], &op, sizeof(char));
            float result = tinhToan(n1, n2, op);
            close(fp2[0]);
            write(fp2[1], &result, sizeof(float));
        }
        else {
            close(fp1[0]);
            int n1 = atoi(argv[1]);
            int n2 = atoi(argv[2]);
            char op = argv[3][0];
            write(fp1[1], &n1, sizeof(int));
            write(fp1[1], &n2, sizeof(int));
            write(fp1[1], &op, sizeof(char));
            close(fp2[1]);
            float result = 0;
            read(fp2[0], &result, sizeof(float));
            cout << "Ket qua la: " << result << endl;
        }
    }
    else {
        cout << "Pipe failed" << endl;
    }

}
