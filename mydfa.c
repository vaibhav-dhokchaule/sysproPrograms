#include <stdio.h> 
#define STATES 2
#define FINAL_STATES 1
#define ALPHABET 2
#define UNKNOWN_SYMBOL_ERR 0
#define NOT_REACHED_FINAL_STATE 1
#define REACHED_FINAL_STATE 2
enum DFA_STATES{q0,q1};
enum input{a,b};
int Accepted_states[FINAL_STATES]={q1};
char alphabet[ALPHABET]={'a','b'};
int Table[STATES][ALPHABET];
int Current_state=q0;

void DefineDFA()
{
    Table[q0][a] = q1;
    Table[q0][b] = q0;
    Table[q1][a] = q1;
    Table[q1][b] = q0;
}

int DFA(char current_symbol)
{
int i,pos;
    for(pos=0;pos<ALPHABET; pos++)
        if(current_symbol==alphabet[pos])   
            break;
    if(pos==ALPHABET)
         return UNKNOWN_SYMBOL_ERR;
    for(i=0;i<FINAL_STATES;i++)
 if((Current_state=Table[Current_state][pos])==Accepted_states[i])
            return REACHED_FINAL_STATE;
    return NOT_REACHED_FINAL_STATE;
}


void main(void)
{
    char current_symbol;
    int result;
    DefineDFA();   
    printf("Enter a string with 'a' s and 'b's:\n Press Enter Key to stop\n");
    while((current_symbol=getchar())!= '\n')
        if((result= DFA(current_symbol))==UNKNOWN_SYMBOL_ERR)
            break;
    switch (result) {
    case UNKNOWN_SYMBOL_ERR:printf("Unknown Symbol %c",
  current_symbol); 
 break;
    case NOT_REACHED_FINAL_STATE:printf("Not accepted"); break;
    case REACHED_FINAL_STATE:printf("Accepted");break;
    default: printf("Unknown Error");
    }
}
