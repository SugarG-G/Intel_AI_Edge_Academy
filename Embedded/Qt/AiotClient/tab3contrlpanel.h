#ifndef TAB3CONTRLPANEL_H
#define TAB3CONTRLPANEL_H

#include <QWidget>

namespace Ui {
class Tab3ContrlPanel;
}

class Tab3ContrlPanel : public QWidget
{
    Q_OBJECT

public:
    explicit Tab3ContrlPanel(QWidget *parent = nullptr);
    ~Tab3ContrlPanel();

private:
    Ui::Tab3ContrlPanel *ui;
};

#endif // TAB3CONTRLPANEL_H
