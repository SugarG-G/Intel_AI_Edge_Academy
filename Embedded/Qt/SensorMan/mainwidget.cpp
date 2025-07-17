#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    pSocket = new Socket(ui->pTab1Socket);
    ui->pTab1Socket->setLayout(pSocket->layout());

    pSensor = new Sensor(ui->pTab2Sensor);
    ui->pTab2Sensor->setLayout(pSensor->layout());

    pSqlite = new Sqlite(ui->pTab3Sqlite);
    ui->pTab3Sqlite->setLayout(pSqlite->layout());

    ui->pTabWidget->setCurrentIndex(0);

    connect(pSocket, SIGNAL(sensorDataSig(QString)), pSensor, SLOT(SensorRecvDataSlot(QString)));
    connect(pSocket, SIGNAL(sensorDataSig(QString)), pSqlite, SLOT(SqliteRecvDataSlot(QString)));
}

MainWidget::~MainWidget()
{
    delete ui;
}
