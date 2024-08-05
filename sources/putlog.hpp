// Author: Kondius A.V.
// kondius@mail.ru, andreykondius@gmail.com
// 2024

#include <stdio.h>
#include <time.h>
// #define NOLOG

enum LogLevel
{
    I,
    LOG_INFO,
    LOG_MESSAGE,
    LOG_WARN,
    LOG_ERROR
} ;

#ifdef __cplusplus
#include "logrec.h"
#include "SingltoneCollection.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define Putlog(LogLevel,...) PutlogCPP(__FILE__ , __FUNCTION__ , TOSTRING(__LINE__) , LogLevel , __VA_ARGS__ )

inline void print(){}
template<typename T11, typename ... Tnn>
void print(const T11& beg, const Tnn& ... val)
{
    SingltoneCollection::instance().getLogFile().getFileLog() << beg<<" ";
    print(val ...);
}

template<typename T1, typename ... Tn>
void PutlogCPP(const std::string &name, const std::string &fo, const std::string &line, LogLevel level, const T1& beg, const Tn&...val)
{
#ifndef NOLOG
    std::lock_guard<std::mutex> lock(mut);
    SingltoneCollection::instance().createLogFile();
    SingltoneCollection::instance().getLogFile().open();
    if(level != I)
    {
        SingltoneCollection::instance().getLogFile().getFileLog() << SingltoneCollection::instance().getLogFile().getDataFromFormat("%H:%M:%S ");
        SingltoneCollection::instance().getLogFile().getFileLog() << "[" << SingltoneCollection::instance().truncateString(name) << ", "<<fo<<":"<<line<<"] ";
    }
    if(level == LOG_INFO)
    {
        SingltoneCollection::instance().getLogFile().getFileLog() <<"LOG_INFO"<<": ";
    }
    else if(level == LOG_WARN)
    {
        SingltoneCollection::instance().getLogFile().getFileLog() <<"LOG_WARN"<<": ";
    }
    else if(level == LOG_MESSAGE)
    {
        SingltoneCollection::instance().getLogFile().getFileLog() <<"LOG_MESSAGE"<<": ";
    }
    else if(level == LOG_ERROR)
    {
        SingltoneCollection::instance().getLogFile().getFileLog() <<"LOG_ERROR"<<": ";
    }
    else if(level != I)
    {
        SingltoneCollection::instance().getLogFile().getFileLog() <<"LOG_INFO"<<": ";
    }

    print(beg,val...);
    SingltoneCollection::instance().getLogFile().getFileLog() << std::endl;
    SingltoneCollection::instance().getLogFile().close();
#endif
}

#else // C
#pragma once
#include "putlog.h"
#include <stdarg.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define Putlog(LogLevel,...) PutlogC(__FILE__ , __FUNCTION__ , LogLevel , __VA_ARGS__ , NULL)

static void getNameLog(struct tm timeInfo, char *buffer)
{
    char name[512];
    snprintf(name, 512, "%s%s%s", nameLogDir, LogFormat, ".txt");
    strftime(buffer, 512, name, &timeInfo);
}

static  struct tm getTimeInTm()
{
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime_r(&rawtime);
    return *timeinfo;
}

static pthread_mutex_t mutLogrec_c;

//FILE* openLog( const char* name);
//char* truncateString(const char str[256]);
static FILE* openLog( const char* name)
{
    FILE* pFile;
    const char* filename = name;
    pFile = fopen(filename, "ab+");
    if( pFile==NULL)
    {
       fprintf(stderr,"Error: Cannot open file: %s\n",filename);
       return NULL;
    }
    else
    {
        return pFile;
    }
}

static char* truncateString(const char* str)
{
    char* shortName = strrchr(str,'\\');
    static char name[1024] = {"\0"};
    strcpy(name, shortName + 1);
    return name;
}

static void PutlogC( char* file, char* func, int type, char* msg, ... )
{
#ifndef NOLOG
    pthread_mutex_lock(&mutLogrec_c);
    struct tm timeInfo = getTimeInTm();
    char buffer[512];
    getNameLog(timeInfo, buffer);
    FILE* log = openLog(buffer);
    char* str;
    va_list vl;
    str = msg;
    va_start(vl, msg);
    fprintf (log,"%02d:%02d:%02d [", timeInfo.tm_hour,timeInfo.tm_min,timeInfo.tm_sec);
    fprintf (log,"%s ",truncateString(file));
    fprintf (log,"%s] ",func);

    if(type == LOG_INFO)
    {
        fprintf (log,"%s ","LOG_INFO:");
    }
    else if(type == LOG_MESSAGE)
    {
        fprintf (log,"%s ","LOG_MESSAGE:");
    }
    else if(type == LOG_WARN)
    {
        fprintf (log,"%s ","LOG_WARN:");
    }
    else if(type == LOG_ERROR)
    {
        fprintf (log,"%s ","LOG_ERROR:");
    }
    else
    {
        fprintf (log,"%s ","LOG_INFO:");
    }

    while (str!=NULL)
    {
        fprintf (log,"%s",str);
        str=va_arg(vl,char*);
    }
    fprintf (log,"\n");
    va_end(vl);
    fclose(log);
    pthread_mutex_unlock(&mutLogrec_c);
#endif
}

#endif


