#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node node;
typedef struct qnode qnode;
struct node{
    int val;
    node* P;
    node* L;
    node* R;
};
struct qnode{
    node* n;
    qnode* next;
};
node* root = NULL;
qnode* head = NULL;
qnode* tail = NULL;
node* find(int val){
    node* ans = root;
    while(ans){
        if(ans->val == val) return ans;
        if(ans->val > val) ans = ans->L;
        else ans = ans->R;
    }
    return NULL;
}
void insert(int val){
    node* new = malloc(sizeof(node));
    new->val = val;
    new->L = new->R = NULL;
    if(!root){
        root = new;
        root->P = NULL;
        return;
    }
    node* p = root;
    while(1){
        if(val < p->val){
            if(!(p->L)) break;
            p = p->L;
        }
        else{
            if((!p->R)) break;
            p = p->R;
        }
    }
    new->P = p;
    if(val < p->val) p->L = new;
    else p->R = new;
}
void delete(int val){
    node* target = find(val);
    if(!target){
        printf("value not found!!\n");
        return;
    }
    if(!target->L && !target->R){
        if(target->P){
            if(target->P->L == target) target->P->L = NULL;
            else (target->P)->R = NULL;
        }
        else root = NULL;
        free(target);
        return;
    }
    if(!target->L || !target->R){
        node* child = (node*)((unsigned long)target->L ^ (unsigned long)target->R);
        if(target->P){
            if(target->P->L == target) target->P->L = child;
            else target->P->R = child;
            child->P = target->P;
        }
        else {
            root = child;
            root->P = NULL;
        }
        free(target);
        return;
    }
    node* change = target->R;
    while(change->L) change = change->L;
    target->val = change->val;
    if(change->P == target) target->R = change->R;
    else change->P->L = change->R;
    free(change);
}
void push(node* n){
    qnode* new = malloc(sizeof(qnode));
    new->n = n;
    new->next = NULL;
    if(!tail){
        head = tail = new;
        return ;
    }
    tail->next = new;
    tail = new;
}
node* pop(){
    node* n = head->n;
    qnode* temp = head;
    head = head->next;
    if(!head) head = tail = NULL;
    free(temp);
    return n;
}
void printout(){
    if(!root) return;
    push(root);
    node* n;
    int temp = -1;
    while(head){
        n = pop();
        if(temp != -1) printf("%d\n", temp);
        temp = n->val;
        if(n->L) push(n->L);
        if(n->R) push(n->R);
    }
    if(temp != -1)
        printf("%d", temp);
}
int main(){
    char str[100000] = {};
    char num[100000] = {};
    char ch[10] = "0";
    scanf("%[^\n]", str);
    for(int i = 0; str[i] != '\0'; ++i){
        if(str[i] == ' '){
            insert(atoi(num));
            strcpy(num, "");
            continue;
        }
        ch[0] = str[i];
        strcat(num, ch);
    }
    if(atoi(num)) insert(atoi(num));
    getchar();
    strcpy(str, "");
    strcpy(num, "");
    int k;
    while(scanf("%d", &k) != EOF)
        delete(k);
    printout();
    return 0;
}