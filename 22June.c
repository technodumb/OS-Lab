#include<stdio.h>

int Available[10], Allocation[10][10], Max[10][10], Need[10][10];
int n_process, n_resources;
int Finish[10], Work[10];
// banker's algorithm

int isSafe() {
    int no_finished=0, last=0;
    
    for(int i=0; i<n_process; i++){
        Finish[i] = 0;
    }
    for(int i=0; i<n_resources; i++){
        Work[i] = Available[i];
    }

    do{
        last = no_finished;
        for(int i=0; i<n_process; i++){
            if(Finish[i] == 0){
                int flag = 1;
                for(int j=0; j<n_resources; j++){
                    if(Work[j] < Need[i][j]){
                        flag = 0;
                        printf("Process %d has to wait...\n", i);
                        break;
                    }
                }
                if(flag == 1){
                    for(int j=0; j<n_resources; j++){
                        Work[j] += Allocation[i][j];
                    }
                    printf("Process %d completed execution...\n", i);
                    Finish[i] = 1;
                    no_finished++;
                }
            }
        }
    } while(no_finished!=last);
    // if(no_finished==n_process)
    return no_finished==n_process; 
}

void request(){
    int req_process, Request[10];
    printf("\n\n Enter the requesting process: ");
    scanf("%d",&req_process);
    printf("Enter the request: ");
    for(int i=0; i<n_resources; i++){
        scanf("%d", &Request[i]);
    }


    int flag = 0;
    // condition 1: check whether vaild request
    for(int i=0; i<n_resources; i++)
        if(Request[i]>Need[req_process][i]){
            flag=1;
            break;
        }
    if(flag){
        printf("The request is invalid.");
        return;
    }
    flag=0;
    for(int i=0; i<n_resources; i++)
        if(Request[i]>Available[i]){
            flag=1;
            break;
        }
    if(flag){
        printf("The process has to wait due to lack of available free resources..");
        return;
    }

    flag=0;
    for(int i=0; i<n_resources; i++){
        Available[i]=Available[i]-Request[i];
        Allocation[req_process][i] = Allocation[req_process][i] + Request[i];
        Need[req_process][i] = Need[req_process][i] + Request[i];
    }

    if(isSafe()){ 
        printf("\nThe request can be satisfied immediately.");
    }
    else {
        printf("The request cannot be satisfied immediately.");
    }
}

void main(){
    printf("Enter the no of processes (n): ");
    scanf("%d", &n_process);
    printf("Enter the no of types of resources (m): ");
    scanf("%d", &n_resources);

    printf("Enter the no of instances of each resource: \n");
    for(int i=0; i<n_resources; i++){
        scanf("%d", &Available[i]);
    }

    printf("Enter the Max matrix (n x m): \n");
    for(int i=0; i<n_process; i++){
        for(int j=0; j<n_resources; j++){
            scanf("%d", &Max[i][j]);
        }
    }

    printf("Enter the allocation matrix (n x m): \n");
    for(int i=0; i<n_process; i++){
        for(int j=0; j<n_resources; j++){
            scanf("%d", &Allocation[i][j]);
        }
    }

    // find the need matrix
    for(int i=0; i<n_process; i++){
        for(int j=0; j<n_resources; j++){
            Need[i][j] = Max[i][j] - Allocation[i][j];
            printf("%d ",Need[i][j]);
        }
        printf("\n");
    }

    if(isSafe()){
        printf("\n\nThe given snapshot is in safe condition.");
        request();
    }
    else{    
        printf("\n\nThe given snapshot is not safe");
    }
}


