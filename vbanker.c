#include<stdio.h>
#define MAX 10

int m,n,total[MAX],avail[MAX],alloc[MAX][MAX],
    max[MAX][MAX],need[MAX][MAX],work[MAX],finish[MAX],
    seq[MAX],request[MAX];

void accept()
{
int i,j;

printf("Enter no.of process:");
scanf("%d",&n);

printf("Enter no.of resource types:");
scanf("%d",&m);
printf("Enter no.of allocated resources of each resource type by each process:\n");

for(i=0;i<n;i++)
{
printf("P%d:\n",i);
for(j=0;j<m;j++)
{
printf("%c:",65+j);
scanf("%d",&alloc[i][j]);
}
}

printf("Enter no.of maximum resources of each resource type by each process:\n");

for(i=0;i<n;i++)
{
printf("P%d:\n",i);
for(j=0;j<m;j++)
{
printf("%c:",65+j);
scanf("%d",&max[i][j]);
}
}
printf("Enter the Available resources:\n");
for(i=0;i<m;i++)
{
printf("%c:",65+j);
scanf("%d",&avail[i]);
}
}

void calc_need()
{
int i,j;

for(i=0;i<n;i++)
for(j=0;j<m;j++)
need[i][j]=max[i][j]-alloc[i][j];
}

void banker()
{
int i,j,k=0;

for(i=0;i<n;i++)
finish[i]=0;

for(j=0;j<m;j++)
work[j] = avail[j];

i=0;
while((i=check(i))!=-1)
{
printf("Process P%d resource granted.\n",i);
finish[i] = 1;

for(j=0;j<m;j++)
work[j] += alloc[i][j];

printf("finish(");
for(j=0;j<n;j++)
printf("%d,",finish[j]);
printf("\b)\nwork(");
for(j=0;j<m;j++)
printf("%d,",work[j]);
printf("\b)\n");

seq[k++]=i;

i=(i+1)%n;
}

if(k==n)
{
printf("System is in safe state.\n");
printf("Safe sequence:");
for(j=0;j<n;j++)
printf("P%d ",seq[j]);
}
else
{
printf("System is not in safe state.");
}
printf("\n");
}

void print()
{
int i,j;

printf("\tAllocation\tMax\tNeed\n\t");

for(i=0;i<3;i++)
{
for(j=0;j<m;j++)
printf("%3c",65+j);
printf("\t");
}

printf("\n");
for(i=0;i<n;i++)
{
printf("P%d\t",i);
for(j=0;j<m;j++)
printf("%3d",alloc[i][j]);
printf("\t");
for(j=0;j<m;j++)
printf("%3d",max[i][j]);
printf("\t");
for(j=0;j<m;j++)
printf("%3d",need[i][j]);
printf("\n");
}

printf("Available\n");
for(j=0;j<m;j++)
printf("%3c",65+j);
printf("\n");
for(j=0;j<m;j++)
printf("%3d",avail[j]);

printf("\n");
}

int check(int s)
{
int i,j;

i = s;
do
{
if(!finish[i])
{
for(j=0;j<m;j++)
{
if(need[i][j]>work[j])
break;
}

if(j==m) return i;
}

i=(i+1)%n;
}while(i!=s);

return -1;
}


int main()
{
accept();
calc_need();
print();
banker();
}

output:-
bcs@linux-5c0o:~> cc vbanker.c
bcs@linux-5c0o:~> ./a.out
Enter no.of process:5
Enter no.of resource types:4
Enter no.of allocated resources of each resource type by each process:
P0:
A:0
B:0
C:1
D:2
P1:
A:1
B:1
C:0
D:0
P2:
A:1
B:3
C:5
D:4
P3:
A:0
B:6
C:3
D:2
P4:
A:1
B:0
C:1
D:4
Enter no.of maximum resources of each resource type by each process:
P0:
A:0
B:0
C:1
D:2
P1:
A:1
B:7
C:5
D:0
P2:
A:2
B:3
C:5
D:6
P3:
A:0
B:6
C:5
D:2
P4:
A:1
B:6
C:5
D:6
Enter the Available resources:
E:1
E:4
E:2
E:0
	Allocation	Max	Need
	  A  B  C  D	  A  B  C  D	  A  B  C  D	
P0	  0  0  1  2	  0  0  1  2	  0  0  0  0
P1	  1  1  0  0	  1  7  5  0	  0  6  5  0
P2	  1  3  5  4	  2  3  5  6	  1  0  0  2
P3	  0  6  3  2	  0  6  5  2	  0  0  2  0
P4	  1  0  1  4	  1  6  5  6	  0  6  4  2
Available
  A  B  C  D
  1  4  2  0
Process P0 resource granted.
finish(1,0,0,0,0)
work(1,4,3,2)
Process P2 resource granted.
finish(1,0,1,0,0)
work(2,7,8,6)
Process P3 resource granted.
finish(1,0,1,1,0)
work(2,13,11,8)
Process P4 resource granted.
finish(1,0,1,1,1)
work(3,13,12,12)
Process P1 resource granted.
finish(1,1,1,1,1)
work(4,14,12,12)
System is in safe state.
Safe sequence:P0 P2 P3 P4 P1 

