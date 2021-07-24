#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char file[100][80],fn[80];
struct PROG
{
	char label[20],inst[20],opnd[40],opnd1[40],opnd2[40];
}sc[200];
char filename[14];
char OPTAB[12][6]={"STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"};
char REGTAB[5][5]={"AREG","BREG","CREG","DREG"};
char CCTAB[6][4]={"LT","LE","EQ","GT","GE","ANY"};
long OBJECT[300];
struct SYMTAB
{
	char symbol[20];
	int addr;
	char value[40];
}st[50];

struct LITTAB
{
	int lit,addr;
}lt[50];
int POOLTAB[1000];
struct IC
{
	char instrtype;
	int opcode;
	int op1;
	char optype;
	int code;
	char opnd2[40];
}ic[200];
int stp=0,ltp=0,ptp=0,scp=0,otp=0,rtp=0,ctp=0,lc=0,icp=0;

int readfile(char name[20])
{
	FILE *fp;
	char t1[40],t2[40],t3[40],line[80];
	int t,l,j,i=0,k;
	fp=fopen(name,"r");
	if(fp==NULL)
	{
		printf("Error in opening file!!");
		return 0;
	}
	while(!feof(fp))
	{
		fgets(file[i],80,fp);
		if(feof(fp)==1)break;
		t=sscanf(file[i],"%s%s%s",t1,t2,t3);
		switch(t)
		{
			case 1:strcpy(sc[i].label," ");
			strcpy(sc[i].inst,t1);
			strcpy(sc[i].opnd," ");
			strcpy(sc[i].opnd1," ");
			break;
			case 2:strcpy(sc[i].label," ");
			strcpy(sc[i].inst,t1);
			strcpy(sc[i].opnd,t2);
			for(j=0;t2[j]!=',';j++)
			{
				sc[i].opnd1[j]=t2[j];
				if(t2[j]=='\0')break;
		    }sc[i].opnd1[j]='\0';
		    if(t2[j]==',')
		    {
					for(k=0,j++;t2[j]!='\0';k++,j++)
					sc[i].opnd2[k]=t2[j];
					sc[i].opnd2[k]='\0';
			}else
				strcpy(sc[i].opnd2," ");
				break;
				case 3:strcpy(sc[i].label,t1);
				strcpy(sc[i].inst,t2);
				strcpy(sc[i].opnd,t3);
				for(j=0;t3[j]!=',';j++)
				{
					sc[i].opnd1[j]=t3[j];
					if(t3[j]=='\0') break;
				}
				sc[i].opnd1[j]='\0';
				if(t3[j]==',')
				{
					for(k=0,j++;t3[j]!='\0';k++,j++)
					sc[i].opnd2[k]=t3[j];
					sc[i].opnd2[k]='\0';
				}
				else
				strcpy(sc[i].opnd2," ");
				break;
			}
			i++;
		}
		fclose(fp);
		l=i-1;
		return i-1;
	}
	
	print(int l)
	{
		int i;
		printf("\n\n\n Register Table\n\n\n");
		printf("Register\t code");
		for(i=0;i<4;i++)
		printf("\n%s\t\t%d",REGTAB[i],i+1);
		printf("\n\n\nConditional code table\n\n\n");
		printf("\nCondition \t Code");
		for(i=0;i<6;i++)
		printf("\n%s\t\t%d",CCTAB[i],i+1);
		printf("\n\n\nOPCODE Table\n\n\n");
		printf("\nInstruction \t TYPE\t Code");
		for(i=0;i<18;i++)
		{
			if(i<=10)
			printf("\n%s\t\tIS\t%d",OPTAB[i],i);
			else
			if(i<=12)
			printf("\n%s\t\tDL\t%d",OPTAB[i],i-10);
			else
			printf("\n%s\t\tDL\t%d",OPTAB[i],i-12);
		}
		printf("\n\n\n Source File\n\n\n");
		for(i=0;i<=l;i++)
		printf("\n%s\t%s\t%s,%s",sc[i].label,sc[i].inst,sc[i].opnd1,sc[i].opnd2);
	}
	
	pass1(int l)
	{
		int i,j;
		char str[40];
		stp=0;
		ltp=0;
		ptp=0;
		scp=0;
		lc=0;
		icp=0;
		POOLTAB[ptp]=0;
		for(scp=0;scp<=l;scp++)
		{
			if(strcmp(sc[scp].label," ")!=0)
			{
				strcpy(st[stp].symbol,sc[scp].label);
				st[stp].addr=lc;
				stp++;
			}
			if(strcmp(sc[scp].inst,"LTORG")==0)
			{
				for(i=POOLTAB[ptp];i<ltp;i++)
				{
					lt[i].addr=lc;
					lc++;
				}
			ptp++;
			POOLTAB[ptp]=ltp;
			ic[icp].instrtype='A';
			ic[icp].opcode=5;
			ic[icp].op1=0;
			ic[icp].optype=' ';
			ic[icp].code=0;
			strcpy(ic[icp].opnd2,sc[scp].opnd2);
			icp++;
			continue;
			}
			if((strcmp(sc[scp].inst,"START")==0)||(strcmp(sc[scp].inst,"ORG")==0))
			{
				lc=atoi(sc[scp].opnd1);
				ic[icp].instrtype='A';
				ic[icp].opcode=1;
				ic[icp].op1=0;
				ic[icp].optype='C';
				ic[icp].code=atoi(sc[scp].opnd1);
				icp++;
				strcpy(ic[icp].opnd2,sc[scp].opnd2);
				continue;
			}
			if(strcmp(sc[scp].inst,"EQU")==0)
			{
				strcpy(st[stp-1].value,sc[scp].opnd1);
				ic[icp].instrtype='A';
				ic[icp].opcode=4;
				ic[icp].op1=0;
				ic[icp].optype='C';
				ic[icp].code=-1;
				strcpy(ic[icp].opnd2,sc[scp].opnd2);
				icp++;
				continue;
			}
			if(strcmp(sc[scp].inst,"END")==0)
			{
				for(i=POOLTAB[ptp];i<ltp;i++)
				{
					lt[i].addr=lc;
					lc++;
				}
				ptp++;
				POOLTAB[ptp]=ltp;
				ic[icp].instrtype='A';
				ic[icp].opcode=2;
				ic[icp].op1=0;
				ic[icp].optype=' ';
				ic[icp].code=0;
				strcpy(ic[icp].opnd2,sc[scp].opnd2);
				icp++;
				break;
			}
			if((strcmp(sc[scp].inst,"DS")==0)||(strcmp(sc[scp].inst,"DC")==0))
			{
				strcpy(st[stp-1].value,sc[scp].opnd1);
			}
			else
			{
			 ic[icp].opcode=2;
			 lc++;	
			}
			ic[icp].op1=0;
			ic[icp].optype='C';
			ic[icp].code=atoi(sc[scp].opnd1);
			strcpy(ic[icp].opnd2,sc[scp].opnd2);
			icp++;
			continue;
		}
		ic[icp].instrtype='I';
		strcpy(ic[icp].opnd2,sc[scp].opnd2);
		i=0;
		for(otp=0;otp<11;otp++)
		{
			if(strcmp(OPTAB[otp],sc[scp].inst)==0)
			{
				ic[icp].opcode=otp;
				i=1;
				break;
			}
		}
			if(i==0)
			printf("\nError\n");
			switch(ic[icp].opcode)
			{
			case 0:ic[icp].op1=0;
			ic[icp].optype=' ';
			ic[icp].code=0;
			break;
			
			case 7:i=0;
			for(ctp=0;ctp<6;ctp++)
			{
			 if(strcmp(CCTAB[ctp],sc[scp].opnd1)==0)
			 {
			 	ic[icp].op1=ctp+1;
			 	i=1;
			 	break;
			 }
			}
			if(i==0)
			printf("\n Error \n");
			break;
			default:i=0;
			for(rtp=0;rtp<4;rtp++)
			{
				if(strcmp(REGTAB[rtp],sc[scp].opnd1)==0)
				{
					ic[icp].op1=rtp+1;
					i=1;
					break;
				}
			}
			if(i==0)
			printf("\nError\n");
			}
			if(ic[icp].opcode==0)//continue;
			{
				lc++;
				icp++;
			//	continue;
			}//continue;
			if(sc[scp].opnd2[0]=='=')
			{
				ic[icp].optype='L';
				ic[icp].code=ltp;
				for(i=1;sc[scp].opnd2[i]!='\0';i++)
				str[i-1]=sc[scp].opnd2[i];
				str[i-1]='\0';
				lt[ltp].lit=atoi(str);
				ltp;
			}
			else
			{
				ic[icp].optype='S';
				i=0;
				for(j=0;j<stp;j++)
				{
					if(strcmp(st[j].symbol,sc[scp].opnd2)==0)
					{
						ic[icp].code=j;
						i=1;
						break;
					}
				}
				if(i==0)
				ic[icp].code=-1;
			}
			icp++;
			lc++;
    for(icp=0;icp<=l;icp++)
	{
		if(ic[icp].optype=='S')
		{
			if(ic[icp].code==-1)
			{
				for(j=0;j<stp;j++)
				{
					if(strcmp(st[j].symbol,ic[icp].opnd2)==0)
					{
						ic[icp].code=j;
						break;
					}
				}
			}
		}
	}
}
save()
{
	FILE *fp;
	int i;
	fp=fopen("ass.obj","w");
	for(i=0;i<1000;i++)
	{
		fprintf(fp,"\n%d\t\t\t%ld",i,OBJECT[i]);
	}
	fclose(fp);
}

print2()
{
	int i;
	printf("\n\n\nPOOL Table \n\n");
	for(i=0;i<ptp;i++)
	printf("\n%d",POOLTAB[i]);
	printf("\n\n\nLiteral Table\n\n");
	for(i=0;i<ltp;i++)
	printf("\n%d\t%d",lt[i].lit,lt[i].addr);
	printf("\n\n\nSymbol Table\n\n");
	for(i=0;i<stp;i++)
	printf("\n%s\t%d\t%s",st[i].symbol,st[i].addr,st[i].value);
	printf("\n\n\nIntermediate code\n\n");
	for(i=0;i<icp;i++)
	printf("\n(%c,%d)\t%d\t(%c,%d),\t%s",ic[i].instrtype,ic[i].opcode,ic[i].op1,ic[i].optype,ic[i].code,ic[i].opnd2);
}

pass2()
{
	int i,j=0,k,flag=0,p=0;
	for(i=0;i<icp;i++)
	{
		switch(ic[i].instrtype)
		{
			case 'I':
				switch(ic[i].optype)
				{
					case 'L':OBJECT[j]=ic[icp].opcode*10000+ic[i].op1*1000+lt[ic[i].code].addr;
					break;
					case 'S':OBJECT[j]=ic[i].opcode*10000+ic[i].op1*100+st[ic[i].code].addr;
					break;
				}
				j++;
				break;
			case 'D':
				switch(ic[i].opcode)
				{
					case 1:for(k=0;k<ic[i].code;k++)
					{
						OBJECT[j]=0;
						j++;
					}break;
					case 2:OBJECT[j]=ic[i].code;
					j++;
					printf("\n%d\t\t%ld",j-1,OBJECT[j-1]);
				}break;
			case 'A':
				switch(ic[i].opcode)
				{
					case 1:
					case 3:OBJECT[j]=76*1000+ic[i].code;
					j=ic[i].code;
					case 2:for(k=POOLTAB[p];k<ltp;k++)
		                    {
		                    	OBJECT[j]=lt[k].lit;
		                    	j++;
							}
							flag=1;
							break;
							case 4:break;
							case 5:for(k=POOLTAB[p];k<POOLTAB[p+1];k++)
							       {
							       	OBJECT[j]=lt[k].lit;
							       	j++;
								   }
								   p++;
				}
		}
		if(flag==1)break;
	}
}

int main()
{
	int i;
	char name[20];
	printf("Enter the file name:  ");
	scanf("%s",name);
	i=readfile(name);
	if(i==0)
	return 0;
	print(i);
	pass1(i);
	print2();
	pass2();
	save();	
}
