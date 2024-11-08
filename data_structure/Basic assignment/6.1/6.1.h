#ifndef TREE_H
#define TREE_H
#define TElemType int

//顺序存储
#define Max_Tree_Size 100
//0号单元储存根节点
typedef TElemType Sq_BiTree[Max_Tree_Size];

//链式存储
//二叉链表
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

//三叉链表
typedef struct TriTNode
{
    TElemType data;
    struct TriTNode *lchild,*rchild;
    struct TriTNode *parent;
}TriTNode,*TriTree;

//双亲链表
//结点类型
typedef struct BiPTNode
{
    TElemType data;
    int parent;
    char LRTag;
}BiPTNode;

//双亲类型
typedef struct BiPTree
{
    BiPTNode nodes[Max_Tree_Size];
    int num;
    int root;
}BiPTree;

#endif