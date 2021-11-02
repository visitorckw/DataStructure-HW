#include <stdio.h>
#include <limits.h>
#include <memory.h>
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))
#define push(val) (st[stP++] = val)
#define pop() (st[--stP])
int N;
typedef struct E E;
struct E{
    int a, i , j, w;
};
E edge[105];
int matrix[105][105];

int ctr[105];
int early[105];
int late[105];
int vertex = 0;

int st[105];
int stP = 0;

int main(){
    for(int i = 0 ; i < 105; ++i)
        for(int j = 0; j < 105; ++j)
            matrix[i][j] = -1;
    scanf("%d", &N);
    for(int i = 0; i < N; ++i){
        scanf("%d%d%d%d", &edge[i].a, &edge[i].i, &edge[i].j, &edge[i].w);
        matrix[edge[i].i][edge[i].j] = edge[i].w;
        vertex = max(vertex, edge[i].i);
        vertex = max(vertex, edge[i].j);
    }

    for(int i = 0 ; i < N; ++i)
        ctr[edge[i].j]++;
    push(0);
    while(stP){
        int v = pop();
        for(int i = 0; i < 105; ++i){
            if(matrix[v][i] != -1){
                ctr[i]--;
                early[i] = max(early[i], early[v] + matrix[v][i]);
                if(!ctr[i]) push(i);
            }
        }
    }
    for(int i = 0; i < 105; ++i) ctr[i] = 0;
    stP = 0;
    for(int i = 0 ; i < N; ++i)
        ctr[edge[i].i]++;
    for(int i = 0; i < 105; ++i)
        late[i] = INT_MAX;
    late[vertex] = early[vertex];
    push(vertex);
    while(stP){
        int v = pop();
        for(int i = 0; i < 105; ++i){
            if(matrix[i][v] != -1){
                ctr[i]--;
                late[i] = min(late[i], late[v] - matrix[i][v]);
                if(!ctr[i]) push(i);
            }
        }
    }
    
    for(int i = 0 ; i < N; ++i)
        printf("%d %d %d\n", i, early[edge[i].i], late[edge[i].j] - edge[i].w);
    int ctr = 0;
    for(int i = 0 ; i < N; ++i)
        if(early[edge[i].i] == late[edge[i].j] - edge[i].w)
            ctr++ ? printf(" %d", i) : printf("%d", i);
    return 0;
}