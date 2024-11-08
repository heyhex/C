#include"print.h"

//打印歌曲信息：传入歌曲数组以及个数来进行打印
void PrintSong(const Song *song, int num)
{
    printf("********************************************************************\n");
    printf("%-20s%-20s%-20s%-20s\n","Name","Singer","Composer","Lyricist");
    for(int i=0;i<num;i++)
        printf("%-20s%-20s%-20s%-20s\n",song[i].name,song[i].singer,song[i].composer,song[i].lyricist);
    printf("********************************************************************\n");
}

//打印歌单就直接传入歌单
void PrintList(const SongList S)
{
    int length=S.list_size;

    printf("********************************************************************\n");
    printf("%-20s%-20s%-20s%-20s\n","Name","Singer","Composer","Lyricist");
    for(int i=0;i<length;i++)
        printf("%-20s%-20s%-20s%-20s\n",S.song[i].name,S.song[i].singer,S.song[i].composer,S.song[i].lyricist);
    printf("********************************************************************\n");
}