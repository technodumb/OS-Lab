// demonstrate the working of system calls in linux
// fork, exec, getpid

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<dirent.h>
void main()
{
    int pid;
    int ch;
    struct stat sfile;
    DIR *d;
    char fname[30];
    struct dirent *de;
    do{
    printf("\n\t\tMENU\n");
    printf("\n1. fork");
    printf("\n2. exec");
    printf("\n3. getpid");
    printf("\n4. wait and exit");
    printf("\n5. stat");
    printf("\n6. opendir, readdir & closedir");
    printf("\n7. Exit");
    printf("\n\nEnter your choice: ");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1: pid=fork();
                if(pid==0) {
                    printf("\n Executing child process");
                    printf("\n Child process id is %d\n",getpid());
                }
                else
                {
                    wait();
                    printf("\n Executing parent process");
                    printf("\n Parent process id is %d",getpid());
                }
               break;
        case 2: printf("\nRunning the ls command in the current folder: \n");
                execl("/usr/bin/ls","ls","-l",NULL);
                break;
        case 3:printf("Process ID of the calling process = %d",getpid());
               break;
        case 4: 
                pid = fork();
                int status;
                if(pid==0)
                {
                    printf("\nChild process execution completes in 10 seconds\n");
                    sleep(10);
                    printf("\nChild process exiting\n\n");
                    exit(10);
                }
                else
                {
                    printf("Creating a new fork!\n\n");
                    printf("Parent (waiting for child process to finish execution) \n");
                    wait(&status);
                    printf("Process ID: %d", pid);
                    printf("Exit status is %d\n",WEXITSTATUS(status));
                }
                break;
        case 5: printf("Enter the filename: ");
                scanf("%s", &fname);
                
                stat(fname,&sfile);
                printf("\nFile Size: %ld \n",sfile.st_size);
               break;
        case 6:d=opendir(".");
               while(de=readdir(d))
               {
                   printf("%s\n",de->d_name);
               }
               closedir(d);
               break;
        case 7: printf("Exiting...");
                break;
        default: printf("\nInvalid choice");
    }
    }
   while(ch!=7);
}