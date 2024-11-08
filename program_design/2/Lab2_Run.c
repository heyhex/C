#include"Lab2_Run.h"
#include"Lab2_Fun.c"
#include<stdio.h>

void Run(int argc, char *argv[])
{
    if(argc==1)
        Prompt();
    else if(argc==2)
        printf("Wrong Number of argument!\n");
    else if(argc==3)
    {
        if(Is_Legal(*argv[1]))
            Create(argv);
        else
            printf("Wrong case of Input\n");
    }
    else
        printf("Wrong Number of argument!\n");
    printf("End of Run!\n");
}