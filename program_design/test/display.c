#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_PATH 512

// HTML模板
const char* HTML_HEADER = 
"<!DOCTYPE html>\n"
"<html lang=\"zh-CN\">\n"
"<head>\n"
"    <meta charset=\"UTF-8\">\n"
"    <title>文件统计结果</title>\n"
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
"        .stats-item { \n"
"            background: white; \n"
"            margin: 10px 0; \n"
"            padding: 15px; \n"
"            border-radius: 8px; \n"
"            transition: all 0.3s ease; \n"
"        }\n"
"        .stats-item:hover { \n"
"            background: white; \n"
"            transform: translateY(-5px); \n"
"            box-shadow: 0 4px 8px rgba(0,0,0,0.1); \n"
"        }\n"
"        .divider { \n"
"            border-top: 2px solid #ddd; \n"
"            margin: 20px 0; \n"
"        }\n"
"    </style>\n"
"</head>\n"
"<body>\n"
"    <div class=\"container\">\n";

// HTML尾部
const char* HTML_FOOTER = 
"    </div>\n"
"</body>\n"
"</html>\n";

// 生成HTML文件名
void generateHtmlFilename(const char* resultPath, char* htmlPath) {
    char baseName[256] = {0};
    strcpy(baseName, resultPath);
    // strrchr函数用于获取文件名中的点
    char* dot = strrchr(baseName, '.');
    if (dot) *dot = '\0';
    // 生成HTML文件名
    sprintf(htmlPath, "%s.html", baseName);
}

// 打开浏览器显示HTML文件
void openBrowser(const char* htmlPath) {
    char command[MAX_PATH + 10];
    sprintf(command, "start %s", htmlPath);
    // system函数用于执行命令打开网页
    system(command);
}

// 获取文件名（不含路径和扩展名）
void getBaseName(const char* filePath, char* baseName) {
    // 获取文件名（不含路径），strrchr函数用于获取文件名中的最后一个斜杠或反斜杠
    //strrchr返回的是一个指针，指向最后一个斜杠或反斜杠
    const char* fileName = strrchr(filePath, '/');
    if (!fileName) fileName = strrchr(filePath, '\\');
    //当fileName为空时，fileName指向filePath，不为空时，fileName指向最后一个斜杠或反斜杠的下一个字符
    fileName = fileName ? fileName + 1 : filePath;
    
    // 复制文件名并去除扩展名
    strcpy(baseName, fileName);
    char* dot = strrchr(baseName, '.');
    if (dot) *dot = '\0';
}

// 将统计结果转换为HTML
void convertToHtml(const char* resultPath, const char* htmlPath, int autoOpen) {
    FILE* inFile = fopen(resultPath, "r");
    if (!inFile) {
        printf("无法打开结果文件：%s\n", resultPath);
        return;
    }

    FILE* outFile = fopen(htmlPath, "w");
    if (!outFile) {
        printf("无法创建HTML文件：%s\n", htmlPath);
        fclose(inFile);
        return;
    }

    // 获取文件名
    char baseName[256];
    getBaseName(resultPath, baseName);

    // 写入HTML头部，使用HTML_HEADER常量
    fprintf(outFile, "%s", HTML_HEADER);

    char line[MAX_LINE];
    int inStats = 0;

    while (fgets(line, sizeof(line), inFile)) {
        line[strcspn(line, "\n")] = 0;
        
        if (strstr(line, "====================")) {
            fprintf(outFile, "        <div class=\"divider\"></div>\n");
            continue;
        }

        if (strstr(line, "统计结果报告")) {
            fprintf(outFile, "        <h1>%s - 统计结果</h1>\n", baseName);
        } else if (strstr(line, "输入文件：")) {
            fprintf(outFile, "        <div class=\"stats-item\">%s</div>\n", line);
        } else if (line[0] >= '1' && line[0] <= '7') {
            fprintf(outFile, "        <div class=\"stats-item\">%s</div>\n", line);
        }
    }

    // 写入HTML尾部，使用HTML_FOOTER常量
    fprintf(outFile, "%s", HTML_FOOTER);

    fclose(inFile);
    fclose(outFile);

    char fullPath[MAX_PATH];
    _fullpath(fullPath, htmlPath, MAX_PATH);

    if (autoOpen) {
        openBrowser(fullPath);
    } else {
        printf("已生成html文件，文件路径为：%s\n", fullPath);
    }
}

int main(int argc, char* argv[]) {
    // 判断是否输入了结果文件路径
    if (argc < 2) {
        printf("使用方法：%s <结果文件路径> [-s]\n", argv[0]);
        printf("选项：\n");
        printf("  -s    静默模式（不自动打开浏览器）\n");
        return 1;
    }

    const char* resultPath = argv[1];
    //如果argc大于2，并且argv[2]等于-s，则将silentMode设置为1，否则设置为0
    int silentMode = (argc > 2 && strcmp(argv[2], "-s") == 0);
    
    // 生成HTML文件名
    char htmlPath[MAX_PATH];
    generateHtmlFilename(resultPath, htmlPath);
    
    // 将统计结果转换为HTML，!silentMode用于判断是否自动打开浏览器
    convertToHtml(resultPath, htmlPath, !silentMode);
    
    return 0;
} 