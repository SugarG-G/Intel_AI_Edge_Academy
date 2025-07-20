#ifndef TAB5SENSORDATABASE_H
#define TAB5SENSORDATABASE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QChartView>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QTableWidgetItem>
#include <QDebug>
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
    QT_CHARTS_USE_NAMESPACE
#endif

namespace Ui {
class Tab5SensorDatabase;
}

class Tab5SensorDatabase : public QWidget
{
    Q_OBJECT

public:
    explicit Tab5SensorDatabase(QWidget *parent = nullptr);
    ~Tab5SensorDatabase();

private:
    Ui::Tab5SensorDatabase *ui;
    QSqlDatabase qSqlDatabase;
    QLineSeries *illuLine;
    QChart *pQChart;
    QChartView *pQChartView;
    QDateTimeAxis *pQDateTimeAxisX;
    QDateTime firstDateTime;
    QDateTime lastDateTime;


    QTableWidgetItem* pQTableWidgetItemId = nullptr;
    QTableWidgetItem* pQTableWidgetItemDate = nullptr;
    QTableWidgetItem* pQTableWidgetItemIllu = nullptr;

    void updateLastDateTime(bool);
    void updateLastDateTimeSql(bool);
private slots:
    void tab5RecvDataSlot(QString);
    void on_pPBClearChart_clicked();
    void on_pPBsearchDB_clicked();
    void on_pPBdeleteDB_clicked();
};

#endif // TAB5SENSORDATABASE_H
