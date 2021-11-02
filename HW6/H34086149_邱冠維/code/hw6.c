#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max(a,b) (a > b ? a : b)
#define geth(a) (a ? a->h : 0) //取節點高度
#define getb(a) (a ? geth(a->L) - geth(a->R) : 0) //取節點的平衡因子
typedef struct node node;
struct node{
    char key[10000];
    char val[10000];
    node* L;
    node* R;
    int h;
};
node* Lrotate(node* root){
    node *pivot = root->R;
    root->R = pivot->L;
    pivot->L = root;
    root->h = max(geth(root->L), geth(root->R)) + 1;
    pivot->h = max(geth(pivot->L), geth(pivot->R)) + 1;
    return pivot;
}
node* Rrotate(node* root){
    node *pivot = root->L;
    root->L = pivot->R;
    pivot->R = root;
    root->h = max(geth(root->L), geth(root->R)) + 1;
    pivot->h = max(geth(pivot->L), geth(pivot->R)) + 1;
    return pivot;
}
node* insert(node *N, char key[10000], char val[10000]){
    if(!N){
        N = (node*)malloc(sizeof(node));
        strcpy(N->key, key);
        strcpy(N->val, val);
        N->L = N->R = NULL;
        N->h = 1;
        return N;
    }
    if(strcmp(key, N->key) < 0)
        N->L = insert(N->L, key, val);
    else N->R = insert(N->R, key, val);
    N->h = 1 + max(geth(N->L), geth(N->R));
    int balance = getb(N);
    if(balance > 1){
        if(strcmp(key, N->L->key) < 0)    // LL
            return Rrotate(N);
        else{ //LR
            N->L = Lrotate(N->L);
            return Rrotate(N);           
        }
    }
    else if(balance < -1){
        if(strcmp(key, N->R->key) > 0)    // RR
            return Lrotate(N);
        else{ //RL
            N->R = Rrotate(N->R);
            return Lrotate(N);           
        }
    }
    return N;
}
node* find(node* N, char key[10000]){
    int cmp;
    while(N && (cmp = strcmp(key, N->key)))
        N = cmp < 0 ? N->L : N->R;
    return N;
}
void preorder(node* N, int flag){
    if(!N) return;
    flag ? printf(" %s", N->key) : printf("%s", N->key);
    preorder(N->L, 1);
    preorder(N->R, 1);
}
int main(){
    node* root = NULL;
    char key[10000];
    char val[10000];
    scanf("%s", key);
    while(scanf("%s", key) && strcmp(key, "S")){
        scanf("%s", val);
        root = insert(root, key, val);
    }
    preorder(root, 0);
    while(scanf("%s", key) && strcmp(key, "E")){
        node* N = find(root, key);
        if(N) printf("\n%s %s", key, N->val);
        else printf("\n%s null", key);
    }
    return 0;
}