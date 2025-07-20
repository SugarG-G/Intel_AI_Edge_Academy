#include "tab4sensorchart.h"
#include "ui_tab4sensorchart.h"

Tab4SensorChart::Tab4SensorChart(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tab4SensorChart)
{
    ui->setupUi(this);
    illuLine = new QLineSeries(this);
    illuLine->setName("조도");

    QPen pen;
    pen.setWidth(2);
    pen.setBrush(Qt::red);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    illuLine->setPen(pen);

    pQChart = new QChart();
    pQChart->addSeries(illuLine);
    pQChart->createDefaultAxes();
    pQChart->axes(Qt::Vertical).constFirst()->setRange(0, 100);

    pQChartView = new QChartView(pQChart);
    pQChartView->setRenderHint(QPainter::Antialiasing);

    ui->pChartViewLayout->layout()->addWidget(pQChartView);
    pQDateTimeAxisX = new QDateTimeAxis;
    pQDateTimeAxisX->setFormat("hh:mm");
//    pQDateTimeAxisX->setFormat("MM-dd hh:mm");

    updateLastDateTime(0);
    pQChartView->chart()->setAxisX(pQDateTimeAxisX,illuLine);

}
void Tab4SensorChart::updateLastDateTime(bool bFlag)
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    firstDateTime.setDate(date);
    firstDateTime.setTime(time);

    lastDateTime.setDate(date);
    QTime tempTime = time.addSecs(10*60);  //10분
    lastDateTime.setTime(tempTime);

    pQDateTimeAxisX->setRange(firstDateTime,lastDateTime);
}
Tab4SensorChart::~Tab4SensorChart()
{
    delete ui;
}

void Tab4SensorChart::tab4RecvDataSlot(QString recvData)
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QDateTime xValue;
    xValue.setDate(date);
    xValue.setTime(time);

    QStringList strList = recvData.split("@");   //recvData : [SENSIRID]SENSOR@조도@온도@습도
    QString illu  = strList[3];     //조도
    illuLine->append(xValue.toMSecsSinceEpoch(),illu.toInt());
//    qDebug() << illu ;
}

void Tab4SensorChart::on_pPBClearChart_clicked()
{
    illuLine->clear();
    updateLastDateTime(0);
}

