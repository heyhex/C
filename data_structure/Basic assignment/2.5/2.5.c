#include<stdio.h>
#include"2.5.h"

void Reverse(Linklist *L)
{
    Linklist p,q;
    p=(*L)->next;
    (*L)->next=NULL;
    while(p)
    {
        q=p;
        p=p->next;
        //先移动后继再移动前驱
        q->next=(*L)->next;
        (*L)->next=q;
    }
}