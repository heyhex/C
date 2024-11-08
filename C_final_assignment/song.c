#include"song.h"

//初始化
void Initial(SongList *S)
{
    //首先分配内存
    S->song=(Song*)malloc(sizeof(Song)*Initial_Size);
    //失败的话返回
    if(!S->song)
    {
        printf("Allocation Failure!\n");
        exit(0);
    }
    //初始化SongList的信息
    S->list_size=0;
}

//从文件中读入歌曲信息
void Import(SongList *S)
{
    char buffer[256];
	GetModuleFileNameA(NULL, buffer, sizeof(buffer));
	/*
	strrchr:函数功能：查找一个字符c在另一个字符串str中末次出现的位置
    （也就是从str的右侧开始查找字符c首次出现的位置），
	并返回这个位置的地址。如果未能找到指定字符，那么函数将返回NULL。
	使用这个地址返回从最后一个字符c到str末尾的字符串。                                                                  
	*/
	(strrchr(buffer, '\\'))[0] = 0; // 删除文件名，只获得路径字串//
    strcat(buffer,"\\SongList.txt");
    FILE *fp=fopen(buffer,"r");
    if(fp==NULL)
    {
        printf("File Open Error!\n");
        exit(0);
    }
    //当文件到达最大歌单容量的时候读入歌单数据
    int i=0;
    //fscnaf返回读取到的数目，只有当输入的数据为6个的时候才会存入歌单
    while(i<Initial_Size && fscanf(fp,"%s %s %s %s %d %d\n",
            S->song[i].name,
            S->song[i].singer,
            S->song[i].composer,
            S->song[i].lyricist,
            &S->song[i].freq,
            &S->song[i].time)==6)
    {   
        i++;
    }
    S->list_size=i;
    //关闭文件指针
    fclose(fp);
    printf("Success Import!\n");
}

//查找歌曲：通过不同的参数查找，返回找到的数目，并且记录在find_song里面
int FindByName(SongList S,char name[],Song find_song[])
{
    //遍历查找
    int i=0,length=S.list_size,num=0;
    for(i=0;i<length;i++)
        //依次匹配
        if(strcmp(name,S.song[i].name)==0)
        {
            find_song[num]=S.song[i];
            num++;
        }
    //判断是否找到
    if(num==0)
        printf("Not Found!\n");

    return num;
}

int FindBySinger(SongList S,char singer[],Song find_song[])
{
    //遍历查找
    int i,length=S.list_size,num=0;
    for(i=0;i<length;i++)
        if(strcmp(singer,S.song[i].singer)==0)
        {
            find_song[num]=S.song[i];
            num++;
        }
    //判断是否找到
    if(num==0)
        printf("Not Found!\n");

    return num;
}

int FindByComposer(SongList S,char composer[],Song find_song[])
{
    //遍历查找
    int i,length=S.list_size,num=0;
    for(i=0;i<length;i++)
        if(strcmp(composer,S.song[i].composer)==0)
        {
            find_song[num]=S.song[i];
            num++;
        }
    //判断是否找到
    if(num==0)
        printf("Not Found!\n");

    return num;
}

int FindByLyricist(SongList S,char lyricist[],Song find_song[])
{
    //遍历查找
    int i,length=S.list_size,num=0;
    for(i=0;i<length;i++)
        if(strcmp(lyricist,S.song[i].lyricist)==0)
        {
            find_song[num]=S.song[i];
            num++;
        }
    //判断是否找到
    if(num==0)
        printf("Not Found!\n");

    return num;
}

//通过调用Find总函数来实现不同方式的查找
int Find(SongList S,Song find_song[])
{
    //先提示用户进行选择
    printf("\n1.Find by name\n2.Find by singer\n");
    printf("3.Find by composer\n4.Find by lyricist\n");
    printf("Choose the way of search:");
    int state,num=0;
    char words[20];
    scanf("%d",&state);
    if(state==1)
    {
        printf("Enter the name: ");
        scanf("%s",words);
        //储存数目
        num=FindByName(S,words,find_song);
        if(num!=0)
        {
            //当找到值的话就进行打印
            printf("Success!\n");
            PrintSong(find_song,num);
        }
    }
    //下面情况均同state==1
    else if(state==2)
    {
        printf("Enter the singer: ");
        scanf("%s",words);
        num=FindBySinger(S,words,find_song);
        if(num!=0)
        {
            printf("Success!\n");
            PrintSong(find_song,num);
        }
    }
    else if(state==3)
    {
        printf("Enter the composer: ");
        scanf("%s",words);
        num=FindByComposer(S,words,find_song);
        if(num!=0)
        {
            printf("Success!\n");
            PrintSong(find_song,num);
        }
    }
    else if(state==4)
    {
        printf("Enter the lyricist: ");
        scanf("%s",words);
        num=FindByLyricist(S,words,find_song);
        if(num!=0)
        {
            printf("Success!\n");
            PrintSong(find_song,num);
        }
    }
    else
        printf("Wrong choice!\n");
    
    //最后返回num值，如果没有找到就是0
    return num;
}