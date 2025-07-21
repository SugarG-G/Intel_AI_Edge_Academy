#ifndef TAB7CAMVIEWTHREAD_H
#define TAB7CAMVIEWTHREAD_H

#include <QWidget>
#include <QDebug>
#include "webcamthread.h"

namespace Ui
{
class Tab7CamViewThread;
}

class Tab7CamViewThread : public QWidget
{
        Q_OBJECT

    public:
        explicit Tab7CamViewThread(QWidget *parent = nullptr);
        ~Tab7CamViewThread();

        WebCamThread* getpWebCamThread();

    private slots:
        void on_pPBcamStart_clicked(bool checked);

        void on_pPBsnapShot_clicked();

        void on_pCBrgb_clicked(bool checked);

    private:
        Ui::Tab7CamViewThread *ui;
        WebCamThread *pWebCamThread;
};

#endif // TAB7CAMVIEWTHREAD_H
