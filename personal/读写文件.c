/*#include<stdio.h>

void fileread()
{   //以只读的形式打开文件
    FILE *p=fopen("result.txt","r");
    //判断是否有这个文件
    if(p==NULL)
    {
        //perror会返回错误原因
        perror("Failed: ");
        return;
    }
    //foef判断是否为空字符
    while(!feof(p))
    {
        //fgetc读取字符
        char ch=fgetc(p);
        printf("%c",ch);
    }
    //fclose关闭文件
    fclose(p);
}

void filewrite()
{   //以只写的形式打开文件
    FILE *fp=fopen("result.txt","w");
    if(fp==NULL)
    {
        perror("Failed: ");
        return;
    }
    //写字符
    char ch=fputs("hehe",fp);
    //记得关闭！
    fclose(fp);
}

int main()
{
    filewrite();

    return 0;
}
*/

#include<stdio.h>
#include<math.h>

int main()
{
    FILE *fp=fopen("result.txt","w");
    if(fp==NULL)
        return 0;
    
    int num,sum;
    printf("Enter the number of x: ");
    scanf("%d",&num);
    for(int i=0;i<num;i++)
    {
        sum=pow(2,i);
        fscanf(fp,"%d\t",&i);
        fscanf(fp,"%d\n",&sum);
    }

    fclose(fp);
    return 0;
}