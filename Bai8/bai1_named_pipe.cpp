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

int fact(int n) {
    int f = 1;
    for(int i = 1; i <= n; i++) {
        f *= i;
    }
    return f;
}

int main(int argc, char* argv[]) {
    int readfd, writefd;
    if (argc < 2) {
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
            int n;
            read(readfd, &n, sizeof(int));
            int f = fact(n);
            write(writefd, &f, sizeof(int));
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
            int n = atoi(argv[1]);
            write(writefd, &n, sizeof(int));
            int f;
            read(readfd, &f, sizeof(int));
            cout << n << "! = " << f << endl;
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
