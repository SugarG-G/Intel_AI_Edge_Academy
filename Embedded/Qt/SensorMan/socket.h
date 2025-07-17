#ifndef SOCKET_H
#define SOCKET_H

#include <QWidget>
#include <QDebug>
#include <QTime>
#include <QLineEdit>
#include "socketclient.h"
#include "keyboard.h"

namespace Ui {
class Socket;
}

class Socket : public QWidget
{
    Q_OBJECT

public:
    explicit Socket(QWidget *parent = nullptr);
    ~Socket();

private slots:
    void on_pPBServerConnect_toggled(bool checked);

    void updateRecvDataSlot(QString);

    void on_pLEClientID_selectionChanged();

    void on_pLESendData_selectionChanged();

    void on_pPBSend_clicked();

    void on_pPBRecvDataClear_clicked();

private:
    Ui::Socket *ui;
    SocketClient *pSocketClient;
    Keyboard *pKeyboard;

signals:
    void sensorDataSig(QString);
};

#endif // SOCKET_H
