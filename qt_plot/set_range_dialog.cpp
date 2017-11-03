#include "set_range_dialog.h"
#include "ui_set_range_dialog.h"

SetRange_Dialog::SetRange_Dialog(QWidget *parent, RangeContext defaultVal) :
    QDialog(parent),
    ui(new Ui::SetRange_Dialog)
{
    ui->setupUi(this);
    ui->xa_SpinBox->setValue(defaultVal.xa);
    ui->xb_SpinBox->setValue(defaultVal.xb);
    ui->ya_SpinBox->setValue(defaultVal.ya);
    ui->yb_SpinBox->setValue(defaultVal.yb);
}

SetRange_Dialog::~SetRange_Dialog()
{
    delete ui;
}


void SetRange_Dialog::getData(RangeContext& ctx) {
    ctx.xa = ui->xa_SpinBox->value();
    ctx.xb = ui->xb_SpinBox->value();
    ctx.ya = ui->ya_SpinBox->value();
    ctx.yb = ui->yb_SpinBox->value();
}
