// Автор: Кондиус А.В.
// Класс-синглтон предназначенный для управления логированием
#pragma once
#include <assert.h>

#include "logrec.h"
#include <utility>
#include <mutex>
#include <memory>

class Logrec;

class SingltoneCollection
{
private:
    SingltoneCollection();
    ~SingltoneCollection();

    static SingltoneCollection inst;
    std::shared_ptr<Logrec> logfile = nullptr;
    static std::mutex mut;
public:
    SingltoneCollection(const SingltoneCollection &val) = delete;
    SingltoneCollection &operator=(const SingltoneCollection &val) = delete;

    static SingltoneCollection& instance();
    Logrec &getLogFile();
    void createLogFile();
    void closeLogFile();
    std::string truncateString(std::string string);
};

extern std::mutex mut;
