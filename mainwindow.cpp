#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setFixedSize(1800,1350+30);
    this->setWindowTitle("幸存者");
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
    mdata = new class data;
    msave_pause = new save_pause;
    mscene = new scene;
    mscene->set(mdata,msave_pause);
    mshop = new shop;
    mshop->set(mdata);
    mchoose = new choose;
    mchoose->set(mdata, mscene);
    connect(mshop,SIGNAL(EmitS()),this,SLOT(show()));
    connect(mscene,SIGNAL(ExitM()),this,SLOT(show()));
    connect(mchoose,SIGNAL(ExitC()),this,SLOT(show()));
    connect(ui->btn_quit,SIGNAL(clicked()),this,SLOT(quit()));
    connect(msave_pause,SIGNAL(ExitS()),this,SLOT(show()));
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0,0+30,2700,1350,QPixmap(":/img/startBK.jpg"));
    painter.drawPixmap(1100,100+30,600,300,QPixmap(":/img/startBK2.png"));
}

void MainWindow::quit() {
    save_game();
    this->close();
}

void MainWindow::which_show() {
    if(mdata->choice==0) {
        mchoose->load();
        mchoose->show();
    } else {
        mscene->load();
        mscene->restart();
        mscene->show();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::save_game() {
    ofstream fout;
    fout.open("D:/source.txt",ios::out);
    fout<<mdata->player1.atk<<" "<<mdata->player1.hp<<" "<<mdata->player1.sp<<" "<<mdata->player1.cd<<" "<<mdata->player1.dt<<" "<<mdata->player1.pk<<" "<<mdata->player1.ar<<" "<<mdata->player1.x<<" "<<mdata->player1.y<<"\n";
    fout<<mdata->player2.atk<<" "<<mdata->player2.hp<<" "<<mdata->player2.sp<<" "<<mdata->player2.cd<<" "<<mdata->player2.dt<<" "<<mdata->player2.pk<<" "<<mdata->player2.ar<<" "<<mdata->player2.x<<" "<<mdata->player2.y<<"\n";
    fout<<mdata->choice<<"\n"<<mdata->coin<<" "<<mdata->rec<<" "<<mdata->exp<<" "<<mdata->level<<" "<<mdata->time<<"\n"<<mdata->coin_rate<<"\n";
    fout<<mdata->ad_atk<<" "<<mdata->ad_hp<<" "<<mdata->ad_sp<<" "<<mdata->ad_cd<<" "<<mdata->ad_dt<<" "<<mdata->ad_pk<<" "<<mdata->ad_ar;
    fout.close();
}

void MainWindow::on_btn_shop_clicked() {
    this->hide();
    mshop->show();
}

void MainWindow::on_btn_start_clicked() {
    this->hide();
    which_show();
}
