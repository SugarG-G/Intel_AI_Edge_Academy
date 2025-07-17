#ifndef SQLITE_H
#define SQLITE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QTime>
#include <QDate>
#include <QDebug>

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
class Sqlite;
}

class Sqlite : public QWidget
{
    Q_OBJECT

public:
    explicit Sqlite(QWidget *parent = nullptr);
    ~Sqlite();

private:
    Ui::Sqlite *ui;

    QSqlDatabase qSqlDatabase;

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
    void SqliteRecvDataSlot(QString);
    void on_pPBsearchDB_clicked();
    void on_pPBdeleteDB_clicked();
    void on_pPBClearChart_clicked();
};

#endif // SQLITE_H
