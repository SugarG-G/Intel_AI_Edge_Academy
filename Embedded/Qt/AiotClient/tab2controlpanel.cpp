#include "tab2controlpanel.h"
#include "ui_tab2controlpanel.h"

Tab2ControlPanel::Tab2ControlPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tab2ControlPanel)
{
    ui->setupUi(this);
}

Tab2ControlPanel::~Tab2ControlPanel()
{
    delete ui;
}
