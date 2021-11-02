#include <stdio.h>
#include <stdlib.h>
char target[] = "KQJ198765432A";
typedef struct node node;
struct node{
    char ch;
    node* next;
};
node* front = NULL;
node* back = NULL;
void push(char ch){
    node* temp = malloc(sizeof(node));
    temp->ch = ch;
    temp->next = NULL;
    if(!back){
        front = back = temp;
        return;
    }
    back->next = temp;
    back = temp;
}
char pop(){
    if(!front) exit(1);
    char ch = front->ch;
    node* temp = front;
    front = front->next;
    if(!front) back = NULL;
    free(temp);
    return ch;
}
void printout(){
    node* p = front;
    while(p){
        if(p->ch == '1') printf("10 ");
        else printf("%c ", p->ch);
        p = p->next;
    }
    printf("\n");
}
int main(){
    char str[10];
    for(int i = 0; i < 13; ++i){
        scanf("%s",str);
        push(str[0]);
    }
    int p = 0;
    while(p < 13){
        printout();
        char ch = pop();
        if(ch != target[p])
            push(ch);
        else ++p;
    }
    return 0 ;
}