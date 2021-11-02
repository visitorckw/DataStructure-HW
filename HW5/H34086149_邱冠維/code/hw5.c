#include <stdio.h>
#include <memory.h>
#define TABLE_SIZE 13
#define PRIME 7

int table[TABLE_SIZE];
int hash1(int key){
    return key % TABLE_SIZE;
}
int hash2(int key){
    return PRIME - (key % PRIME);
}
int hash(int key){
    int ans;
    for(int i = 0; table [ ans = ( hash1(key) + i * hash2(key) ) % TABLE_SIZE ] != -1; ++i);
    table[ans] = key;
}
int main(){
    memset(table,-1,sizeof(table));
    int key;
    for(int i = 0; i < TABLE_SIZE; ++i){
        scanf("%d", &key);
        hash(key);
    }
    for(int i = 0; i < TABLE_SIZE - 1; ++i)
        printf("%d->%d\n", i, table[i]);
    printf("%d->%d",TABLE_SIZE - 1, table[TABLE_SIZE - 1]);
    
    return 0;
}