
#ifndef FILELOADER_H
#define FILELOADER_H

#include "Castle.h"
#include "EnemyLists.h"

class FileLoader
{
public:
    static bool Load(const char* fileName, Castle& castle, EnemyLists& lists);
};

#endif
