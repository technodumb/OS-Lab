#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

pthread_t threads[5];

sem_t semaphore[5];

// void wait(int *sem){
//     while(*sem<=0);
//     (*sem)--;
//         // printf("%d--", *sem);

// }

// void signal(int *sem){
//     (*sem)++;
// }



void eat(int i){
    int next = (i+1)%5;
        printf("Philosopher %d is waiting for chopstick %d\n", i+1, i+1);
    // while(!semaphore[i] || !semaphore[next]);
        // printf("%d--", semaphore[i]);
        sem_wait(&semaphore[i]);
        printf("Philosopher %d picked up chopstick %d\n", i+1, i+1);
        // printf("%d--", semaphore[i]);

        printf("Philosopher %d is waiting for chopstick %d\n", i+1, next+1);
        sem_wait(&semaphore[next]);
        printf("Philosopher %d picked up chopstick %d\n", i+1, next+1);

        printf("Philosopher %d is eating\n", i+1);
        sleep(5);
        sem_post(&semaphore[i]);
        printf("Philoosopher %d placed chopstick %d\n", i+1, i+1);
        sem_post(&semaphore[next]);
        printf("Philosopher %d placed chopstick %d\n", i+1, next+1);
        printf("\t\t\t\tPhilosopher %d is thinking\n", i+1);
        // pthread_join(threads[i], NULL);
    // }

}

void main(){
    for(int i=0; i<5; i++){
        sem_init(&semaphore[i], 0, 1);
    }
    int n_hung, hungry[5];
    printf("Enter the number of Philosophers that are hungry: ");
    scanf("%d", &n_hung);
    for(int i=0; i<n_hung; i++){
        printf("Enter the Philosopher that is hungry: ");
        scanf("%d", &hungry[i]);

    }

    for(int i=0; i<n_hung; i++){
        pthread_create(&threads[hungry[i]-1], NULL, (void*)eat, (void*)hungry[i]-1);
    } 
    for(int i=0; i<5; i++){
        pthread_join(threads[i], NULL);
    }
}