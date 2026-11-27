
#ifndef FILELOADER_H
#define FILELOADER_H

#include "../Castle/Castle.h"
#include "../EnemyLists/EnemyLists.h"

class FileLoader
{
public:
    static bool Load(const char* fileName, Castle& castle, EnemyLists& lists);
};

#endif
