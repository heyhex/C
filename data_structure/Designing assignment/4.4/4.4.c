#include"4.2.c"

void Find_In_s_Not_In_t(StringType s,StringType t)
{
    StringType r;
    r.ch=(char*)malloc(sizeof(char)*(s.length)+1);
    if(!r.ch)
        exit(1);
    r.length=0;

    //分别记录他所在的位置，t当中的字符以及是否在r当中
    int position[256]={0};
    int char_t[256]={0};
    int char_r[256]={0};

    //遍历t，标记在t当中的字符：char_t[i]=1,表示字符i在t里面
    for(int i=0;i<t.length;i++)
    {
        char_t[t.ch[i]]=1;
    }

    //遍历s，找到在s不在t的字符
    for(int i=0;i<s.length;i++)
    {
        char cur=s.ch[i];
        if(!char_r[cur] && !char_t[cur])
        {
            //添加该字符
            r.ch[r.length]=cur;
            //记录位置
            position[r.length]=i+1;
            //并且记录该字符已经存入r当中
            char_r[cur]=1;
            r.length++;
        }
    }
    r.ch[r.length]='\0';
    //打印输出
    printf("result: %s\n",r.ch);
    for(int i=0;i<r.length;i++)
    {
        printf("'%c' appear at position %d\n",r.ch[i],position[i]);
    }
}

int main()
{
    StringType s,t;
    char arr1[10];
    char arr2[10];
    printf("Enter String \'s\': ");
    scanf("%s",arr1);
    printf("Enter String \'t\': ");
    scanf("%s",arr2);
    s.ch=(char*)malloc(sizeof(char)*(strlen(arr1)+1));
    t.ch=(char*)malloc(sizeof(char)*(strlen(arr2)+1));
    strcpy(s.ch,arr1);
    strcpy(t.ch,arr2);
    s.length=strlen(arr1);
    t.length=strlen(arr2);

    Find_In_s_Not_In_t(s,t);

    return 0;
}