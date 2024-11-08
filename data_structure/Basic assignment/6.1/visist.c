#include<stdio.h>
#include<stdlib.h>

#define Max_Size 10001

typedef struct TreeNode
{
    int lchild;
    int rchild;
}TreeNode;

TreeNode Tree[Max_Size];

//先序遍历
void Preorder(int Node)
{
    if(Node==0)
        return;
    else
    {
        printf("%d ",Node);
        Preorder(Tree[Node].lchild);
        Preorder(Tree[Node].rchild);
    }
}

//后序遍历
void Postorder(int Node)
{
    if(Node==0)
        return;
    else
    {
        Postorder(Tree[Node].lchild);
        Postorder(Tree[Node].rchild);
        printf("%d ",Node);
    }
}

//中序非遍历
void Inorder(int Node)
{
    int stack[Max_Size];
    int top=-1;
    while(Node!=0 || top!=-1)
    {
        //左孩子入栈
        while(Node!=0)
        {
            top++;
            stack[top]=Node;
            Node=Tree[Node].lchild;
        }
        //依次出栈
        Node=stack[top];
        top--;
        printf("%d ",Node);
        //在输出完左孩子以及根节点之后处理右孩子
        Node=Tree[Node].rchild;
    }
}

//遍历非递归
void Levelorder(int Node)
{
    //运用队列实现
    if(Node==0)
        return;
    int queue[Max_Size];
    int front=0,rear=0;
    queue[rear]=Node;
    rear++;

    while(front<rear)
    {
        int cur=queue[front];
        front++;
        printf("%d ",cur);
        if(Tree[cur].lchild!=0)
        {
            queue[rear]=Tree[cur].lchild;
            rear++;
        }
        if(Tree[cur].rchild!=0)
        {
            queue[rear]=Tree[cur].rchild;
            rear++;
        }
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    int lc,rc;
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&lc,&rc);
        Tree[i].lchild=lc;
        Tree[i].rchild=rc;
    }

    Preorder(1);
    printf("\n");
    Inorder(1);
    printf("\n");
    Postorder(1);
    printf("\n");
    Levelorder(1);
    printf("\n");
}