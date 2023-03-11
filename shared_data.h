#ifndef SHARED_DATA_H
#define SHARED_DATA_H
#include <QStringList>
#include <QFile>

class SharedData
{
public:
    SharedData();
    static QFile audioSourceFile;
    static QStringList peopleList;
};

#endif // SHARED_DATA_H
