#include <iostream>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
using namespace std;

int main() {
    key_t read = ftok(".",0);
    key_t write = ftok(".",1);
    
    int shmid_read = shmget(read, 1024, 0666 | IPC_CREAT);
    int shmid_write = shmget(write, 1024, 0666 | IPC_CREAT);

    int *dataRead = (int *) shmat(shmid_read, 0, 0);
    int *dataWrite = (int *) shmat(shmid_write, 0, 0);

    int pid = fork();
    if (pid < 0) {
        cout << "Loi tao tien trinh" << endl;
    }
    else if(pid == 0) {
        cout << "Nhap so phan tu: ";
        cin >> dataWrite[0];
        for(int i = 1; i <= dataWrite[0]; i++) {
            cout << "Nhap phan tu thu " << i << ": ";
            cin >> dataWrite[i];
        }
        sleep(10);
        cout << "Tong la: " << dataRead[0] << endl;
        shmdt((void *)dataWrite);
        shmctl(shmid_write, IPC_RMID, NULL);
    }
    else {
        sleep(10);
        int s = 0;
        for(int i = 1; i <= dataWrite[0]; i++) {
            s += dataWrite[i];
        }
        dataRead[0] = s;
        shmdt((void *)dataRead);
        shmctl(shmid_read, IPC_RMID, NULL);
        sleep(3);
    }


}
