// Write a c program to simulate the following continuous memory allocation techniques:
// 1. Worst Fit
// 2. Best Fit
// 3. First Fit

#include<stdio.h>
#include<stdlib.h>

void process_input(int *nb, int blocks[100], int *np, int processes[100], int allocated[100]){
    printf("Enter the number of blocks: ");
    scanf("%d",nb);
    printf("Enter the sizes of blocks: \n");
    for(int i=0; i<*nb; i++){
        printf("\tBlock %d: ", i+1);
        scanf("%d", &blocks[i]);
    }
    printf("Enter the number of processes: ");
    scanf("%d", np);
    printf("Enter the memory required by the processes: \n");
    for(int i=0; i<*np; i++){
        printf("\tProcess %d: ", i+1);
        scanf("%d", &processes[i]);
    }
    for(int i=0; i<*np; i++){
        allocated[i] = -1;
    }
}

void display(int np, int processes[100], int allocated[100]){
    printf("Process ID\t\tProcess Size\t\tBlock No.\n");
    for(int i=0; i<np; i++){
        printf("%d\t\t\t%d\t\t\t", i+1, processes[i]);
        if(allocated[i] == -1){
            printf("Not Allocated\n");
        }
        else{
            printf("%d\n", allocated[i]+1);
        }
    }
}


void firstfit(){
    int nb, blocks[100];
    int np, processes[100], allocated[100];
    process_input(&nb, blocks, &np, processes, allocated);

    for(int i=0; i<np; i++){
        for(int j = 0; j < nb; j++){
            if(blocks[j] >= processes[i]){
                allocated[i] = j;
                blocks[j] -= processes[i];
                printf("Process %d allocated in block %d\n", i+1, j+1);
                break;
            }
        }
    }
    printf("\nFirst Fit Memory Allocation\n");
    display(np, processes, allocated);

}

void bestfit(){
    int nb, blocks[100], np, processes[100], allocated[100];
    process_input(&nb, blocks, &np, processes, allocated);

    for(int i=0; i<np; i++){
        int min = 1000000;
        int index = -1;
        for(int j = 0; j < nb; j++){
            if(blocks[j] >= processes[i] && blocks[j] < min){
                min = blocks[j];
                index = j;
            }
        }
        if(index != -1){
            allocated[i] = index;
            blocks[index] -= processes[i];
            printf("Process %d allocated in block %d\n", i+1, index+1);
        }
    }
    printf("\nBest Fit Memory Allocation\n");
    display(np, processes, allocated);
}


void worstfit(){
    int nb, blocks[100], np, processes[100], allocated[100];
    process_input(&nb, blocks, &np, processes, allocated);

    for(int i=0; i<np; i++){
        int max = -1;
        int index = -1;
        for(int j = 0; j < nb; j++){
            if(blocks[j] >= processes[i] && blocks[j] > max){
                max = blocks[j];
                index = j;
            }
        }
        if(index != -1){
            allocated[i] = index;
            blocks[index] -= processes[i];
            printf("Process %d allocated in block %d\n", i+1, index+1);
        }
    }
    printf("\nWorst Fit Memory Allocation\n");
    display(np, processes, allocated);
}

void main(){
    int choice=0;
    do {
        printf("\n\n\tMENU \n\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                firstfit();
                break;
            case 2:
                bestfit();
                break;
            case 3:
                worstfit();
                break;
            case 4:
                printf("Exiting...");
                break;
            default:
                printf("Invalid Choice\n");
        }
    } while(choice!=4);
}