#include "mainwindow.h"
#include <QApplication>
#include <QRegularExpression>
#include <QFile>
#include <QDate>
#include <INIReader.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //first read the config file (same folder as .exe)
    const INIReader inir((QCoreApplication::applicationDirPath() + "/config.ini").toStdString());
    if (inir.ParseError() < 0)
    {
        return -1;
    }

    const QString bdayFileName = QString::fromStdString(inir.Get("options", "bday_file_path", ""));
    const QString audioFileName = QString::fromStdString(inir.Get("options", "music_path", ""));
    if (bdayFileName.isEmpty())
        return -1;
    QFile bdayFile(bdayFileName);
    //bday file is mandatory, try to open it
    if (!bdayFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;

    //read bday file contents (main part)
    const QDate currentDate = QDate::currentDate();
    QStringList peopleList;
    QTextStream bdayStream(&bdayFile);
    while (!bdayStream.atEnd())
    {
        const QStringList lineParts = bdayStream.readLine().simplified().split(' ');
        if (lineParts.size() < 2)
            continue;
        const QDate parsedDate = QDate::fromString(lineParts.last(), "d/M");
        if (!parsedDate.isValid() || parsedDate.day() != currentDate.day() || parsedDate.month() != currentDate.month())
            continue;
        //all good, add the line text to the list of people (without the date)
        peopleList.append(lineParts.mid(0, lineParts.size() - 1).join(" "));
    }

    bdayFile.close();
    //if no bdays found -> don't show gui at all
    if (peopleList.isEmpty())
        return 0;

    //create the GUI
    MainWindow w(audioFileName, peopleList);
    w.show();
    w.setFixedSize(QSize(920, 371));
    QFile styleFile( ":/stylesheets/application.qss" );
    styleFile.open( QFile::ReadOnly );
    a.setStyleSheet(QString(styleFile.readAll()));
    return a.exec();
}
