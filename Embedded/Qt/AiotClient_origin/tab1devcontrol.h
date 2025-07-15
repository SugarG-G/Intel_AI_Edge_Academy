#ifndef TAB1DEVCONTROL_H
#define TAB1DEVCONTROL_H

#include <QWidget>
#include <QTimer>
#include <QButtonGroup>
#include "ledkeydev.h"

namespace Ui {
class Tab1DevControl;
}

class Tab1DevControl : public QWidget
{
    Q_OBJECT

public:
    explicit Tab1DevControl(QWidget *parent = nullptr);
    ~Tab1DevControl();

private slots:
    void on_pPushButtoiTimerStart_clicked(bool checked);
    void updateDialValue();

    void on_pComboBoxTimerValue_currentTextChanged(const QString &arg1);

    void updateCheckBoxKey(int);
    void updateCheckBoxMouseSlot(int);
    void stopQtimer();

private:
    Ui::Tab1DevControl *ui;
    LedKeyDev *pLedKeyDev;
    QTimer *pQTimer;
    QButtonGroup *pQButtonGroup;
    QCheckBox *pQCheckBox[8];
    unsigned char lcdData = 0;

};

#endif // TAB1DEVCONTROL_H
