// navaneeth wrote this code its proven to be wrong
// please stay away from this code.

#include <stdio.h>
int main()
{
  int n,m;
  printf("Enter the number of processes: ");
  scanf("%d",&n);
  printf("Enter the number of resources: ");
  scanf("%d",&m);
  int all[n][m],max[n][m],need[n][m],avail[m],req[m],p[n],f[n];
  for(int i=0;i<n;i++)
    {
      p[i]=i+1;
      f[i]=0;
    }
  printf("Enter the allocation matrix:\n ");
  for(int i=0;i<n;i++)
    {
      for(int j=0;j<m;j++)
        {
          scanf("%d",&all[i][j]);
        }
    }
  printf("Enter the maximum matrix:\n ");
  for(int i=0;i<n;i++)
    {
      for(int j=0;j<m;j++)
        {
          scanf("%d",&max[i][j]);
        }
    }
   for(int i=0;i<n;i++)
    {
      for(int j=0;j<m;j++)
        {
          need[i][j]=max[i][j]-all[i][j];
        }
    }
  printf("Need matrix\n ");
   for(int i=0;i<n;i++)
    {
      for(int j=0;j<m;j++)
        {
          printf("%d  ",need[i][j]);
        }
      printf("\n");
    }
  printf("Enter the available\n");
  for(int i=0;i<m;i++)
    {
      scanf("%d",&avail[i]);
    }
  int a,ch;
  printf("Do you want to request: ");
  scanf("%d",&ch);
  int t=0;
  if(ch)
  {
    printf("Enter the process ID: ");
    scanf("%d",&a);
    printf("Enter the request\n");
    for(int i=0;i<m;i++)
      scanf("%d",&req[i]);
    for(int i=0;i<m;i++)
      {
        if(req[i]<=avail[i] && req[i]<=all[a-1][i])
          t=0;
        else
        {
          printf("Request cannot be granted\n");
          t=1;
          break;
        }
      }
    if(t!=1)
    {
      for(int i=0;i<m;i++)
        {
          avail[i]-=req[i];
          all[a-1][i]+=req[i];
          need[a-1][i]-=req[i];
        }
    }
  }
  int j=0,k;
  //find out the error....there is some issue with the while loop
  while(j<n) 
    {
      if(f[j]!=1)
      {
      for(int i=0;i<m;i++)
        {
          if(need[j][i]<=avail[i])
          {
            k++;
          }
          else
          {
            j++;
          }
        }
      if(k==m)
      {
        for(int i=0;i<m;i++)
          {
            avail[i]+=all[j][i];
          }
        f[j]=1;
        printf("Process %d has executed\n",j+1);
      }
      }
      if(j==n-1)
      {
        j=0;
        k=0;
      }
      else
      {
        j++;
        k=0;
      }
    }
  for(int i=0;i<n;i++)
    {
      if(f[i]!=1)
      {
        printf("Deadlock found\n");
        break;
      }
    }
  return 0;
  }
