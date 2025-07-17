/********************************************************************************
** Form generated from reading UI file 'tab5sensordatabase.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB5SENSORDATABASE_H
#define UI_TAB5SENSORDATABASE_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tab5SensorDatabase
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QDateTimeEdit *pDateTimeEditFrom;
    QDateTimeEdit *pDateTimeEditTo;
    QPushButton *pPBsearchDB;
    QPushButton *pPBdeleteDB;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *pTBsensor;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pPBClearChart;
    QVBoxLayout *pChartViewLayout;

    void setupUi(QWidget *Tab5SensorDatabase)
    {
        if (Tab5SensorDatabase->objectName().isEmpty())
            Tab5SensorDatabase->setObjectName("Tab5SensorDatabase");
        Tab5SensorDatabase->resize(738, 462);
        verticalLayout_2 = new QVBoxLayout(Tab5SensorDatabase);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pDateTimeEditFrom = new QDateTimeEdit(Tab5SensorDatabase);
        pDateTimeEditFrom->setObjectName("pDateTimeEditFrom");
        pDateTimeEditFrom->setDate(QDate(2025, 7, 16));
        pDateTimeEditFrom->setTime(QTime(9, 0, 0));

        horizontalLayout->addWidget(pDateTimeEditFrom);

        pDateTimeEditTo = new QDateTimeEdit(Tab5SensorDatabase);
        pDateTimeEditTo->setObjectName("pDateTimeEditTo");
        pDateTimeEditTo->setDate(QDate(2025, 12, 31));
        pDateTimeEditTo->setTime(QTime(0, 0, 0));

        horizontalLayout->addWidget(pDateTimeEditTo);

        pPBsearchDB = new QPushButton(Tab5SensorDatabase);
        pPBsearchDB->setObjectName("pPBsearchDB");

        horizontalLayout->addWidget(pPBsearchDB);

        pPBdeleteDB = new QPushButton(Tab5SensorDatabase);
        pPBdeleteDB->setObjectName("pPBdeleteDB");

        horizontalLayout->addWidget(pPBdeleteDB);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pTBsensor = new QTableWidget(Tab5SensorDatabase);
        if (pTBsensor->columnCount() < 5)
            pTBsensor->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        pTBsensor->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        pTBsensor->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        pTBsensor->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        pTBsensor->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        pTBsensor->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        pTBsensor->setObjectName("pTBsensor");
        pTBsensor->setLineWidth(1);
        pTBsensor->horizontalHeader()->setDefaultSectionSize(50);

        horizontalLayout_2->addWidget(pTBsensor);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pPBClearChart = new QPushButton(Tab5SensorDatabase);
        pPBClearChart->setObjectName("pPBClearChart");

        horizontalLayout_3->addWidget(pPBClearChart);

        horizontalLayout_3->setStretch(0, 9);
        horizontalLayout_3->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_3);

        pChartViewLayout = new QVBoxLayout();
        pChartViewLayout->setObjectName("pChartViewLayout");

        verticalLayout->addLayout(pChartViewLayout);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 9);

        horizontalLayout_2->addLayout(verticalLayout);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(Tab5SensorDatabase);

        QMetaObject::connectSlotsByName(Tab5SensorDatabase);
    } // setupUi

    void retranslateUi(QWidget *Tab5SensorDatabase)
    {
        Tab5SensorDatabase->setWindowTitle(QCoreApplication::translate("Tab5SensorDatabase", "Form", nullptr));
        pPBsearchDB->setText(QCoreApplication::translate("Tab5SensorDatabase", "\354\241\260\355\232\214", nullptr));
        pPBdeleteDB->setText(QCoreApplication::translate("Tab5SensorDatabase", "\354\202\255\354\240\234", nullptr));
        QTableWidgetItem *___qtablewidgetitem = pTBsensor->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Tab5SensorDatabase", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = pTBsensor->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Tab5SensorDatabase", "\353\202\240\354\247\234", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = pTBsensor->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Tab5SensorDatabase", "\354\241\260\353\217\204", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = pTBsensor->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Tab5SensorDatabase", "\354\230\250\353\217\204", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = pTBsensor->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("Tab5SensorDatabase", "\354\212\265\353\217\204", nullptr));
        pPBClearChart->setText(QCoreApplication::translate("Tab5SensorDatabase", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tab5SensorDatabase: public Ui_Tab5SensorDatabase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB5SENSORDATABASE_H
