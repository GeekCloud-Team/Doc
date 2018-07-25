
## 数据结构相关概念及定义

### 数据结构框架

* 数据结构
    * 逻辑结构
        * 线性结构
            * 线性表、栈、队列
        * 非线性结构
            * 树、图、集合   
    * 存储结构（存储结构）
        * 顺序存储、链式存储、索引存储、散列存储
    * 数据的运算

### 什么是算法

* 算法 是对特定问题求解步骤的一种描述,它是指令的有限序列,其中每一条指令都表示一个或多个操作

### 算法的5个重要特性

- 有穷性 一个算法必须总是在执行有穷步之后结束,且每一步都可在有穷时间内完成
- 确定性 算法中每一条指令必须有确切的含义,读者理解时不会产生二义性,并且在任何条件下,算法只有-唯一的一条执行路径
- 可行性 一个算法是能行的,即算法描述的操作都是可以通过已经实现的基本运算执行优先次来实现的
- 输入   一个算法有零个或多个的输入,这些输入取自于某个特定的对象的集合
- 输出   一个算法有一个或多个输出,这些输出是同输入有着某些特定关系的量

### 算法设计要求（算法优劣四大标准）
- 正确性 算法应当满足具体问题的需求。设计或选择的算法应当能正确的反应这种需求。
- 可读性 算法主要是为了人的阅读和交流，其次才是机器执行，可读性好有助于人对算法的理解。
- 健壮性 当输入数据非法时，算法也能适当的作出反应或进行处理，而不会产生莫名其妙的输出结果。
- 高效性 评价算法的效率主要包括时间和空间两个方面。
### 效率与低存储量需求 
通俗的说，效率指的是算法执行的时间。对于同一个问题如果有多种算法可以解决，执行时间短的算法效率高。低存储量需求指的是算法执行工程中所需要的最大存储空间。

#### 渐进时间复杂度
一般情况下，算法中基本操作重复执行的次数是问题规模n的某个函数f(n)，算法的时间量度记作：

$$T(n)=O(f(n))$$
它表示随问题规模n的增大,算法执行时间的增长率和f(n)的增长率相同,称做算法的渐进时间复杂度,简称时间复杂度,语句的频度指的是该语句重复执行的次数.
举例:
```c
    (a){++x;s=0;}
    (b)for(i= 1;i<=n;++i){++x;s+=x;}
    (c)for (j=1;j<=n;++j)
        for(k=1;k<=n;++k){++x;s+=x;}
```
含基本操作”x增1”的语句频度分别为1、n和n2，则这三个程序段的时间复杂度分别为$O(1)$、$O(n)$、$O(n^2)$ 分别称为常量阶、线性阶和平方阶，算法可能还有对数阶$O(log_2 n)$、指数阶$O(2^n)$等。
##### 常见渐进时间复杂度比较:
$$ O(1)<O(log_2 n)<O(n)<O(nlog_2n)<O(n^2)<O(n^3) $$

> 影响算法的时间效率最主要的因素是`问题规模`
### 数据结构的基本概念

#### 数据 
数据，是对客观事务的符号表示,在计算机科学中是指所有能输入到计算机中并被计算机程序处理的符号的总称
#### 数据元素 
数据元素，是数据的基本单位,在计算机程序中通常作为一个整体进行考虑和处理
#### 数据对象
数据对象 是性质形体的数据元素的集合,是数据的一个子集

#### 什么是数据结构

数据结构 是相互直接存在一种或多种特定关系的数据元素的集合,这种数据元素相互之间的关系称为结构 ,根据数据元素之间关系的不同特性,通常有下列四类基本结构: 

 (1)集合 结构中的数据元素之间除了”属于同一个集合”的关系外,别无其他关系;
 (2)线性结构  结构中的数据元素之间存在一个对一个的关系;
 (3)树形结构 结构中的数据元素之间存在一个对多个的关系;
 (4)图状结构或网状结构 结构中的数据元素之间存在多个对多个的关系



物理结构 数据结构在计算机中的表示(又称映像)称为数据的物理结构,又称存储结构 

#### 元素/节点

在计算机中,我们可以用一个由若干位组合起来形成的一个位串表示一个数据元素(如果一个字长的位串表示一个整数,用8位二进制数表示一个字符等),通常称这个位串为元素或节点.当数据元素由若干数据项组成时,位串中对应于各个数据项的子位串称为数据域.因此,元素或节点可看成是数据元素在计算机中的印象.

####存储结构 (物理结构)

物理结构 数据结构在计算机中的表示(又称映像)称为数据的物理结构,又称存储结构 

数据元素之间的关系在计算机中有两种不同的表示方法:顺序映像和非顺序映像,并由此得到两种不同的存储结构:顺序存储结构和链式存储结构.顺序映像的特点是借助元素在存储器中的相对位置来表示数据元素之间的逻辑关系.非顺序映像的特点是借助指示元素存储地址的指针表示数据元素之间的逻辑关系.

#### 数据类型

数据类型是和数据结构密切相关的一个概念,他是最早出现在高级程序语言中,用以刻画(程序)操作对象的特性.

1\.原子类型：其值不可再分
2\.结构类型：可以在分解为若干分量
3\.抽象数据类型：抽象数据组织和与之相关的操作

>按’值’的不同特性,高级程序语言中的数据类型可分为两类:
1\.非结构的原子类型.原子类型的值是不可分解的,例如C语言中的基本类型(int/double…).
2\.结构类型 结构类型的值是由若干成分按某种结构组成的,因此是可以分解的,并且它的成分可以是非结构的,也可以说是结构的.

#### 抽象数据类型-ADT

抽象数据类型(Abstract Date Type,简称ADT)是指一个数学模型以及定义在该模型上的一组操作.
ADT按其值的不同特性,可细分为下列三种类型:
原子类型 属原子类型的变量的值是不可分解的.这类抽象数据类型比较少,因为一般情况下已有的固有数据类型足以满足需求.
固定聚合类型 属该类型的变量,其值由确定数目的成分按某种结构组成.
可变聚合类型 和固定聚合类型相比较,构成可变聚合类型’值’的成分的数目不确定

和数据结构的形式相对应,抽象数据类型可用以下三元组表示:
						$$(D.S.P)$$
D : 数据对象 S:   D上的关系集 P: 对D的基本操作集
##### 多形数据类型
多形数据类型是指其值的成分不确定的数据类型

### 线性表知识框架

* 线性表
    * 顺序存储
        * 顺序表
    * 链式存储
        * 单链表 （指针实现）
        * 双链表 （指针实现）
        * 循环链表 （指针实现）
        * 静态链表

### 数据结构算法常用设置

```c
//函数结果状态码
#define TURE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//Status 是函数的类型,其值是函数结果状态代码
typedef int Status;
```
#### 基本函数
```c
//求最大值 
max(表达式1,…,表达式n)
//求最小值 
min(表达式1,…,表达式n)
//求绝对值 
abs(表达式)
//求不足整数值 
floor(表达式)
//求进位整数值 
ceil (表达式)
//判定文件结束 
eof(文件变量) 或eof
//判定行结束 
eoln(文件变量) 或eoln
```



### 常见数据结构类型定义

#### 顺序表
```c
//静态分配
#define MaxSize 50
typedef struct {
    ElemType data[MaxSize];
    int length;
}SqList;
//动态分配
#define InitSize 100
typedef struct {
    ElemType *data;
    int MaxSize,length;
}SeqList;
//动态分配内存
L.data=(ElemType*)malloc(sizeof(ElemType*)InitSize);
```

#### 单链表
```c
typedef struct LNode {
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;
```
#### 静态链表
```c
#define MaxSize 50 
typedef struct {
    ElemType data;
    int next;
}SLinkList[MaxSize];
```

#### 顺序栈
```c
#define MaxSize 50
typedef struct {
    Elemtype data[MaxSize];
    int top;
} SqStack;
```
#### 链式栈
```c
typedef struct Linknode {
    ElemType data;
    struct Linknode *next;
} *LiStack;
```

#### 顺序队列
```c
#define MaxSize 50
typedef sturct {
    ElemType data[NaxSize];
    int front,rear;
}SqQueue;
```

#### 链式队列
```c
typedef struct {
    ElemType data;
    struct LinkNode *next;
}LinkNode;
typedef struct {
    LinkNode *front , *rear ;
} LinkQueue;
```

> 队列相关操作：

```
    初始： Q.front=Q.rear=0
    队头指针进1(出队)：Q.front=(Q.front+1)%MaxSize
    队尾指针进1(入队)：Q.rear=(Q.rear+1)%MaxSize
    队列长度：(Q.rear+MaxSize-Q.front)%MaxSize
    队列已满：(Q.rear+1)%MaxSize==Q.front;
    队空:Q.front==Q.rear
```

#### 二叉树
```c
typedef struct BiTNode{
    ElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
```
#### 线索二叉树
```c
typedef struct ThreadNode{
    ElemType data;
    struct BiTNode *lchild,*rchild;
} ThreadNode,*ThreadNode;
```
#### 图（邻接矩阵法）
```c
#define MaxVertexNum 100 //顶点数目的最大值
typedef char VertexType; //顶点的数据类型
typedef int EdgeType;  //带权图中边上权值的数据类型
typedef struct { 
    VertexType Vex[MaxVertexNum]; //顶点表
    EdgeType Edge[MaxVertex]; //邻接矩阵
    int vexnum,arcnum; //图的当前顶点数和弧度数
}MGragh;
```
#### 图（邻接表法）
```c
#define MaxVertexNum 100 //顶点数目的最大值
typedef struct ArcNode{ //边表节点
    int adjvex; //该弧所指向的顶点位置
    struct ArcNode *next; //指向下一条弧的指针
    //InfoType info; //网的边权值
}ArcNode;
typedef struct VNode{ //顶点表节点
    VertexType data; //顶点信息
    ArcNode *first;  //指向第一条依附该顶点的弧的指针
}VNode,AdjList[MaxVertexNum];
typedef struct { //邻接表
    AdjList vertices;
    int vexnum,arcnum;  //图的顶点数和弧数
}ALGraph; //ALGraph是以邻接表存储的图类型
```
