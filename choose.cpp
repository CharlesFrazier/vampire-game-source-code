#include "choose.h"
#include "ui_choose.h"

choose::choose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choose) {
    ui->setupUi(this);
    this->setFixedSize(1800,1350+30);
    this->setWindowTitle("幸存者");

    QLabel *label1 = new QLabel(this);
    label1->setGeometry(200,180,300,300);
    QMovie *movie1 = new QMovie("://img//w1.gif");
    movie1->setScaledSize(QSize(300,300));
    label1->setMovie(movie1);
    movie1->start();
    label1->show();

    QLabel *label3 = new QLabel(this);
    label3->setGeometry(260,500,80,80);
    QImage *img3 = new QImage();
    img3->load("://img//w1.png");
    img3->scaled(80,80,Qt::KeepAspectRatio);
    label3->setScaledContents(true);
    label3->setPixmap(QPixmap::fromImage(*img3));

    QLabel *label2 = new QLabel(this);
    label2->setGeometry(200,700,300,300);
    QMovie *movie2 = new QMovie("://img//w2.gif");
    movie2->setScaledSize(QSize(200,300));
    label2->setMovie(movie2);
    movie2->start();
    label1->show();

    QLabel *label4 = new QLabel(this);
    label4->setGeometry(260,1050,80,80);
    QImage *img4 = new QImage();
    img4->load("://img//w2.png");
    img4->scaled(80,80,Qt::KeepAspectRatio);
    label4->setScaledContents(true);
    label4->setPixmap(QPixmap::fromImage(*img4));


    ui->treeWidget->setHeaderLabels(QStringList()<<"player1"<<"属性");
    hp1 = new QTreeWidgetItem(QStringList()<<"生命值"<<"");
    atk1 = new QTreeWidgetItem(QStringList()<<"攻击力"<<"");
    sp1 = new QTreeWidgetItem(QStringList()<<"移动速度"<<"");
    pk1 = new QTreeWidgetItem(QStringList()<<"拾取范围"<<"");
    QTreeWidgetItem* non1 = new QTreeWidgetItem(QStringList()<<""<<"");
    ae1 = new QTreeWidgetItem(QStringList()<<"伤害区域"<<"");
    dt1 = new QTreeWidgetItem(QStringList()<<"持续时间"<<"");
    cd1 = new QTreeWidgetItem(QStringList()<<"冷却时间"<<"");
    ui->treeWidget->addTopLevelItem(hp1);
    ui->treeWidget->addTopLevelItem(atk1);
    ui->treeWidget->addTopLevelItem(sp1);
    ui->treeWidget->addTopLevelItem(pk1);
    ui->treeWidget->addTopLevelItem(non1);
    ui->treeWidget->addTopLevelItem(ae1);
    ui->treeWidget->addTopLevelItem(dt1);
    ui->treeWidget->addTopLevelItem(cd1);


    ui->treeWidget_2->setHeaderLabels(QStringList()<<"player2"<<"属性");
    hp2 = new QTreeWidgetItem(QStringList()<<"生命值"<<"");
    atk2 = new QTreeWidgetItem(QStringList()<<"攻击力"<<"");
    sp2 = new QTreeWidgetItem(QStringList()<<"移动速度"<<"");
    pk2 = new QTreeWidgetItem(QStringList()<<"拾取范围"<<"");
    QTreeWidgetItem* non2 = new QTreeWidgetItem(QStringList()<<""<<"");
    ae2 = new QTreeWidgetItem(QStringList()<<"伤害区域"<<"");
    dt2 = new QTreeWidgetItem(QStringList()<<"持续时间"<<"");
    cd2 = new QTreeWidgetItem(QStringList()<<"冷却时间"<<"");
    ui->treeWidget_2->addTopLevelItem(hp2);
    ui->treeWidget_2->addTopLevelItem(atk2);
    ui->treeWidget_2->addTopLevelItem(sp2);
    ui->treeWidget_2->addTopLevelItem(pk2);
    ui->treeWidget_2->addTopLevelItem(non2);
    ui->treeWidget_2->addTopLevelItem(ae2);
    ui->treeWidget_2->addTopLevelItem(dt2);
    ui->treeWidget_2->addTopLevelItem(cd2);
}

void choose::set(class data * d, scene *s) {
    mdata = d;
    mscene = s;
}

void choose::load() {
    hp1->setText(1,QString::number(mdata->player1.hp));
    atk1->setText(1,QString::number(mdata->player1.atk));
    sp1->setText(1,QString::number(mdata->player1.sp));
    dt1->setText(1,QString::number(mdata->player1.dt));
    cd1->setText(1,QString::number(mdata->player1.cd));
    pk1->setText(1,QString::number(mdata->player1.pk));
    ae1->setText(1,QString::number(mdata->player1.ar));

    hp2->setText(1,QString::number(mdata->player2.hp));
    atk2->setText(1,QString::number(mdata->player2.atk));
    sp2->setText(1,QString::number(mdata->player2.sp));
    dt2->setText(1,QString::number(mdata->player2.dt));
    cd2->setText(1,QString::number(mdata->player2.cd));
    pk2->setText(1,QString::number(mdata->player2.pk));
    ae2->setText(1,QString::number(mdata->player2.ar));
}

choose::~choose() {
    delete ui;
}

void choose::on_btn_chs1_clicked()  {
    mdata->choice=1;
    this->hide();
    mscene->load();
    mscene->restart();
    mscene->show();
}

void choose::on_btn_chs2_clicked() {
    mdata->choice=2;
    this->hide();
    mscene->load();
    mscene->restart();
    mscene->show();
}

void choose::on_btn_back_clicked() {
    this->hide();
    emit ExitC();
}
