#include "tab3contrlpanel.h"
#include "ui_tab3contrlpanel.h"

Tab3ContrlPanel::Tab3ContrlPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tab3ContrlPanel)
{
    ui->setupUi(this);
}

Tab3ContrlPanel::~Tab3ContrlPanel()
{
    delete ui;
}
