#ifndef TAB3CONTROLPANEL_H
#define TAB3CONTROLPANEL_H

#include <QWidget>
#include <QPalette>

namespace Ui {
class Tab3ControlPanel;
}

class Tab3ControlPanel : public QWidget
{
    Q_OBJECT

public:
    explicit Tab3ControlPanel(QWidget *parent = nullptr);
    ~Tab3ControlPanel();

private slots:
    void tab3RecvDataSlot(QString);

    void on_pPBlamp_clicked(bool checked);

    void on_pPBplug_clicked(bool checked);

private:
    Ui::Tab3ControlPanel *ui;
    QPalette paletteOn;
    QPalette paletteOff;

signals:
    void sendControlDataSig(QString);
};

#endif // TAB3CONTROLPANEL_H
