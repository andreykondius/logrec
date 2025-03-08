#include "SingltoneCollection.h"
#include <string>
#define WIN32

SingltoneCollection SingltoneCollection::inst;
std::mutex mut;

SingltoneCollection::SingltoneCollection()
{
}

SingltoneCollection::~SingltoneCollection()
{
}

Logrec &SingltoneCollection::getLogFile()
{
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
    return inst;
}

void SingltoneCollection::closeLogFile()
{
    SingltoneCollection::instance().logfile->closeAll();
}

std::string SingltoneCollection::truncateString(const std::string &str)
{
    auto numLastSlash = str.rfind('\\');
    return str.substr(numLastSlash + 1);
}
