
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

char *buff, *t1, *t2, *t3, ch;
FILE *fp;
int pid;

void count(char *t2, char *t3)
{
	int charcount=0, wordcount=0, linecount=0;
	if((fp=fopen(t3,"r"))==NULL)
	{
		printf("File Not Found!!");
		exit(0);
	}
	while((ch=fgetc(fp))!=EOF)
	{
		if(ch==' ')
			wordcount++;
		else if(ch=='\n')
		{
			linecount++;
			wordcount++;
		}
		else
			charcount++;
	}
	fclose(fp);
	if(strcmp(t2,"c")==0)
		printf("Total no of characters = %d \n",charcount);
	else if(strcmp(t2,"w")==0)
		printf("Total no of words = %d \n",wordcount);
	else if(strcmp(t2,"l")==0)
		printf("Total no of lines = %d \n",linecount);
	else
		printf("%s: Command not found!! \n",t2);
	
}

main()
{
	while(1)
	{
		printf("[MyShell]$ ");
		fflush(stdin);
		t1 = (char *)malloc(80);
		t2 = (char *)malloc(80);
		t3 = (char *)malloc(80);
	      buff = (char *)malloc(80);
		
		fgets(buff,80,stdin);
		sscanf(buff,"%s %s %s",t1,t2,t3);
	
		if(strcmp(t1,"pause")==0)
			exit(0);
		else if(strcmp(t1,"count")==0)
			count(t2,t3);
		else
		{
			pid = fork();
			if(pid<0)
				printf("Child Process is not created\n");
			else if(pid==0)
			{
				execlp("/bin",NULL);
				if(strcmp(t1,"exit")==0)
					exit(0);
				system(buff);
			}
			else
			{
				wait(NULL);
				exit(0);
			}
		}
	}
}		
/*	OUTPUT:
[MyShell]$ ls
abc.txt  a.out  count.c  proc.c

[MyShell]$ ls /usr
bin  etc  games  include  java  kerberos  lib  libexec  local  sbin  share  src  tmp  X11R6

[MyShell]$ pwd
/root/ty175

[MyShell]$ count c abc.txt
Total no of characters = 239 

[MyShell]$ count w abc.txt
Total no of words = 48 

[MyShell]$ count l abc.txt
Total no of lines = 7 

[MyShell]$ pause

[MyShell]$ count m abc.txt
m: Command not found!! 

[MyShell]$ date
Fri Dec  7 11:40:56 IST 2012

[MyShell]$ exit  	*/
		












