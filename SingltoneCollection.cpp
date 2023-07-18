#include "SingltoneCollection.h"
#include <string>
#define WIN32

SingltoneCollection SingltoneCollection::inst;
std::mutex SingltoneCollection::mut;
std::mutex mut;

SingltoneCollection::SingltoneCollection()
{
}

SingltoneCollection::~SingltoneCollection()
{
    closeLogFile();
}

Logrec &SingltoneCollection::getLogFile()
{
    std::lock_guard<std::mutex> lock(mut);
    if (!logfile)
        logfile = std::make_shared<Logrec>();
    return *logfile;
}

void SingltoneCollection::createLogFile()
{
    if (!logfile)
        logfile = std::make_shared<Logrec>();
}

SingltoneCollection &SingltoneCollection::instance()
{
    std::lock_guard<std::mutex> lock(mut);
    return inst;
}

void SingltoneCollection::closeLogFile()
{
    std::lock_guard<std::mutex> lock(mut);
    inst.logfile = nullptr;
}

std::string SingltoneCollection::truncateString(std::string str)
{
    auto numLastSlash = str.rfind('\\');
    return str.substr(numLastSlash + 1);
}
