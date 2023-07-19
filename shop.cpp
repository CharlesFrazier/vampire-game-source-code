#include "shop.h"
#include "ui_shop.h"

shop::shop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::shop) {
    ui->setupUi(this);
    atk= new QTableWidgetItem ();
    atk->setText ("");
    ui->table->setItem (0,0,atk);
    hp= new QTableWidgetItem ();
    hp->setText ("");
    ui->table->setItem (1,0,hp);
    sp= new QTableWidgetItem ();
    sp->setText ("");
    ui->table->setItem (2,0,sp);
    cd= new QTableWidgetItem ();
    cd->setText ("");
    ui->table->setItem (3,0,cd);
    dt= new QTableWidgetItem ();
    dt->setText ("");
    ui->table->setItem (4,0,dt);
    pk= new QTableWidgetItem ();
    pk->setText ("");
    ui->table->setItem (5,0,pk);
    ar= new QTableWidgetItem ();
    ar->setText ("");
    ui->table->setItem (6,0,ar);
    rec= new QTableWidgetItem ();
    rec->setText ("");
    ui->table->setItem (7,0,rec);
    rate= new QTableWidgetItem ();
    rate->setText ("");
    ui->table->setItem (8,0,rate);
    connect(ui->btn_back,SIGNAL(clicked()),this,SLOT(exits()));
}

void shop::set(class data *d) {
    mdata = d;
    ui->textBrowser->setText(QString::number(mdata->coin));
}

void shop::load() {
    ui->textBrowser->setText(QString::number(mdata->coin));
}

void shop::exits() {
    this->hide();
    emit EmitS();
}

shop::~shop() {
    delete ui;
}

void shop::box() {
    QMessageBox box;
    box.setText("你没币了！");
    box.exec();
    return;
}
void shop::on_player1_clicked() {
    choice=1;
    atk->setText(QString::number(mdata->player1.atk));
    hp->setText(QString::number(mdata->player1.hp));
    sp->setText(QString::number(mdata->player1.sp));
    cd->setText(QString::number(mdata->player1.cd));
    dt->setText(QString::number(mdata->player1.dt));
    pk->setText(QString::number(mdata->player1.pk));
    ar->setText(QString::number(mdata->player1.ar));
    rec->setText(QString::number(mdata->rec));
    rate->setText(QString::number(mdata->coin_rate));
}

void shop::on_player2_clicked() {
    choice=2;
    atk->setText(QString::number(mdata->player2.atk));
    hp->setText(QString::number(mdata->player2.hp));
    sp->setText(QString::number(mdata->player2.sp));
    cd->setText(QString::number(mdata->player2.cd));
    dt->setText(QString::number(mdata->player2.dt));
    pk->setText(QString::number(mdata->player2.pk));
    ar->setText(QString::number(mdata->player2.ar));
    rec->setText(QString::number(mdata->rec));
    rate->setText(QString::number(mdata->coin_rate));
}

void shop::on_atk_clicked() {
    if(mdata->coin<20) {
        box();
        return;
    }
    if(choice==1) {
        mdata->player1.atk+=1;
        ui->player1->click();
    }
    else if(choice==2) {
        mdata->player2.atk+=1;
        ui->player2->click();
    }
    mdata->coin-=20;
    ui->textBrowser->setText(QString::number(mdata->coin));
}

void shop::on_hp_clicked() {
    if (mdata->coin<20) {
        box();
        return;
    }
    if (choice==1) {
        mdata->player1.hp+=5;
        ui->player1->click();
    }
    else if(choice==2) {
        mdata->player2.hp+=5;
        ui->player2->click();
    }
    mdata->coin-=20;
    ui->textBrowser->setText(QString::number(mdata->coin));
}

void shop::on_sp_clicked() {
    if(mdata->coin<20) {
        box();
        return;
    }
    if(choice==1) {
        mdata->player1.sp+=1;
        ui->player1->click();
    }
    else if(choice==2) {
        mdata->player2.sp+=1;
        ui->player2->click();
    }
    mdata->coin-=20;
    ui->textBrowser->setText(QString::number(mdata->coin));
}

void shop::on_cd_clicked() {
    if(mdata->coin<20) {
        box();
        return;
    }
    if(choice==1) {
        mdata->player1.cd-=1;
        ui->player1->click();
    }
    else if(choice==2) {
        mdata->player2.cd-=1;
        ui->player2->click();
    }
    mdata->coin-=20;
    ui->textBrowser->setText(QString::number(mdata->coin));
}

void shop::on_dt_clicked() {
    if(mdata->coin<20) {
        box();
        return;
    }
    if(choice==1) {
        mdata->player1.dt+=1;
        ui->player1->click();
    }
    else if(choice==2) {
        mdata->player2.dt+=1;
        ui->player2->click();
    }
    mdata->coin-=20;
    ui->textBrowser->setText(QString::number(mdata->coin));
}

void shop::on_pk_clicked() {
    if(mdata->coin<20) {
        box();
        return;
    }
    if(choice==1) {
        mdata->player1.pk+=1;
        ui->player1->click();
    }
    else if(choice==2) {
        mdata->player2.pk+=1;
        ui->player2->click();
    }
    mdata->coin-=20;
    ui->textBrowser->setText(QString::number(mdata->coin));
}

void shop::on_ar_clicked() {
    if(mdata->coin<20) {
        box();
        return;
    }
    if(choice==1) {
        mdata->player1.ar+=1;
        ui->player1->click();
    }
    else if(choice==2) {
        mdata->player2.ar+=1;
        ui->player2->click();
    }
    mdata->coin-=20;
    ui->textBrowser->setText(QString::number(mdata->coin));
}

void shop::on_rec_clicked() {
    if(mdata->coin<50) {
        box();
        return;
    }
    if(choice==1) {
        mdata->rec+=1;
        ui->player1->click();
    }
    else if(choice==2) {
        mdata->rec+=1;
        ui->player2->click();
    }
    mdata->coin-=50;
    ui->textBrowser->setText(QString::number(mdata->coin));
}

void shop::on_rate_clicked() {
    if(mdata->coin<50) {
        box();
        return;}
    if(choice==1) {mdata->coin_rate+=0.1;
        ui->player1->click();
    }
    else if(choice==2) {
        mdata->coin_rate+=0.1;
        ui->player2->click();
    }
    mdata->coin-=50;
    ui->textBrowser->setText(QString::number(mdata->coin));
}

void shop::on_coin_clicked() {
    mdata->coin+=10;
    ui->textBrowser->setText(QString::number(mdata->coin));
}
