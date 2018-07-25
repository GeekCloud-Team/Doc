#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
typedef struct Node{
	int element;
	struct Node *link;
}Node;
typedef struct{
	Node *first;
	int n;
}LinkedList;

//单链表初始化
void Init(LinkedList *L)
{
	L->first = NULL;
	L->n = 0;
}
//单链表查找，查找下标为i的数据元素，通过x返回
bool Find(LinkedList *L,int i,int *x)
{
	if(i<0 || i>L->n-1)//进行越界检查
		return false;
	Node *p = L->first;
	for(int j=0;j<i;j++)//查找Ai
		p = p -> link;
	*x = p -> element;//通过x返回Ai的值
	return true;
}
//单链表插入，将新元素x插入下标为i的位置
bool Insert(LinkedList *L,int i,int x)
{
	if(i<-1 || i>L->n-1)
		return false;
	Node *p = L -> first;
	for(int j=0;j<i;j++)
		p = p -> link;//从头结点开始查找Ai
	Node *q = (Node *)malloc(sizeof(Node));//生成新结点q
	q->element = x;
	if(i>-1){//新结点插入在p所指结点之后
		q -> link = p -> link;
		p -> link = q;
	}
	else{
		q -> link = L -> first;//新结点插在头结点之前，成为新的头结点
		L -> first = q;
	}
	L->n++;
	return true;
}
//单链表删除，删除下标为i的元素，从0开始计数
bool Delete(LinkedList *L,int i)
{
	if(L -> n == 0)//无元素
		return false;
	if(i<0 || i>L->n-1)//越界
		return false;
	Node *q = L -> first;
	Node *p = L -> first;
	for(int j=0;j<i-1;j++)
		q = q -> link;
	if(i == 0)//删除第一个元素
		L -> first = L -> first -> link;
	else{
		p = q -> link;//p指向Ai
		q -> link = p -> link;//从单链表中删除p指向的节点
	}
	free(p);
	L->n--;
	return true;
}
//单链表修改
bool Modify(LinkedList *L,int i,int x)
{
	if(i<0 || i>L->n-1)//进行越界检查
		return false;
	Node *p = L->first;
	for(int j=0;j<i;j++)//查找Ai
		p = p -> link;
	p -> element = x;
	return true;
}
//顺序表输出
bool Output(LinkedList *L)
{
	if(L->n == 0)//顺序表为空
		return false;
	Node *p = L -> first;
	while(p){
		printf("%d ",p->element);
		p = p -> link;
	}
	printf("\n");
	return true;
}
//顺序表撤销
void Destroy(LinkedList *L)
{
	while(L->first)
	{
		Node *p = L -> first -> link;//保存后继节点的地址，防止断链
		free(L -> first);
		L -> first = p;
	}
}

int main()
{
	LinkedList list;
	Init(&list);//初始化
	int choice = -1;
	while(choice != 0)
	{
		printf("---------- 菜单 ----------\n");
		printf("请输入你想选择的操作：\n");
		printf("        1.插入链表\n");
		printf("        2.删除链表\n");
		printf("        3.修改链表\n");
		printf("        4.查找链表\n");
		printf("        5.销毁链表\n");
		printf("按0退出菜单\n");
		printf("-------------------------\n");
		scanf("%d",&choice);
		int overall = 0,input = 0,index = 0,value = 0,out = 0,flag = 1;
		switch(choice)
		{
			case 1://插入
				printf("请输入你想插入的链表元素个数：\n");
				scanf("%d",&overall);
				printf("请输入你想插入的元素，全部输入在一行");
				for(int i=0;i<overall;i++)
				{
					scanf("%d",&input);
					flag = Insert(&list,i-1,input);
				}
				if(flag)
					printf("插入后的元素为：\n");
				else
					printf("无法插入！\n");
				Output(&list);
				break;
			case 2://删除
				printf("请输入你想删除的元素下标位置:\n");
				scanf("%d",&index);
				flag = Delete(&list, index);
				if(flag)
					printf("删除后的元素为：\n");
				else
					printf("无法删除！\n");
				Output(&list);
				break;
			case 3://修改
				printf("请输入你想修改的元素下标位置和值:\n");
				scanf("%d%d",&index,&value);
				flag = Modify(&list, index, value);
				if(flag)
					printf("修改后的元素为：\n");
				else
					printf("无法修改！\n");
				Output(&list);
				break;
			case 4://查找
				printf("请输入你想查找的元素下标位置:\n");
				scanf("%d",&index);
				flag = Find(&list,index,&out);
				if(flag)
					printf("第%d个的元素值为: %d\n",index,out);
				else
					printf("无法找到该下标值！\n");
				break;
			case 5://销毁
				Destroy(&list);
				printf("销毁后的元素为：\n");
				Output(&list);
				break;
			case 0:
				break;
			default:
				printf("输入错误，请重新输入\n");
				break;
		}
	}
	printf("谢谢您的使用，再见！\n");
	return 0;
}