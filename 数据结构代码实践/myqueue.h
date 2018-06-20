/*此文件主要负责定义队列基本数据结构*/
#include <bits/stdc++.h>
typedef struct{
	int front;
	int rear;
	int maxSize;
	int *element;
}Queue;

//创造一个能容纳mSize个单元的空队列
void Create(Queue *Q,int mSize)
{
	Q -> maxSize = mSize;
	Q -> element = (int*)malloc(sizeof(int) * mSize);
	Q -> front = Q -> rear = 0;
}

//销毁一个已存在的队列，即释放队列占用的数组空间
void Destroy(Queue *Q)
{
	Q -> maxSize = -1;
	free(Q -> element);
	Q -> front = Q -> rear = -1;
}

//判断队列是否为空，若是，则返回true，否则返回false
bool IsEmpty(Queue *Q)
{
	return Q -> front == Q -> rear;
}

//判断堆栈是否已满，若是，则返回true,否则返回false
bool IsFull(Queue *Q)
{
	return (Q -> rear + 1) % Q -> maxSize == Q -> front;
}

//获取队头元素，并通过x返回。若操作成功，则返回true，否则返回false
bool Front(Queue *Q,int *x)
{
	if(IsEmpty(Q))//空队列处理
		return false;
	x = &Q -> element[(Q -> front + 1) % Q -> maxSize];
	return true;
}

//在队列Q的队尾插入元素x（入队操作）。操作成功返回true，否则返回false
bool EnQueue(Queue *Q,int x)
{
	if(IsFull(Q))//溢出处理
		return false;
	Q -> rear = (Q -> rear + 1) % Q -> maxSize;
	Q -> element[Q -> rear] = x;
	return true;
}

//从队列Q中删除队头元素（出队操作）。操作成功返回true，否则返回false
bool DeQueue(Queue *Q)
{
	if(IsEmpty(Q))//空队列处理
		return false;
	Q -> front = (Q -> front + 1) % Q -> maxSize;
	return true;
}

//清除堆栈中全部元素，但并不释放空间
void Clear(Queue *Q)
{
	Q -> front = Q -> rear = 0;
}






