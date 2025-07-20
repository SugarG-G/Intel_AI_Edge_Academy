#include "tab2socketclient.h"
#include "ui_tab2socketclient.h"

Tab2SocketClient::Tab2SocketClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tab2SocketClient)
{
    ui->setupUi(this);
    pKeyBoard = new Keyboard();
    ui->pPBSend->setEnabled(false);
    pSocketClient = new SocketClient(this);
    connect(pSocketClient, SIGNAL(socketRecvDataSig(QString)),this, SLOT(updateRecvDataSlot(QString)));

//    on_pPBserverConnect_toggled(true);
}

Tab2SocketClient::~Tab2SocketClient()
{
    delete ui;
}

void Tab2SocketClient::on_pPBserverConnect_toggled(bool checked)
{
    bool bFlag;
//    qDebug() << "on_pPBserverConnect_toggled()";
    if(checked)
    {
        pSocketClient->connectToServerSlot(bFlag);
        if(bFlag)
        {
            ui->pPBserverConnect->setText("서버 해제");
            ui->pPBSend->setEnabled(true);
        }
    }
    else {
        pSocketClient->socketClosedServerSlot();
        ui->pPBserverConnect->setText("서버 연결");
        ui->pPBSend->setEnabled(false);
    }
}

 void Tab2SocketClient::updateRecvDataSlot(QString strRecvData)
{
    strRecvData.chop(1);   //끝문자 한개 "\n" 제거
    QTime time = QTime::currentTime();
    QString strTime = time.toString();
    strTime = strTime + " " + strRecvData;
    ui->pTErecvData->append(strTime);

    //[KSH_QT]@LED@0xff  ==> @KSH_QT@LED@0xff
    strRecvData.replace("[","@");
    strRecvData.replace("]","@");
    QStringList strList = strRecvData.split("@");
    if(strList[2].indexOf("LED") == 0)
    {
        bool bFlag;
        int ledNo = strList[3].toInt(&bFlag,16);
        if(bFlag)
            emit ledWriteSig(ledNo);
    }
    else if((strList[2].indexOf("LAMP") == 0) || (strList[2].indexOf("PLUG") == 0) || (strList[2].indexOf("GAS") == 0))
    {
        emit tab3RecvDataSig(strRecvData);
    }
    else if(strList[2].indexOf("SENSOR") == 0)
    {
        emit tab4RecvDataSig(strRecvData);
        emit tab5RecvDataSig(strRecvData);
    }
}

void Tab2SocketClient::on_pPBrecvDataClear_clicked()
{
    ui->pTErecvData->clear();
}

void Tab2SocketClient::on_pPBSend_clicked()
{
    QString strRecvId = ui->pLErecvId->text();
    QString strSendData = ui->pLEsendData->text();
    if(strRecvId.isEmpty())
    {
        strSendData = "[ALLMSG]" + strSendData;
    }
    else
    {
        strSendData = "["+strRecvId+"]" + strSendData;
    }
    pSocketClient->socketWriteDataSlot(strSendData);
    ui->pLEsendData->clear();
}

void Tab2SocketClient::socketSendToLinux(int keyNo)
{
    pSocketClient->socketWriteDataSlot("[KSH_LIN]KEY@"+QString::number(keyNo));
}

SocketClient * Tab2SocketClient::getpSocketClient()
{
    return pSocketClient;
}


void Tab2SocketClient::on_pLErecvId_selectionChanged()
{
    QLineEdit *pQLineEdit = (QLineEdit *)sender();
    pKeyBoard->setLineEdit(pQLineEdit);
    pKeyBoard->show();
}


void Tab2SocketClient::on_pLEsendData_selectionChanged()
{
    QLineEdit *pQLineEdit = (QLineEdit *)sender();
    pKeyBoard->setLineEdit(pQLineEdit);
    pKeyBoard->show();
}

