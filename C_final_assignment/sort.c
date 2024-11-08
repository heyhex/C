#include"sort.h"

//SongExchange函数是交换两首歌的相关信息
void SongExchange(Song *song1,Song *song2)
{
    Song temp;
    strcpy(temp.name,song2->name);
    strcpy(song2->name,song1->name);
    strcpy(song1->name,temp.name);
    strcpy(temp.singer,song2->singer);
    strcpy(song2->singer,song1->singer);
    strcpy(song1->singer,temp.singer);
    strcpy(temp.composer,song2->composer);
    strcpy(song2->composer,song1->composer);
    strcpy(song1->composer,temp.composer);
    strcpy(temp.lyricist,song2->lyricist);
    strcpy(song2->lyricist,song1->lyricist);
    strcpy(song1->lyricist,temp.lyricist);
    temp.freq=song2->freq;
    song2->freq=song1->freq;
    song1->freq=temp.freq;
    temp.time=song2->time;
    song2->time=song1->time;
    song1->time=temp.time;
}

//第一种排序：按照名字顺序排列，seq=1代表顺序，seq=2代表逆序
void Sort_Name(SongList *S,int seq)
{
    if(seq==1)
    {
        //利用冒泡排序
        int len=S->list_size;
        for(int i=0;i<len;i++)
            for(int j=0;j<len-i-1;j++)
                if(strcmp(S->song[j].name,S->song[j+1].name)>0)
                    SongExchange(&(S->song[j]),&(S->song[j+1]));
    }
    else if(seq==2)
    {
        int len=S->list_size;
        for(int i=0;i<len;i++)
            for(int j=0;j<len-i-1;j++)
                if(strcmp(S->song[j].name,S->song[j+1].name)<0)
                    SongExchange(&(S->song[j]),&(S->song[j+1]));
    }
    printf("Success!\n");
    PrintList(*S);
}

//第二种排序：按照歌手顺序排列，seq=1代表顺序，seq=2代表逆序
void Sort_Singer(SongList *S,int seq)
{
    if(seq==1)
    {
        int len=S->list_size;
        for(int i=0;i<len;i++)
            for(int j=0;j<len-i-1;j++)
                if(strcmp(S->song[j].singer,S->song[j+1].singer)>0)
                    SongExchange(&(S->song[j]),&(S->song[j+1]));
    }
    else if(seq==2)
    {
        int len=S->list_size;
        for(int i=0;i<len;i++)
            for(int j=0;j<len-i-1;j++)
                if(strcmp(S->song[j].singer,S->song[j+1].singer)<0)
                    SongExchange(&(S->song[j]),&(S->song[j+1]));
    }
    printf("Success!\n");
    PrintList(*S);
}

//第三种排序：按照作曲家顺序排列，seq=1代表顺序，seq=2代表逆序
void Sort_Composer(SongList *S,int seq)
{
    if(seq==1)
    {
        int len=S->list_size;
        for(int i=0;i<len;i++)
            for(int j=0;j<len-i-1;j++)
                if(strcmp(S->song[j].composer,S->song[j+1].composer)>0)
                    SongExchange(&(S->song[j]),&(S->song[j+1]));
    }
    else if(seq==2)
    {
        int len=S->list_size;
        for(int i=0;i<len;i++)
            for(int j=0;j<len-i-1;j++)
                if(strcmp(S->song[j].composer,S->song[j+1].composer)<0)
                    SongExchange(&(S->song[j]),&(S->song[j+1]));
    }
    printf("Success!\n");
    PrintList(*S);
}

//第四种排序：按照作词家顺序排列，seq=1代表顺序，seq=2代表逆序
void Sort_Lyricist(SongList *S,int seq)
{
    if(seq==1)
    {
        int len=S->list_size;
        for(int i=0;i<len;i++)
            for(int j=0;j<len-i-1;j++)
                if(strcmp(S->song[j].lyricist,S->song[j+1].lyricist)>0)
                    SongExchange(&(S->song[j]),&(S->song[j+1]));
    }
    else if(seq==2)
    {
        int len=S->list_size;
        for(int i=0;i<len;i++)
            for(int j=0;j<len-i-1;j++)
                if(strcmp(S->song[j].lyricist,S->song[j+1].lyricist)<0)
                    SongExchange(&(S->song[j]),&(S->song[j+1]));
    }
    printf("Success!\n");
    PrintList(*S);
}

//通过调用总函数Sort来实现排序功能
void Sort(SongList *S)
{
    int state;
    int seq;
    //先提示用户输入
    printf("\n1.Sort by name\n2.Sort by singer\n");
    printf("3.Sort by composer\n4.Sort by lyricist\n");
    printf("Second enter:1.Sequential 2.Reversed\n");
    printf("Enter 2 number: ");
    scanf("%d %d",&state,&seq);
    if(seq<1 || seq>2 || state<1 || state>4)
        printf("Wrong Enter!\n");
    else if(state==1)
        Sort_Name(S,seq);
    else if(state==2)
        Sort_Singer(S,seq);
    else if(state==3)
        Sort_Composer(S,seq);
    else if(state==4)
        Sort_Lyricist(S,seq);
}