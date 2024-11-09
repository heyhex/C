#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <windows.h>

#define MY_MAX_PATH 512
#define MAX_FILES 1000

// 汇总HTML的模板
const char* SUMMARY_HTML_HEADER = 
"<!DOCTYPE html>\n"
"<html lang=\"zh-CN\">\n"
"<head>\n"
"    <meta charset=\"UTF-8\">\n"
"    <title>批量文件统计结果汇总</title>\n"
"    <style>\n"
"        body { \n"
"            font-family: \'Microsoft YaHei\', sans-serif; \n"
"            margin: 40px auto; \n"
"            max-width: 800px; \n"
"            line-height: 1.6; \n"
"            background: url(\"https://t.mwm.moe/pc\"); \n"
"            background-size: cover;\n"
"            background-attachment: fixed;\n"
"            min-height: 100vh;\n"
"        }\n"
"        .container { \n"
"            background: rgba(255, 255, 255, 0.7); \n"
"            backdrop-filter: blur(10px); \n"
"            -webkit-backdrop-filter: blur(10px); \n"
"            padding: 20px; \n"
"            border-radius: 8px; \n"
"            box-shadow: 0 4px 15px rgba(0,0,0,0.1); \n"
"            border: 1px solid rgba(255, 255, 255, 0.3); \n"
"        }\n"
"        h1 { \n"
"            color: #333; \n"
"            text-align: center; \n"
"        }\n"
"        .file-link { \n"
"            display: block; \n"
"            background: white; \n"
"            margin: 10px 0; \n"
"            padding: 15px; \n"
"            border-radius: 8px; \n"
"            text-decoration: none; \n"
"            color: #2196F3; \n"
"            transition: all 0.3s ease; \n"
"        }\n"
"        .file-link:hover { \n"
"            background: #e3f2fd; \n"
"            transform: translateY(-5px); \n"
"            box-shadow: 0 4px 8px rgba(0,0,0,0.1); \n"
"        }\n"
"        .process-time { \n"
"            color: #666; \n"
"            font-size: 0.9em; \n"
"            margin-left: 10px; \n"
"        }\n"
"    </style>\n"
"</head>\n"
"<body>\n"
"    <div class=\"container\">\n"
"        <h1>批量文件统计结果汇总</h1>\n";

const char* SUMMARY_HTML_FOOTER = 
"    </div>\n"
"</body>\n"
"</html>\n";

// 执行外部命令并返回执行时间
double executeCommand(const char* command) {
    // clock_t类型用于存储时间，在time.h头文件中定义
    clock_t start = clock();
    system(command);
    clock_t end = clock();
    // 计算执行时间，返回秒
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

// 创建result文件夹
void createResultFolder(const char* basePath) {
    char resultPath[MY_MAX_PATH];
    sprintf(resultPath, "%s/result", basePath);
    // CreateDirectory函数用于创建目录
    CreateDirectory(resultPath, NULL);
}

// 获取文件所在目录路径
void getDirectoryPath(const char* filePath, char* dirPath) {
    strcpy(dirPath, filePath);
    // strrchr函数用于获取字符串中最后一个斜杠或反斜杠的位置
    char* lastSlash = strrchr(dirPath, '/');
    // 如果lastSlash为空，则获取字符串中最后一个反斜杠的位置
    if (!lastSlash) lastSlash = strrchr(dirPath, '\\');
    // 如果lastSlash不为空，则将lastSlash的下一个字符设置为结束符
    if (lastSlash) {
        *(lastSlash + 1) = '\0';
    } else {
        // 如果lastSlash为空，则将dirPath设置为当前目录
        strcpy(dirPath, "./");
    }
}

// 处理单个文件
void processSingleFile(const char* filePath) {
    char command[MY_MAX_PATH * 3];
    double processTime;
    char dirPath[MY_MAX_PATH];
    int statisticMode, displayMode;
    
    // 选择统计程序模式
    printf("\n请选择统计模式：\n");
    printf("1. 详细模式（显示详细统计结果）\n");
    printf("2. 概要模式（仅显示文件路径）\n");
    printf("请输入选择（1-2）：");
    scanf("%d", &statisticMode);
    getchar(); // 清除换行符
    
    // 选择显示程序模式
    printf("\n请选择显示模式：\n");
    printf("1. 自动展示模式（自动打开浏览器）\n");
    printf("2. 静默模式（仅显示文件路径）\n");
    printf("请输入选择（1-2）：");
    scanf("%d", &displayMode);
    getchar(); // 清除换行符
    
    // 获取文件所在目录并创建result文件夹
    getDirectoryPath(filePath, dirPath);
    createResultFolder(dirPath);
    
    // 检查文件是否存在
    FILE* testFile = fopen(filePath, "r");
    if (!testFile) {
        printf("错误：无法打开文件 \"%s\"！\n", filePath);
        return;
    }
    fclose(testFile);

    // 调用子任务1，指定结果文件保存到result文件夹
    char resultPath[MY_MAX_PATH];
    char baseName[256];
    // 获取文件名
    char* lastSlash = strrchr(filePath, '/');
    if (!lastSlash) lastSlash = strrchr(filePath, '\\');
    // 将baseName设置为文件名，如果lastSlash不为空，则复制lastSlash的下一个字符到baseName，否则复制filePath到baseName
    strcpy(baseName, lastSlash ? lastSlash + 1 : filePath);
    char* dot = strrchr(baseName, '.');
    if (dot) *dot = '\0';
    // 生成结果文件路径
    sprintf(resultPath, "%sresult/%s_result.txt", dirPath, baseName);
    
    // 确保使用绝对路径调用statistic.exe
    char absResultPath[MY_MAX_PATH];
    _fullpath(absResultPath, resultPath, MY_MAX_PATH);

    // 根据选择的模式调用statistic.exe
    if (statisticMode == 1) {
        // 详细模式，传入-d参数
        sprintf(command, "statistic.exe \"%s\" \"%s\" -d", filePath, absResultPath);
    } else {
        // 概要模式
        sprintf(command, "statistic.exe \"%s\" \"%s\"", filePath, absResultPath);
    }
    processTime = executeCommand(command);
    printf("文件统计耗时：%.2f秒\n", processTime);

    // 检查结果文件是否生成
    testFile = fopen(resultPath, "r");
    if (!testFile) {
        printf("错误：统计结果文件未生成！\n");
        return;
    }
    fclose(testFile);

    // 根据选择的模式调用display.exe
    if (displayMode == 2) {
        // 静默模式，传入-s参数
        sprintf(command, "display.exe \"%s\" -s", resultPath);
    } else {
        // 自动展示模式，传入-a参数
        sprintf(command, "display.exe \"%s\" -a", resultPath);
    }
    processTime = executeCommand(command);
    printf("HTML生成耗时：%.2f秒\n", processTime);
}

// 处理文件夹中的所有文件
void processBatchFiles(const char* folderPath) {
    // DIR*类型用于打开目录，在dirent.h头文件中定义
    DIR* dir;
    // struct dirent*类型用于存储目录中的每个文件信息，在dirent.h头文件中定义
    struct dirent* entry;
    char filePaths[MAX_FILES][MY_MAX_PATH];
    char htmlPaths[MAX_FILES][MY_MAX_PATH];
    int fileCount = 0;
    double totalTime = 0;
    int statisticMode, displayMode;
    
    // 在开始处理前选择模式
    printf("\n请选择统计模式：\n");
    printf("1. 详细模式（显示详细统计结果）\n");
    printf("2. 概要模式（仅显示文件路径）\n");
    printf("请输入选择（1-2）：");
    scanf("%d", &statisticMode);
    getchar(); // 清除换行符
    
    printf("\n请选择显示模式：\n");
    printf("1. 自动展示模式（自动打开浏览器）\n");
    printf("2. 静默模式（仅显示文件路径）\n");
    printf("请输入选择（1-2）：");
    scanf("%d", &displayMode);
    getchar(); // 清除换行符
    
    // 创建result文件夹
    createResultFolder(folderPath);
    
    // opendir函数用于打开目录
    dir = opendir(folderPath);
    if (!dir) {
        printf("错误：无法打开指定的文件夹！\n");
        return;
    }

    // 收集所��txt文件
    // readdir函数用于读取目录中的每个文件
    while ((entry = readdir(dir)) != NULL) {
        // 如果文件名以.txt结尾
        if (strstr(entry->d_name, ".txt")) {
            char fullPath[MY_MAX_PATH];
            sprintf(fullPath, "%s/%s", folderPath, entry->d_name);
            // 将文件路径复制到filePaths数组中
            strcpy(filePaths[fileCount], fullPath);
            fileCount++;
        }
    }
    closedir(dir);

    if (fileCount == 0) {
        printf("错误：指定文件夹中未找到任何txt文件！\n");
        return;
    }

    // 处理每个文件，利用for循环完成
    for (int i = 0; i < fileCount; i++) {
        printf("\n正在处理文件 %d/%d：%s\n", i + 1, fileCount, filePaths[i]);
        
        char command[MY_MAX_PATH * 3];
        double processTime;
        char resultPath[MY_MAX_PATH];
        char baseName[256];
        //可以输入\\或/
        char* lastSlash = strrchr(filePaths[i], '/');
        if (!lastSlash) lastSlash = strrchr(filePaths[i], '\\');
        //如果lastSlash不为空，则复制lastSlash的下一个字符到baseName，否则复制filePaths[i]到baseName
        strcpy(baseName, lastSlash ? lastSlash + 1 : filePaths[i]);
        char* dot = strrchr(baseName, '.');
        if (dot) *dot = '\0';
        
        // 生成结果文件路径
        sprintf(resultPath, "%s/result/%s_result.txt", folderPath, baseName);
        
        // 调用统计程序
        if (statisticMode == 1) {
            // 详细模式，传入-d参数
            sprintf(command, "statistic.exe \"%s\" \"%s\" -d", filePaths[i], resultPath);
        } else {
            // 概要模式
            sprintf(command, "statistic.exe \"%s\" \"%s\"", filePaths[i], resultPath);
        }
        processTime = executeCommand(command);
        printf("文件统计耗时：%.2f秒\n", processTime);

        // 调用显示程序（始终使用静默式）
        sprintf(command, "display.exe \"%s\" -s", resultPath);
        processTime = executeCommand(command);
        printf("HTML生成耗时：%.2f秒\n", processTime);
        
        // 保存HTML路径用于汇总
        sprintf(htmlPaths[i], "%s/result/%s_result.html", folderPath, baseName);
    }

    // 生成汇总HTML
    char summaryPath[MY_MAX_PATH];
    sprintf(summaryPath, "%s/summary.html", folderPath);
    FILE* fp = fopen(summaryPath, "w");
    if (!fp) {
        printf("错误：无法创建汇总HTML文件！\n");
        return;
    }

    fprintf(fp, "%s", SUMMARY_HTML_HEADER);
    for (int i = 0; i < fileCount; i++) {
        // 获取HTML文件名
        char* htmlFileName = strrchr(htmlPaths[i], '/') ? strrchr(htmlPaths[i], '/') + 1 : htmlPaths[i];
        // 写入HTML文件路径
        fprintf(fp, "        <a href=\"result/%s\" class=\"file-link\">%s</a>\n", 
               htmlFileName, filePaths[i]);
    }
    fprintf(fp, "%s", SUMMARY_HTML_FOOTER);
    fclose(fp);

    // 根据选择的显示模式决定是否打开汇总HTML
    if (displayMode == 1) {
        char command[MY_MAX_PATH * 2];
        sprintf(command, "start %s", summaryPath);
        system(command);
    } else {
        char fullPath[MY_MAX_PATH];
        _fullpath(fullPath, summaryPath, MY_MAX_PATH);
        printf("\n已生成汇总html文件，文件路径为：%s\n", fullPath);
    }
}

void showMenu() {
    while (1) {
        printf("\n实验5程序：\n");
        printf("     1. 对单个英文文档进行统计\n");
        printf("     2. 对批量英文文档进行统计\n");
        printf("     0. 退出\n");
        printf("请输入您要执行的程序序号：");

        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("错误：请输入有效的数字！\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();

        if (choice == 0) {
            break;
        }

        char path[MY_MAX_PATH];
        switch (choice) {
            case 1:
                printf("请输入要统计的文件路径：");
                fgets(path, MY_MAX_PATH, stdin);
                path[strcspn(path, "\n")] = 0;
                processSingleFile(path);
                break;
            case 2:
                printf("请输入要统计的文件夹路径：");
                fgets(path, MY_MAX_PATH, stdin);
                path[strcspn(path, "\n")] = 0;
                processBatchFiles(path);
                break;
            default:
                printf("错误：无效的选择，请重新输入！\n");
        }
    }
}

int main() {
    showMenu();
    return 0;
} 