#include"4.2.c"

void Reverse(StringType *s)
{
    StringType result,temp;
    int len=StrLength(*s);
    result.ch=temp.ch=NULL;
    result.length=temp.length=0;
    while(len)
    {
        temp=SubString(*s,len,1);
        result=Concat(result,temp);
        len--;
    }
    StrAssign(s,result);
    
    if (temp.ch != NULL) 
        free(temp.ch);
    if (result.ch != NULL)
        free(result.ch);
}

int main()
{
    StringType s;
    char arr[10];
    printf("Enter a string:");
    scanf("%s",arr);
    s.ch=(char*)malloc(sizeof(char)*(strlen(arr)+1));
    s.length=strlen(arr);
    for(int i=0;i<s.length;i++)
    {
        s.ch[i]=arr[i];
    }
    s.ch[s.length]='\0';

    printf("Before: %s\n",s.ch);
    Reverse(&s);
    printf("After:%s\n",s.ch);

    return 0;
}