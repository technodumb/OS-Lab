#include<stdio.h>

struct sector {
    int used;
    struct sector *next;
}s[100];

int directory[100][2];
int sSize, bSize, sNo;
int dSpace;

void sequential(){
    int nFiles, startBlock, fSize, nBlocks;
    printf("\n\nEnter the no of files: ");
    scanf("%d", &nFiles);
    for(int i = 0; i < nFiles; i++){
        printf("\nFile %d: ", i);
        printf("\nEnter the starting block: ");
        scanf("%d", &startBlock);
        printf("Enter the file size: ");
        scanf("%d", &fSize);
        nBlocks = fSize / bSize;

        // check if space is available
        int flag=0;
        for(int j = startBlock; j < startBlock+nBlocks; j++){
            if(s[i].used){
                flag++;
                break;
            }
        }
        if(flag){
            printf("\n\nThe file cannot be allocated.\n");
        }
        else {
            for(int j=startBlock; j < startBlock+nBlocks; j++){
                s[j].used = 1;
                if(j>startBlock) printf("---> ");
                printf("%d ", j);
            }
            directory[i][0] = startBlock;
            directory[i][1] = nBlocks;
            printf("The file was successfully allocated.\n");
        }
    }

}


void main() {
    printf("\nEnter the total disk space: ");
    scanf("%d", &dSpace);
    printf("Enter the size of the sector: ");
    scanf("%d", &sSize);
    bSize = sSize;
    sNo = dSpace/sSize;
    printf("\nThe number of sectors in disk are: %d", sNo);
    int choice;
    do {
        for(int i=0; i<sNo; i++){
            s[i].used = 0;
        }
        printf("\n\nMENU\n");
        printf("\n1. Sequential allocation");
        printf("\n2. Linked allocation");
        printf("\n3. Indexed allocation");
        printf("\n4. Exit");
        printf("\n\n Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: 
                    sequential();
                    break;
            case 4: printf("\n\nExiting...\n\n");
                    break;
            default: printf("\nEnter a valid choice..\n\n");            
        }
    } while(choice !=4);
}