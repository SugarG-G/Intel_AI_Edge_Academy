/********************************************************************************
** Form generated from reading UI file 'tab3controlpanel.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB3CONTROLPANEL_H
#define UI_TAB3CONTROLPANEL_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tab3ControlPanel
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *label;
    QPushButton *pPBplug;
    QPushButton *pPBlamp;

    void setupUi(QWidget *Tab3ControlPanel)
    {
        if (Tab3ControlPanel->objectName().isEmpty())
            Tab3ControlPanel->setObjectName("Tab3ControlPanel");
        Tab3ControlPanel->resize(551, 350);
        Tab3ControlPanel->setMinimumSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(Tab3ControlPanel);
        verticalLayout->setObjectName("verticalLayout");
        scrollArea = new QScrollArea(Tab3ControlPanel);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
        scrollArea->setWidgetResizable(false);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 531, 330));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 523, 326));
        label->setMinimumSize(QSize(0, 0));
        label->setContextMenuPolicy(Qt::ContextMenuPolicy::PreventContextMenu);
        label->setPixmap(QPixmap(QString::fromUtf8(":/Images/Images/room1.png")));
        pPBplug = new QPushButton(scrollAreaWidgetContents);
        pPBplug->setObjectName("pPBplug");
        pPBplug->setGeometry(QRect(320, 160, 70, 70));
        pPBplug->setMinimumSize(QSize(70, 70));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Images/Images/plug_off.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon.addFile(QString::fromUtf8(":/Images/Images/plug_on.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pPBplug->setIcon(icon);
        pPBplug->setIconSize(QSize(70, 70));
        pPBplug->setCheckable(true);
        pPBplug->setFlat(true);
        pPBlamp = new QPushButton(scrollAreaWidgetContents);
        pPBlamp->setObjectName("pPBlamp");
        pPBlamp->setGeometry(QRect(40, 80, 70, 70));
        pPBlamp->setMinimumSize(QSize(70, 70));
        pPBlamp->setAutoFillBackground(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Images/Images/light_off.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon1.addFile(QString::fromUtf8(":/Images/Images/light_on.png"), QSize(), QIcon::Mode::Normal, QIcon::State::On);
        pPBlamp->setIcon(icon1);
        pPBlamp->setIconSize(QSize(70, 70));
        pPBlamp->setCheckable(true);
        pPBlamp->setChecked(false);
        pPBlamp->setAutoDefault(false);
        pPBlamp->setFlat(true);
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(Tab3ControlPanel);

        QMetaObject::connectSlotsByName(Tab3ControlPanel);
    } // setupUi

    void retranslateUi(QWidget *Tab3ControlPanel)
    {
        Tab3ControlPanel->setWindowTitle(QCoreApplication::translate("Tab3ControlPanel", "Form", nullptr));
        label->setText(QString());
        pPBplug->setText(QString());
        pPBlamp->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Tab3ControlPanel: public Ui_Tab3ControlPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB3CONTROLPANEL_H
