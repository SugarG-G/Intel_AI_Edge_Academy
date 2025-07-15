#include "tab3controlpanel.h"
#include "ui_tab3controlpanel.h"

Tab3ControlPanel::Tab3ControlPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tab3ControlPanel)
{
    ui->setupUi(this);
    paletteOn.setColor(ui->pPBlamp->backgroundRole(),QColor(255,0,0));
    paletteOff.setColor(ui->pPBlamp->backgroundRole(),QColor(0,255,0));
    ui->pPBlamp->setPalette(paletteOff);
    ui->pPBplug->setPalette(paletteOff);
}


Tab3ControlPanel::~Tab3ControlPanel()
{
    delete ui;
}

void Tab3ControlPanel::tab3RecvDataSlot(QString strRecvData)
{
    // qDebug() << strRecvData;
    //[CHI_QT]@LED@0xff  ==> @CHI_QT@LED@0xff
    strRecvData.replace("[","@");
    strRecvData.replace("]","@");
    QStringList strList = strRecvData.split("@");
    if(strList[2].indexOf("LAMPON") == 0)
    {
        ui->pPBlamp->setChecked(true);
        ui->pPBlamp->setPalette(paletteOn);
        // qDebug() << ui->pPBlamp->isChecked();
    }
    else if(strList[2].indexOf("LAMPOFF") == 0)
    {
        ui->pPBlamp->setChecked(false);
        ui->pPBlamp->setPalette(paletteOff);
        // qDebug() << ui->pPBlamp->isChecked();
    }

    if(strList[2].indexOf("PLUGON") == 0)
    {
        ui->pPBplug->setChecked(true);
        ui->pPBplug->setPalette(paletteOn);
        // qDebug() << ui->pPBlamp->isChecked();
    }
    else if(strList[2].indexOf("PLUGOFF") == 0)
    {
        ui->pPBplug->setChecked(false);
        ui->pPBplug->setPalette(paletteOff);
        // qDebug() << ui->pPBlamp->isChecked();
    }
}

void Tab3ControlPanel::on_pPBlamp_clicked(bool checked)
{
    // qDebug() << "on_pPBlamp_toggled";
    if(checked)
    {
        emit sendControlDataSig("[CHI_LIN]LAMPON");  // 시그널 발생
        ui->pPBlamp->setChecked(false);
    }
    else
    {
        emit sendControlDataSig("[CHI_LIN]LAMPOFF");  // 시그널 발생
        ui->pPBlamp->setChecked(true);
    }
}

void Tab3ControlPanel::on_pPBplug_clicked(bool checked)
{
    // qDebug() << "on_pPBlamp_toggled";
    if(checked)
    {
        emit sendControlDataSig("[CHI_LIN]PLUGON");  // 시그널 발생
        ui->pPBplug->setChecked(false);
    }
    else
    {
        emit sendControlDataSig("[CHI_LIN]PLUGOFF");  // 시그널 발생
        ui->pPBplug->setChecked(true);
    }
}
