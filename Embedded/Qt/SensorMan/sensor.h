#ifndef SENSOR_H
#define SENSOR_H

#include <QWidget>
#include <QDebug>
#include <QDate>
#include <QTime>
#include <QStringList>

#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
#include <QChartView>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#else
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
QT_CHARTS_USE_NAMESPACE
#endif

namespace Ui {
class Sensor;
}

class Sensor : public QWidget
{
    Q_OBJECT

public:
    explicit Sensor(QWidget *parent = nullptr);
    ~Sensor();

private:
    Ui::Sensor *ui;

    QLineSeries *pCDSLine;
    QLineSeries *pTempLine;
    QLineSeries *pHumiLine;

    QChart *pQChart;
    QChartView *pQChartView;
    QDateTimeAxis *pQDateTimeAxisX;
    QDateTime firstDateTime;
    QDateTime lastDateTime;

    void updateLastDateTime(bool);
private slots:
    void SensorRecvDataSlot(QString);
    void on_pPBClearChart_clicked();
};

#endif // SENSOR_H
