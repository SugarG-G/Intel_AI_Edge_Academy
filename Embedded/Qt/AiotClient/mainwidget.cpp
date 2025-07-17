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

    pTab3ControlPanel = new Tab3ControlPanel(ui->pTab3);
    ui->pTab3->setLayout(pTab3ControlPanel->layout());

    pTab4SensorChart = new tab4SensorChart(ui->pTab4);
    ui->pTab4->setLayout(pTab4SensorChart->layout());

    pTab5SensorDatabase = new Tab5SensorDatabase(ui->pTab5);
    ui->pTab5->setLayout(pTab5SensorDatabase->layout());

    ui->pTabWidget->setCurrentIndex(4);

    connect(pTab2SocketClient, SIGNAL(ledWriteSig(int)), pTab1DevControl->getpDial(), SLOT(setValue(int)));
    connect(pTab1DevControl->getpLedKeyDev(), SIGNAL(updateKeyDataSig(int)), pTab2SocketClient, SLOT(socketSendToLinux(int)));
    connect(pTab3ControlPanel, SIGNAL(sendControlDataSig(QString)), pTab2SocketClient->getSocketClient(), SLOT(socketWriteDataSlot(QString)));
    connect(pTab2SocketClient, SIGNAL(tab3RecvDataSig(QString)), pTab3ControlPanel, SLOT(tab3RecvDataSlot(QString)));
    connect(pTab2SocketClient, SIGNAL(tab4RecvDataSig(QString)), pTab4SensorChart, SLOT(tab4RecvDataSlot(QString)));
    connect(pTab2SocketClient, SIGNAL(tab4RecvDataSig(QString)), pTab5SensorDatabase, SLOT(tab5RecvDataSlot(QString)));
}

MainWidget::~MainWidget()
{
    delete ui;
}
