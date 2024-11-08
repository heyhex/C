#include"management.h"

int Management(SongList *S)
{
    //首先初始化
    Initial(S);

    //进行基本的提示
    printf("**********************************\n");
    printf("    Welcome to SongList System    \n");
    printf("    何宇恒 23291139 计科2307       \n");
    printf("**********************************\n");
    
    char num;
    while(1)
    {
        //为了显示效果，暂停一秒钟
        Sleep(1000);
        //提示用户输入选择
        printf("----------------------------------\n");
        printf("    1. Import a Song List         \n");
        printf("    2. Print a Song List          \n");
        printf("    3. Find a Song                \n");
        printf("    4. Play a Song                \n");
        printf("    5. Sort the Song List         \n");
        printf("    0. Exit Program               \n");
        printf("----------------------------------\n");
        printf("Enter a Number:");
        scanf("%d",&num);
        switch (num)
        {
        case 1:
            //调用Import函数实现数据的读写
            Import(S);
            break;

        case 2:
            //调用PrintList打印整个歌单
            PrintList(*S);
            break;

        case 3:
            //为了后续操作方便，Find函数会传入一个找到的歌曲数组
            Song find_song[Initial_Size];
            Find(*S,find_song);
            break;

        case 4:
            //调用Play函数实现播放功能
            Play(*S);
            break;

        case 5:
            //调用Sort函数实现排序功能
            Sort(S);
            break;

        case 0:
            return 0;

        default:
            printf("Wrong number! Enter again:\n");
        }
    }
}