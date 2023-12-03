#include <iostream>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

sem_t sem;

void *thr_chan(void* arg) {
    for(int i = 2; i <= 10; i+=2){
        sem_wait(&sem);
        cout << i << " ";
        sem_post(&sem);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *thr_le(void* arg) {
    for(int i = 1; i <= 11; i+=2){
        sem_wait(&sem);
        cout << i << " ";
        sem_post(&sem);
        sleep(1);
    }
    pthread_exit(NULL);

}


int main() {
    sem_init(&sem, 0, 1);
    pthread_t thr1, thr2;
    pthread_create(&thr1, NULL, thr_le, NULL);
    pthread_create(&thr2, NULL, thr_chan, NULL);
    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);
    cout << endl;
    sem_destroy(&sem);
}
