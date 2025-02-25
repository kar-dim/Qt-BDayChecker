#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAudioOutput>
#include <QFile>
#include <QIcon>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QString>
#include <QStringList>
#include <QUrl>
#include <Qt>

MainWindow::MainWindow(const QString musicFileName, const QStringList peopleList)
    : QMainWindow(nullptr)
    , ui(new Ui::MainWindow)
    , player(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
    , audioOnIcon(QIcon(":/assets/sound.png"))
    , audioOffIcon(QIcon(":/assets/sound_off.png"))
{
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ui->setupUi(this);

    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(100);
    //no music -> disable music "button"
    if (!QFile(musicFileName).exists())
    {
        ui->musicBtn->setEnabled(false);
        ui->musicBtn->setVisible(false);
    } else
    {
        ui->musicBtn->toggle(); //turn on
        //TODO check if audio file is really an audio file?
        player->setSource(QUrl::fromLocalFile(musicFileName));
        player->play();
    }

    //populate the people list
    if (!peopleList.isEmpty())
    {
        ui->people->addItems(peopleList);
        ui->headerLabel->setText(header);
    }

    //connect the button with the music
    connect(ui->musicBtn, SIGNAL(toggled(bool)), this, SLOT(playMusic(bool)));
}

void MainWindow::playMusic(const bool enable)
{
    ui->musicBtn->setIcon(enable ? audioOnIcon : audioOffIcon);
    if (enable) player->play();
    else player->pause();
}

MainWindow::~MainWindow()
{
    delete ui;
}

