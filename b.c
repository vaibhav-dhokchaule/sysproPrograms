#include <stdio.h>
int main()
{
int n, m, i, j, k,alloc[10][10],max[10][10],avail[10];
printf("Enter the total no.of processes and resources:\n");
scanf("%d%d",&n,&m);
printf("Enter Allocation matrix:\n");
for(i=0;i<n;i++)
{
for(j=0;j<m;j++)
{
scanf("%d",&alloc[i][j]);
}
}
printf("Enter Max matrix:\n");
for(i=0;i<n;i++)
{
for(j=0;j<m;j++)
{
scanf("%d",&max[i][j]);
}
}
printf("Enter Available matrix:\n");
for(j=0;j<m;j++)
{
scanf("%d",&avail[j]);
}
int f[n], ans[n], ind = 0;
for (k = 0; k < n; k++) 
f[k] = 0;
     
int need[n][m];
printf("The need matrix is\n"); 
for (i = 0; i < n; i++)
{
for (j = 0; j < m; j++)
{
need[i][j] = max[i][j] - alloc[i][j];
printf("%3d\t",need[i][j]);
printf("\t");
}
printf("\n");
} 
int y = 0;
for (k = 0; k < m; k++) 
{
for (i = 0; i < n; i++) 
{
if (f[i] == 0) {
  
int flag = 0;
for (j = 0; j < m; j++) {
if (need[i][j] > avail[j]){
 flag = 1;
 break;
 }
}
  
if (flag == 0)
   {
ans[ind++] = i;
for (y = 0; y < m; y++)
 avail[y] += alloc[i][y];
f[i] = 1;
}
}
}
}
  
printf("Following is the SAFE Sequence\n");
for (i = 0; i < n - 1; i++)
printf(" P%d ->", ans[i]);
printf(" P%d", ans[n - 1]);
}


output
bcs@linux-w1qw:~> ./a.out
Enter the no of processes : 5


Enter the no of resources : 4


Enter the Max Matrix for each process : 
For process 1 : 0
0
1
2

For process 2 : 1
7
5
0

For process 3 : 2
3
5
6

For process 4 : 0
6
5
2

For process 5 : 1
6
5
6


Enter the allocation for each process : 
For process 1 : 0
0
1
2

For process 2 : 1
1
0
0

For process 3 : 1
3
5
4

For process 4 : 0
6
3
2

For process 5 : 1
0
1
4


Enter the Available Resources : 1
4
2
0

 Max matrix:	Allocation matrix:
0  0  1  2  		0  0  1  2  
1  7  5  0  		1  1  0  0  
2  3  5  6  		1  3  5  4  
0  6  5  2  		0  6  3  2  
1  6  5  6  		1  0  1  4  

Process 1 runs to completion!
 Max matrix:	Allocation matrix:
0  0  0  0  		0  0  0  0  
1  7  5  0  		1  1  0  0  
2  3  5  6  		1  3  5  4  
0  6  5  2  		0  6  3  2  
1  6  5  6  		1  0  1  4  

Process 3 runs to completion!
 Max matrix:	Allocation matrix:
0  0  0  0  		0  0  0  0  
1  7  5  0  		1  1  0  0  
0  0  0  0  		0  0  0  0  
0  6  5  2  		0  6  3  2  
1  6  5  6  		1  0  1  4  

Process 2 runs to completion!
 Max matrix:	Allocation matrix:
0  0  0  0  		0  0  0  0  
0  0  0  0  		0  0  0  0  
0  0  0  0  		0  0  0  0  
0  6  5  2  		0  6  3  2  
1  6  5  6  		1  0  1  4  

Process 4 runs to completion!
 Max matrix:	Allocation matrix:
0  0  0  0  		0  0  0  0  
0  0  0  0  		0  0  0  0  
0  0  0  0  		0  0  0  0  
0  0  0  0  		0  0  0  0  
1  6  5  6  		1  0  1  4  

Process 5 runs to completion!
The system is in a safe state!!
Safe Sequence : < 1  3  2  4  5  >
bcs@linux-w1qw:~> clear
[3;J
bcs@linux-w1qw:~> cc b.c
bcs@linux-w1qw:~> ./a.out
Enter the total no.of processes and resources:
5
4
Enter Allocation matrix:
0
0
1
2
1
1
0
0
1
3
5
4
0
6
3
2
1
0
1
4
Enter Max matrix:
0
0
1
2
1
7
5
0
2
3
5
6
0
6
5
2
1
6
5
6
Enter Available matrix:
1
4
2
0
The need matrix is
  0		  0		  0		  0		
  0		  6		  5		  0		
  1		  0		  0		  2		
  0		  0		  2		  0		
  0		  6		  4		  2		
Following is the SAFE Sequence
 P0 -> P2 -> P3 -> P4 -> P1bcs@linux-w1qw:~> ^C
bcs@linux-w1qw:~> 

