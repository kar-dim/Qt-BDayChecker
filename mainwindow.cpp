#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shared_data.h"
#include <QSound>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //no music -> disable music "button"
    if (SharedData::audioSourceFileName.fileName().isNull()){
        ui->btn_music->setEnabled(false);
        ui->btn_music->setVisible(false);
    } else {
        //check if audio file is really an audio file? probably done from Qt automatically
        QSound::play(SharedData::audioSourceFileName.fileName());
    }

    //
    if (!SharedData::peopleList.isEmpty()){
        ui->listWidget->addItems(SharedData::peopleList);
        ui->lb_found_text->setText("Birthdays found!");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

