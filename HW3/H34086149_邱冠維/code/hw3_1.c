#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
	int val;
	struct node *next;
}node;

node* qf[2] = {NULL, NULL};
node* qe[2] = {NULL, NULL};
node* st = NULL;

void push(const int n){
	node* p = malloc(sizeof(node));
	if(!p) exit(1);
	p->val = n;
	p->next = st;
	st = p;
}
int pop(){
	if(!st) exit(1);
	int top = st->val;
	node* temp = st;
	st = st->next;
	free(temp);
	return top;
}
void enqueue(char ch, const int n){
	int key = ch - 'A';
	node* temp = malloc(sizeof(node));
	if(!temp) exit(1);
	temp->val = n;
	temp->next = NULL;
	if(!qe[key]) qf[key] = qe[key] = temp;
	else{
		qe[key]->next = temp;
		qe[key] = temp;
	}
}
void dequeue(char ch){
	int key = ch - 'A';
	if(!qf[key]) exit(1);
	printf("%d\n", qf[key]->val);
	node* temp = qf[key];
	qf[key] = qf[key]->next;
	if(!qf[key]) qf[key] = qe[key] = NULL;
	free(temp);
}

int main(){
	char cmd[1000];
	int x;
	int top;
	while(scanf("%s",cmd) != EOF){
		if(!strcmp(cmd,"PUSH")){
			scanf("%d", &x);
			push(x);
		}
		else if(!strcmp(cmd,"POP")){
			top = pop();
		}
		else if(!strcmp(cmd,"ENQUEUE")){
			scanf("%s", cmd);
			enqueue(cmd[0], top);
		}
		else if(!strcmp(cmd,"DEQUEUE")){
			scanf("%s", cmd);
			dequeue(cmd[0]);
		}
	}
	return 0;
}
