#ifndef TAB4SENSORCHART_H
#define TAB4SENSORCHART_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QDebug>
#include <QDateTimeAxis>
#include <QDate>
#include <QTime>
#include <QStringList>

namespace Ui {
class Tab4SensorChart;
}

class Tab4SensorChart : public QWidget
{
    Q_OBJECT

public:
    explicit Tab4SensorChart(QWidget *parent = nullptr);
    ~Tab4SensorChart();

private:
    Ui::Tab4SensorChart *ui;

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
