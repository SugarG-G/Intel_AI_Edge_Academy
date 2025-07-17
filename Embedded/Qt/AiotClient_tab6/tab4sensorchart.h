#ifndef TAB4SENSORCHART_H
#define TAB4SENSORCHART_H

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
class tab4SensorChart;
}

class tab4SensorChart : public QWidget
{
    Q_OBJECT

public:
    explicit tab4SensorChart(QWidget *parent = nullptr);
    ~tab4SensorChart();

private:
    Ui::tab4SensorChart *ui;

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
    void tab4RecvDataSlot(QString);

    void on_pPBClearChart_clicked();
};

#endif // TAB4SENSORCHART_H
