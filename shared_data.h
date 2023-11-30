#ifndef SHARED_DATA_H
#define SHARED_DATA_H
#include <QStringList>
#include <QFile>
#include <QString>

class SharedData
{
public:
    SharedData();
    static QFile audioSourceFile;
    static QStringList peopleList;
    static const QString HEADER_TEXT;
};

#endif // SHARED_DATA_H
