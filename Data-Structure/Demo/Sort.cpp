#include <bits/stdc++.h>
#include <time.h>
typedef long long ll;
using namespace std;

//简单选择排序:每次选最小的放前面
//复杂度O(n2),不稳定
void SelectSort(int A[],int n)
{
	int small = 0;
	for(int i=0;i<n-1;i++){
		small = i;
		for(int j=i+1;j<n;j++){
			if(A[j] < A[small])
				small = j;
		}
		swap(A[i],A[small]);
	}
}

//直接插入排序：每次取边界的数，然后放入合适的位置
//复杂度O(n2),稳定
void InsertSort(int A[],int n)
{
	for(int i=1;i<n;i++)
	{
		int j = i;
		int temp = A[i];
		while(j>0 && temp<A[j-1]){
			A[j] = A[j-1];
			j--;
		}
		A[j] = temp;
	}
}

//冒泡排序：每次考察相邻两个元素的大小，并调整为从小到大的顺序
//每次确定最后一个元素的位置，并进行多趟排序
//复杂度O(n2),稳定
void BubbleSort(int A[],int n)
{
	int i = n - 1;
	while(i>0){
		int last = 0;
		for(int j=0;j<i;j++){
			if(A[j+1] < A[j]){
				swap(A[j],A[j+1]);
				last = j;
			}
		}
		i = last;
	}
}

/*快速排序:首先选取第一个元素作为参照元素，
然后，选取游标i和j分别从头尾向中间移动
每次比较参照元素和A[i],A[j]的大小，移动直到A[i]>=target和A[j]<=target时停止
然后交换A[i]与A[j],当i>=j时跳出循环
然后，将最左参照元素和A[j]交换
然后，二分之，对左边元素(下标在left到j之间)和右边元素(下标在j+1到right之间)进行递归调用
反复排序，直到所有元素排序完成*/
//复杂度O(nlogn),不稳定
void QuickSort(int A[],int left,int right)
{
	if(left < right){
		int i = left,j = right + 1;
		do{
			do	i++;while(A[i] < A[left] && i <= right);
			do	j--;while(A[j] > A[left] && j >= right);
			if(i < j)
				swap(A[i],A[j]);
		}while(i < j);
		swap(A[left],A[j]);
		QuickSort(A, left, j - 1);
		QuickSort(A, j + 1, right);
	}
}

/*两路合并排序：先将n个元素看成n个长度为1的序列
然后修改size每次*2，然后两两合并子序列，不停两两合并
最后得到的就是长度为n的有序序列
在合并时，设定游标i和j分别开始于，两个序列初始位置
然后每次取A[i]和A[j]较小的元素，加到大数组中
最后把剩余的元素加到后面就行
*/
//时间复杂度O(nlogn)，稳定
void Merge(int A[],int i1,int j1,int i2,int j2)
{
	int *temp = (int*)malloc(sizeof(int) * (j2 - i1 + 1));//先开辟跟原数组一样大小的内存
	int i = i1,j = i2,k = 0;
	while(i <= j1 && j <= j2)
	{
		if(A[i] <= A[j])
			temp[k++] = A[i++];
		else
			temp[k++] = A[j++];
	}
	while(i <= j1)
		temp[k++] = A[i++];
	while(j < j2)
		temp[k++] = A[j++];
	for(int i=0;i<k;i++)//把temp数组所有取出来，放到原数组A中
		A[i1++] = temp[i];
	free(temp);
}

void MergeSort(int A[],int n)
{
	int i1,j1,i2,j2;
	int size = 1;
	while(size < n)
	{
		i1 = 0;
		while(i1 + size < n){
			i2 = i1 + size;
			j1 = i2 - 1;
			if(i2 + size - 1 > n - 1)
				j2 = n - 1;
			else
				j2 = i2 + size - 1;
			Merge(A,i1,j1,i2,j2);
			i1 = j2 + 1;
		}
		size *= 2;
	}
}

/*堆排序：将初始序列构造成最大堆
第一趟排序，将堆顶元素A[0]和堆底元素A[n-1]交换位置，
调用AdjustDown函数将A[0]向下调整，使得剩余的前n-1个元素满足最大堆要求
一次调用直到第i趟排序
当队中只剩一个记录时，排序结束。
*/
//时间复杂度O(nlogn),不稳定
void AdjustDown(int A[],int r,int j)
{
	int child = 2 * r + 1;
	int temp = A[r];
	while(child <= j)
	{
		if(child < j && A[child] < A[child + 1])
			child++;
		if(temp >= A[child])
			break;
		A[(child - 1) / 2] = A[child];
		child = 2 * child + 1;
	}
	A[(child - 1) / 2] = temp;
}

void HeapSort(int A[],int n)
{
	for(int i=(n-1)/2;i>-1;i--)//调整为最大堆
		AdjustDown(A,i,n-1);
	for(int i=n-1;i>0;i--){
		swap(A[0],A[i]);
		AdjustDown(A,0,i-1);
	}
}

//希尔排序：从大到小每次选择一个gap，比较A[j]和A[j+gap]，若A[j]>a[j+gap],则交换两个元素，然后缩小gap
//不稳定
void ShellSort(int A[],int n)
{
	int gap = n / 2;
	while(gap > 0)
	{
		for(int i=gap;i<n;i++)
			for(int j=i-gap;j>=0 && A[j]>A[j+gap];j -= gap)
				swap(A[j],A[j+gap]);
		gap /= 2;
	}
}

//复制数组
void Copy(int A[],int B[],int n)
{
	for(int i=0;i<n;i++)
		B[i] = A[i];
}
//输出
void Print(int A[],int n)
{
	for(int i=0;i<n;i++)
		printf("%d ",A[i]);
}
//生成随机数
void DataGen(int A[],int n)
{
	srand((unsigned)time(NULL));
	for(int i=0;i<n;i++)
		A[i] = rand() * rand();
}

int main() 
{
	int n = 5000;
	int *A = new int[n];
	int *B = new int[n];
	clock_t start,finish;double elaps;
	
	DataGen(A,n);
	printf("%d数据生成成功！开始测试排序性能...\n\n",n);
	
	
	/*printf("尚未排序前：");
	for(int i=0;i<n;i++)
		printf("%d ",A[i]);
	printf("\n");*/
	
	
	Copy(A,B,n);
	start = clock();
	QuickSort(B,0,n-1);
	finish = clock();
	elaps = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("快速排序：%f seconds\n",elaps);
	//Print(B,n);
	printf("\n");
	
	Copy(A,B,n);
	start = clock();
	ShellSort(B,n);
	finish = clock();
	elaps = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("希尔排序：%f seconds\n",elaps);
	//Print(B,n);
	printf("\n");
	
	Copy(A,B,n);
	start = clock();
	MergeSort(B,n);
	finish = clock();
	elaps = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("合并排序：%f seconds\n",elaps);
	//Print(B,n);
	printf("\n");
	
	Copy(A,B,n);
	start = clock();
	HeapSort(B,n);
	finish = clock();
	elaps = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("堆排序：%f seconds\n",elaps);
	//Print(B,n);
	printf("\n");
	
	Copy(A,B,n);
	start = clock();
	SelectSort(B,n);
	finish = clock();
	elaps = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("选择排序：%f seconds\n",elaps);
	//Print(B,n);
	printf("\n");
	
	Copy(A,B,n);
	start = clock();
	InsertSort(B,n);
	finish = clock();
	elaps = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("插入排序：%f seconds\n",elaps);
	//Print(B,n);
	printf("\n");
	
	Copy(A,B,n);
	start = clock();
	BubbleSort(B,n);
	finish = clock();
	elaps = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("冒泡排序：%f seconds\n",elaps);
	//Print(B,n);
	return 0;
}