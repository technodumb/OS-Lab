#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

int n, indp, indc;
sem_t mutex, empty, full;
pthread_t thread[20];
int buffer[10];


void produce(){
    printf("\n\nEnter the value to push to the buffer");
    scanf("%d", &buffer[indp]);
    sem_wait(&empty);
    sem_wait(&mutex);
    printf("\nItem pushed to the buffer...");
    sem_post(&mutex);
    sem_post(&full);
}

void consume(){
    printf("\n\nConsuming Item...");
    sem_wait(&full);
    sem_wait(&mutex);
    printf("\nItem %d consumed from the buffer...", buffer[indc]);
    sem_post(&mutex);
    sem_post(&empty);
}

void main(){
    printf("Enter the size of the buffer: ");
    scanf("%d", &n);
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, n);
    sem_init(&full, 0, 0);
    indp = indc = 0;
    int choice = 0, sememp, semmut;
    do{
        printf("MENU\n\n");
        printf("1. Produce\n");
        printf("2. Consume\n");
        printf("3. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        sem_getvalue(&empty, &sememp);
        sem_getvalue(&mutex, &semmut);
        switch(choice){
            case 1: if(sememp!=0 && semmut== 1)
                        producer();
                    else
                        printf("Buffer is full");
                    break;
            case 2: if(sememp!=n && semmut== 1)
                        consumer();
                    else
                        printf("Buffer is empty");
                    break;
        }

    } while(choice != 3);

}