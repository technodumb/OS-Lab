#include<stdio.h>
#include<string.h>

int ref[100], nref, fsize, frame[20];
int index=0, fInd=0, pageFaults = 0, freqcount[30];

int checkFault(int fSize, int page, int frame[20]){
    int fault = 1;
    for(int i = 0; i < fSize; i++){
        if(frame[i]==page){
            fault--;
            break;
        }
    }
    return fault;
}

void initFill(){
    while(fInd<fsize && index<nref){
        printf("\n%d", ref[index]);
        freqcount[ref[index]]++;
        int fault = checkFault(fsize, ref[index], frame);
        if(fault){
            frame[fInd] = ref[index];
            fInd++;
            pageFaults++;
            printf(" -> PF");
        }
        index++;
    }
}

void fcfs(){
    printf("\n\nFCFS: \n\n");
    for(int i = 0; i < fsize; i++)
        frame[i] = -1;

    // add to empty frames
    index=fInd=pageFaults=0;
    
    initFill();
    
    fInd=0;
    // fcfs
    for(int i=index; i<nref; i++){
        int fault = checkFault(fsize, ref[i], frame);
        printf("\n%d", ref[i]);
        if(fault){
            printf(" -> PF");
            pageFaults++;
            frame[fInd] = ref[i];
            fInd=(fInd+1)%fsize;
        }
    }   
    printf("\n\nNo of page faults = %d", pageFaults);
}



void lru() {
    printf("\n\nLRU: \n\n");
    for(int i = 0; i < fsize; i++)
        frame[i] = -1;

    // add to empty frames
    index=fInd=pageFaults=0;
    initFill();
    fInd=0;

    // lru
    for(int i=index; i<nref; i++){
        int fault = checkFault(fsize, ref[i], frame);
        printf("\n%d", ref[i]);
        if(fault){
            int least=nref, lruind;
            for(int j=0; j<fsize; j++){
                for(int k=i-1; k>=0; k--){
                    if(ref[k]==frame[j]){
                        if(k<least){
                            least=k;
                            lruind = j;
                        }
                        break;
                    }
                }
            }
            frame[lruind] = ref[i];
            printf(" -> PF");
            pageFaults++;
        }
    }
    printf("\n\nNo of page faults: %d", pageFaults);
}

void lfu(){
    printf("\n\nLFU: \n\n");
    for(int i = 0; i < fsize; i++)
        frame[i] = -1;

    // add to empty frames
    index=fInd=pageFaults=0;
    memset(freqcount, 0, 30);
    
    initFill();
    fInd=0;

    // lfu
    for(int i=index; i<nref; i++){
        int fault = checkFault(fsize, ref[i], frame);
        printf("\n%d", ref[i]);
        freqcount[ref[i]]++; 
        if(fault){
            int lfu=nref, lfuind=0, j=0;
            for(int j=0; j<fsize; j++){
                if(freqcount[frame[fInd]]<lfu){
                    lfu = freqcount[frame[fInd]];
                    lfuind=fInd;
                }
                fInd = (fInd+1)%fsize;
            }
            frame[lfuind] = ref[i];
            fInd = (lfuind+1)%fsize;
            printf(" -> PF");
            pageFaults++;
        }
    }
    printf("\n\nNo of page faults: %d", pageFaults);
}

void main(){
    printf("\n\nEnter the length of reference string: ");
    scanf("%d", &nref);
    printf("Enter the reference string: \n");
    for(int i = 0; i < nref; i++)
        scanf("%d", &ref[i]);
    printf("Enter the frame size: ");
    scanf("%d", &fsize);
    int choice=0;
    do{
        printf("\n\nMENU");
        printf("\n1. FCFS");
        printf("\n1. LRU");
        printf("\n3. LFU");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1: fcfs();
                    break;
            case 2: lru();
                    break;
            case 3: lfu();
                    break;
            case 4: printf("\n Exiting...");
                    break;
            default: printf("enter a valid option...");
        }
    } while(choice!=4);
}