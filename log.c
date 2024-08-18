#pragma once

#include <stdio.h>
#include <sys/types.h>    
#include <sys/stat.h>    
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#define LOG_PATH "./my_freertos.log" 
#define LOG_BUFFER_SIZE 512
int fd;
void logInit()
{
    fd = open(LOG_PATH, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(fd < 0){
        perror("logInit fail");
        return;
    }
}

void logExit()
{
    close(fd);
}

void logWrite(const char * buf, int size)
{
    int ret = write(fd, buf, size);
    if(ret < 0) {
        perror("logWrite fail");
        close(fd);
        return;
    }
    printf(buf);
}

void pr_debug(const char *format, ...)
{
    char buf[LOG_BUFFER_SIZE] = {0};
    int ret; 
    time_t rawtime;
    struct tm * timeinfo;
    va_list args; // 定义可变参数列表
    va_start(args, format); // 初始化可变参数列表

    // 获取当前时间
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    ret = snprintf(buf, sizeof(buf), "Time: %s", asctime(timeinfo));  // asctime会加一个换行符
    ret += snprintf(buf + ret - 1, sizeof(buf), ", ");
    ret += vsnprintf(buf + ret - 1, sizeof(buf) - ret, format, args);
    
    logWrite(buf, ret - 1);
    va_end(args); 
}