#include<stdio.h>

void main(){
    int m_size, p_size, n_frames, n_process, n_page[100], page_table[100][100];
    printf("Enter memory size: ");
    scanf("%d", &m_size);
    printf("Enter the page size: ");
    scanf("%d", &p_size);
    printf("Enter the number of frames avaliable: ");
    scanf("%d", &n_frames);
    printf("Enter the number of processes to be loaded: ");
    scanf("%d", &n_process);
    printf("Enter the process details:\n");
    for(int i = 0; i < n_process; i++){
        printf("\nProcess %d: ");
        printf("\n\tNo of pages: ");
        scanf("%d", &n_page[i]);
        printf("\n\tEnter the page table: \n\t\t");
        for(int j= 0; j<n_page[i]; j++)
            scanf("%d", &page_table[i][j]);
    }

    int choice=0;
    do {
        printf("\t\tMENU\n\n");
        printf("\n1. Convert logical address to physical address: ");
        printf("\n2. Exit");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);
        
    } while(choice!=2);
}