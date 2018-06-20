

---
title:  Graph traversal  of Data Structure
date: 2017-12-12 15:53:44
tags: Data Structure
---


## 图的遍历
- 广度优先搜索 （Breath-First-Search,BFS）
- 深度优先搜索 （Depth-First-Search,DFS）

### 常识

图：Graph (G)
顶点（节点）：Vertex (V)
边：Edge (E)

### BFS 广度优先搜索
```c
bool visited[MaxNum];
void BFSTraverse(Graph G){
    Queue Q;
    for(i=0;i<G.vexnum;++i){ //数组下标初始化
        visited[i]=False;
    }
    InitQueue Q;
    for(i=0;i<G.vexnum;++i){
        if(!visited[i]){ //对每个连通分量调用一次BFS
            BFS(G,i); //i如果没被访问，从i开始BFS
        }
    }
}

void BFS(Graph G,int v){
    visit(v);
    visited[v]=True;
    EnQueue(Q,v);
    while(!IsEmpty(Q)){
        DeQueue(Q,v);
        for(w=FirstNeighbour(G,v);w>=0;w=NextNeighbor(G,v,w)){
            if(!visited[w]){
                visit(w);
                visited[w]=True;
                EnQueue(Q,w);
            }
        }
    }
}
```
#### BFS 性能分析
> 空间复杂度：$O(|V|)$
> 时间复杂度：$O(|V|^2)$
### BFS算法求单源最短路径
```c
void min_Distance(Graph G,int u){
    //d[i]表示从u到i节点的最短路径
    for(i=0;i<G.vexnum;++i){
        d[i]=MaxSize; //初始化长度
    }
    visited[u]=True;
    d[u]=0;
    EnQueue(Q,u);
    while(!IsEmpty(Q)){
        DeQueue(Q,u);
        for(w=FirstNeighbour(G,u),w>=0;w=NextNeighbour(G,u,w)){
            if(!visited[w]){
                visited[w]=True;
                d[w]=d[u]+1;
                EnQueue(Q,w);
            }
        }
    }
}
```
### DFS 深度优先搜索
```c
bool visited[MaxNum];
void DFSTraverse(Graph G){
    for(v=0;v<G.vexnum;++v){
        visited[v]=False;
    }
    for(v=0;v<G.vexnum;++v){
        if(!visited[v]){
            DFS(G,v);
        }
    }
}

void DFS(Graph G,int v){
    visit(v);
    visited[v]=True;
    for(w=FirstNeighbour(G,v);w>=0;w=NextNeighbour(G,v,w)){
        DFS(G,w);
    }
}
```
#### DFS性能分析
> 空间复杂度： $O(|V|)$
> 时间复杂度： $O(|V|+|E|)$

## Hash表
### 散列函数的构造方法
- 直接地址法
H(key)=a*key+b
- 除留余数法
H(key)=key%p
- 数字分析法
如果关键字在某些位数上分布均匀，某些位置上分配不均匀，那么就选在分配均匀的若干位做位散列地址
- 平方取中法
取关键字的平均值的中间几位作为散列地址
- 折叠法
将关键字分割成位数相同的几部分，然后取这及部分的叠加作为散列地址

### 处理冲突的方法
1.开地址法
$ H_i = ( H( key )  + d_i)\%m $  ,其中i=1,2,3...k，m为散列表表长,di为增量序列
(1)线性探测法
发现被占往后存
(2) 平方探测法
$d_i = 1^2 ,-1^2,2^2,-2^2,...,k^2,-k^2  (k \leq m/2 )$其中m必须是一个可以表示成4k+3的质数。
(3) 再散列法
 $ d_i = Hash_2(key) $也称为双散列法
(4)伪随机序列法
di=伪随机序列
> 在开地址的情形下，不能随便物理删除已有元素，若删除则会截断与他具有相同的查找地址的元素的查找地址。所以如果想删除一个元素，就给他做删除标记，进行逻辑删除。副作用是表面上看起来散列表很满，但是有很多的位置没有利用。

2.拉链法

### 散列表查找性能分析

$ \alpha =  \frac{n}{m} $  其中n为表中记录数，m为散列表长度
