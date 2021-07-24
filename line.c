#include<stdlib.h>
	#include<stdio.h>
#include<string.h>
	 
void main(int argc,char **argv)
	{

	if(strcmp("-c",argv[2])==0)            //create file
	{
	FILE *fp=fopen(argv[1],"a");
	if(fp!=NULL)
	printf("\nFile Created Successfully");
else
	printf("ERROR");
	}
 
if(strcmp("-del",argv[2])==0)         //delete file
020	{
021	int r = remove(argv[1]);
022	if(r==0)
023	printf("\nFile removed successfully");
024	else
025	printf("\nERROR in remove");
026	}
027	 
028	if(strcmp("-d",argv[2])==0)                        //delete a line
029	{
030	int no=-atoi(argv[3]);char line[80];
031	int i=1;
032	FILE *fp=fopen(argv[1],"r");
033	FILE *ft=fopen("temp.txt","w");
034	for(;i<no;i++)
035	{
036	fgets(line,80,fp);
037	fputs(line,ft);
038	}
039	fgets(line,80,fp);
040	while(!feof(fp))
041	{
042	fgets(line,80,fp);
043	fputs(line,ft);
044	}
045	remove(argv[1]);
046	rename("temp.txt",argv[1]);
047	}
048	 
049	if(strcmp("-p",argv[2])==0)       // print all
050	 {
051	 
052	 
053	    if(strcmp("-all",argv[3])==0)
054	      {
055	       FILE *fp=fopen(argv[1],"r");int ch=0;
056	       while(ch!=EOF)
057	        {
058	         ch = getc(fp);
059	         putchar(ch);
060	 
061	      }
062	       }
063	    else                        // print n specfic line
064	    {
065	     FILE *fp=fopen(argv[1],"r");
066	     int i=0;
067	     int n= -atoi(argv[3]);
068	    // printf("%d",n);
069	     for(int count=0;count<n-1;)
070	     {
071	     i=getc(fp);
072	     if(i=='\n')
073	     count++;
074	     }
075	     i=getc(fp);
076	     while(i!='\n')
077	     {
078	putchar(i);
079	i=getc(fp);
080	       }
081	       }
082	}
083	 
084	if(strcmp("-u",argv[2])==0)    //update a file pointer
085	{
086	FILE *fp,*ft;
087	int ch;char line[80];
088	 
089	int a= -atoi(argv[3]);
090	int b= -atoi(argv[4]);
091	int c= -atoi(argv[5]);
092	 
093	fp = fopen("temp.txt","w");
094	ft = fopen(argv[1],"r");
095	 
096	int count = 1;
097	 
098	while(count<a)
099	    {
100	     fgets(line,80,ft);
101	     fputs(line,fp);
102	     count++;
103	     }
104	     count =1;
105	 
106	     while(count<b)
107	     {
108	     ch= getc(ft);
109	     putc(ch,fp);
110	     count++;
111	     }
112	     int l=strlen(argv[6]);
113	     fprintf(fp,"%s",argv[6]);
114	     int k=c-l;
115	     while(k>0)
116	     {
117	     putc(' ',fp);
118	     k--;
119	     }
120	     fseek(ft,c-b,SEEK_CUR);
121	     char ch1=getc(ft);
122	     while(ch1!=EOF)
123	     {
124	     ch1=getc(ft);
125	     putc(ch1,fp);
126	     }
127	     remove(argv[1]);
128	 
129	       rename("temp.txt",argv[1]);
130	fclose(fp);
131	     }
132	 
133	if(strcmp("-i",argv[2])==0)    //insert in file
134	{
135	FILE *fp,*ft;
136	int ch;char line[80];
137	 
138	int a= -atoi(argv[3]);
139	int b= -atoi(argv[4]);
140	 
141	fp = fopen("temp.txt","w");
142	ft = fopen(argv[1],"r");
143	 
144	int count = 1;
145	 
146	while(count<a)
147	    {
148	     fgets(line,80,ft);
149	     fputs(line,fp);
150	     count++;
151	     }
152	     count =1;
153	 
154	     while(count<b)
155	     {
156	     ch= getc(ft);
157	     putc(ch,fp);
158	     count++;
159	     }
160	 
161	     fprintf(fp,"%s",argv[5]);
162	 
163	     while(!feof(ft))
164	     {
165	     fgets(line,80,ft);
166	     fputs(line,fp);
167	     }
168	 
169	       remove(argv[1]);
170	 
171	       rename("temp.txt",argv[1]);
172	fclose(fp);
173	}
174	 
175	if(strcmp("-a",argv[2])==0)
176	{
strcmp("-e",argv[3])==0)     //append at end
	{
	FILE *fp=fopen(argv[1],"a");
	printf("%s",argv[4]);
	fprintf(fp,"%s",argv[4]);
	fclose(fp);

}	if(strcmp("-b",argv[3])==0)     // append at beginning
	{
	FILE *fp,*ft;int ch=0;
	fp=fopen(argv[1],"r");
	ft=fopen("temp.txt","w");
	fprintf(ft,"%s",argv[4]);
	while(ch!=EOF)
	{
	ch=getc(fp);
putc(ch,ft);
	}
	remove(argv[1]);
	rename("temp.txt",argv[1]);
	}
	}

	}
