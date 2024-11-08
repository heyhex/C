#ifndef SONG_H
#define SONG_H

#define Initial_Size 100
#define Max_String_Length 20
#include"print.h"
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

//歌曲信息结构体
typedef struct Song
{
    char name[Max_String_Length];
    char singer[Max_String_Length];
    char composer[Max_String_Length];
    char lyricist[Max_String_Length];
    int freq;
    int time;
}Song;

//歌单结构体
typedef struct SongList
{
    //通过歌曲结构体数组首地址访问
    Song *song;
    int list_size;
}SongList;

void Initial(SongList *S);
void Import(SongList *S);
int FindByName(SongList S,char name[],Song find_song[]);
int FindBySinger(SongList S,char singer[],Song find_song[]);
int FindByComposer(SongList S,char composer[],Song find_song[]);
int FindByLyricist(SongList S,char lyricist[],Song find_song[]);
int Find(SongList S,Song find_song[]);

#endif