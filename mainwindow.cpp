#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shared_data.h"
#include <QMediaPlayer>
#include <QAudioOutput>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setup audio player for music
    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(100);
    //no music -> disable music "button"
    if (SharedData::audioSourceFile.fileName().isNull()){
        ui->btn_music->setEnabled(false);
        ui->btn_music->setVisible(false);
    } else {
        ui->btn_music->toggle(); //turn on
        //TODO check if audio file is really an audio file? probably done from Qt automatically
        player->setSource(QUrl::fromLocalFile(SharedData::audioSourceFile.fileName()));
        player->play();
    }

    //populate the people list
    if (!SharedData::peopleList.isEmpty()){
        ui->listWidget->addItems(SharedData::peopleList);
        ui->lb_found_text->setText("Birthdays found!");
    }

    //connect the button with the music
    connect(ui->btn_music, SIGNAL(toggled(bool)), this, SLOT(playOrPauseMusic(bool)));
}

void MainWindow::playOrPauseMusic(bool isButtonChecked) {
    if(isButtonChecked){
        ui->btn_music->setIcon(QIcon(":/assets/sound.png"));
        this->player->play();
    }
    else {
        ui->btn_music->setIcon(QIcon(":/assets/sound_off.png"));
        this->player->pause();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
    delete audioOutput;
}

