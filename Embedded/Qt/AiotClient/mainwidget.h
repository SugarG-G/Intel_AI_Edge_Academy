#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "tab1devcontrol.h"
#include "tab2socketclient.h"
#include "tab3controlpanel.h"
#include "tab4sensorchart.h"
#include "tab5sensordatabase.h"

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
    Tab3ControlPanel *pTab3ControlPanel;
    Tab4SensorChart *pTab4SensorChart;
    Tab5SensorDatabase *pTab5SensorDatabase;
};
#endif // MAINWIDGET_H
