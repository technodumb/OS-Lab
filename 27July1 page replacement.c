#include<stdio.h>

// page replacement

// checks if the request leads to page fault
int checkFault(int fsize, int need, int f[100]){
    for(int i = 0; i < fsize; i++){
        if(f[i] == -1){
            f[i] = need;
            return 2;
        }
        if(need == f[i])
            return 0;
    }
    return 1;
}



void fifo(int n, int ref[100]){
    int frameSize, frames[100];
    printf("Enter the frame size: ");
    scanf("%d", &frameSize);
    for(int i = 0; i < frameSize; i++)
        frames[i] = -1;

    printf("\n\nFIFO Page Replacement:\n\n");
    printf("\tPage\t\tFrames");

    int outEnd=0, fault, noFaults=0;
    for(int i = 0; i < n; i++){
        fault = checkFault(frameSize, ref[i], frames);
        if(fault == 1){
            frames[outEnd] = ref[i];
            outEnd = (outEnd+1)%frameSize;
        }
        
        printf("\n\t%d\t\t", ref[i]);
        for(int j=0; j<frameSize; j++){
            if(frames[j] != -1)
                printf("%d", frames[j]);
            printf("\t");
        }
        if(fault) {
            noFaults++;
            printf("PF");
        }
    }
    printf("\n\nNo of Page faults = %d\n", noFaults);
}

void lru(int n, int ref[100]){
    int frameSize, frames[100], used[100];
    printf("Enter the frame size: ");
    scanf("%d", &frameSize);
    for(int i = 0; i < frameSize; i++){
        frames[i] = -1;
        used[i] = -1;
    }
    printf("\n\nLRU Page Replacement:\n\n");
    printf("\tPage\t\tFrames");

    int fault, noFaults=0;
    for(int i = 0; i <n; i++){
        fault = checkFault(frameSize, ref[i], frames);

        if(fault==1) {
            for(int j = 0; j<frameSize; j++)
                for(int k = i; k>=0; k--)
                    if(frames[j]==ref[k]){
                        used[j] = i-k;
                        break;
                    }
            
            int max = 0, lruind;
            for(int j = 0; j < frameSize; j++){
                if(used[j]>max){
                    max = used[j];
                    lruind = j;
                }
            }
            frames[lruind] = ref[i];
        }
        printf("\n\t%d\t\t", ref[i]);
        for(int j=0; j<frameSize; j++){
            if(frames[j] != -1)
                printf("%d", frames[j]);
            printf("\t");
        }
         if(fault) {
            noFaults++;
            printf("PF");
        }
    }
    
    printf("\n\nNo of Page faults = %d\n", noFaults);
}

void opt(int n, int ref[100]){
    int frameSize, frames[100], used[100];
    printf("Enter the frame size: ");
    scanf("%d", &frameSize);
    for(int i = 0; i < frameSize; i++){
        frames[i] = -1;
        used[i] = -1;
    }
    printf("\n\nOPT Page Replacement:\n\n");
    printf("\tPage\t\tFrames");

    int fault, noFaults=0;
    for(int i = 0; i <n; i++){
        fault = checkFault(frameSize, ref[i], frames);

        if(fault==1) {
            for(int j = 0; j<frameSize; j++)
                for(int k = i; k<n; k++){
                    used[j] = 100;
                    if(frames[j]==ref[k]){
                        used[j] = k-i;
                        break;
                    }
                }
            
            int max = 0, optind;
            for(int j = 0; j < frameSize; j++){
                if(used[j]>max){
                    max = used[j];
                    optind = j;
                }
            }
            frames[optind] = ref[i];
        }
        printf("\n\t%d\t\t", ref[i]);
        for(int j=0; j<frameSize; j++){
            if(frames[j] != -1)
                printf("%d", frames[j]);
            printf("\t");
        }
         if(fault) {
            noFaults++;
            printf("PF");
        }
    }
    
    printf("\n\nNo of Page faults = %d\n", noFaults);
}


void main(){
    int n, refStr[100], temp[100];
    printf("Input the number of terms in reference string: ");
    scanf("%d",&n);
    printf("Input the reference string: ");
    for(int i=0; i<n; i++){
        scanf("%d",&refStr[i]);
    }
    int choice;
    do{
        for(int i=0; i<n; i++){
            temp[i] = refStr[i];
        }
        printf("\n\n\n\t\tMENU");
        printf("\n1. FIFO");
        printf("\n2. OPT");
        printf("\n3. LRU");
        printf("\n4. Exit");
        printf("\n\nEnter your choice: ");
        scanf("%d",&choice);
        
        switch(choice){
            case 1: fifo(n, temp);
                    break;
            
            case 2: opt(n, temp);
                    break;
            
            case 3: lru(n, temp);
                    break;

            case 4: printf("\nExiting...\n\n");
                    break;

            default: printf("\n\nEnter a valid choice..\n\n");
        }
    } while(choice !=4);
}
