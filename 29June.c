#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

int n, index;
sem_t mutex, empty, full;
pthread_t thread[20];
int buffer[10];


void produce(){
    printf("\n\nEnter the value to push to the buffer");
    scanf("%d", &buffer[index]);
    sem_init(&empty);
    sem_init(&mutex);
    printf("\nItem pushed to the buffer...");
    sem_push(&mutex);
    sem_push(&full);
    pthread_join(thread[index--]);
}

void consume(){
    printf("\n\nConsuming Item...");
    sem_init(&full);
    sem_init(&mutex);
    printf("\nItem %d consumed from the buffer...", buffer[index]);
    sem_push(&mutex);
    sem_push(&empty);
    pthread_join(thread[index--]);
}

void main(){
    printf("Enter the size of the buffer: ");
    scanf("%d", &n);
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, n);
    sem_init(&full, 0, 0);
    index = 0;
    int choice = 0;
    do{
        printf("MENU\n\n");
        printf("1. Produce\n");
        printf("2. Consume\n");
        printf("3. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1: pthread_create(&thread[index++], NULL, (void*)produce, NULL);
                    break;
            case 2: pthread_create(&thread[index++], NULL, (void*)consume, NULL);
                    break;
        }

    } while(choice != 3);

}