#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
typedef struct BTNode{
	int data;
	struct BTNode *lchild;
	struct BTNode *rchild;
}BTNode;

//先序规则创建二叉树，如AB##C##，其中#分别表示A和B的左右子树均为空
BTNode* PreCreateBt(BTNode *t)
{
	char ch = getchar();
	if(ch == '#')
		t = NULL;
	else
	{
		t = (BTNode*)malloc(sizeof(BTNode));
		t -> data = ch;
		t -> lchild = PreCreateBt(t -> lchild);
		t -> rchild = PreCreateBt(t -> rchild);
	}
	return t;
}

//先序遍历二叉树
void PreOrderTransverse(BTNode *t)
{
	if(t == NULL)
		return;
	printf("%c ",t -> data);//根
	PreOrderTransverse(t -> lchild);//左
	PreOrderTransverse(t -> rchild);//右
}

//中序遍历二叉树
void InOrderTransverse(BTNode *t)
{
	if(t == NULL)
		return;
	InOrderTransverse(t -> lchild);//左
	printf("%c ",t -> data);//根
	InOrderTransverse(t -> rchild);//右
}

//后序遍历二叉树
void PostOrderTransverse(BTNode *t)
{
	if(t == NULL)
		return;
	PostOrderTransverse(t -> lchild);//左
	PostOrderTransverse(t -> rchild);//右
	printf("%c ",t -> data);//根
}

//删除整棵二叉树
void Clear(BTNode *t)
{
	if(!t)
		return;
	Clear(t -> lchild);
	Clear(t -> rchild);
	delete t;
}

//求二叉树中节点的数量
int Size(BTNode *t)
{
	if(!t)
		return 0;
	else
		return Size(t -> lchild) + Size(t -> rchild) + 1;
}

//求二叉树中叶子节点的数量
int Leaves(BTNode *t)
{
	if(!t)
		return 0;
	if(t -> lchild == NULL && t -> rchild == NULL)
		return 1;
	return Leaves(t -> lchild) + Leaves(t -> rchild);
}
//求二叉树的高度
int Height(BTNode *t)
{
	if(!t)
		return 0;
	int l = Height(t -> lchild);
	int r = Height(t -> rchild);
	return max(l,r) + 1;
}

//拷贝一棵二叉树
BTNode* Copy(BTNode *t)
{
	if(!t)
		return NULL;
	BTNode* q = (BTNode *)malloc(sizeof(BTNode));
	q -> lchild = Copy(t -> lchild);
	q -> rchild = Copy(t -> rchild);
	return q;
}

//交换二叉树的所有左右子树
void Exchange(BTNode* t)
{
	if(t -> lchild == NULL && t -> rchild == NULL)
		return;
	BTNode *temp = t -> lchild;
	t -> lchild = t -> rchild;
	t -> rchild = temp;
	Exchange(t -> lchild);
	Exchange(t -> rchild);
}

//main函数仅用作测试
int main() 
{
	printf("先序建树：");
	BTNode *t = PreCreateBt(t);
	
	printf("\n先序遍历：");
	PreOrderTransverse(t);
	
	printf("\n中序遍历：");
	InOrderTransverse(t);
	
	printf("\n后序遍历：");
	PostOrderTransverse(t);
	
	printf("\n该树包含的节点总数：%d\n",Size(t));
	printf("该树的高度：%d\n",Height(t));
	printf("该树包含叶子节点的总数：%d\n",Leaves(t));
	return 0;
}