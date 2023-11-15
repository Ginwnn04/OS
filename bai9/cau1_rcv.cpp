#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
using namespace std;

struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;

int factorial(int n) {
    int f = 1;
    for (int i = 1; i <= n; i++) {
        f *= i;
    }
    return f;
}

int main(int argc, char* argv[]) {
    key_t key = ftok(".", 1);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    int n = atoi(message.msg_text);
    int f = factorial(n);
    cout << n << "!= " << f << endl;
    msgctl(msgid, IPC_RMID, NULL);
}