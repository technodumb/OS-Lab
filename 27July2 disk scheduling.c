#include<stdio.h>
#include<math.h>

int nreq, req[100], temp[100], init, tot;

void getRequest() {
    printf("Enter the number of requests in disk queue: ");
    scanf("%d", &nreq);
    printf("Enter the requests in order: \n");
    for(int i = 0; i < nreq; i++){
        scanf("%d", &req[i]);
    }
    printf("Enter the initial position of head: ");
    scanf("%d", &init);

    printf("Enter the number of cylinders in the disk: ");
    scanf("%d", &tot);
}

void sort(){
    int t;
    for(int i = 0; i < nreq-1; i++)
        for(int j = i+1; j < nreq; j++)
            if(temp[i]>temp[j]){
                t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
}

void fcfs(){
    // abs => absolute func.. (aka negative->positive)
    int stime = abs(req[0]-init);
    printf("\n\nOrder:\n\t%d -> %d", init, req[0]);
    for(int i = 1; i < nreq; i++){
        stime += abs(req[i]-req[i-1]);
        printf(" -> %d", req[i]);
    }
    printf("\nTotal Seek time is: %d\n\n", stime);
}

void scan(){
    int start, stime=0;
    sort();
    
    for(int i = 0; i < nreq; i++)
        if(temp[i]>init){
            start = i;
            break;
        }
    
    if(start==0){
        stime = temp[nreq-1] - init;
    }
    else 
        stime = (tot-1)*2 - init - temp[0];

    printf("\n\nOrder:\n\t%d", init);
    for(int i = start; i < nreq; i++)
        printf(" -> %d", temp[i]);
    for(int i=start-1; i>=0; i--)
        printf(" -> %d", temp[i]);

    printf("\nTotal Seek time is: %d\n\n", stime);
}


void cscan(){
    int start, stime=0;
    sort();
    
    for(int i = 0; i < nreq; i++)
        if(temp[i]>init){
            start = i;
            break;
        }
    
    if(start==0)
        stime = temp[nreq-1] - init;
    else 
        stime = tot-1 - init + temp[start-1];

    printf("\n\nOrder:\n\t%d", init);
    for(int i = start; i < nreq; i++)
        printf(" -> %d", temp[i]);
    for(int i=0; i<start; i++)
        printf(" -> %d", temp[i]);

    printf("\nTotal Seek time is: %d\n\n", stime);
}


void main() {
    getRequest();
    int choice;
    do {
        for(int i = 0; i < nreq; i++)
            temp[i] = req[i];

        printf("\n\n\t\tMENU");
        printf("\n1. FCFS");
        printf("\n2. SCAN");
        printf("\n3. C-SCAN");
        printf("\n4. Exit");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1: printf("\n\nFCFS Disk Scheduling\n");
                    fcfs();
                    break;

            case 2: printf("\n\nSCAN Disk Scheduling\n");
                    scan();
                    break;
                
            case 3: printf("\n\nC-SCAN Disk Scheduling\n");
                    cscan();
                    break;

            case 4: printf("\n\nExiting...\n\n");
                    break;

            default:
                    printf("\n\nEnter a valid choice...\n\n"); 
        }
    } while(choice!=4);
}
