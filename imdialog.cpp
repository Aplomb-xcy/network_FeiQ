#include "imdialog.h"
#include "ui_imdialog.h"

IMDialog::IMDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::IMDialog)
{
    ui->setupUi(this);
}

IMDialog::~IMDialog()
{
    delete ui;
}

