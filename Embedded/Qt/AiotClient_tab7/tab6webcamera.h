#ifndef TAB6WEBCAMERA_H
#define TAB6WEBCAMERA_H

#include <QWidget>
#include <QWebEngineView>
#include <QProcess>
#include <QGraphicsPixmapItem>
#include <QThread>

namespace Ui {
class Tab6WebCamera;
}

class Tab6WebCamera : public QWidget
{
    Q_OBJECT

public:
    explicit Tab6WebCamera(QWidget *parent = nullptr);
    ~Tab6WebCamera();

private:
    Ui::Tab6WebCamera *ui;
    QWebEngineView *pQWebEngineView;
    QProcess *pQProcess;
    QUrl webcamUrl;

private slots:
    void camStartSlot(bool);
};

#endif // TAB6WEBCAMERA_H
