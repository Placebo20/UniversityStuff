#include "mainwindow.h"
#include <QDebug>
#include <QScrollBar>
#include <QPushButton>
#include <iostream>

MainWindow::MainWindow()
{
    doNotLbl = new QLabel("Do not disturbe mode");
    doNotCheckBox = new QCheckBox();
    doNotCheckBox->setChecked(false);
    doNotDisturb = false;

    tmp = "\0";
    temp.setHMS(0,0,0);
    setToolBar();

    QLabel *tmr = new QLabel("Nearest Timer",this);
    tmr->setGeometry(50,85,100,20);
    mainTimerLbl = new QLabel(this);
    mainTimerLbl->setText("00:00:00");
    mainTimerLbl->setGeometry(40,100,130,40);

    QFont font = mainTimerLbl->font();
    font.setPixelSize(32);
    mainTimerLbl->setFont(font);

    QLabel *desc = new QLabel("Description",this);
    desc->setGeometry(260,60,70,20);

    mainTimerDescriptionLbl = new QTextEdit(this);
    mainTimerDescriptionLbl->setGeometry(250,80,230,100);
    mainTimerDescriptionLbl->setReadOnly(true);

    QLabel *tmrslbl = new QLabel("Timers",this);
    tmrslbl->setGeometry(40,205,50,20);

    QScrollBar *sb = new QScrollBar(Qt::Vertical);

    listW = new QListWidget(this);
    listW->setVerticalScrollBar(sb);
    listW->setGeometry(30,225,200,200);

    startTimer(1000);
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    timelbl->setText(QTime::currentTime().toString());
    if(timers.size() > 0){
        for(int i = 0; i < timers.size(); i++){
            timers[i].setTime(timers[i].getTime().addMSecs(-500));
            listW->item(i)->setText(timers[i].getTime().toString());
        }
        if(!stoppedTimersPositions.empty()){
            for(int i = 0; i < stoppedTimersPositions.size(); i++){
                timers[stoppedTimersPositions[i]].setTime(timers[stoppedTimersPositions[i]].getTime().addMSecs(500));
            }
        }
        mainTimerLbl->setText(timers[0].getTime().toString());
        mainTimerDescriptionLbl->setText(timers[0].getDesc());

        if(timers[0].getTime() == temp){
            timeoutWindow();
            timers.removeAt(0);
            delete listW->takeItem(0);
        }

        for(int i = 0; i < timers.size(); i++){
            if(timers[i].getTime() == temp){
                stoppedTimersPositions.append(i);
                timers.removeAt(i);
                delete listW->takeItem(i);
            }

        }

    } else {
        mainTimerDescriptionLbl->setText("\0");
    }
}

QList<Timer> MainWindow::getTimers()
{
    if(timers.size() > 0){
        for(int i = 0; i < timers.size(); i++){
            qDebug() << timers[i].getTime();
            qDebug() << timers[i].getDesc() << Qt::endl;
        }
        return timers;
    } else qDebug() << "No!" << Qt::endl;
}

void MainWindow::setToolBar()
{
    QPixmap addpix("add.png");
    QPixmap editpix("edit.png");
    QPixmap deletepix("delete.png");
    QPixmap deleteallpix("deleteAll.png");
    QPixmap infopix("info.png");
    QPixmap stoppix("stop.jpg");

    toolbar = addToolBar("Main Toolbar");
    toolbar->setFixedHeight(50);
    toolbar->setStyleSheet("QToolBar{spacing:10px;}");

    toolbar->addSeparator();
    QAction *add = toolbar->addAction(QIcon(addpix),"New Timer");
    QAction *stop = toolbar->addAction(QIcon(stoppix),"Stop timer");
    QAction *edit = toolbar->addAction(QIcon(editpix),"Edit Timer");
    QAction *dlete = toolbar->addAction(QIcon(deletepix),"Delete Timer");
    QAction *dleteAll = toolbar->addAction(QIcon(deleteallpix),"Delete All Timers");
    QAction *info = toolbar->addAction(QIcon(infopix),"Timer's Info");
    toolbar->setMovable(false);
    toolbar->addSeparator();

    QLabel *lbl = new QLabel("Current time: ");

    toolbar->addWidget(lbl);

    timelbl = new QLabel(QTime::currentTime().toString());
    startTimer(1000);
    toolbar->addWidget(timelbl);

    connect(stop, &QAction::triggered, this, &MainWindow::stopTimer);
    connect(add, &QAction::triggered, this, &MainWindow::addTimer);
    connect(edit, &QAction::triggered, this, &MainWindow::toEditWindow);
    connect(dlete, &QAction::triggered, this, &MainWindow::deleteTimer);
    connect(dleteAll, &QAction::triggered, this, &MainWindow::deleteAllTimers);
    connect(info, &QAction::triggered, this, &MainWindow::settingsWindowSlot);
}

void MainWindow::addTimer()
{
    addWindow = new QWidget();
    addWindow->resize(250,200);
    addWindow->setWindowTitle("New Timer");

    addTimerLbl = new QLabel("Time");
    addTimerLbl->setGeometry(20,60,50,20);

    addTimeEdit = new QTimeEdit();
    addTimeEdit->setDisplayFormat("hh:mm:ss");
    addTimeEdit->setGeometry(90,65,100,25);

    addDescLbl = new QLabel("Description");
    addDescLbl->setGeometry(20, 100, 50, 20);

    addTextEdit = new QTextEdit();
    addTextEdit->setGeometry(90,130,100,150);

    addCountLbl = new QLabel("Count of timers");
    addCountTextEdit = new QTextEdit();

    QPushButton *addBtn = new QPushButton("Set Timer",addWindow);

    // Добавим на окно менеджер вертикального расположения элементов
    addWindow->setLayout(new QVBoxLayout());
    // А теперь, при помощи менеджера расположения, добавим сами виджеты на окно
    addWindow->layout()->addWidget(addTimerLbl);
    addWindow->layout()->addWidget(addTimeEdit);
    addWindow->layout()->addWidget(addDescLbl);
    addWindow->layout()->addWidget(addTextEdit);
    addWindow->layout()->addWidget(addCountLbl);
    addWindow->layout()->addWidget(addCountTextEdit);
    addWindow->layout()->addWidget(addBtn);

    connect(addBtn, &QPushButton::clicked, this, &MainWindow::addTimerBtnClicked);
    addWindow->show();
}

void MainWindow::timeoutWindow()
{
    QVBoxLayout *vbox = new QVBoxLayout();

    QSound *sound=new QSound("AlarmClock.wav", this);
    sound->play();

    signalWindow = new QWidget();
    signalWindow->resize(250,200);
    signalWindow->setObjectName("TIMEOUT!");
    timeoutLbl = new QLabel("Timeout! There is description:");
    timeoutDescLbl = new QTextEdit(this);
    timeoutDescLbl->setText(timers[0].getDesc());
    timeoutDescLbl->setReadOnly(true);
    timeoutOKBtn = new QPushButton("OK", this);

    vbox->addWidget(timeoutLbl);
    vbox->addWidget(timeoutDescLbl);
    vbox->addWidget(timeoutOKBtn);

    connect(timeoutOKBtn, &QPushButton::clicked, signalWindow, &QPushButton::close);

    signalWindow->show();
    signalWindow->setLayout(vbox);
}

void MainWindow::toEditWindow()
{
    if(!timers.empty()){
        tmp = listW->selectedItems().first()->text();
        if(tmp == "\0"){
            QMessageBox::warning(this,tr("Choose the timer"),tr("Please, choose the timer in Timers tab"));
            return;
        }
    } else {
        QMessageBox::warning(this,tr("Timers is empty"),tr("Timers is empty"));
        return;
    }

    for(int i = 0; i < timers.size(); i++){
        if(tmp == timers[i].getTime().toString()){
            positionToEdit = i;
            buffer.setTime(timers[i].getTime());
            buffer.setDesc(timers[i].getDesc());
        }
    }
    editWindow = new QWidget();
    editWindow->resize(200,250);
    editWindow->setObjectName("Edit Timers");

    QVBoxLayout *vbox = new QVBoxLayout();

    editTimeLbl = new QLabel("Edit time:");
    editDescLbl = new QLabel("Edit description:");
    editTimeEdit = new QTimeEdit();
    editTimeEdit->setDisplayFormat("hh:mm:ss");
    editDescEdit = new QTextEdit();
    editTimerBtn = new QPushButton("OK");

    vbox->addWidget(editTimeLbl);
    vbox->addWidget(editTimeEdit);
    vbox->addWidget(editDescLbl);
    vbox->addWidget(editDescEdit);
    vbox->addWidget(editTimerBtn);

    connect(editTimerBtn, &QPushButton::clicked, this, &MainWindow::editTimerBtnClicked);
    editWindow->setLayout(vbox);
    editWindow->show();
}

void MainWindow::addTimerBtnClicked()
{
    QTime time(addTimeEdit->time().hour(),addTimeEdit->time().minute(),addTimeEdit->time().second());
    Timer timer(time,addTextEdit->toPlainText());
    for(int i = 0; i < addCountTextEdit->toPlainText().toInt(); i++){
        timers.append(timer);
    }
    addWindow->close();
    timersSort();
    if(timers.empty()){
        mainTimerLbl->setText("00:00:00");
        mainTimerDescriptionLbl->setText(" ");
    } else {
        mainTimerLbl->setText(timers[0].getTime().toString());
        mainTimerDescriptionLbl->setText(timers[0].getDesc());
    }
    updateTimersListW();
}

void MainWindow::stopTimer()
{
    for(int i = 0; i < timers.size(); i++){
        if(timers[i].getTime().toString() == listW->selectedItems().first()->text()){
            if(!stoppedTimersPositions.empty()){
                for(int j = 0; j < stoppedTimersPositions.size(); j++){
                    if(i != stoppedTimersPositions[j]){
                        stoppedTimersPositions.append(i);
                    } else {
                        stoppedTimersPositions.removeAt(j);
                    }
                }
             } else
                 stoppedTimersPositions.append(i);
        }
    }
}

void MainWindow::editTimerBtnClicked()
{
    QTime time(editTimeEdit->time().hour(),editTimeEdit->time().minute(),editTimeEdit->time().second());

    timers[positionToEdit].setTime(time);
    timers[positionToEdit].setDesc(editDescEdit->toPlainText());

    buffer.setTime(time);
    buffer.setDesc(editDescEdit->toPlainText());

    editWindow->close();
}

void MainWindow::deleteTimer()
{
    for(int i = 0; i < timers.size(); i++){
        if(listW->selectedItems().first()->text() == timers[i].getTime().toString()){
            timers.removeAt(i);
            positionToEdit = i;
        }
    }
    delete listW->takeItem(positionToEdit);
    if(timers.empty()){
        mainTimerLbl->setText("00:00:00");
        mainTimerDescriptionLbl->setText("\0");
    }
}

void MainWindow::deleteAllTimers()
{
    timers.clear();
    listW->clear();
    mainTimerLbl->setText("00:00:00");
    mainTimerDescriptionLbl->setText("\0");
}

void MainWindow::settingsWindowSlot()
{
    settingsWindow = new QWidget;
    QVBoxLayout *vbox = new QVBoxLayout();
    QHBoxLayout *hbox = new QHBoxLayout();

    infoOKBtn = new QPushButton("OK");

    hbox->addWidget(doNotLbl);
    hbox->addWidget(doNotCheckBox);
    vbox->addLayout(hbox);
    vbox->addWidget(infoOKBtn);

    settingsWindow->setLayout(vbox);
    settingsWindow->setObjectName("Settings");
    settingsWindow->setFixedSize(250,150);
    settingsWindow->show();

    connect(infoOKBtn, &QPushButton::clicked, this, &MainWindow::infoOKBtnClicked);
}

void MainWindow::infoOKBtnClicked()
{
    doNotDisturb = doNotCheckBox->isChecked();
    settingsWindow->close();
}

void MainWindow::timersSort() {
    if(timers.size() > 1) {
        int i, j;
        for (i = 0; i < timers.size()-1; i++)
        for (j = 0; j < timers.size()-i-1; j++){
            if (timers[j].getTime() > timers[j+1].getTime()){
                Timer tmp = timers[j];
                timers[j] = timers[j+1];
                timers[j+1] = tmp;
            }
        }
    } else return;
}

void MainWindow::updateTimersListW()
{
    listW->clear();
    for(int i = 0; i < timers.size(); i++){
        listW->addItem(timers[i].getTime().toString());
    }
}
