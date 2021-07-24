#include<stdio.h>
#include<stdlib.h>
#define newnode (struct node*)malloc(sizeof(struct node))
struct node
{
struct node *next;
char line[100];
}*f;

struct node *create(int n)
{
struct node *f,*s;
int i;
f=newnode;
printf("\n Enter the first node:");
scanf("%s",f->line);
s=f;
for(i=2;i<=n;i++)
{
s->next=newnode;
s=s->next;
printf("\n  Enter data for %d node:",i);
scanf("%s",s->line);
}
s->next=NULL;
return(f);
}

void display(struct node *f)
{
struct node *t;
int i=1;
for(t=f;t!=NULL;t=t->next)
printf("%d: %s\n",i++,t->line);
}

int save (struct node *f,char *fn)
{
FILE *fp;
struct node *t;
t=f;
fp=fopen(fn,"w");
while(t!=NULL)
{
fputs(t->line,fp);
t=t->next;
}
fclose(fp);
return(0);
}

struct node *append(struct node *f)
{
int i;
struct node *s,*t;
s=newnode;
s->next=NULL;
printf("\n Enter data for new node: ");
scanf("%s",s->line);
if(f==NULL)
{
f=s;
}
else
{
for(t=f,i=0;t->next!=NULL;i++)
{
t=t->next;
}
s->next=t->next;
t->next=s;
}
return(f);
}


struct node *insert(struct node *f)
{
struct node *p=NULL,*temp=NULL;
int i,pos;
printf("\n Enter the posion:");
scanf("%d",&pos);
for(temp=f,i=1;i<pos&&temp!=NULL;i++)
{
temp=temp->next;
}
if(temp!=NULL)
{
p=newnode;
printf("Enter the value\n");
scanf("%s",p->line);
p->next=NULL;
p->next=temp->next;
temp->next=p;
}
else
{
printf("position out of order\n");
}
return(f);
}

struct node *delete(struct node *f)
{
struct node *temp=NULL,*p=NULL;
int i,pd;
printf("Enter the position of element is to be delete\n");
scanf("%d",&pd);
for(temp=f,i=1;(i<pd-1)&&temp->next!=NULL;i++)
{
temp=temp->next;
}
if(temp->next!=NULL)
{
p=temp->next;
temp->next=p->next;
printf("The deleted line is %s\n",p->line);
free(p);
}
else
{
printf("position out of order\n");
}
return(f);
}

struct node *move(struct node *f)
{
struct node *temp=NULL,*p=NULL;
int i,pos,pos1;
printf("Enter the line no to be moved:\n");
scanf("%d",&pos);
for(temp=f,i=1;(i<pos-1)&&temp->next!=NULL;i++)
{
temp=temp->next;
}
if(temp->next!=NULL)
{
p=temp->next;
temp->next=p->next;
printf("The moving line is %s\n",p->line);
}
else
{
printf("position out of order\n");
}
printf("Enter the position where to move:\n");
scanf("%d",&pos1);
for(temp=f,i=1;(i<pos1-1)&&temp!=NULL;i++)
{
temp=temp->next;
}
if(temp!=NULL)
{
p->next=temp->next;
temp->next=p;
}
else
{
printf("position out of order\n");
}
return(f);
}

int main()
{
int a,i=0,q=0;
char b,d[10];
struct node *f=NULL;
struct node *create();
struct node *insert();
struct node *delete();
struct node *move();
void display();
int save();
printf("c=create\ni=insert\ns=save\na=append\nm=move\nd=delete\ne=Exit");
do
{ 
printf("Enter your choice:\n");
scanf("%c",&b);
switch(b)
{
case 'c':
case 'C':printf("Enter how many lines\n ");
         scanf("%d",&a);
         f=create(a);
         display(f);
         break;
case 'i':
case 'I':f=insert(f);
         display(f);
         break;
case 's':
case 'S':printf("Enter the file name");
         scanf("%s",d);
         i=save(f,d);
         if(i==1)
         {
         printf("File saving Error\n");
         }
         else
         {
         printf("File saved succesfully");
         }
         break;
case 'a':
case 'A':f=append(f);
         display(f);
         break;
case 'm':
case 'M':f=move(f);
         display(f);
         break;
case 'd':
case 'D':f=delete(f);
         display(f);
         break;
case 'e':
case 'E':q=1;
         break;
}
}while(q==0);

}
