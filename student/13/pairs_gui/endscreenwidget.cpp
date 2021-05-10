#include "endscreenwidget.hh"
#include "ui_endscreenwidget.h"

EndscreenWidget::EndscreenWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EndscreenWidget)
{
    ui->setupUi(this);
}

EndscreenWidget::~EndscreenWidget()
{
    delete ui;
}
