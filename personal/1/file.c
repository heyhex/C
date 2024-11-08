#include<stdio.h>

struct list
{
    char name[20];
    int age;
    char number[20];
    struct list *next;
};

int main()
{
    while(1)
    {
        struct list *p;
        struct list *head;
        struct list *tail;
        int age;
        scanf("%d",&age);
        

        p=(struct list *)malloc(sizeof(struct list));





    }
   


    return 0;
}