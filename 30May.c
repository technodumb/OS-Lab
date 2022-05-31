// Write a c program to simulate the following cpu scheduling algorithms 
// 1) FCFS
// 2) SJF(non preemptive)
// 3)Round Robin(preemptive)
// 4)priority(non preemptive)

// Also display the average waiting time and turn around time

#include<stdio.h>

struct prdet{
    int pid;
    float bt;
    float wt;
    float tat;
    int pri;
};


void fcfs(struct prdet p[10], int n, float *avg_wt, float *avg_tat){
    *avg_wt = 0;
    *avg_tat = 0;
    for (int i = 0; i < n; i++){
        if(i==0)
            p[0].wt = 0;
        else
            p[i].wt = p[i - 1].wt + p[i - 1].bt;
        p[i].tat = p[i].bt + p[i].wt;
        *avg_wt += p[i].wt;
        *avg_tat += p[i].tat;
    }
    *avg_wt /= n;
    *avg_tat /= n;
}

void sjf(struct prdet p[10], int n, float *avg_wt, float *avg_tat) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (p[i].bt > p[j].bt) {
                struct prdet temp = p[j];
                p[j]= p[i];
                p[i] = temp;
            }
        }
    }
    fcfs(p, n, avg_wt, avg_tat);
    for (int i = 0; i < n; i++) {
        for(int j = i+1; j<n; j++){
            if(p[i].pid > p[j].pid){
                struct prdet temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void priority(struct prdet p[10], int n, float *avg_wt, float *avg_tat){
    printf("\nEnter the priority for each process: (highest priority first)");
    for (int i = 0; i < n; i++) {
        printf("\nP%d: ", i + 1);
        scanf("%d", &p[i].pri);
    }
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (p[i].pri < p[j].pri) {
                struct prdet temp = p[j];
                p[j]= p[i];
                p[i] = temp;
            }
        }
    }
    fcfs(p, n, avg_wt, avg_tat);
    for (int i = 0; i < n-1; i++) {
        for(int j = i+1; j<n; j++){
            if(p[i].pid > p[j].pid){
                struct prdet temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void roundrobin(struct prdet p[10], int n, float *avg_wt, float *avg_tat){
    int timeQuantum;
    printf("\nEnter the time quantum: ");
    scanf("%d", &timeQuantum);
    int t = 0, k = 0, tempBt[10];
    for (int i = 0; i < n; i++){
        tempBt[i] = p[i].bt;
    }
    int count = n;
    while(count > 0){
        if(tempBt[k]==0){
            k = (k+1)%n;
            continue;
        }
        if(tempBt[k] > timeQuantum){
            tempBt[k] -= timeQuantum;
            t += timeQuantum;
        }
        else{
            t = t + tempBt[k];
            tempBt[k] = 0;
            p[k].tat = t;
            p[k].wt = p[k].tat - p[k].bt;
            *avg_wt += p[k].wt;
            *avg_tat += p[k].tat;
            count--;
        }
        k = (k+1)%n;
    }
    *avg_wt = *avg_wt / n;
    *avg_tat = *avg_tat / n;
}

void display(struct prdet p[10], int n, float avg_wt, float avg_tat){
    printf("\nPID\tBurst Time\tWait Time\tTurn-Around-Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%.2f\t\t%f\t\t%.2f\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat);
    }
    printf("\nAverage waiting time = %f\n", avg_wt);
    printf("Average turn around time = %f\n", avg_tat);
}

void getinput(struct prdet p[10], int *n){
    printf("Enter the number of processes: ");
    scanf("%d", n);
    for (int i = 0; i < *n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter burst time for P%d: ", i + 1);
        scanf("%f", &p[i].bt);
    }
  
}

void main() {
    int n, i, j, temp, sum_wt, sum_tat;
    float avg_wt, avg_tat;
    struct prdet p[10], tempP[10];
  
    int choice;
    do {
        printf("Choose the scheduling algorithm\n");
        printf("1. FCFS (non preemptive)\n");
        printf("2. SJF (non preemptive)\n");
        printf("3. Round Robin (preemptive)\n");
        printf("4. Priority (non preemptive)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("\nFCFS (non preemptive)");
                getinput(p, &n);
                fcfs(p, n, &avg_wt, &avg_tat);
                display(p, n, avg_wt, avg_tat);
                break;

            case 2:
                printf("\nSJF (non preemptive)");
                getinput(p, &n);
                sjf(p, n, &avg_wt, &avg_tat);
                display(p, n, avg_wt, avg_tat);
                break;
            
            case 3: 
                printf("\nRound Robin (preemptive)");
                getinput(p, &n);
                roundrobin(p, n, &avg_wt, &avg_tat);
                display(p, n, avg_wt, avg_tat);
                break;
            
            case 4: 
                printf("\nPriority (non preemptive)");
                getinput(p, &n);
                priority(p, n, &avg_wt, &avg_tat);
                display(p, n, avg_wt, avg_tat);
                break;
            
            case 5:
                printf("\nExiting...\n\n");
                break;
            
            default:
                printf("\nEnter a valid choice...");
        }
    } while(choice != 5);
}