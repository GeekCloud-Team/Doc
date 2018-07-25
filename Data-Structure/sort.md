

## 排序算法

这里讨论的排序算法都是内排序算法

排序分为：

* 插入排序
    * 直接插入排序
    * 折半插入排序 
    * Shell排序
* 交换排序
    * 冒泡排序
    * 快速排序
* 选择排序
    * 简单选择排序
    * 堆排序
* 归并排序
* 基数排序

### 插入排序

插入排序是一种简单直观的排序方法,其基本思想在于每次将一个待排序的记录,按其关键字大小插入到前面已经排好序的子序列中,直到全部记录完成.

- 由插入排序的思想可以引伸出三个重要排序算法: 直接插入排序 / 折半插入排序 / 希尔排序

#### 直接插入排序

在排序过程中序列的状态如下:

```
            |  有序序列L[1...i-1]  |   L[i]   |    无序序列L[i+1...n]  |
```

也就是说，每趟排序保证前面的序列是有序的。

排序流程:
```
    1 ) 查找出L[i]在L[1...i-1]中的位置 k

    2 ) 将L[k...i-1]中所有元素全部后移一个位置

    3 )将L[i]复制到L[k] 
```

C代码实现:
```c
#不使用哨兵
void InsertSort ( ElemType A[ ],int n ){
    int i , j;
    //定义temp用于存储L[i]
    ElemType temp;
    //外层循环
    for(i=1;i<n;i++){
        j=i;
        //将待排序的值赋值给temp
        temp=A[i];
        //内存循环
        while(j>0 && temp < A[j-1] ){
            //依次把待排序数和有序序列从后往前比较,如果比其小就往后移动
            A[j]=A[j-1];
            j--;
        }
        //找到所在位置，赋值
        A[j]=temp;
    }

#使用哨兵
void InsertSort ( ElemType A[ ],int n ){
    int i , j;
    for( i=2 ; i<= n ; i++ ){         //依次将A[2]~A[n]插入到前面已排序
        if( A[i] < A[i-1] ){  //若A[i]小于其前驱
            A[0]=A[i];                //复制为哨兵,A[0]不存放元素
            for( j=i-1 ; A[0] < A[j] ; --j ){  //从后往前查找待插入位置
                A[j+1] = A[j];        //向后挪位
            }
            A[j+1] = A[0];              //复制到插入位置
        }
    }
}
```

平均时间复杂度O(n²)

> 最好情况下，表中元素已经有序，此时没插入一个元素，都只需比较一次而不用移动元素，因而时间复杂度为O(n)
> 最坏情况下，表中的元素为逆序，总的比较次数就达到最大，为：$ \sum _{i=1}^n i $， 移动次数达到最大，为 $ \sum _{i=2}^n (i+1) $



#### 折半插入排序:
    
在前面简单插入排序过程中,每趟排序都进行了2项工作:
```
    1.从前面的子表中查找出待插入元素应该被插入的位置
    2.给插入位置腾出空间
```

折半查找原理很简单，就是把直接插入排序过程中的直接查找过程用二分查找代替，即减少比较次数。 

C代码算法实现:
```c
void HalfInsertSort (ElemType A[], int n){
    int i , j , low , high , mid ;
    for( i=2 ; i < n ; i++ ){    //依次将A[2]~A[n]插入到前面已排序序列
        A[0] = A[i];             //将A[i]暂存到A[0]
        low = 1;                 //设置折半查找的范围
        high = i -1 ;           
        while(low <= high){      //折半查找(默认递增有序)
            mid = (low+high)/2;  //取中间点
            if(A[mid] > A[0]){ //查找左半子表
                high = mid-1;   
            }
            else low = mid + 1;  //查找右半子表
        }
        for(j=i-1;j>high+1;--j){  //统一后移元素,空出插入位置
            A[j+1]=A[j];
        }
        A[high+1]=A[0];              //插入操作
    }
}
```

> 时间复杂度依旧为O(n²),折半插入排序仅仅是减少比较元素的次数,适用于n比较大时。


#### 希尔(Shell)排序

前面2种算法适用于基本有序或者数据量不大的排序表,基于这2点,1959年Shell提出希尔排序,又称为缩小增量排序.

基本思想:将排序表分成若干个形如L[i,i+d,i+2d,...,i+kd]的特殊子表,分别进行插入排序,当整个表基本有序时,再对全体记录经行一次直接插入排序

C代码算法实现:
```c
void ShellSort (ElemType A[],int n ){
    //对顺序表做希尔插入排序,该算法与直接插入排序相比,做了以下修改
    //1.前后记录位置增量是dk,不是1
    //2.A[0]知识暂存单元,不是哨兵,当j<=0时,插入位置已到
    int dk,i,j;
    for(dk = n/2 ; dk >= 1 ; dk= dk/2 ){ //步长变化
        for(i=dk+1; i<= n ; ++i ){       
            if(A[i] < A[i-dk] ){  //需将A[i]插入有序增量子表
                A[0]=A[i];                    //暂存到A[0]
                for(j=i-dk ; j>0 && A[0]<A[j] ; j-=dk ){ //记录后移,查找插入位置
                    A[j+dk]=A[j];
                }
                A[j+dk]=A[0];        //插入
            }
        }
    }
}
```
时间复杂度:O(n²)


### 交换排序

交换排序,就是根据序列中的两个元素关键字的比较结果来对换这两个记录在序列中的位置.基于交换的排序算法很多,考研主要要求冒泡排序和快速排序

#### 冒泡排序

冒泡排序不多说,大家都懂,每趟排序都将待排序序列中最大/最小的元素找出来,这也是冒泡的由来

冒泡排序不同于直接插入排序，冒泡排序是两两相比，插入排序是

直接撸上C代码:
```c
#define false 0

void BubbleSort(ElemType A[],int n ){
    for(i=0;i<n;i++){
        flag=false ; //表示每趟冒泡是否发生交换的标志
        for(j=n-1;j>i;j--){ //一趟冒泡过程
            if(A[j-1] > A[j]){ //若为逆序
                swap(A[j-1],A[j]); //交换
                flag=true;
            }
        }
        if (flag==false){
            return ;  //本趟遍历如果没有发送交换,说明表已经有序
        }
    }
}
```

时间复杂度O(n²)

#### 快速排序

快速排序是对冒泡排序的一种改进。


C代码：
```c
//递归算法
void QuickSort(ElemType A[],int left,int right){
    //i，j分别为扫描指针
    //i向右扫描大于等于left的元素
    //j向左扫描小于等于left的元素
    int i , j ; 
    if(left<right){
        i=left;
        j=right+1;
        do{
            do{i++;}while(A[i] <= A[left]);
            do{j--;}while(A[j] > A[left] );
            //大于left的数和小于left的数交换位置
            if(i<j){swap(A[i],A[j]);}
        }while(i<j);
        //当i大于等于j的时候跳出循环，此时将当前j所在位置，将left与j交换位置
        swap(A[left],A[j]);        
        //从刚刚赋值的left的位置进行划分，分别进行快排
        QuickSort(A,left,j-1);
        QuickSort(A,j+1,right);
    }
}

//非递归算法
void QuickSort(ElemType A[],int n){
    int i , j , left = 0 , right = n-1;
    //创建两个栈，分别用于存划分之后的左右部分
    stack SL,SR;
    //将left分别压栈
    push(SL,left);
    push(SR,left);
    while(!IsEmpty(SL) && !IsEmpty(SR) ){
        left=pop(SL);
        right=pop(SR);
        if(left<right){
            i=left;
            j=right+1;
            do{
                //比较方式与非递归算法相同
                do{i++;}while(A[i]<A[left]);
                do{j--;}while(A[j]>A[left]);
                //大于left的数和小于left的数交换位置
                if(i<j)swap(A[i],A[j]);
            }while(i<j);
            //当i大于等于j的时候跳出循环，此时将当前j所在位置，将left与j交换位置
            swap(A[left],A[j]);
            push(SL,j+1);
            push(SR,right);
            push(SL,left);
            push(SR,j-1);
            //此时SL栈底是j+1(下一次i++，正好是中轴右面的元素)，栈顶是left（最左），SR栈底是right（最右），栈顶是j-1(中轴右面的元素)
        }
    }
}

```

空间效率：
最好情况: $\left \lfloor log_2 (n+1) \right \rfloor$
最坏情况： $O(n)$
平均情况： $O(log_2(n))$
有很多方法可以提高算法效率：
    
- [x] 当递归过程中划分得到的子序列规模较小时，不要再继续递归调用快速排序，可以直接采用直接插入排序法进行后续工作。  

- [x] 尽量取一个可以将数据中分的枢轴元素，使得最坏情况在实际排序中不会发生。  


### 选择排序

选择排序的基本思想:
每一趟(如第i趟)在后面n-i+1(i=1,2...n-1) 个待排序元素中选取关键字最小的元素,作为有序子序列的第i个元素,直到第n-1趟做完,待排序元素只剩下1个,就不用再选了.

#### 简单选择排序

##### 思想：

每趟都从查找的集合里找到最大小的放最前面，然后缩小查找范围，直到查找范围里面只有一个数。

代码：
```c
void SelectSort(ElemType A[],int n ){
    for(i=0;i<n-1;i++){  //一共经行n-1趟
        min=i;          //记录最小元素位置
        for(j=i+1;j<n;j++){  //在A[i...n-1]中选择最小元素
            if(A[j]<A[min]){
                min=j;
                } //更新最小元素位置
        }                        
        if (min!=i){swap(A[i],A[min]);} //与第i个位置交换
    }
}
```

时间复杂度： $O(n^2)$
> 元素移动次数不会超过3(n-1),比较次数与序列状态无关，始终是$ n(n-1)/2 $ 次

空间复杂度： $O(1)$

#### 堆排序


##### 堆
堆就是包含N个节点的完全二叉树，数的美国节点关键字值` 大于等于1 `或 `小于等于1` 其双亲节点的关键字的值，这颗二叉树的根称 ` 堆顶 ` ，是整个树的 `最大值`或者`最小值`,这个数分别对应的是 `最大堆` 或者 `最小堆` 。

##### 堆排序步骤

- 1\. 建堆  `最大堆` 或者 `最小堆` （之后以最大堆为例）
- 2\. 将堆顶与堆底互换，（然后把堆底元素拔下来）
- 3\. 调整堆，使其为最大堆，重复2步骤。

> 跟冒泡和选择一样，每趟排序出一个最大的或者最小的，然后缩小范围,但是剩下的数组排列不一定和前面2个排序一样。

##### 建堆大体流程
构造堆的扫描指针，初始指针r在（n-1)/2,也就是最后一个有孩子的节点，对其所指的子树做向下调整操作（AdjustDown），最后结果是大元素放在树顶端调整结束后，初始指针r往前移动。

此时堆构造完成，开始第一趟排序，将堆顶A[0]与堆底元素A[n-1]交换，使用AdjustDown函数将A[0]向下调整，使得前n-1个元素仍是堆。

第i趟将A[0]与A[n-i]交换，A[0]向下调整，使剩余n-i个元素仍是堆，一直到堆中只剩下一个元素


C语言算法：
```c
void AdjustDown(ElemType A[],int r,int j){ //j是最后一个节点编号
    //指向r的左孩子
    int child=2*r+1;
    //保存r的值
    ElemType temp=A[r];
    while(child <= j){
        if(child<j && (A[child]<A[child+1])){//如果child不是最后的节点或并且小于兄弟节点
            child++;
        }
        if(temp>=A[child]){break;}//如果r比孩子节点都大则无需调整
        A[(child-1)/2]=A[child];//否则将child赋值给父节点
        child=2*child+1; //指向当前节点的左孩子
    }
    A[(child-1)/2]=temp; //将调整节点插入到该位置
}

void HeapSort(ElemType A[],int n){
    int i;
    for(i=(n-2)/2;i>-1;i--){ AdjustDown(A,i,n-1); } //构造堆
    for(i=n-1;i>0;i--){ //进行堆排序
        swap(A[0],A[i]);
        AdjustDown(A,0,i-1);  
    }
}
```

空间效率：$O(1)$
时间效率：建堆时间 $O(n)$ 平均调整时间 $O(nlog_2 n)$

### 归并排序（二合一排序/2-路归并排序）

#### 思想
将N个元素的序列看出是N个长度为1的有序子序列，然后两两合并子序列，得到 $\left \lceil n/2 \right \rceil$个长度为2或为1的有序子序列，再两两合并，直到得到一个长度为N的有序序列。

设置两个函数，`Merge()`的功能是将前后相邻的两个有序表归并成一个有序表的算法`MergeSort()`是完整的排序算法

C代码：
```c
ElemType *B = (ElemType *)malloc((n+1) *sizeof(ElemType));//构造辅助数组B
void Merge(ElemType A[],int low,int mid,int high){
    int i ,j ,k ;
    for(int k=low;k<=high;k++){
        B[k]=A[k]; //将A中所有元素复制到B中
    }
    for(i=low,j=mid+1,k=i,i<=mid&&j<=high;k++){
        if(B[i]<=B[j]){A[k]=B[i++];} //比较B左右两段中的元素，将较小的赋值到A中
        else{A[k]=B[j++];} 
    }
    while(i<=mid){A[k++]=B[i++];} //若第一个表未检测完 ，复制
    while(j<=high){A[k++]=B[j++];} //若第二个表未检测完 ，复制
}

void MergeSort(ElemType A[],int low,int high){
    int mid ;
    if(low<high){
        mid = (low+high)/2; //从中间划分子序列
        MergeSort(A,low,mid); //对左侧子序列进行递归排序
        MergeSort(A,mid+1,high); //对右侧子序列进行递归排序
        Merge(A,low,mid,high); //归并
    }
}
```
空间效率： $O(n)$
时间效率： $n \left \lceil log_2 n \right \rceil$

### 基数排序

基数排序是一种特别的排序方法，它不是基于比较进行排序的，而是采用多关键字思想（根据各位的大小排序），借助“分配”和“收集”两种操作对单逻辑关键字进行排序。

#### 两种模式

分为最高位优先排序（MSD），最低位优先（LSD）排序

直接附上C代码：
```c
void print(int *a, int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%d\t", a[i]);
  }
}

void radixsort(int *a, int n) {
  int i, b[MAX], m = a[0], exp = 1;

  for (i = 1; i < n; i++) {
    if (a[i] > m) {
      m = a[i];
    }
  }

  while (m / exp > 0) {
    int bucket[BASE] = { 0 };

    for (i = 0; i < n; i++) {
      bucket[(a[i] / exp) % BASE]++;
    }

    for (i = 1; i < BASE; i++) {
      bucket[i] += bucket[i - 1];
    }

    for (i = n - 1; i >= 0; i--) {
      b[--bucket[(a[i] / exp) % BASE]] = a[i];
    }

    for (i = 0; i < n; i++) {
      a[i] = b[i];
    }

    exp *= BASE;

#ifdef SHOWPASS
    printf("\nPASS   : ");
    print(a, n);
#endif
  }
}

int main() {
  int arr[MAX];
  int i, n;

  printf("Enter total elements (n <= %d) : ", MAX);
  scanf("%d", &n);
  n = n < MAX ? n : MAX;

  printf("Enter %d Elements : ", n);
  for (i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  printf("\nARRAY  : ");
  print(&arr[0], n);

  radixsort(&arr[0], n);

  printf("\nSORTED : ");
  print(&arr[0], n);
  printf("\n");

  return 0;
}
```

时间复杂度：$O(d(n+r))$ 其中r是队列数，d是趟数
空间复杂度：$O(r)$