#include "mainwindow.h"
#include "shared_data.h"
#include <QApplication>
#include <QRegularExpression>
#include <QFile>
#include <QDate>

void log(QFile &, QString);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile bdayFile;
    QFile logFile;
    bool bdays_loaded = false; //mandatory config section

    //first read the config file (same folder as .exe)
    QFile cfg_file(QCoreApplication::applicationDirPath() + "/config.cfg");
    if (!cfg_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //no config file, exit!
        return -1;
    }
    QTextStream in(&cfg_file);
    while (!in.atEnd()) {
        //[config_name = config_value]
        QList<QString> list = in.readLine().trimmed().split('=');
        if (list.size() != 2) {
            continue; //skip invalid format
        }
        list[0] = list[0].trimmed();
        list[1] = list[1].trimmed();
        if (list[0].isEmpty() || list[1].isEmpty())
            continue;
        QString settingKey = list[0];
        QString settingValue = list[1];
        QFile file_path(settingValue); //full path must be provided or the file name if file is in the same folder as the exe

        if (settingKey.compare("bday_file_path", Qt::CaseInsensitive) == 0) {
            if (!file_path.exists()) {
                settingValue = QCoreApplication::applicationDirPath() + "/" + list[1];
                QFile file(settingValue);
                if (!file.exists()) {
                    return -1;
                }
            }
            bdayFile.setFileName(settingValue);
            bdays_loaded = true;
        }
        //music is not mandatory, if not found then audioSourceFile is null -> will be ignored later
        else if (settingKey.compare("music_path", Qt::CaseInsensitive) == 0){
            if (!file_path.exists()) {
                settingValue = QCoreApplication::applicationDirPath() + "/" + list[1];
                QFile file(settingValue);
                if (file.exists())
                    SharedData::audioSourceFile.setFileName(settingValue);
            } else
                SharedData::audioSourceFile.setFileName(settingValue);
        }
        //log file is not mandatory, no checks here because if it does not exist -> will be created (later)
        else if (settingKey.compare("log_path", Qt::CaseInsensitive) == 0)
            logFile.setFileName(settingValue);
    }
    //bday file is mandatory
    if (!bdays_loaded)
        return -1;

    //open bday file
    bdayFile.open(QIODevice::ReadOnly | QIODevice::Text);
    //open logFile (creates it if it does not exist)
    if (!logFile.fileName().isNull()){
        if (logFile.exists())
            logFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
        else
            logFile.open(QIODevice::WriteOnly | QIODevice::Text);
    }

    //read bday file (main part)
    QTextStream inBday(&bdayFile);
    QRegularExpression dayFormat("\\d{1,2}/\\d{1,2}");
    while (!inBday.atEnd()) {
        QString line = inBday.readLine().simplified();
        QStringList list = line.split(' ');
        int day = -1, month = -1;
        //format checks
        if (list.size() < 2) {
            log(logFile, QString("Wrong birthday line : \' %1 \'\n").arg(line));
            continue;
        }
        //birthday check (should be number + dates should be valid)
        QRegularExpressionMatch match = dayFormat.match(list[list.size()-1]);
        if (!match.hasMatch()) {
            log(logFile, QString("Birthday should be a number! Line : \' %1 \'\n").arg(line));
            continue;
        }
        else {
            QStringList daysList = list[list.size()-1].split('/');
            day = daysList[0].toInt();
            month = daysList[1].toInt();
            if (day <= 0 || day >= 32 || month <= 0 || month > 12){
                log(logFile, QString("Birthday should be a valid number! Line : \' %1 \'\n").arg(line));
                continue;
            }
        }

        //date check, should be today's date (day+month should match)
        QStringList cd = QDate::currentDate().toString("d/M").split('/');
        if (cd[0].toInt() != day || cd[1].toInt() != month)
            //no match, continue to the next person
            continue;

        //all good, add the line text to the list of people (without the date)
        QString lineToShow;
        for(int i=0; i<list.size()-2; i++)
            lineToShow.append(list[i]).append(" ");
        lineToShow.append(list[list.size()-2]);
        SharedData::peopleList.append(lineToShow);
    }
    //close files
    if (audioSourceFile.isOpen())
        audioSourceFile.close();
    if (bdayFile.isOpen())
        bdayFile.close();
    if (logFile.isOpen())
        logFile.close();

    //create the GUI
    MainWindow w;
    w.show();
    w.setFixedSize(QSize(920, 385));
    // Load the application style
    QFile styleFile( ":/stylesheets/application.qss" );
    styleFile.open( QFile::ReadOnly );
    // Apply the stylesheet
    a.setStyleSheet(QString(styleFile.readAll()));

    return a.exec();
}

void log(QFile &logFile, QString log){
    if (logFile.isOpen())
        logFile.write(log.toUtf8());
}
