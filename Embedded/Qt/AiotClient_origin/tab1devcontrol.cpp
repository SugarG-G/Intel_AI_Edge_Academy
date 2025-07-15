#include "tab1devcontrol.h"
#include "ui_tab1devcontrol.h"
#include <QDebug>

Tab1DevControl::Tab1DevControl(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tab1DevControl)
{
    ui->setupUi(this);
    pLedKeyDev = new LedKeyDev(this);


    connect(ui->pDialLed, SIGNAL(valueChanged(int)), pLedKeyDev, SLOT(writeLedDataSlot(int)));
/* -------------------------------------------------------------------------------------------- */
    pQTimer = new QTimer(this);
    connect(pQTimer, SIGNAL(timeout()), this, SLOT(updateDialValue()));
/* -------------------------------------------------------------------------------------------- */
    connect(ui->pPushButtonQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(pLedKeyDev, SIGNAL(updateKeyDataSig(int)), this, SLOT(updateCheckBoxKey(int)));
/* -------------------------------------------------------------------------------------------- */
    pQButtonGroup = new QButtonGroup(this);

    int keyCount = ui->pGridLayout->rowCount() * ui->pGridLayout->columnCount();
    for(int i = 0; i < ui->pGridLayout->rowCount(); i++)
    {
        for(int j = 0; j < ui->pGridLayout->columnCount(); j++)
        {
            pQCheckBox[--keyCount] = dynamic_cast<QCheckBox*>(ui->pGridLayout->itemAtPosition(i,j)->widget());
            // pQCheckBox[keyCount++] = dynamic_cast<QCheckBox*>(ui->pGridLayout->itemAtPosition(i,j)->widget());
        }
    }
    pQButtonGroup->setExclusive(false);
    keyCount = ui->pGridLayout->rowCount() * ui->pGridLayout->columnCount();
    for(int i = 0; i < keyCount; i++)
    {
        pQButtonGroup->addButton(pQCheckBox[i], i+1);
    }

    connect(pQButtonGroup, SIGNAL(idClicked(int)), this, SLOT(updateCheckBoxMouseSlot(int)));
    // connect(pQButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(updateCheckBoxMouseSlot(int)));
/* -------------------------------------------------------------------------------------------- */
    connect(pQButtonGroup, SIGNAL(idClicked(int)), this, SLOT(stopQtimer()));
    connect(pLedKeyDev, SIGNAL(updateKeyDataSig(int)), this, SLOT(stopQtimer()));
}

Tab1DevControl::~Tab1DevControl()
{
    delete ui;
}

void Tab1DevControl::on_pPushButtoiTimerStart_clicked(bool checked)
{
    if(checked)
    {
        QString strValue = ui->pComboBoxTimerValue->currentText();
        pQTimer->start(strValue.toInt());
        ui->pPushButtoiTimerStart->setText("TimerStop");
    }
    else
    {
        pQTimer->stop();
        ui->pPushButtoiTimerStart->setText("TimerStart");
    }
}

void Tab1DevControl::updateDialValue()
{
    int dialValue = ui->pDialLed->value();
    dialValue++;
    if(dialValue > ui->pDialLed->maximum())
    {
        dialValue = 0;
    }
    ui->pDialLed->setValue(dialValue);
}

void Tab1DevControl::on_pComboBoxTimerValue_currentTextChanged(const QString &arg1)
{
    if(pQTimer->isActive())
    {
        pQTimer->stop();
        pQTimer->start(arg1.toInt());
    }
}

void Tab1DevControl::updateCheckBoxKey(int keyNo)
{
    // QCheckBox *pQCheckBox[8] = {ui->pCheckBoxKey1, ui->pCheckBoxKey2,ui->pCheckBoxKey3,ui->pCheckBoxKey4,
    //                             ui->pCheckBoxKey5,ui->pCheckBoxKey6,ui->pCheckBoxKey7,ui->pCheckBoxKey8};
    // static unsigned char lcdData = 0;
    lcdData = lcdData ^ (0x01 << (keyNo - 1));
    ui->pLcdNumberKey->display(lcdData);
    pLedKeyDev->writeLedDataSlot(lcdData);

    for(int i = 0; i < 8; i++)
    {
        if(keyNo == i+1)
        {
            if(pQCheckBox[i]->isChecked())
            {
                pQCheckBox[i]->setChecked(false);
            }
            else
            {
                pQCheckBox[i]->setChecked(true);
            }
        }
    }
}

void Tab1DevControl::updateCheckBoxMouseSlot(int keyNo)
{
    // QCheckBox *pQCheckBox[8] = {ui->pCheckBoxKey1, ui->pCheckBoxKey2,ui->pCheckBoxKey3,ui->pCheckBoxKey4,
    //                             ui->pCheckBoxKey5,ui->pCheckBoxKey6,ui->pCheckBoxKey7,ui->pCheckBoxKey8};
    // static unsigned char lcdData = 0;

    lcdData = lcdData ^ (0x01 << (keyNo - 1));
    ui->pLcdNumberKey->display(lcdData);
    pLedKeyDev->writeLedDataSlot(lcdData);
}

void Tab1DevControl::stopQtimer()
{
    pQTimer->stop();
    ui->pPushButtoiTimerStart->setChecked(false);
    ui->pPushButtoiTimerStart->setText("TimerStart");
}
