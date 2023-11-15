#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <unistd.h>
using namespace std;

struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;

int main(int argc, char* argv[]) {
    key_t key = ftok(".", 1);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    int a = atoi(&message.msg_text[0]);
    int b = atoi(&message.msg_text[2]);
    char op = message.msg_text[4];
    switch (op) {
        case '+':
            cout << a << " + " << b << " = " << a + b << endl;
            break;
        case '-':
            cout << a << " - " << b << " = " << a - b << endl;
            break;
        case '*':
            cout << a << " * " << b << " = " << a * b << endl;
            break;
        case '/':
            cout << a << " / " << b << " = " << a / (b*(1.0)) << endl;
            break;
    }
    msgctl(msgid, IPC_RMID, NULL);
}