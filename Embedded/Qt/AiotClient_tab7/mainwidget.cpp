#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    pTab1DevControl = new Tab1DevControl(ui->pTab1);
    ui->pTab1->setLayout(pTab1DevControl->layout());

    pTab2SocketClient = new Tab2SocketClient(ui->pTab2);
    ui->pTab2->setLayout(pTab2SocketClient->layout());

    pTab3ControlPannel = new Tab3ControlPannel(ui->pTab3);
    ui->pTab3->setLayout(pTab3ControlPannel->layout());

    pTab4SensorChart = new Tab4SensorChart(ui->pTab4);
    ui->pTab4->setLayout(pTab4SensorChart->layout());

    pTab5SensorDatabase = new Tab5SensorDatabase(ui->pTab5);
    ui->pTab5->setLayout(pTab5SensorDatabase->layout());

    pTab6WebCamera = new Tab6WebCamera(ui->pTab6);
    ui->pTab6->setLayout(pTab6WebCamera->layout());

    pTab7CamViewThread = new Tab7CamViewThread(ui->pTab7);
    ui->pTab7->setLayout(pTab7CamViewThread->layout());

    ui->pTabWidget->setCurrentIndex(5);

    connect(pTab2SocketClient, SIGNAL(ledWriteSig(int)), pTab1DevControl->getpDial(), SLOT(setValue(int)));
    connect(pTab1DevControl->getpLedKeyDev(), SIGNAL(updateKeyDataSig(int)), pTab2SocketClient, SLOT(socketSendToLinux(int)));
    connect(pTab3ControlPannel, SIGNAL(socketSendDataSig(QString)), pTab2SocketClient->getpSocketClient(), SLOT(socketWriteDataSlot(QString)));
    connect(pTab2SocketClient, SIGNAL(tab3RecvDataSig(QString)), pTab3ControlPannel, SLOT(tab3RecvDataSlot(QString)));
    connect(pTab2SocketClient, SIGNAL(tab4RecvDataSig(QString)), pTab4SensorChart, SLOT(tab4RecvDataSlot(QString)));
    connect(pTab2SocketClient, SIGNAL(tab5RecvDataSig(QString)), pTab5SensorDatabase, SLOT(tab5RecvDataSlot(QString)));
}

MainWidget::~MainWidget()
{
    delete ui;
}
