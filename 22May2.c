#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
// #include<sys/types.h>

void main()
{
    int n,fp,fp1,ch;
    char r[100],w[100],buf[100];
    do{
        printf("\n\n\tMENU");
        printf("\n1.Open the files");
        printf("\n2.Execute read command");
        printf("\n3.Execute write command");
        printf("\n\nEnter your choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:printf("Enter file to be read: ");
                   scanf("%s",r);
                   printf("Enter file to write to: ");
                   scanf("%s",w);
                   fp=open(r,O_RDONLY);
                   fp1=open(w,O_CREAT|O_WRONLY);
                   break;
            case 2:
                     printf("First 100 characters were read from %s", r);
                     n=read(fp,buf,100);
                     break;

            case 3:  printf("The read data was written to %s", w);
                     write(fp1,buf,n);
                     break;
              case 4: printf("Exiting");
                     break;
              default: printf("Enter a valid choice");
        }
    }
 while(ch!=4);
}
