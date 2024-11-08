#include"2.2.h"
#include<stdio.h>
#include<stdlib.h>

void Find_Delete(LinkList *L,int mink,int maxk)
{
    LinkList p=L;
    LinkList q=p->next;
    while(q)
    {
        if(q->data>mink && q->data<maxk)
        {
            p->next=q->next;
            free(q);
            q=p->next;
        }
        else
        {
            p=p->next;
            q=q->next;
        }
    }
}