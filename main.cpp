#include "mainwindow.h"
#include "appsettings.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    bool bdays_loaded = false; //mandatory config section

    //first read the config file (same folder as .exe)
    QFile cfg_file(QCoreApplication::applicationDirPath() + "/config.cfg");
    if (!cfg_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //TODO, na anoigei h efarmogh ws "empty" xwris MUSIC ktl kai na afhnei new bday/nameday gia EXPORT (h IMPORT)
    }
    else {
        QTextStream in(&cfg_file);
        while (!in.atEnd()) {
            //[config_name = config_value]
            QList<QString> list = in.readLine().trimmed().split('=');
            if (list.size() != 2) {
                continue; //skip invalid format
            }
            list[0] = list[0].trimmed();
            list[1] = list[1].trimmed();
            QString settingKey = list[0];
            QString settingValue = list[1];
            QFile file_path(settingValue); //full path must be provided or the file name if file is in the same folder as the exe

            if (!file_path.exists()) {
                settingValue = QCoreApplication::applicationDirPath() + "/" + list[1];
                QFile file(settingValue);
                if (!file.exists()) {
                    return -1;
                }
            }
            if (settingKey.compare("bday_file_path", Qt::CaseInsensitive) == 0) {
                AppSettings::bdayFilePath = settingValue;
                bdays_loaded = true;
            }
            else if (settingKey.compare("music_path", Qt::CaseInsensitive) == 0)
                AppSettings::audioSource = settingValue;
        }
        //bday file is mandatory
        if (!bdays_loaded)
            return -1;
    }
    //create the GUI
    MainWindow w;
    w.show();
    w.setFixedSize(QSize(800, 360));
    return a.exec();
}
