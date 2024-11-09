#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 统计结构体
typedef struct {
    int words;          // 单词数
    int letters;        // 字母数
    int digits;         // 数字数
    int spaces;         // 空格数
    int newlines;       // 换行符数
    int punctuations;   // 标点符号数
    int others;         // 其他字符数
} Statistics;

// 写入统计结果到文件，并保存到resultPath路径下
void writeResults(const char* resultPath, const Statistics* stats, const char* inputPath) {
    FILE* fp = fopen(resultPath, "w");
    if (!fp) {
        printf("错误：无法创建结果文件！\n");
        return;
    }
    
    // 写入统计结果
    fprintf(fp, "统计结果报告\n");
    fprintf(fp, "====================\n");
    fprintf(fp, "输入文件：%s\n\n", inputPath);
    fprintf(fp, "1. 单词总数：%d\n", stats->words);
    fprintf(fp, "2. 字母总数：%d\n", stats->letters);
    fprintf(fp, "3. 数字字符数：%d\n", stats->digits);
    fprintf(fp, "4. 空格字符数：%d\n", stats->spaces);
    fprintf(fp, "5. 换行符数：%d\n", stats->newlines);
    fprintf(fp, "6. 标点符号数：%d\n", stats->punctuations);
    fprintf(fp, "7. 其他字符数：%d\n", stats->others);
    
    fclose(fp);
}

// 打印详细统计结果
void printDetailedResults(const Statistics stats) {
    printf("\n详细统计结果：\n");
    printf("====================\n");
    printf("1. 单词总数：%d\n", stats.words);
    printf("2. 字母总数：%d\n", stats.letters);
    printf("3. 数字字符数：%d\n", stats.digits);
    printf("4. 空格字符数：%d\n", stats.spaces);
    printf("5. 换行符数：%d\n", stats.newlines);
    printf("6. 标点符号数：%d\n", stats.punctuations);
    printf("7. 其他字符数：%d\n", stats.others);
}

// 统计文件内容
void analyzeFile(const char* inputPath, const char* resultPath, int detailMode) {
    FILE* fp = fopen(inputPath, "r");
    if (!fp) {
        printf("错误：无法打开输入文件！\n");
        return;
    }
    
    // 初始化统计结果
    Statistics stats = {0};
    int inWord = 0;
    int c;
    
    // 读取文件内容并统计
    while ((c = fgetc(fp)) != EOF) {
        // 判断字符是否为字母
        if (isalpha(c)) {
            stats.letters++;
            // 判断是否为单词的开始
            if (!inWord) {
                stats.words++;
                inWord = 1;
            }
        } 
        // 判断字符是否为数字
        else if (isdigit(c)) {
            stats.digits++;
            inWord = 0;
        } 
        // 判断字符是否为空格
        else if (isspace(c)) {
            if (c == '\n') {
                stats.newlines++;
            } else if (c == ' ') {
                stats.spaces++;
            }
            // 让inWord为0，表示当前不是单词
            inWord = 0;
        } 
        // 判断字符是否为标点符号
        else if (ispunct(c)) {
            stats.punctuations++;
            inWord = 0;
        } 
        // 其他字符
        else {
            stats.others++;
            inWord = 0;
        }
    }
    
    fclose(fp);
    
    // 写入结果文件
    writeResults(resultPath, &stats, inputPath);
    
    // 根据模式输出结果，detailMode为1时输出详细结果，否则输出简要结果
    if (detailMode) {
        printDetailedResults(stats);
    } 
    else {
        char fullPath[512];
        // _fullpath()函数用于获取文件的绝对路径
        _fullpath(fullPath, resultPath, sizeof(fullPath));  // 只使用Windows的API
        printf("\n已完成\"%s\"文件的统计，统计结果保存在文件\"%s\"中！\n", 
               inputPath, fullPath);
    }
}

int main(int argc, char* argv[]) {
    // 检查参数是否正确
    if (argc < 2) {
        printf("使用方法：%s <输入文件路径> [输出文件路径] [-d]\n", argv[0]);
        printf("选项：\n");
        printf("  -d    详细模式（显示详细统计结果）\n");
        return 1;
    }
    
    // 获取输入文件路径
    const char* inputPath = argv[1];
    // 获取输出文件路径
    const char* resultPath = (argc > 2 && argv[2][0] != '-') ? argv[2] : NULL;
    // 判断是否为详细模式
    int detailMode = (argc > 2 && strcmp(argv[argc-1], "-d") == 0);
    
    char defaultResultPath[512];
    if (!resultPath) {
        // 如果没有指定输出路径，使用默认路径
        char* lastSlash = strrchr(inputPath, '/');
        if (!lastSlash) lastSlash = strrchr(inputPath, '\\');
        
        // 获取文件名
        char baseName[256] = {0};
        if (lastSlash) {
            strcpy(baseName, lastSlash + 1);
        } else {
            strcpy(baseName, inputPath);
        }
        
        // 获取文件名中的点
        char* dot = strrchr(baseName, '.');
        if (dot) *dot = '\0';
        
        // 生成默认的输出文件路径
        sprintf(defaultResultPath, "%s_result.txt", baseName);
        resultPath = defaultResultPath;
    }
    
    // 调用analyzeFile函数进行统计
    analyzeFile(inputPath, resultPath, detailMode);
    
    return 0;
}
