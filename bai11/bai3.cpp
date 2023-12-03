#include <iostream>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

sem_t sem;

void SXKhung() {
    sem_wait(&sem);
    cout << "San xuat khung" << endl;
    sem_post(&sem);
}

void SXBanhXe() {
    sem_wait(&sem);
    cout << "San xuat banh xe" << endl;
    sem_post(&sem);

}

void LapRapXe() {
    sem_wait(&sem);
    cout << "Lap rap xe" << endl;
    sem_post(&sem);
}



int main() {
    sem_init(&sem, 0, 1);
    SXKhung();
    SXBanhXe();
    SXBanhXe();
    SXBanhXe();
    SXBanhXe();
    LapRapXe();
    cout << endl;
    sem_destroy(&sem);
}
