/*邻接表实现图结构*/
#include <bits/stdc++.h>
#include "myqueue.h"
typedef long long ll;
using namespace std;
//边节点结构
typedef struct ENode
{
	int adjVex;//顶点编号
	int data;//存取数据
	ENode* nextArc;//指向下一邻接结点
}ENode;

//邻接表结构
typedef struct LGraph{
	int n;//顶点数量
	int e;//边的数量
	ENode** a;//邻接链表
}LGraph;

//创建包含mSize个节点的图
void CreateLGraph(LGraph *L,int mSize)
{
	L -> n = mSize;
	L -> e = 0;
	L -> a = (ENode **)malloc(sizeof(ENode*) * mSize);
	for(int i=0;i<L->n;i++)
		L -> a[i] = NULL;
}

//清空图顶点和边
void Clear(LGraph *L)
{
	ENode *p,*q;
	for(int i=0;i<L->n;i++){
		p = L -> a[i];
		q = p;
		while(p){
			p = p -> nextArc;
			free(q);
			q = p;
		}
	}
	L -> e = 0;
	L -> n = 0;
	free(L -> a);
}

//判断图中是否存在边(i,j)
bool Exist(LGraph *L,int i,int j)
{
	if(i<0 || j<0 || j>L->n-1 || i==j)
		return false;
	ENode *p = L -> a[i];
	while(p && p -> adjVex != j)
		p = p -> nextArc;
	if(!p)
		return false;
	else
		return true;
}

//在图中插入边（i,j）
bool Insert(LGraph *L,int i,int j)
{
	if(i<0 || j<0 || j>L->n-1 || i==j)
		return false;
	if(Exist(L,i,j))
		return false;
	ENode* p = (ENode *)malloc(sizeof(ENode));
	p -> adjVex = j;
	p -> nextArc = L -> a[i];
	L -> a[i] = p;
	L -> e++;
	return true;
}

//在图中删除边（i,j）
bool Remove(LGraph *L,int i,int j)
{
	if(i<0 || j<0 || j>L->n-1 || i==j)
		return false;
	ENode *p = L -> a[i],*q = NULL;
	while(p && p -> adjVex != j){
		q = p;
		p = p -> nextArc;
	}
	if(!p)
		return false;
	if(q)
		q -> nextArc = p -> nextArc;
	else
		L -> a[i] = p -> nextArc;
	free(p);
	L -> e--;
	return true;
}

//从i顶点开始递归dfs优先遍历图
void dfs(LGraph *L,int i,bool *visited)
{
	visited[i] = true;
	printf(" %d",i);
	for(ENode *p = L -> a[i];p;p = p -> nextArc)
		if(!visited[p -> adjVex])
			dfs(L,p->adjVex,visited);
}

//深度优先遍历图
void dfs(LGraph *L)
{
	bool *visited = (bool*)malloc(sizeof(bool) * L -> n);
	for(int i=0;i<L->n;i++)
		visited[i] = false;
	for(int i=0;i<L->n;i++)
		if(!visited[i])
			dfs(L,i,visited);
	free(visited);
}

//从i顶点出发广度优先遍历图
void bfs(LGraph  *L,int i,bool* visited)
{
	Queue Q;
	Create(&Q,L->n);
	visited[i] = true;
	printf("%d ",i);
	EnQueue(&Q, i);
	while(!IsEmpty(&Q)){
		DeQueue(&Q);
		for(ENode* p = L -> a[i];p;p = p -> nextArc)
			if(!visited[p->adjVex]){
				visited[p->adjVex] = true;
				printf("%d ",p->adjVex);
				EnQueue(&Q,p -> adjVex);
			}
	}
}

//广度优先遍历图
void bfs(LGraph *L)
{
	bool* visited = (bool*)malloc(sizeof(bool) * L -> n);
	for(int i=0;i<L->n;i++)
		visited[i] = false;
	for(int i=0;i<L->n;i++)
		if(!visited[i])
			bfs(L,i,visited);
	free(visited);
}

//输出邻接表结构
void Output(LGraph *L)
{
	for(int i=0;i<L->n;i++){
		ENode* p = L -> a[i];
		if(p == NULL)
			printf("%d --> NULL\n",i);
		else{
			printf("%d ",i);
			for(;p;p=p->nextArc)
				printf(" --> %d",p->adjVex);
			printf(" --> NULL\n");
		}
	}
}

int main() 
{
	LGraph G;
	CreateLGraph(&G, 5);
	Insert(&G,0,4);
	Insert(&G,0,2);
	Insert(&G,4,3);
	Insert(&G,2,1);
	
	printf("图的邻接表表示：\n");
	Output(&G);
	printf("\n");
	
	printf("深度遍历图结果为：");
	dfs(&G);
	printf("\n");
	
	printf("宽度遍历图结果为：");
	bfs(&G);
	printf("\n");
	return 0;
}