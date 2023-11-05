#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <sys/stat.h>
extern int errno;
using namespace std;

const char fifo1[] = "fifo1";
const char fifo2[] = "fifo2";

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

int main(int argc, char* argv[]) {
    int readfd, writefd;
    if (argc < 4) {
            cout << "Thieu doi so" << endl;
            return 1;
    }
    if (mknod(fifo1, S_IFIFO | 0666, 0) < 0 && errno != EEXIST) {
            cout << "Khong tao duoc fifo1" << endl;
            return 1;
    }
    if (mknod(fifo2, S_IFIFO | 0666, 0) < 0 && errno != EEXIST) {
            cout << "Khong tao duoc fifo2" << endl;
            return 1;
    }
    int pid = fork();
    if (pid < 0) {
            cout << "Khong tao duoc tien trinh con" << endl;
            return 1;
    }
    else if (pid == 0) {
            if ((readfd = open(fifo1, 0)) < 0) {
                perror("Khong mo duoc fifo1");
                return 1;
            }
            if ((writefd = open(fifo2, 1)) < 0) {
                perror("Khong mo duoc fifo2");
                return 1;
            }
            int n1, n2;
            char op;
            read(readfd, &n1, sizeof(int));
            read(readfd, &n2, sizeof(int));
            read(readfd, &op, sizeof(char));
            cout << "n1 = " << n1 << endl;
            cout << "n2 = " << n2 << endl;
            cout << "op = " << op << endl;
            float result = tinhToan(n1, n2, op);
            write(writefd, &result, sizeof(float));
            close(readfd);
            close(writefd);
    }
    else {
            if ((writefd = open(fifo1, 1) )< 0) {
                cout << "Khong mo duoc fifo2" << endl;
                return 1;
            }
            if ((readfd = open(fifo2, 0) )< 0) {
                cout << "Khong mo duoc fifo1" << endl;
                return 1;
            }
            int n1 = atoi(argv[1]);
            int n2 = atoi(argv[2]);
            char op = argv[3][0];
            write(writefd, &n1, sizeof(int));
            write(writefd, &n2, sizeof(int));
            write(writefd, &op, sizeof(char));
            float result;
            read(readfd, &result, sizeof(float));
            cout << "ket qua la: " << result << endl;
            while(wait(NULL) != pid) {
                close(readfd);            
            }
            close(writefd);
            if (unlink(fifo1) < 0) {
                cout << "Khong xoa duoc fifo1" << endl;
                return 1;
            }
            if (unlink(fifo2) < 0) {
                cout << "Khong xoa duoc fifo2" << endl;
                return 1;
            }
    }
}
