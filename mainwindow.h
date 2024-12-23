#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString audioFileName, const QStringList peopleList);
    ~MainWindow();
public slots:
    void playMusic(const bool);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QIcon audioOnIcon, audioOffIcon;
    const QString audioFileName;
    const QStringList peopleList;
    const QString header = "Celebrations!";

};
#endif // MAINWINDOW_H
