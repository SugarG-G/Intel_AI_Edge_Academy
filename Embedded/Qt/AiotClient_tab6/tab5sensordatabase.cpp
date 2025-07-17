#include "tab5sensordatabase.h"
#include "ui_tab5sensordatabase.h"

Tab5SensorDatabase::Tab5SensorDatabase(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tab5SensorDatabase)
{
    ui->setupUi(this);
//SQL
    qSqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
    qSqlDatabase.setDatabaseName("aiot.db");
    if(qSqlDatabase.open())
    {
        qDebug() << "Success DB Connection";
    }
    else
    {
        qDebug() << "Fail DB Connection";
    }

    QString strQuery = "create table sensor_tb ("
                       "name varchar(10),"
                       "date DATETIME primary key,"
                       "illu varchar(10),"
                       "temp varchar(10),"
                       "humi varchar(10))";

    QSqlQuery sqlQuery;
    if(sqlQuery.exec(strQuery))
    {
        qDebug() << "Create Table";
    }
//SQL

//chart
    QPen pen;
    pen.setWidth(2);
    pen.setBrush(Qt::red);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);

    pCDSLine = new QLineSeries(this);
    pCDSLine->setName("조도");
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
    pQDateTimeAxisX->setFormat("hh:mm::ss");

    updateLastDateTime(0);

    pQChartView->chart()->setAxisX(pQDateTimeAxisX, pCDSLine);
    pQChartView->chart()->setAxisX(pQDateTimeAxisX, pTempLine);
    pQChartView->chart()->setAxisX(pQDateTimeAxisX, pHumiLine);
//chart

}

void Tab5SensorDatabase::updateLastDateTime(bool bFlag)
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    firstDateTime.setDate(date);
    firstDateTime.setTime(time);

    lastDateTime.setDate(date);
    lastDateTime.setTime(time.addSecs(60));

    pQDateTimeAxisX->setRange(firstDateTime,lastDateTime);
}

void Tab5SensorDatabase::tab5RecvDataSlot(QString strRecvData)
{
    // qDebug() << "tab4RecvDataSlot";
    QDateTime datetime = QDateTime::currentDateTime();

    // qDebug() << "xValue : " << xValue;
    QStringList strList = strRecvData.split("@");
    QString cds = strList[3];
    QString temp = strList[4];
    QString humi = strList[5];
    // qDebug() << "cds : " << cds;
    // qDebug() << "temp : " << temp;
    // qDebug() << "humi : " << humi;

    QString name = strList[1];

    // pCDSLine->append(datetime.toMSecsSinceEpoch(),cds.toInt());
    // pTempLine->append(datetime.toMSecsSinceEpoch(),temp.toDouble());
    // pHumiLine->append(datetime.toMSecsSinceEpoch(),humi.toDouble());

    // if(datetime > lastDateTime)
    // {
    //     lastDateTime = datetime.addSecs(60);
    //     pQDateTimeAxisX->setRange(firstDateTime,lastDateTime);
    // }

    // QString strQuery = "insert into sensor_tb(name, date, illu, temp, humi) values('" + name + "', '" + datetime.toString("yyyy/MM/dd hh:mm:ss") +"', '" + cds + ", '" + temp +"', '" + humi + "')";
    QSqlQuery sqlQuery;
    sqlQuery.prepare("INSERT INTO sensor_tb(name, date, illu, temp, humi) "
                     "VALUES(:name, :date, :illu, :temp, :humi)");
    sqlQuery.bindValue(":name", name);
    sqlQuery.bindValue(":date", datetime.toString("yyyy/MM/dd hh:mm:ss"));
    sqlQuery.bindValue(":illu", cds);
    sqlQuery.bindValue(":temp", temp);
    sqlQuery.bindValue(":humi", humi);

    if(sqlQuery.exec())
    {
        qDebug() << "insert Query OK";
    }
}

Tab5SensorDatabase::~Tab5SensorDatabase()
{
    delete ui;
}

void Tab5SensorDatabase::on_pPBClearChart_clicked()
{
    pCDSLine->clear();
    pTempLine->clear();
    pHumiLine->clear();
    updateLastDateTime(0);
}


void Tab5SensorDatabase::on_pPBsearchDB_clicked()
{
    QDateTime fromDateTime = ui->pDateTimeEditFrom->dateTime();
    QDateTime toDateTime = ui->pDateTimeEditTo->dateTime();

    QString strFromDateTime = fromDateTime.toString("yyyy/MM/dd hh:mm:ss");
    QString strtoDateTime = toDateTime.toString("yyyy/MM/dd hh:mm:ss");

    // ui->pTBsensor->clearContents();
    // pCDSLine->clear();
    on_pPBClearChart_clicked();

    // QString strQuery = "select * from sensor_tb where date >= '" + strFromDateTime +"' and date <= '"+ strtoDateTime + "'";
    QSqlQuery sqlQuery;
    sqlQuery.prepare("SELECT * FROM sensor_tb WHERE date >= :fromDate AND date <= :toDate");
    sqlQuery.bindValue(":fromDate", strFromDateTime);
    sqlQuery.bindValue(":toDate", strtoDateTime);

    if(sqlQuery.exec())
    {
        int rowCount = 0;
        qDebug() << "select Query OK";

        QDateTime minTime, maxTime;

        while(sqlQuery.next())
        {
            // rowCount++;
            // ui->pTBsensor->setRowCount(rowCount);

            // QTableWidgetItem *pQTableWidgetItemID = new QTableWidgetItem();
            // QTableWidgetItem *pQTableWidgetItemDate = new QTableWidgetItem();
            // QTableWidgetItem *pQTableWidgetItemIllu = new QTableWidgetItem();

            // pQTableWidgetItemID->setText((sqlQuery.value("name")).toString());
            // pQTableWidgetItemDate->setText((sqlQuery.value("date")).toString());
            // pQTableWidgetItemIllu->setText((sqlQuery.value("illu")).toString());

            // ui->pTBsensor->setItem(rowCount - 1, 0, pQTableWidgetItemID);
            // ui->pTBsensor->setItem(rowCount - 1, 1, pQTableWidgetItemDate);
            // ui->pTBsensor->setItem(rowCount - 1, 2, pQTableWidgetItemIllu);

            rowCount++;
            ui->pTBsensor->setRowCount(rowCount);

            QString name = sqlQuery.value("name").toString();
            QString dateStr = sqlQuery.value("date").toString();
            QString illuStr = sqlQuery.value("illu").toString();
            QString tempStr = sqlQuery.value("temp").toString();
            QString humistr = sqlQuery.value("humi").toString();

            QTableWidgetItem *pQTableWidgetItemID = new QTableWidgetItem(name);
            QTableWidgetItem *pQTableWidgetItemDate = new QTableWidgetItem(dateStr);
            QTableWidgetItem *pQTableWidgetItemIllu = new QTableWidgetItem(illuStr);
            QTableWidgetItem *pQTableWidgetItemTemp = new QTableWidgetItem(tempStr);
            QTableWidgetItem *pQTableWidgetItemHumi = new QTableWidgetItem(humistr);

            // qDebug() << QDateTime::fromString(dateStr, "yyyy/MM/dd hh:mm:ss");

            ui->pTBsensor->setItem(rowCount - 1, 0, pQTableWidgetItemID);
            ui->pTBsensor->setItem(rowCount - 1, 1, pQTableWidgetItemDate);
            ui->pTBsensor->setItem(rowCount - 1, 2, pQTableWidgetItemIllu);
            ui->pTBsensor->setItem(rowCount - 1, 3, pQTableWidgetItemTemp);
            ui->pTBsensor->setItem(rowCount - 1, 4, pQTableWidgetItemHumi);

            QDateTime dateTime = QDateTime::fromString(dateStr, "yyyy/MM/dd hh:mm:ss");
            if (dateTime.isValid()) {
                pCDSLine->append(dateTime.toMSecsSinceEpoch(), illuStr.toInt());
                pTempLine->append(dateTime.toMSecsSinceEpoch(), tempStr.toDouble());
                pHumiLine->append(dateTime.toMSecsSinceEpoch(), humistr.toDouble());

                //기존에 처음과 끝을 확인하기 위한 코드 하지만 아래 .first() .last()로바뀜
                // if (fristFlag) {
                //     minTime = maxTime = dateTime;
                //     fristFlag = false;
                // } else {
                //     if (dateTime < minTime) minTime = dateTime;
                //     if (dateTime > maxTime) maxTime = dateTime;
                // }
            }
        }
        // if (!fristFlag) {
        //     pQDateTimeAxisX->setRange(minTime, maxTime);
        // }

        //id 날짜 조도 온도 습도 간격 자동조절
        ui->pTBsensor->resizeColumnToContents(0);
        ui->pTBsensor->resizeColumnToContents(1);
        ui->pTBsensor->resizeColumnToContents(2);
        ui->pTBsensor->resizeColumnToContents(3);
        ui->pTBsensor->resizeColumnToContents(4);
    }
    //쿼리의 첫번째와 마지막을 가져올 수있음
    sqlQuery.first();
    firstDateTime = QDateTime::fromString(sqlQuery.value("date").toString(), "yyyy/MM/dd hh:mm:ss");
    sqlQuery.last();
    lastDateTime = QDateTime::fromString(sqlQuery.value("date").toString(), "yyyy/MM/dd hh:mm:ss");

    pQDateTimeAxisX->setRange(firstDateTime, lastDateTime);
}



void Tab5SensorDatabase::on_pPBdeleteDB_clicked()
{
    QDateTime fromDateTime = ui->pDateTimeEditFrom->dateTime();
    QDateTime toDateTime = ui->pDateTimeEditTo->dateTime();

    QString strFromDateTime = fromDateTime.toString("yyyy/MM/dd hh:mm:ss");
    QString strtoDateTime = toDateTime.toString("yyyy/MM/dd hh:mm:ss");

    QSqlQuery sqlQuery;
    sqlQuery.prepare("DELETE FROM sensor_tb WHERE date >= :fromDate AND date <= :toDate");
    sqlQuery.bindValue(":fromDate", strFromDateTime);
    sqlQuery.bindValue(":toDate", strtoDateTime);

    if(sqlQuery.exec())
    {
        qDebug() << "delete Query OK";
    }
    ui->pTBsensor->clearContents();
    on_pPBClearChart_clicked();
    on_pPBsearchDB_clicked();
}

