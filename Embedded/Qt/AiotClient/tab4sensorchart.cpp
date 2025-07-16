#include "tab4sensorchart.h"
#include "ui_tab4sensorchart.h"

Tab4SensorChart::Tab4SensorChart(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tab4SensorChart)
{
    ui->setupUi(this);
    //cds
    pCDSLine = new QLineSeries(this);
    pCDSLine->setName("조도");

    QPen pen;
    pen.setWidth(2);
    pen.setBrush(Qt::red);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);

    pCDSLine->setPen(pen);
    //cds

    //Temp
    pTempLine = new QLineSeries(this);
    pTempLine->setName("온도");

    pen.setBrush(Qt::green);

    pTempLine->setPen(pen);
    //Temp

    //Humi
    pHumiLine = new QLineSeries(this);
    pHumiLine->setName("습도");

    pen.setBrush(Qt::blue);

    pHumiLine->setPen(pen);
    //Humi

    //chart
    pQChart = new QChart();

    pQChart->addSeries(pCDSLine);
    pQChart->addSeries(pTempLine);
    pQChart->addSeries(pHumiLine);

    pQChart->createDefaultAxes();
    pQChart->axes(Qt::Vertical).constFirst()->setRange(0,100);
    //chart

    //chartview
    pQChartView = new QChartView(pQChart);
    pQChartView->setRenderHint(QPainter::Antialiasing);
    //chartview

    ui->pChartViewLayout->layout()->addWidget(pQChartView); //레이아웃에 차트 표시

    pQDateTimeAxisX = new QDateTimeAxis();
    pQDateTimeAxisX->setFormat("hh:mm");

    updateLastDateTime(0);

    pQChartView->chart()->setAxisX(pQDateTimeAxisX, pCDSLine);
    pQChartView->chart()->setAxisX(pQDateTimeAxisX, pTempLine);
    pQChartView->chart()->setAxisX(pQDateTimeAxisX, pHumiLine);
}

void Tab4SensorChart::updateLastDateTime(bool bFlag)
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    firstDateTime.setDate(date);
    firstDateTime.setTime(time);

    lastDateTime.setDate(date);
    lastDateTime.setTime(time.addSecs(60));

    pQDateTimeAxisX->setRange(firstDateTime,lastDateTime);

}

void Tab4SensorChart::tab4RecvDataSlot(QString strRecvData)
{
    // qDebug() << "tab4RecvDataSlot";
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QDateTime currentTime = QDateTime::currentDateTime();

    QDateTime xValue;

    xValue.setDate(date);
    xValue.setTime(time);
    // qDebug() << "xValue : " << xValue;
    QStringList strList = strRecvData.split("@");
    QString cds = strList[3];
    QString temp = strList[4];
    QString humi = strList[5];
    // qDebug() << "cds : " << cds;
    // qDebug() << "temp : " << temp;
    // qDebug() << "humi : " << humi;

    pCDSLine->append(xValue.toMSecsSinceEpoch(),cds.toInt());
    pTempLine->append(xValue.toMSecsSinceEpoch(),temp.toDouble());
    pHumiLine->append(xValue.toMSecsSinceEpoch(),humi.toDouble());

    if(currentTime > lastDateTime)
    {
        lastDateTime = currentTime.addSecs(60);
        pQDateTimeAxisX->setRange(firstDateTime,lastDateTime);
    }
    // qDebug() << "xValue.toMSecsSinceEpoch() : " << xValue.toMSecsSinceEpoch();
}

Tab4SensorChart::~Tab4SensorChart()
{
    delete ui;
}

void Tab4SensorChart::on_pPBClearChart_clicked()
{
    pCDSLine->clear();
    pTempLine->clear();
    pHumiLine->clear();
    updateLastDateTime(0);
}

