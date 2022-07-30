#include<stdio.h>

struct sector {
    int used;
    int next;
} s[100];

int directory[100][2];
int sNo, nFree;
int dSpace;

void sequential(){
    int nFiles, curBlock=0, nBlocks;
    printf("\n\nEnter the no of files: ");
    scanf("%d", &nFiles);
    for(int i = 0; i < nFiles; i++){
        if(nFree==0){
            printf("\nAll sectors are full\n");
            break;
        }
        printf("\nFile %d: ", i);
        printf("\nStarting position: %d", curBlock);
        printf("\nEnter the no of Blocks in file: ");
        scanf("%d", &nBlocks);

        if(nFree<nBlocks)
            printf("\n\nThe file cannot be allocated.\n");
        else {
            for(int j=curBlock; j < curBlock+nBlocks; j++){
            s[j].used = 1;
            if(j>curBlock) printf("---> ");
                printf("%d ", j);
            }
            printf("\n\nThe file was successfully allocated.\n");
            curBlock += nBlocks;
            nFree-=nBlocks;
        }
    }

}

void linked() {
    int nFiles, nBlocks, start;
    printf("Enter no of files: ");
    scanf("%d", &nFiles);
    for(int i = 0; i < nFiles; i++){
        if(nFree==0){
            printf("\nAll sectors are full\n");
            break;
        }
        printf("\nFile %d: ", i);
        do {
            printf("\nEnter Starting position: ");
            scanf("%d", &start);
            if(s[start].used)
                printf("\nSector already used\n");
        } while(s[start].used);
        int current=start;
        printf("Enter the no of Blocks in file: ");
        scanf("%d", &nBlocks);
        if(nBlocks>nFree)
            printf("\n\nThe file cannot be allocated.\n");
        else {
            current = start;
            for(int j=0; j<nBlocks; j++){
                if(s[current].used){
                    while(s[current].used)
                        current = (current+1)%sNo;
                }
                s[current].used=1;
                if(current!=start) printf("---> ");
                printf("%d ", current);
            }
            nFree-=nBlocks;
            printf("\n\nThe file was successfully allocated.\n");
        }
    }
}

void indexed() {
    int nFiles, start, nBlocks, curBlock=0;
    int indexBlock[10][100], directory[10];
    printf("Enter no of files: ");
    scanf("%d", &nFiles);
    for(int i = 0; i < nFiles; i++) {
        if(nFree<2){
            printf("\nAll sectors are full\n");
            break;
        }
        printf("\n\nFile %d: ", i);
        do {
            printf("\nEnter the location of index block: ");
            scanf("%d", &directory[i]);
            if(s[directory[i]].used)
                printf("\nSpecified sector is already in use.");
        } while(s[directory[i]].used);
        s[directory[i]].used++;
        nFree--;

        printf("\nEnter the no of Blocks in file: ");
        scanf("%d", &nBlocks);
        indexBlock[i][0] = nBlocks;
        if(nBlocks>nFree)
           printf("\nThe file cannot be allocated.\n");
        
        else {
            for(int j=0; j<nBlocks; j++){
                if(s[curBlock].used){
                    while(s[curBlock].used)
                        curBlock = (curBlock+1)%sNo;
                }
                s[curBlock].used=1;
                indexBlock[i][j+1] = curBlock;
            }
            nFree-=nBlocks;
            printf("\nThe file was successfully allocated.\n");
        }
    }
    printf("\n\nIndex Block:\n");
    for(int i=0; i<nFiles; i++){
        printf("\nFile %d: Index Block at Sector %d\n", i, directory[i]);
        for(int j=0; j<indexBlock[i][0]; j++){
            printf("\t %d", indexBlock[i][j+1]);
        }
        printf("\n");
    }
}

void main() {
    printf("\nEnter the number of sectors in Disk: ");
    scanf("%d", &sNo);
    int choice;
    do {
        for(int i=0; i<sNo; i++){
            s[i].used = 0;
        }
        nFree=sNo;
        printf("\n\nMENU\n");
        printf("\n1. Sequential allocation");
        printf("\n2. Linked allocation");
        printf("\n3. Indexed allocation");
        printf("\n4. Exit");
        printf("\n\n Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: sequential();
                    break;
            case 2: linked();
                    break;
            case 3: indexed();
                    break;
            case 4: printf("\n\nExiting...\n\n");
                    break;
            default: printf("\nEnter a valid choice..\n\n");
        }
    } while(choice !=4);
}