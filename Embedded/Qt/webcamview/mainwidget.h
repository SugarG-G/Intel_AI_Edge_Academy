#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QWebEngineView>

QT_BEGIN_NAMESPACE
namespace Ui
{
class mainwidget;
}
QT_END_NAMESPACE

class mainwidget : public QWidget
{
        Q_OBJECT

    public:
        mainwidget(QWidget *parent = nullptr);
        ~mainwidget();

    private:
        Ui::mainwidget *ui;
        QWebEngineView *pQWebEngineView1;
        QWebEngineView *pQWebEngineView2;
        QWebEngineView *pQWebEngineView3;
        QWebEngineView *pQWebEngineView4;
};
#endif // MAINWIDGET_H
