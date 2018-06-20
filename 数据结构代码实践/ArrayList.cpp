#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
typedef struct SeqList{
	int maxLength;
	int n;
	int *elements;
}SeqList;
const int SIZE = 20;

//创建顺序表
void Create(SeqList *L,int mSize)
{
	L -> maxLength = mSize;
	L -> elements = (int *)malloc(sizeof(int) * mSize);
	L -> n = 0;
}
//判断顺序表是否为空
bool IsEmpty(SeqList *L)
{
	return L -> n == 0;
}
//获取顺序表的长度
int Length(SeqList *L)
{
	return L -> n;
}
//查找下标为i的元素，由x返回
bool Find(SeqList *L,int i,int *x)
{
	if(i<0 || i>L->n-1){
		printf("Out of bounds\n");
		return false;
	}
	x = &L->elements[i];
	return true;
}
//查找与元素x相等的元素，返回该相等元素的下标
int Search(SeqList *L,int x)
{
	for(int i=0;i<L->n;i++)
		if(L->elements[i] == x)
			return i;
	return -1;
}
//在下标为i的位置插入新元素x
bool Insert(SeqList *L,int i,int x)
{
	if(i<-1 || i>L->n-1){
		printf("Out of bounds\n");
		return false;
	}
	if(L->n == L->maxLength){
		printf("Overflow!\n");
		return false;
	}
	for(int j=L->n-1;j>i;j--)//插入，然后后移
		L->elements[j+1] = L->elements[j];
	L->elements[i+1] = x;
	L->n++;
	return true;
}
//删除下标为i的元素
bool Delete(SeqList *L,int i)
{
	if(L->n == 0)
	{
		printf("Overflow!\n");
		return false;
	}
	if(i<-1 || i>L->n-1){
		printf("Out of bounds\n");
		return false;
	}
	for(int j=i+1;j<L->n;j++){//删除，然后左移
		L->elements[j-1] = L->elements[j];
	}
	L->n--;
	return true;
}
//删除所有值等于x的元素，若不存在x，则返回false
bool DeleteX(SeqList *L,int x)
{
	bool flag = false;
	if(L->n == 0)
	{
		printf("Underflow\n");
		return false;
	}
	for(int i=0;i<L->n;i++){
		if(L->elements[i] == x){
			Delete(L,i);
			i--;
			flag = true;
		}
	}
	return flag;
}
//删除元素值介于a和b的所有元素
bool DeleteAB(SeqList *L,int a,int b)
{
	bool flag = false;
	if(a > b)
		swap(a,b);
	if(L->n == 0){
		printf("Underflow!\n");
		return false;
	}
	for(int i=0;i<L->n;i++){
		if(L->elements[i]<=b && L->elements[i]>=a){
			Delete(L, i);
			i--;
			flag = true;
		}
	}
	return flag;
}
//将下标为i的元素更新为x
bool Update(SeqList *L,int i,int x)
{
	if(i<-1 || i>L->n-1){
		printf("Out of bounds\n");
		return false;
	}
	L->elements[i] = x;
	return true;
}
//逆置顺序表中所有元素
void Reverse(SeqList *L){
	if(L->n <=1)
		return;
	for(int i=0,j=L->n-1;i<j;i++,j--){
		swap(L->elements[i],L->elements[j]);
	}
}
//输出顺序表中所有元素
void Output(SeqList *L)
{
	for(int i=0;i<L->n;i++)
		printf("%d ",L->elements[i]);
	printf("\n");
}

int main() {
	SeqList list;
	Create(&list,SIZE);
	Insert(&list,-1,12);
	Insert(&list,0,13);
	Insert(&list,1,14);
	Insert(&list,2,15);
	printf("原始顺序表：");
	Output(&list);
	
	DeleteAB(&list,13,14);
	printf("删除区间元素后的结果：");
	Output(&list);
	
	Reverse(&list);
	printf("逆置后的结果：");
	Output(&list);
	return 0;
}