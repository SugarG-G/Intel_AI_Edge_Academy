#include "mainwidget.h"
#include "ui_mainwidget.h"

mainwidget::mainwidget(QWidget *parent) : QWidget(parent), ui(new Ui::mainwidget) {
    ui->setupUi(this);

    pQWebEngineView1 = new QWebEngineView(this);
    // pQWebEngineView->load(QUrl("http://www.naver.com"));
    pQWebEngineView1->load(QUrl("http://192.168.0.83:8080/?action=stream"));
    ui->pVLCam1->addWidget(pQWebEngineView1);

    pQWebEngineView2 = new QWebEngineView(this);
    // pQWebEngineView->load(QUrl("http://www.naver.com"));
    pQWebEngineView2->load(QUrl("http://192.168.0.84:8080/?action=stream"));
    ui->pVLCam2->addWidget(pQWebEngineView2);

    pQWebEngineView3 = new QWebEngineView(this);
    // pQWebEngineView->load(QUrl("http://www.naver.com"));
    pQWebEngineView3->load(QUrl("http://192.168.0.85:8080/?action=stream"));
    ui->pVLCam3->addWidget(pQWebEngineView3);

    pQWebEngineView4 = new QWebEngineView(this);
    // pQWebEngineView->load(QUrl("http://www.naver.com"));
    pQWebEngineView4->load(QUrl("http://192.168.0.86:8080/?action=stream"));
    ui->pVLCam4->addWidget(pQWebEngineView4);
}

mainwidget::~mainwidget() {
    delete ui;
}
