#ifndef TAB2SOCKETCLIENT_H
#define TAB2SOCKETCLIENT_H

#include <QWidget>
#include <QDebug>
#include <QTime>
#include "socketclient.h"
namespace Ui {
class Tab2SocketClient;
}

class Tab2SocketClient : public QWidget
{
    Q_OBJECT

public:
    explicit Tab2SocketClient(QWidget *parent = nullptr);
    ~Tab2SocketClient();

private slots:
    void on_pPBserverConnect_toggled(bool checked);
    void updateRecvDataSlot(QString);
    void on_pPBrecvDataClear_clicked();
    void on_pPBSend_clicked();
    void socketSendToLinux(int);
signals:
    void ledWriteSig(int);
private:
    Ui::Tab2SocketClient *ui;
    SocketClient *pSocketClient;

};

#endif // TAB2SOCKETCLIENT_H
