
---
title:  Binary tree  of Data Structure
date: 2017-12-12 22:43:22
tags: Data Structure
---

## 树与二叉树

### 度
树中一个节点的子节点个数称为该`节点的度`，树中节点的最大度数称为`树的度`。
度大于0的节点称为`分支节点`(又称未终端节点)；度为0的节点称为叶子节点。

### 节点的深度、高度、层次

`节点层次`从树根开始定义，根节点为第一层，他的子节点为第二层，以此类推。  

`节点深度`是从根节点开始从顶向下逐层累加。  
 
`节点高度`是从叶子节点开始从底向上逐层累加。  

`树的高度`（又称深度）是从树中节点的最大层数。

### 树的性质
- 树中的节点数等于所有节点的度数加1.
- 度为m的树中第i层上至多有$m^{i-1}$个节点
- 高度为h的m叉树最多有$(m^h-1)/(m-1)$个节点
- 具有n个节点的m叉树的最小高度为:$\left \lceil log_m(n(m-1)+1) \right \rceil$

> Tips: 二叉树可以为空，但是树不能为空

### 二叉树
二叉树是有序树，一共有5种形态: 空二叉树、只有根节点、只有根节点和左孩子、只有根节点和右孩子、根节点和左孩子右孩子都有。


### 二叉树和度为2的树的区别

- 度为2的树至少有2个节点，二叉树可以为空
- 度为2的树的孩子节点的左右次序是相对而言的，而二叉树的左右孩子节点是确定的。

### 特殊的二叉树  
  

#### 1) 满二叉树 
一颗高度为n，并且有$2^h-1$个节点的二叉树称为满二叉树。
> 满二叉树的叶子节点全部集中在二叉树的最下一层并且除了叶子节点外q其余节点度数均为2。

#### 2) 完全二叉树
设一个高度为h，有n个节点的二叉树，当且仅当每一个节点都与高度为h的满二叉树中编号为1-n的节点一一对应时，称为完全二叉树。
### 二叉树的特点
- 非空二叉树是的叶子节点个数等于度为2的节点树加1,即$N_0=N_2+1$
- 非空二叉树是第K层上至多有$2^{k-1}$个节点
- 高度为H的二叉树至多有$2^H-1$个节点（$H\geq 1$）
- 节点i的双亲编号为$\left \lfloor i/2 \right \rfloor$，左右孩子的编号为2i,2i+1
- 节点i所在层次（深度）为$\left \lfloor log_2i \right \rfloor+1$
- 具有N个节点的完全二叉树的高度为$\left \lceil log_2(N+1) \right \rceil$ 或者 $\left \lfloor log_2N \right \rfloor+1$

### 二叉树的存储结构

根据二叉树的性质，完全二叉树和满二叉树采用顺序存储合适，但是其他二叉树采用顺序存储会有很多空节点，浪费存储空间，因此一般的二叉树采用链式存储。

节点结构：
|lchilld|data|rchild|
|--:|---|--:|


```c
//获取二叉树高度
//递归算法
int TreeDepth(BiTree T)
{
      if(!T){
        return 0;
      }
      int Left = TreeDepth(T->lchild); //先获取左子树高度
      int Right = TreeDepth(T->rchild); //获取右子树高度
      return (Left > Right) ? (Left + 1) : (Right + 1); //当前高度加上两边子树的最大值
}
//非递归
int TreeDepth(BiTree T){
    //last指向下一层第一个节点的位置
    int front = -1 ,rear = -1 ,last = 0 , level = 0;
    Queue Q[MaxSize],p;
    if(!T){
        return 0;
    }
    Q[++rear]=T; //根节点入队
    while(front<rear){ //如果队非空则循环
        p=Q[++front]; //队列元素出队，即正在访问的节点
        if(p->lchild){ //左孩子入队 
            Q[++rear]=p->lchild; 
        }
        if(p->rchild){ //右孩子入队
            Q[++rear]=p->rchild;
        }
        if(front==last){ //处理该层的最右节点
            level++; //层数增1
            last=rear++; //last指向下一层
        }
    }
    return level;
}
```

### 补充 * m叉树
一颗高为h的满m叉树的性质：
- 第i层有$m^{i-1}$个节点
- 在m叉树,节点i的第一个孩子编号为j=(i-1)*m+2,反之，节点i的父节点编号是：$\left \lfloor (i-2)/m \right \rfloor+1$
- 节点i的第K个孩子编号$(i-1)*m+k+1 (1\leq k \leq m)$
- 如果编号为i的节点有有右兄弟，那么应满足$i\leq \left \lfloor (i+m-2)/m \right \rfloor*m$

### 二叉树遍历

二叉树遍历一共有三种遍历:

- 先序遍历（NLR） 即`先序遍历根节点`
- 中序遍历（LNR）
- 后序遍历（LRN）
- 层序遍历 `(一层一层遍历)`

遍历算法：
- 递归：
```c
//先序遍历
void PreOrder(BiTree T){
    if(T!=NULL){
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}
//中序遍历
void InOrder(BiTree T){
    if(T!=NULL){
        PreOrder(T->lchild);
        visit(T);
        PreOrder(T->rchild);
    }
}
//后序遍历
void PostOrder(BiTree T){
    if(T!=NULL){
        PreOrder(T->lchild);
        PreOrder(T->rchild);
        visit(T);
    }
}
//层序遍历
//递归函数
void LevelNode(BiTree T,int level){ //此函数是用于输出level层节点的所有元素
    if (!T||level<1){
        return ;
    }
    if(level == 1){
        Visit[T];
    }
    LevelNode(T->lchild,level-1);
    LevelNode(T->rchild,level-1);
}
//主函数
void LevelOrder(BiTree T){
    int depth = Depth(T)，i;
    if (NULL==T){
        return ;
    }
    for(i=1;i<depth;i++){ //循环输出一层，二层，...，直到结束
        LevelNodeOrder(T,i);
    }
}
```
- 非递归：
```c
//先序遍历
void PreOrder(BiTree T){
    Stack S //创建栈
    InitStack(S); //初始化栈
    BiTree p=T; //p设置为遍历指针
    while(p||!IsEmpty(S)){
        //基本思想： 压栈，访问，跳转左子树
        //左子树访问完了判断栈是否空，非空弹栈，跳转右子树
        while(p){
            Push(S,p);
            visit(p);
            p=p->lchild;
        }
        if(!IsEmpty(S)){
            Pop(S,p);
            p->rchild;
        }
    }
}
//中序遍历
void InOrder(BiTree T){
    Stack S // 创建栈
    InitStack(S); //初始化栈
    BiTree p=T; //p设置为遍历指针
    while(p||!IsEmpty(S)){ //只要栈非空或者p非空进入循环
        //基本思想：不同于先序，访问的位置在弹栈之后
        //压栈，跳转左子树
        //否则弹栈访问，访问右子树
        if(p){   
            Push(S,p);
            p=p->child;
        }
        else{  //否则 根指针退栈，访问根节点，遍历右子树
            Pop(S,p);
            visit(p);
            p=p->rchild;
        }
    }
}
//后序遍历
void PostOrder(BiTree T){
    Stack S;
    InitStack(S);
    BiTree p=T,r=NULL;
    while(p||!IsEmpty(S)){
        if(p){
            Push(S,p);
            p=p->lchild;
        }
        else{
            GetTop(S,p);//取栈顶节点，但不弹出
            if(p->rchild && p=p->rchild!=r){ //右子树存在，且未被访问
                p=p->rchild; //转向右子树
                Push(S,p); //压栈
                p=p->lchild; //转向左子树
            }
            else{
                Pop(S,p); //否则弹出节点访问
                visit(p->data);
                r=p; //记录最近被访问过的节点
                p=NULL; //重置p
            }
        }
    }
}
//层序遍历
void LevelOrder(BiTree T){
    Queue Q;
    InitQueue(Q);
    BiTree p;
    EnQueue (Q,T); //根节点入队
    while(!IsEmpty(Q)){
        DeQueue(Q,p); //根节点出队
        visit(p); 
        if(p->lchild!=NULL){ 
            Enqueue(Q,p->lchild); //左子树非空，左子树入队
        }
        if(p->rchild!=NULL){
            Enqueue(Q,p->rchild); //右子树非空，右子树入队
        }
    }
}
```


### 树和森林的遍历对应关系

|树|森林|二叉树|
|--:|--:|--:|
|先根遍历|先序遍历|先序遍历|
|后根遍历|中序遍历|中序遍历|


### 线索二叉树
将遍历结果的前后驱关系存入二叉树中，二叉树中存在很多空指针，利用这些空指针用来存取二叉树遍历的前驱和后驱

节点结构：
|ltag|lchild|data|rchild|rtag|
|--:|--:|--:|--:|--:|

这里举个例子：
中序线索化二叉树
```c
void InThread(ThreadTree &p,ThreadTree &pre){
    if(p!=NULL){
        InThread(p->lchild,pre);//递归线索左子树
        if(p->lchild==NULL){//左子树为空，建立前驱线索
            p->lchild=pre;
            p->ltag=1;
        }
        if(pre!=NULL&&pre->rchild==NULL){ //建立前驱节点的后继线索
            pre->rchild=p;
            pre->rtag=1;
        }
        pre= p; //标记当前节点称为刚刚访问的节点
        InThread(p->rchild,pre); //递归，线索化右子树
    }
}
//主函数
void CreateThread(ThreadTree T){
    ThreadTree pre =NULL;
    if(T!=NULL){
        InTread(T,pre);
        pre->rchild=NULL;
        pre->rtag=1;
    }
}
```



### 二叉排序树 （BST）
二叉树排序树的特点：
左子树上所有节点的值均小于根节点的值，右子树上所有节点的值均大于根节点的值

#### BST查找
```c
BiTree Search (BiTree T ,ElemType key){
    BiTree p=T;
    if(!p){
        return 0; //return  NULL;
    }
    while(p||key!=p->data){
        if(key>p->data){
            p=p->rchild;
        }
        else{
            p=p-lchild;
        }
    }
    return p;
}
```

平均查找时间：$O(log_2{n})$
#### BST插入
```c
//非递归
int Insert (BiTree T,ElemType key){
    BiTree p=T;
    if(p){
        p=(BiTree)malloc(sizeof(BiTree));
        p->data=key;
        return p;
    }
    while(p){
        if(key>p->data){
            p=p->rchild;
        }
        else if(p->data==key){
            return NULL;
        }
        else{
            p=p->lchild;
        }
    }
    p=(BiTree)malloc(sizeof(BiTree));
    p->data=key;
    return p;
}
//递归
int Insert (BiTree T,ElemType key){
    BiTree p=T;
    if(p){
        p=(BiTree)malloc(sizeof(BiTree));
        p->data=key;
        return p;
    }
    else if(key>p->data){
        return Insert(p->rchild,key);
    }
    else if(key==p->data){
        return NULL;
    }
    else {
        return Insert(p->lchild,key);
    }
}
```
### 二叉平衡树(AVL树)
二叉平衡树满足两个条件：
- 必须是二叉树
- 二叉树上每个节点的左右子树高度之差不超过1

#### AVL树插入
- LL旋转：在节点A的左孩子的左子树插入新节点
- RR旋转：在节点A的右孩子的右子树插入新节点
- LR旋转：在节点A的左孩子的右子树插入新节点
- RL旋转：在节点A的右孩子的左子树插入新节点

#### AVL树的查找
假设以$ N_h $表示深度为h的平衡树中含有的最少的节点树，则：
$ N_0 = 0 , N_1 = 1 , N_2 =2 $
并且满足: $ N_h = N_{h-1} + N_{h-2}+1 $


### B树
B树又称多路平衡查找树，B树中所有的节点的孩子节点树的最大值称为B树的阶，通常使用m表示。
一棵m阶B树或为空树或为满足下面条件的树：
- 树中的每个节点至多有m棵子树，至多含有m-1个关键字
- 如果节点不是终端节点，那么至少有两颗树，至少一个关键字
- 除了根节点外的非叶子节点至少含有$ \left \lceil m/2  \right \rceil $  棵子树，至少含有$ \left \lceil m/2 \right \rceil - 1 $ 个关键字
- 所有叶子节点都在同一层，而且实际上这些节点不存在
- B树的所有节点的平衡因子都为0
#### B树的高度（磁盘存取次数）
B树的大部分操作所需的存盘次数跟B树的高度成正比
对于关键字个数为n的B树，叶子节点即查找不成功的节点为n+1
因此$ h \leq log_{ \left \lceil m/2  \right \rceil}(n+1)/2+1 $
#### B树的插入与删除
插入先定位插入位置，如果节点不满则插入，如果节点已满，则分裂节点，插入。
删除分三个情况：
- 直接删除关键字 直接删掉还是B树
- 兄弟够借 直接从兄弟借关键字，生成新节点
- 兄弟不够借 不够借则直接从双亲分裂再次合并节点
