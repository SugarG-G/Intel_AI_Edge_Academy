#ifndef TAB2CONTROLPANEL_H
#define TAB2CONTROLPANEL_H

#include <QWidget>

namespace Ui {
class Tab2ControlPanel;
}

class Tab2ControlPanel : public QWidget
{
    Q_OBJECT

public:
    explicit Tab2ControlPanel(QWidget *parent = nullptr);
    ~Tab2ControlPanel();

private:
    Ui::Tab2ControlPanel *ui;
};

#endif // TAB2CONTROLPANEL_H
