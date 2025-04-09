// Author: Kondius A.V.
// kondius@mail.ru, andreykondius@gmail.com
// 2024

#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include "putlog.hpp"
#include "putlog.h"

using namespace std::chrono_literals;

#ifdef __cplusplus

TEST(ConfigParseTest, PutLog)
{
    logrec::Putlog(logrec::LOG_INFO, "parameters = 1", "parameters = 2", "parameters = 3");
    logrec::Putlog(logrec::LOG_MESSAGE, "parameters = 1", "parameters = 2", "parameters = 3");
    logrec::Putlog(logrec::LOG_WARN, "parameters = 1", "parameters = 2", "parameters = 3");
    logrec::Putlog(logrec::LOG_ERROR, "parameters = 1", "parameters = 2", "parameters = 3");
    SUCCEED();
}

TEST(ConfigParseTest, StressTest)
{
    std::thread th1([](){
        for (auto i=0; i < 10000; ++i)
            logrec::Putlog(logrec::LOG_INFO, "Thread 1. Parameter i = ", i);
    });
    std::thread th2([](){
        for (auto i=0; i < 10000; ++i)
            logrec::Putlog(logrec::LOG_INFO, "Thread 2. Parameter i = ", i);
    });
    std::thread th3([](){
        for (auto i=0; i < 10000; ++i)
            logrec::Putlog(logrec::LOG_INFO, "Thread 3. Parameter i = ", i);
    });
    std::thread th4([](){
        for (auto i=0; i < 10000; ++i)
            logrec::Putlog(logrec::LOG_INFO, "Thread 4. Parameter i = ", i);
    });
    std::thread th5([](){
        for (auto i=0; i < 10000; ++i)
            logrec::Putlog(logrec::LOG_INFO, "Thread 5. Parameter i = ", i);
    });

    th1.detach();
    th2.detach();
    th3.detach();
    th4.detach();
    th5.detach();

    std::this_thread::sleep_for(3000ms);
    SUCCEED();
}

#else // C

TEST(ConfigParseTest, GetNameLogTest)
{
    for (auto i=0; i < 100000; ++i) {
        struct tm timeInfo = getTimeInTm();
        char buffer[512];
        getNameLog(timeInfo, buffer);
        std::string s_buf = buffer;
        EXPECT_FALSE(buffer[s_buf.size()-4] != '.' &&
                    buffer[s_buf.size()-3] != 't' &&
                    buffer[s_buf.size()-2] != 'x' &&
                    buffer[s_buf.size()-1] != 't');
    }
}

#endif
