#ifndef PRINT_H
#define PRINT_H

#include"song.h"
#include <stdio.h>
struct Song;  // 前向声明
typedef struct Song Song;
struct SongList;
typedef struct SongList SongList;

void PrintSong(const Song* song, int num);
void PrintList(const SongList S);

#endif