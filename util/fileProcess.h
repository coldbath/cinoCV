#pragma once
#include <fstream>
#include <iostream>

#ifdef WIN32
#include <dirent/dirent.h>
#include <direct.h>
#ifndef PATH_MAX
#define PATH_MAX MAX_PATH
#endif
#else
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#endif

namespace cino
{
    int createDirectory(std::string directoryPath);

    int copyFile(std::string srcPath, std::string dstPath);
} // namespace cino
