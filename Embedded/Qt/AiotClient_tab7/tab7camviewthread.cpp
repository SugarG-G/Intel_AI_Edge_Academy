#include "tab7camviewthread.h"
#include "ui_tab7camviewthread.h"

Tab7CamViewThread::Tab7CamViewThread(QWidget *parent) : QWidget(parent), ui(new Ui::Tab7CamViewThread)
{
    ui->setupUi(this);
    setWindowTitle("CamViewer");
    ui->pPBsnapShot->setEnabled(false);
    pWebCamThread = new WebCamThread(this);
    pWebCamThread->pCamView = ui->plabelCamView;
}

Tab7CamViewThread::~Tab7CamViewThread() { delete ui; }

void Tab7CamViewThread::on_pPBcamStart_clicked(bool checked)
{
    if(checked)
    {
        pWebCamThread->camViewFlag = true;
        //       qDebug() << "on_pPBcamStart_clicked 1 ";
        if(!pWebCamThread->isRunning())
        {
            pWebCamThread->start();
            ui->pPBcamStart->setText("CamStop");
            ui->pPBsnapShot->setEnabled(true);
        }
    }
    else
    {
        //            qDebug() << "on_pPBcamStart_clicked 2";
        pWebCamThread->camViewFlag = false;
        ui->pPBcamStart->setText("CamStart");
        ui->pPBsnapShot->setEnabled(false);
    }
}


void Tab7CamViewThread::on_pPBsnapShot_clicked()
{
    pWebCamThread->snapShot();
}

