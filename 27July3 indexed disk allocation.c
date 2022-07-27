#include<stdio.h>

struct sector {
    int used;
    int next;
} s[100];

int directory[100][2];
int nUsed, sNo;
int dSpace;

void sequential(){
    int nFiles, curBlock=0, nBlocks;
    printf("\n\nEnter the no of files: ");
    scanf("%d", &nFiles);
    for(int i = 0; i < nFiles; i++){
        if(nUsed>=sNo){
            printf("\nAll sectors are full\n");
            break;
        }
        printf("\nFile %d: ", i);
        printf("\nStarting position: %d", curBlock);
        printf("\nEnter the no of Blocks in file: ");
        scanf("%d", &nBlocks);

        // check if space is available
        int flag=0;
        for(int j = curBlock; j < curBlock+nBlocks; j++){
            if(j >= sNo){
                flag++;
                break;
            }
        }
        if(flag){
            printf("\n\nThe file cannot be allocated.\n");
        }
        else {
            for(int j=curBlock; j < curBlock+nBlocks; j++){
            s[j].used = 1;
            if(j>curBlock) printf("---> ");
                printf("%d ", j);
        }
        directory[i][0] = curBlock;
        directory[i][1] = nBlocks;
        printf("\n\nThe file was successfully allocated.\n");
        curBlock += nBlocks;
        }
    }

}

void linked() {
    int nFiles, nBlocks, curBlock=0, start;
    printf("Enter no of files: ");
    scanf("%d", &nFiles);
    for(int i = 0; i < nFiles; i++){
        if(nUsed>=sNo){
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
        // check if space is available
        int flag=0, tUsed = nUsed;

        for(int j=0; j<nBlocks; j++){
            if(tUsed>sNo){
                flag++;
                break;
            }
            if(s[current].used){
                while(s[current].used)
                    current = (current+1)%sNo;
            }
            tUsed++;
        }
        if(flag){
            printf("\n\nThe file cannot be allocated.\n");
        }
        else {
            current = start;
            for(int j=0; j<nBlocks; j++){
                if(s[current].used){
                    while(s[current].used)
                        current = (current+1)%sNo;
                }
                s[current].used=1;
                nUsed++;
                if(current!=start) printf("---> ");
                printf("%d ", current);
            }
            printf("\n\nThe file was successfully allocated.\n");
            curBlock += nBlocks;
        }
    }
}

void indexed() {
    int nFiles, start, nBlocks, curBlock=0;
    int indexBlock[10][100], directory[10];
    printf("Enter no of files: ");
    scanf("%d", &nFiles);
    for(int i = 0; i < nFiles; i++) {
        if(nUsed>=sNo-1){
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
        nUsed++;

        do {
            printf("\nEnter Starting position: ");
            scanf("%d", &start);
            if(s[start].used)
                printf("\n\nSector already used\n");
        } while(s[start].used);
        int current=start;
        printf("\nEnter the no of Blocks in file: ");
        scanf("%d", &nBlocks);
        indexBlock[i][0] = nBlocks;
        int flag=0, tUsed = nUsed;

        for(int j=0; j<nBlocks; j++){
            if(tUsed>sNo){
                flag++;
                break;
            }
            if(s[current].used){
            while(s[current].used)
                current = (current+1)%sNo;
            }
            tUsed++;
        }
        if(flag){
            printf("\nThe file cannot be allocated.\n");
        }
        else {
            current = start;
            for(int j=0; j<nBlocks; j++){
                if(s[current].used){
                    while(s[current].used)
                        current = (current+1)%sNo;
                }
                s[current].used=1;
                nUsed++;
                indexBlock[i][j+1] = current;
            }
            printf("\nThe file was successfully allocated.\n");
            curBlock += nBlocks;
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
        nUsed = 0;
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