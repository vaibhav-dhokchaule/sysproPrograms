#include<stdio.h>
//#include<conio.h>
//#include<process.h>
void main()
{
	long mem[1000],instr;
	int lc=1,i,j,reg[5],cc[7],opd1,opd2,opc;
	char fname[13],buff[80];
	FILE *fp;
	//clrscr();
system("clear");
	printf("enter the file name ");
	gets(fname);
	fp=fopen(fname,"r");
	if(fp==NULL)
	{printf("\nfile not found\n");
	 //exit(0);
	}
	i=0;
	while(!feof(fp))
	{
		fscanf(fp,"%ld",&mem[++i]);
		fgets(buff,80,fp);
	}
	lc=0;
	while(lc<=i)
	{
		instr=mem[lc];
		opc=instr/10000;
		opd1=(instr%10000)/1000;
		opd2=instr%1000;
		lc++;
		switch(opc)
		{
		case 1:reg[opd1]+=mem[opd2];
			break;
		case 2:reg[opd1]-=mem[opd2];
			break;
		case 3:reg[opd1]*=mem[opd2];
			break;
		case 4:reg[opd1]=mem[opd2];
			break;
		case 5:mem[opd2]=reg[opd1];
			break;
		case 6: for(j=1;j<7;j++)
			cc[j]=0;
		       if(reg[opd1]<mem[opd2])
			cc[1]=cc[2]=1;
		       else
		       if(reg[opd1]==mem[opd2])
			cc[2]=cc[3]=cc[5]=1;
		       else
		       if(reg[opd1]>mem[opd2])
			cc[4]=cc[5]=1;
		       cc[6]=1;
		       break;
		case 7:if(cc[opd1]==1)
			lc=opd2;
			break;
		case 8:reg[opd1]/=mem[opd2];
			break;
		case 9:printf("\nEnter the Input:");
		       scanf("%ld",&mem[opd2]);
		       break;
		case 10:printf("\nThe output is:%ld",mem[opd2]);
			 break;
	       }
	}
	//getch();
	}
