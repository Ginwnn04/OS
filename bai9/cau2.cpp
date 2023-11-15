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

int factorial(int n) {
    int f = 1;
    for (int i = 1; i <= n; i++) {
        f *= i;
    }
    return f;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Doi so khong hop le" << endl;
        return 1;
    }
    key_t key = ftok(".", 1);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    int pid = fork();
    if (pid > 0) {
        message.msg_type = 1;
        snprintf(message.msg_text, sizeof(message.msg_text), "%s %s %s", argv[1], argv[2], argv[3]);
        msgsnd(msgid, &message, sizeof(message), 0);
    }
    else if (pid == 0) {
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

        
    }
    else {
        cout << "Loi tao tien trinh" << endl;
    }
}