#include "shared_data.h"
#include <QTextStream>
#include <QFile>

QFile SharedData:: audioSourceFile;
QStringList SharedData:: peopleList;
const QString SharedData::HEADER_TEXT = "Celebrations!";
