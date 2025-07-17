#include "socket.h"
#include "ui_socket.h"

Socket::Socket(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Socket)
{
    ui->setupUi(this);

    ui->pPBSend->setEnabled(false);
    pSocketClient = new SocketClient(this);

    pKeyboard = new Keyboard();

    connect(pSocketClient, SIGNAL(socketRecvDataSig(QString)),this, SLOT(updateRecvDataSlot(QString)));
}

void Socket::on_pPBServerConnect_toggled(bool checked)
{
    bool bFlag;
    qDebug() << "on_pPBserverConnect_toggled()";
    if(checked)
    {
        pSocketClient->connectToServerSlot(bFlag);
        if(bFlag)
        {
            ui->pPBServerConnect->setText("서버 해제");
            ui->pPBSend->setEnabled(true);
        }
    }
    else {
        pSocketClient->socketClosedServerSlot();
        ui->pPBServerConnect->setText("서버 연결");
        ui->pPBSend->setEnabled(false);
    }
}

void Socket::updateRecvDataSlot(QString strRecvData)
{
    strRecvData.chop(1);   //끝문자 한개 "\n" 제거
    QTime time = QTime::currentTime();
    QString strTime = time.toString();
    strTime = strTime + " " + strRecvData;
    ui->pTERecvData->append(strTime);

    strRecvData.replace("[","@");
    strRecvData.replace("]","@");
    QStringList strList = strRecvData.split("@");
    if(strList[2].indexOf("SENSOR") == 0)
    {
        emit sensorDataSig(strRecvData);
    }
}

void Socket::on_pLEClientID_selectionChanged()
{
    QLineEdit *pQLineEdit = (QLineEdit *)sender();
    pKeyboard->setLineEdit(pQLineEdit);
    pKeyboard->show();
}


void Socket::on_pLESendData_selectionChanged()
{
    QLineEdit *pQLineEdit = (QLineEdit *)sender();
    pKeyboard->setLineEdit(pQLineEdit);
    pKeyboard->show();
}


void Socket::on_pPBSend_clicked()
{
    QString strRecvId = ui->pLEClientID->text();
    QString strSendData = ui->pLESendData->text();
    if(strRecvId.isEmpty())
    {
        strSendData = "[ALLMSG]" + strSendData;
    }
    else
    {
        strSendData = "["+strRecvId+"]" + strSendData;
    }
    pSocketClient->socketWriteDataSlot(strSendData);
    ui->pLESendData->clear();
}


void Socket::on_pPBRecvDataClear_clicked()
{
    ui->pTERecvData->clear();
}


Socket::~Socket()
{
    delete ui;
}

