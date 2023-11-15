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

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Doi so khong hop le" << endl;
        return 1;
    }
    key_t key = ftok(".", 1);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    
    message.msg_type = 1;
    strcpy(message.msg_text, argv[1]);
    msgsnd(msgid, &message, sizeof(message), 0);
    
}