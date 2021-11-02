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
int flag = 0;
char target[20000];
FILE* output;

void push(const int n){
	// printf("PUSH %d\n", n);
	node* p = malloc(sizeof(node));
	p->val = n;
	p->next = st;
	st = p;
}
int pop(){
	// printf("POP\n");
	if(!st){
		printf("Stack is empty!\n");
		exit(1);
	}
	int top = st->val;
	node* temp = st;
	st = st->next;
	free(temp);
	return top;
}
void enqueue(char str[], const int n){
	// printf("ENQUEUE %s %d\n", str, n);
	if(!flag) {
		strcpy(target, str);
		// printf("%s\n%s", target, str);
		flag = 1;
	}
	int key = (strcmp(str, target) ? 1 : 0);
	// printf("key of %s = %d\n", str, key);
	node* temp = malloc(sizeof(node));
	temp->val = n;
	temp->next = NULL;
	if(!qe[key]){
		qf[key] = qe[key] = temp;
	}
	else{
		qe[key]->next = temp;
		qe[key] = temp;
	}
}
void dequeue(char str[]){
	// printf("DEQUEUE %s\n", str);
	int key = (strcmp(str, target) ? 1 : 0);
	// printf("key of %s = %d\n", str, key);
	if(!qf[key]){
		printf("Queue is empty!\n");
		exit(1);
	}
	printf("%d\n", qf[key]->val);
	node* temp = qf[key];
	qf[key] = qf[key]->next;
	if(!qf[key]) qf[key] = qe[key] = NULL;
	free(temp);
}

int main(){
	
	// FILE *fp;
	// fp = fopen("input.txt","r");
	// output = fopen("output.txt","w");
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
			enqueue(cmd, top);
		}
		else if(!strcmp(cmd,"DEQUEUE")){
			scanf("%s", cmd);
			dequeue(cmd);
		}
	}
	/*char str[10] = "PUSH";
	if(!strcmp(str,"PUSH"))
		printf("AC");
	else
		printf("WA");*/
	return 0;
}
