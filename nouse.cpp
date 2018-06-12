#include "nouse.h"
#include "ui_nouse.h"

NoUse::NoUse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NoUse) {
    ui->setupUi(this);
}

NoUse::~NoUse() {
    delete ui;
}
