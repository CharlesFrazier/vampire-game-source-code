#include "mwid.h"

mwid::mwid(QWidget *parent) : QMainWindow(parent) {
    addhp = new QPushButton(this);
    addatk = new QPushButton(this);
    addae = new QPushButton(this);
    addcd = new QPushButton(this);
    addpk = new QPushButton(this);
    adddt = new QPushButton(this);
    addsp = new QPushButton(this);
    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(10);
    layout->setContentsMargins(10,10,10,10);
    this->setFixedSize(800,250);
    this->setWindowModality(Qt::ApplicationModal);
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);

    addhp->setText("血量");
    addcd->setText("冷却");
    addatk->setText("攻击");
    addae->setText("攻击范围");
    addsp->setText("移速");
    addpk->setText("拾取范围");
    adddt->setText("技能时间");

    addhp->hide();
    addcd->hide();
    addatk->hide();
    addae->hide();
    addsp->hide();
    addpk->hide();
    adddt->hide();

    vectors.push_back(addhp);
    vectors.push_back(addcd);
    vectors.push_back(addatk);
    vectors.push_back(addae);
    vectors.push_back(addsp);
    vectors.push_back(addpk);
    vectors.push_back(adddt);
}

void mwid::redom() {
    srand(time(NULL));
    for (int i = 0; i < 3; i++) {
        int r = rand() % 7;
        bool repeat = false;
        for (int j = 0; j < i; j++)
            if (r == index[j]) {
                repeat = true;
                break;
            }
        if (repeat) {
            i--;
            continue;
        }
        index[i] = r;
    }
    int buttonWidth = 150;
    int buttonHeight = 100;
    int buttonSpacing = 50;
    int layoutWidth = layout->geometry().width();
    while (QLayoutItem* item = layout->takeAt(0))
        if (QWidget* widget = item->widget())
            layout->removeWidget(widget);
    for(int k = 0; k < 3; k++) {
        QPushButton* button = vectors[index[k]];
        int buttonX = (layoutWidth -3*buttonWidth-2*buttonSpacing)/2+k*(buttonWidth+buttonSpacing)+350;
        button->setGeometry(buttonX,50,buttonWidth,buttonHeight);
        layout->addWidget(button);
        button->show();
    }
    layout->activate();
    this->show();
}

void mwid::set(class data *d) {
    mdata = d;
    connect(addhp,&QPushButton::clicked,[&](){
        mdata->ad_hp+=5;
        this->close();
        emit StartM();
    });
    connect(addatk,&QPushButton::clicked,[&](){
        mdata->ad_atk+=1;
        this->close();
        emit StartM();
    });
    connect(addsp,&QPushButton::clicked,[&](){
        mdata->ad_sp+=1;
        this->close();
        emit StartM();
    });
    connect(addcd,&QPushButton::clicked,[&](){
        mdata->ad_cd-=1;
        this->close();
        emit StartM();
    });
    connect(addae,&QPushButton::clicked,[&](){
        mdata->ad_ar+=1;
        this->close();
        emit StartM();
    });
    connect(addpk,&QPushButton::clicked,[&](){
        mdata->ad_pk+=1;
        this->close();
        emit StartM();
    });
    connect(adddt,&QPushButton::clicked,[&](){
        mdata->ad_dt+=1;
        this->close();
        emit StartM();
    });
}
