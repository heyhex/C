#include"play.h"

//播放音乐
int Play(const SongList S)
{
    //用play_song[]来存储要播放的歌的信息
    Song play_song[Initial_Size];
    printf("First find the song!\n");
    //Find函数返回找到的歌的数量
    int num=Find(S,play_song);
    if(num)
    {
        for(int i=0;i<num;i++)
        {
            //暂停1秒再播放
            Sleep(1000);
            printf("Song NO.%d is playing\n",i+1);
            Beep(play_song[i].freq,play_song[i].time);
        }
        printf("End of play!\n");
        return 1;
    }
    else
    {
        printf("Fail to Play!\n");
        return 0;
    }
}