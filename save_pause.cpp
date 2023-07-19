#include "save_pause.h"
#include "ui_save_pause.h"

save_pause::save_pause(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::save_pause) {
    ui->setupUi(this);
}

save_pause::~save_pause() {
    delete ui;
}

void save_pause::on_btn_save_clicked() {
    emit ExitS();
    this->hide();
}

void save_pause::on_btn_pause_clicked() {
    this->hide();
    emit StartS();
}
