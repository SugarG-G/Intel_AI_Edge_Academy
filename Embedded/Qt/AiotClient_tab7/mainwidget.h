#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "tab1devcontrol.h"
#include "tab2socketclient.h"
#include "tab3controlpannel.h"
#include "tab4sensorchart.h"
#include "tab5sensordatabase.h"
#include "tab6webcamera.h"
#include "tab7camviewthread.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    Tab1DevControl *pTab1DevControl;
    Tab2SocketClient *pTab2SocketClient;
    Tab3ControlPannel *pTab3ControlPannel;
    Tab4SensorChart *pTab4SensorChart;
    Tab5SensorDatabase *pTab5SensorDatabase;
    Tab6WebCamera *pTab6WebCamera;
    Tab7CamViewThread *pTab7CamViewThread;
};
#endif // MAINWIDGET_H
