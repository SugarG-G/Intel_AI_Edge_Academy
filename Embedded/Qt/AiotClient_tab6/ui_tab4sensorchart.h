/********************************************************************************
** Form generated from reading UI file 'tab4sensorchart.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB4SENSORCHART_H
#define UI_TAB4SENSORCHART_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tab4SensorChart
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pPBClearChart;
    QVBoxLayout *pChartViewLayout;

    void setupUi(QWidget *tab4SensorChart)
    {
        if (tab4SensorChart->objectName().isEmpty())
            tab4SensorChart->setObjectName("tab4SensorChart");
        tab4SensorChart->resize(400, 300);
        verticalLayout = new QVBoxLayout(tab4SensorChart);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(178, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pPBClearChart = new QPushButton(tab4SensorChart);
        pPBClearChart->setObjectName("pPBClearChart");

        horizontalLayout->addWidget(pPBClearChart);

        horizontalLayout->setStretch(0, 8);
        horizontalLayout->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout);

        pChartViewLayout = new QVBoxLayout();
        pChartViewLayout->setObjectName("pChartViewLayout");

        verticalLayout->addLayout(pChartViewLayout);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 9);

        retranslateUi(tab4SensorChart);

        QMetaObject::connectSlotsByName(tab4SensorChart);
    } // setupUi

    void retranslateUi(QWidget *tab4SensorChart)
    {
        tab4SensorChart->setWindowTitle(QCoreApplication::translate("tab4SensorChart", "Form", nullptr));
        pPBClearChart->setText(QCoreApplication::translate("tab4SensorChart", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tab4SensorChart: public Ui_tab4SensorChart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB4SENSORCHART_H
