#include <iostream>
#include <pthread.h>
using namespace std;

int count = 0;

struct file {
    char* fileInput;
    char* fileOutput;
};


void *copyFile(void* f) {
    file* f1 = (file*) f;
    FILE* fp1 = fopen(f1->fileInput, "r");
    FILE* fp2 = fopen(f1->fileOutput, "w");
    char c;
    while ((c = fgetc(fp1)) != EOF) {
        fputc(c, fp2);
        count++;
    }
    fclose(fp1);
    fclose(fp2);
}

int main(int agrc, char* agrv[]) {
    file f = file();
    f.fileInput = agrv[1];
    f.fileOutput = agrv[2];
    int status; int* pstatus = &status;
    pthread_t tid;
    pthread_create(&tid, NULL, copyFile, &f);
    if (pthread_join(tid, (void**)pstatus) == 0) {
        cout << "Da copy thanh cong " << count << " ki tu" << endl;
    }
}
