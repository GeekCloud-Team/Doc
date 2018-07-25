#include <bits/stdc++.h>
#include "myqueue.h"
typedef long long ll;
#define NOEDGE 0

//邻接存储结构，有向图，a[i][j]!=0时，存储的是边(i,j)的权值
typedef struct MGraph
{
	int n;//顶点数量
	int e;//边的数量
	int **a;//邻接矩阵
}MGraph;

//创建包含mSize个节点的图
void CreateMGraph(MGraph *G,int mSize)
{
	G -> n = mSize;
	G -> e = 0;
	G -> a = (int **)malloc(sizeof(int*) * mSize);
	for(int i=0;i<mSize;i++){
		G -> a[i] = (int *)malloc(sizeof(int) * mSize);
		for(int j=0;j<mSize;j++)
			G -> a[i][j] = NOEDGE;
	}
}

//清空图顶点和边
void Clear(MGraph *G)
{
	for(int i=0;i<G->n;i++)
		free(G -> a[i]);
	free(G -> a);
	G -> e = 0;
	G -> n = 0;
}

//判断图中是否存在边(i,j)
bool Exist(MGraph *G,int i,int j)
{
	if(i<0 || i>G->n-1 || j>G->n-1 || i==j || G->a[i][j]==NOEDGE)
		return false;
	return true;
}

//在图中插入边(i,j)
bool Insert(MGraph *G,int i,int j,int w)
{
	if(i<0 || i>G->n-1 || j>G->n-1 || i==j)
		return false;
	if(G->a[i][j] != NOEDGE)
		return false;
	G -> a[i][j] = w;
	G -> e++;
	return true;
}

//在图中删除边(i,j)
bool Remove(MGraph *G,int i,int j)
{
	if(i<0 || i>G->n-1 || j>G->n-1 || i==j)
		return false;
	if(G->a[i][j] == NOEDGE)
		return false;
	G -> a[i][j] = NOEDGE;
	G -> e--;
	return true;
}

//从i顶点开始递归深度优先遍历图
void dfs(MGraph *G,int i,bool* visited)
{
	visited[i] = true;
	printf("%d ",i);
	for(int k=0;k<G->n;k++)
		if(!visited[k] && G->a[i][k]!=NOEDGE && k!=i)
			dfs(G,k,visited);
}

//深度优先遍历图
void dfs(MGraph *G)
{
	bool *visited = (bool*)malloc(sizeof(bool) * G->n);
	for(int i=0;i<G->n;i++)
		visited[i] = false;
	for(int i=0;i<G->n;i++)
		if(!visited[i])
			dfs(G,i,visited);
	free(visited);
}

//从i顶点出发广度优先遍历图
void bfs(MGraph *G,int i,bool* visited)
{
	Queue Q;
	Create(&Q, G->n);
	visited[i] = true;
	printf("%d ",i);
	EnQueue(&Q, i);
	while(!IsEmpty(&Q)){
		DeQueue(&Q);
		for(int k=0;k<G->n;k++)
			if(!visited[k] && G->a[i][k]!=NOEDGE && k!=i){
				visited[k] = true;
				printf("%d ",k);
				EnQueue(&Q, k);
			}
	}
}

//广度优先遍历图
void bfs(MGraph *G)
{
	bool *visited = (bool*)malloc(sizeof(bool) * G->n);
	for(int i=0;i<G->n;i++)
		visited[i] = false;
	for(int i=0;i<G->n;i++)
		if(!visited[i])
			bfs(G,i,visited);
	free(visited);
}

//输出邻接表结构
void Output(MGraph *G)
{
	printf("    ");
	for(int i=0;i<G->n;i++)
		printf(" %3d",i);
	printf("\n--------------------------\n");
	for(int i=0;i<G->n;i++){
		printf(" %3d",i);
		for(int j=0;j<G->n;j++)
			printf(" %3d",G->a[i][j]);
		printf("\n");
	}
}

int main() 
{
	MGraph G;
	CreateMGraph(&G,5);
	Insert(&G, 0, 4, 1);
	Insert(&G, 0, 2, 1);
	Insert(&G, 4, 3, 1);
	Insert(&G, 2, 1, 1);
	
	printf("图的邻接矩阵表示：\n");
	Output(&G);
	printf("\n");
	
	printf("深度遍历图的结果为：\n");
	dfs(&G);
	printf("\n");
	
	printf("宽度遍历图的结果为：\n");
	bfs(&G);
	printf("\n");
	return 0;
}