#include <stdio.h>
int main()
{
  int mem,ps,npr,pn,off,pid;
  printf("Enter the memory size: ");
  scanf("%d",&mem);
  printf("Enter the page size: ");
  scanf("%d",&ps);
  printf("Enter the number of processes : ");
  scanf("%d",&npr);
  int np=mem/ps;
  int b[npr],c[npr][np];
  for(int i=0;i<npr; i++)
    {
      printf("Enter number of pages of process %d: ",i+1);
      scanf("%d",&b[i]);
    }
  for(int i=0; i<npr;i++)
    {
      printf("Enter the values into the page table for process %d\n",i+1);
      for(int j=0;j<b[i];j++)
         scanf("%d",&c[i][j]);
    }
  for(int i=0;i<npr;i++)
    {
      printf("The page table of process %d\n",i+1);
      for(int j=0; j<b[i];j++)
        {
          printf("%d",c[i][j]);
          printf("\n");
        }
    }
  printf("Enter the process id: ");
  scanf("%d",&pid);
  printf("The logical address of the process is\n");
  printf("   Enter the page number: ");
  scanf("%d",&pn);
  printf("   Enter the offset: ");
  scanf("%d",&off);
  
  int t=(c[pid-1][pn]*ps)+off;
  printf("  The physical address is: %d",t);
  return 0;
}
