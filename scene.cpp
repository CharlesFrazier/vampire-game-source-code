#include "scene.h"
#include "ui_scene.h"

scene::scene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::scene) {
    ui->setupUi(this);
    this->setFixedSize(1800,1350+min);
    is_win=false;
    is_end=false;
    Deadlist deadlist1(75,150);
    stonlist.append(deadlist1);
    Deadlist deadlist2(225,450);
    stonlist.append(deadlist2);
    Deadlist deadlist3(75,750);
    stonlist.append(deadlist3);
    Deadlist deadlist4(600,675);
    stonlist.append(deadlist4);
    Deadlist deadlist5(975,375);
    stonlist.append(deadlist5);
    player = new charactor;
    keyRespondTimer = new QTimer(this);
    bTimer = new QTimer(this);
    bTimer->setInterval(1000);
    qTimer = new QTimer(this);
    qTimer->setInterval(15);
    mTimer = new QTimer(this);
    mTimer->setInterval(600);
    p_1 = new QPixmap(":/img/h1.png");
    p_1->scaled(75,75);
    p_1_hit = new QPixmap(":/img/h1_hit.png");
    p_1_hit->scaled(75,75);
    p_1_HP = new QPixmap(":/img/h1_HP.png");
    p_1_HP->scaled(75,75);
    p_2 = new QPixmap(":/img/h2.png");
    p_2->scaled(75,75);
    p_2_hit = new QPixmap(":/img/h2_hit.png");
    p_2_hit->scaled(75,75);
    p_2_HP = new QPixmap(":/img/h2_HP.png");
    p_2_HP->scaled(75,75);
    p_boss = new QPixmap(":/img/lonng.png");
    p_boss->scaled(75,75);
    p_boss_hit = new QPixmap(":/img/lonng_hit.png");
    p_boss_hit->scaled(75,75);
    p_short = new QPixmap(":/img/shorrt .png");
    p_short->scaled(75,75);
    p_short_hit = new QPixmap(":/img/shorrt_hit.png");
    p_short_hit->scaled(75,75);
    bang_movie = new QMovie(":/img/fire.gif");
    QSize sz(75,75);
    bang_movie->setScaledSize(sz);
}

void scene::set(class data *d, save_pause *s) {
    mdata = d;
    msave_pause = s;
    mwids = new mwid(this);
    mwids->set(mdata);
    connect(msave_pause,SIGNAL(ExitS()),this,SLOT(hide()));
    connect(msave_pause,SIGNAL(StartS()),this,SLOT(restart()));
    connect(mwids,SIGNAL(StartM()),this,SLOT(restart()));
    connect(keyRespondTimer, &QTimer::timeout, this, &scene::slotTimeOut);
    connect(bTimer,SIGNAL(timeout()),this,SLOT(mboss()));
    connect(bTimer,SIGNAL(timeout()),this,SLOT(update_time()));
    connect(bTimer,SIGNAL(timeout()),this,SLOT(mbuild()));
    connect(qTimer,SIGNAL(timeout()),this,SLOT(mmove()));
    connect(mTimer,SIGNAL(timeout()),this,SLOT(mkill()));
    connect(mTimer,SIGNAL(timeout()),this,SLOT(mpick()));
    connect(mTimer,SIGNAL(timeout()),this,SLOT(mjudge()));
    connect(mTimer,SIGNAL(timeout()),this,SLOT(end_pro()));
    connect(this,SIGNAL(enhance3()),mwids,SLOT(redom()));
}

void scene::end_pro() {
    if(is_end==true) {
        std::cerr<<"is_end";
        restop();
        int new_coin = (int)((60-mdata->time)*mdata->coin_rate);
        mdata->ad_ar=0, mdata->ad_atk=0, mdata->ad_cd=0, mdata->ad_dt=0, mdata->ad_hp=0, mdata->ad_sp=0, mdata->ad_pk=0;
        mdata->choice=0;
        mdata->time=60;
        mdata->player1.x=675;
        mdata->player2.x=675;
        mdata->player1.y=525;
        mdata->player2.y=525;
        mdata->exp = 1;
        mdata->coin+=new_coin;
        for(int i=0;i<qlist.size();++i)
            qlist.removeAt(i);
        for(int i=0;i<list.size();++i)
            list.removeAt(i);
        for(int i=0;i<droplist.size();++i)
            droplist.removeAt(i);
        if(is_win==false) {
            QMessageBox msgBox;
            msgBox.setText("复活次数用光了！人家打游戏菜一点 怎么了么~~ 存活时间金币奖励为：");
            msgBox.setInformativeText(QString::number(new_coin));
            msgBox.addButton("返回开始界面",QMessageBox::NoRole);
            int ret = msgBox.exec();
            if(ret==0) {
                this->hide();
                emit ExitM();
            }
        } else {
            is_win=false;
            QMessageBox msgBox;
            msgBox.setText("你居然挑战成功了！下一关更难哟~~存活时间金币奖励为：");
            msgBox.setInformativeText(QString::number(new_coin));
            msgBox.addButton("返回开始界面",QMessageBox::NoRole);
            int ret = msgBox.exec();
            mdata->level++;
            if(ret==0){
                this->hide();
                emit ExitM();
            }
        }
    }
}

void scene::mjudge() {
    if(player->hp==0&&mresurrection!=0) {
        mresurrection--;
        if(mdata->choice==1) {
            player->hp=mdata->player1.hp+mdata->ad_hp;
        } else {
            player->hp=mdata->player2.hp+mdata->ad_hp;
        }
        time_HP=3;

    } else if(player->hp==0&&mresurrection==0) {
        is_end=true;
        is_win=false;
    }
}

void scene::update_time() {
    if(time_HP!=0)
        time_HP--;
    if(mdata->time>0) {
        mdata->time--;
        ui->countDown->display(mdata->time);
    } else {
        mdata->time=0;
        is_end=true;
        is_win=true;
    }
    if(mdata->time%(player->cd+mdata->ad_cd)==0){
        chatacor_short* new_bang = new chatacor_short(ui->label->x(),ui->label->y());
        new_bang->hp=player->dt-mdata->ad_dt+3;
        new_bang->label = new QLabel(this);
        new_bang->label->setGeometry(new_bang->X,new_bang->Y,75,75);
        new_bang->label->setMovie(bang_movie);
        bang_movie->start();
        new_bang->label->show();
        bang.append(*new_bang);
    }
    for(int i = 0; i < bang.size(); i++) {
        bang[i].hp--;
        if(bang[i].hp==0) {
            QLabel *label1 = new QLabel(this);
            label1->setGeometry(bang[i].X-75,bang[i].Y-75,75*3,75*3);
            QMovie *movie1 = new QMovie(":/img/show.gif");
            movie1->setScaledSize(QSize(75*3,75*3));
            label1->setMovie(movie1);
            movie1->start();
            label1->show();
            for(int j = 0; j < list.size(); j++) {
                if(abs(list[j].X-bang[i].X)<150&&abs(list[j].Y-bang[i].Y)<150)
                    list[j].hp-=5*(player->atk+mdata->ad_atk);
            }
            QTimer::singleShot(500,label1,[=](){
                delete label1;
                delete movie1;
            });
            delete bang[i].label;
            bang.removeAt(i);
        }
    }
}

void scene::load() {
    if(mdata->choice==1) {
        *player = mdata->player1;
        ui->label->setPixmap(*p_1);
        ui->label->setScaledContents(true);
    } else {
        *player = mdata->player2;
        ui->label->setPixmap(*p_2);
        ui->label->setScaledContents(true);
    }
    ui->label->move(675,525);
    ui->labelb->move(1725,0);
    ui->labelb->setPixmap(*p_boss);
    ui->HP_bar->setMinimum(0);
    ui->HP_bar->setFixedSize(76,15);
    ui->HP_bar->setMaximum(player->hp);
    ui->HP_bar->move(ui->label->x(),ui->label->y()-15);
    ui->HP_bar->setValue(player->hp);
    ui->expBar->setMinimum(0);
    ui->expBar->setMaximum(mdata->exp);
    ui->expBar->setValue(restr_exp);
    ui->boss_hpbar->setMinimum(0);
    ui->boss_hpbar->setMaximum(mdata->boss_hp);
    ui->boss_hpbar->setValue(boss.hp);
    ui->boss_hpbar->move(1725,0);
    ui->menu1->setTitle(QString::number(mdata->level));
    ui->menu0->setTitle(QString::number(mdata->coin));
    ui->menu02->setTitle(QString::number(mdata->exp));
    mresurrection = mdata->rec;
    ui->menu3->setTitle(QString::number(mresurrection));
}

void scene::mboss() {
    if(boss.hp<=0) {
        ui->labelb->hide();
        ui->boss_hpbar->hide();
        disconnect(bTimer,SIGNAL(timeout()),this,SLOT(mboss()));
        return;
    }
    int y = ui->label->y();
    boss.Y+=75;
    if(boss.Y>2700)boss.Y-=2700;
    if(mdata->time%2==0) {
    if(abs(boss.Y-y)<=75)
        if(time_HP==0) {
            player->hp-=mdata->boss_atk;
            ui->HP_bar->setValue(player->hp);
            if(mdata->choice==1)ui->label->setPixmap(*p_1_hit);else ui->label->setPixmap(*p_2_hit);
            QTimer::singleShot(300,ui->label,[=](){
                if(mdata->choice==1)ui->label->setPixmap(*p_1);
                else ui->label->setPixmap(*p_2);
            });
        }
    QLabel *label1 = new QLabel(this);
    label1->setGeometry(0,1275*((boss.Y/1350)%2)+pow(-1,(boss.Y/1350)%2)*(boss.Y%1350)+min-75,1800,3*75);
    QMovie *movie1 = new QMovie(":/img/boss'k.gif");
    movie1->setScaledSize(QSize(1800,3*75));
    label1->setMovie(movie1);
    movie1->start();
    label1->show();
    QTimer::singleShot(300,label1,[=](){
        delete label1;
        delete movie1;
    });}
    ui->labelb->move(1725,1275*((boss.Y/1350)%2)+pow(-1,(boss.Y/1350)%2)*(boss.Y%1350)+min);
    ui->boss_hpbar->move(ui->labelb->x(),ui->labelb->y()-15);
}

void scene::mkill() {
    int x = ui->label->x(), y = ui->label->y();
    for(int i = 0; i < qlist.size(); i++)
        qlist.clear();
    for(int i = 0; i < list.size(); i++) {
        for(int j = 0; j < bang.size(); j++)
            if(abs(list[i].X-bang[j].X)<75&&abs(list[i].Y-bang[j].Y)<75)
                list[i].hp-=1;
        if(abs(list[i].X-x)<(player->ar+mdata->ad_ar)*75&&abs(list[i].Y-y)<(player->ar+mdata->ad_ar)*75) {
            list[i].hp-=player->atk;
            list[i].progressBar->setValue(list[i].hp);
            list[i].label->setPixmap(*p_short_hit);
            QTimer::singleShot(300,list[i].label,[=](){
                list[i].label->setPixmap(*p_short);
            });
            if(list[i].hp<=0) {
                delete list[i].progressBar;
                delete list[i].label;
                Deadlist dlist(list[i].X,list[i].Y);
                qlist.append(dlist);
                int rad = qrand()%3;
                Drop drop((Drop::Type)rad,list[i].X, list[i].Y);
                droplist.append(drop);
                list.removeAt(i);
            }
        }
    }
    for(int i = 0; i < bang.size(); i++)
        if(abs(boss.X-bang[i].X)<75&&abs(boss.Y-bang[i].Y)<75)
            boss.hp-=1;
    if(abs(1275*((boss.Y/1350)%2)+pow(-1,(boss.Y/1350)%2)*(boss.Y%1350)-y)<=(player->ar+mdata->ad_ar)*75&&abs(boss.X-x)<=(player->ar+mdata->ad_ar)*75) {
        boss.hp-=player->atk+mdata->ad_atk;
        if(boss.hp>0) {
            ui->boss_hpbar->setValue(boss.hp);
            ui->labelb->setPixmap(*p_boss_hit);
            QTimer::singleShot(300,ui->labelb,[=](){
                ui->labelb->setPixmap(*p_boss);
            });
        }
    }
}

void scene::mbuild() {
    int x=0,y=0;
    int mx=ui->label->x(),my=ui->label->y();
    qsrand(QTime::currentTime().msec());
    int rad = qrand()%4;
    switch (rad) {
    case 0:
        x=qrand()%24*75, y=0;
        break;
    case 1:
        x=qrand()%24*75, y = 1275;
        break;
    case 2:
        x=0, y=qrand()%18*75;
        break;
    case 3:
        x=1725, y=qrand()%18*75;
        break;
    default:
        break;
    }
    chatacor_short new_shorrt(x, y);
    QProgressBar* prg = new QProgressBar(this);
    new_shorrt.progressBar = prg;
    QLabel* lbl = new QLabel(this);
    new_shorrt.label = lbl;
    prg->setRange(0,30);
    prg->setValue(30);
    prg->setTextVisible(false);
    prg->setGeometry(x,y-15,75,15);
    lbl->setGeometry(x,y,75,75);
    lbl->move(x,y+min);
    lbl->setPixmap(*p_short);
    lbl->show();
    lbl->setScaledContents(true);
    prg->move(x,y-23+min);
    prg->show();
    list.append(new_shorrt);
    for(int k = 0; k < list.size(); k++)
        if(abs(list[k].X-mx)<75&&abs(list[k].Y-my)<75)
            if(time_HP==0) {
                player->hp-=mdata->short_atk;
                ui->HP_bar->setValue(player->hp);
                if(mdata->choice==1)
                    ui->label->setPixmap(*p_1_hit);
                else ui->label->setPixmap(*p_2_hit);
                QTimer::singleShot(300,ui->label,[=](){
                    if(mdata->choice==1)
                        ui->label->setPixmap(*p_1);
                    else ui->label->setPixmap(*p_2);
                });
            }
}

void scene::mmove() {
    int x = ui->label->x(), y = ui->label->y();
    for(int k = 0; k < list.size(); k++) {
        int p = 75;
        if(abs(list[k].X-x)>=abs(list[k].Y-y)) {
            if(list[k].X<x) {
                if((list[k].X+1>1725)||((list[k].X+p==p)&&(list[k].Y>150-p)&&(list[k].Y<150+p))||((list[k].X+p==225)&&(list[k].Y<450+p)&&(list[k].Y>450-p))||((list[k].X+p==p)&&(list[k].Y<750+p)&&(list[k].Y>750-p))||((list[k].X+p==600)&&(list[k].Y<675+p)&&(list[k].Y>675-p))||((list[k].X+p==975)&&(list[k].Y<375+p)&&(list[k].Y>375-p)));
                else list[k].X+=1;
            } else if(list[k].X>x){
                if((list[k].X-1<0)||((list[k].X-p==p)&&(list[k].Y>150-p)&&(list[k].Y<150+p))||((list[k].X-p==225)&&(list[k].Y<450+p)&&(list[k].Y>450-p))||((list[k].X-p==p)&&(list[k].Y<750+p)&&(list[k].Y>750-p))||((list[k].X-p==600)&&(list[k].Y<675+p)&&(list[k].Y>675-p))||((list[k].X-p==975)&&(list[k].Y<375+p)&&(list[k].Y>375-p)));
                else list[k].X-=1;
            }
        }else {
            if(list[k].Y<y) {
                if((list[k].Y+1>1275)||((list[k].X>1)&&(list[k].X<150)&&(list[k].Y+p==150))||((list[k].X>225-p)&&(list[k].X<225+p)&&(list[k].Y+p==450))||((list[k].X>1)&&(list[k].X<150)&&(list[k].Y+p==750))||((list[k].X<600+p)&&(list[k].X>600-p)&&(list[k].Y+p==675))||((list[k].X>975-p)&&(list[k].X<975+p)&&(list[k].Y+p==375)));
                else list[k].Y+=1;
            } else if(list[k].Y>y) {
                if((list[k].Y-1<0)||((list[k].X>1)&&(list[k].X<150)&&(list[k].Y-p==150))||((list[k].X>225-p)&&(list[k].X<225+p)&&(list[k].Y-p==450))||((list[k].X>1)&&(list[k].X<150)&&(list[k].Y-p==750))||((list[k].X<600+p)&&(list[k].X>600-p)&&(list[k].Y-p==675))||((list[k].X>975-p)&&(list[k].X<975+p)&&(list[k].Y-p==375)));
                else list[k].Y-=1;
            }
        }
        list[k].label->move(list[k].X,list[k].Y+min);
        list[k].progressBar->move(list[k].X,list[k].Y+23);
    }
}

void scene::mpick(){
    int x = ui->label->x(), y = ui->label->y();
    for(int i = 0; i < droplist.size(); i++)
        if(abs(droplist[i].mX-x)+abs(droplist[i].mY-y)<((player->pk+mdata->ad_pk)*75)) {
            if(droplist[i].mtype==0) {
                mdata->coin++;
                ui->menu0->setTitle(QString::number(mdata->coin));
            } else if(droplist[i].mtype==1) {
                if(restr_exp<mdata->exp) {
                    restr_exp++;
                } else {
                    restr_exp = 0;
                    mdata->exp++;
                    restop();
                    emit enhance3();
                }
                ui->expBar->setValue(restr_exp);
            } else {
                player->hp+=5;
                if(mdata->choice==1) {
                    if(player->hp>mdata->player1.hp)
                        player->hp = mdata->player1.hp;
                } else {
                    if(player->hp>mdata->player2.hp)
                        player->hp = mdata->player2.hp;
                }
                ui->HP_bar->setValue(player->hp);
            }
            droplist.removeAt(i);
        }
}

void scene::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0,0,1800,1400,QPixmap(":/img/background.png"));
    for(int i = 0; i < 5; i++)
        painter.drawPixmap(stonlist[i].X,stonlist[i].Y+min,75,75,QPixmap(":/img/ston.png"));
    painter.drawRect(ui->label->x()-75*(player->ar+mdata->ad_ar),ui->label->y()-75*(player->ar+mdata->ad_ar),75*(1+2*(player->ar+mdata->ad_ar)),75*(1+2*(player->ar+mdata->ad_ar)));
    foreach (Drop i, droplist) {
        switch (i.mtype) {
        case 0:
            painter.drawPixmap(i.mX+20,i.mY+min+20,35,35,QPixmap(":/img/drop_coin.png"));
            break;
        case 1:
            painter.drawPixmap(i.mX+20,i.mY+min+20,35,35,QPixmap(":/img/drop_exp.png"));
            break;
        case 2:
            painter.drawPixmap(i.mX+20,i.mY+min+20,35,35,QPixmap(":/img/drop_add_hp.png"));
            break;
        default:
            break;
        }
    }
}

void scene::keyPressEvent(QKeyEvent *event) {
    if(!event->isAutoRepeat())
        keys.append(event->key());
    if(!keyRespondTimer->isActive())
        keyRespondTimer->start(4);
}

void scene::keyReleaseEvent(QKeyEvent *event) {
    if(!event->isAutoRepeat())
        keys.removeAll(event->key());
    if(keys.isEmpty())
        keyRespondTimer->stop();
}

void scene::slotTimeOut() {
    foreach (int key, keys) {
        int x = ui->label->x(), y = ui->label->y();
        switch (key) {
        case Qt::Key_W:
            for(int i = 0 ; i < (player->sp+mdata->ad_sp); i++) {
                if((y-1<0)||((x>1)&&(x<150)&&(y-p==150))||((x>225-p)&&(x<225+p)&&(y-p==450))||((x>1)&&(x<150)&&(y-p==750))||((x<600+p)&&(x>600-p)&&(y-p==675))||((x>975-p)&&(x<975+p)&&(y-p==375)));
                else y-=1;
            }
            break;
        case Qt::Key_A:
            for(int i = 0 ; i < (player->sp+mdata->ad_sp); i++) {
                if((x-1<0)||((x-p==p)&&(y>150-p)&&(y<150+p))||((x-p==225)&&(y<450+p)&&(y>450-p))||((x-p==p)&&(y<750+p)&&(y>750-p))||((x-p==600)&&(y<675+p)&&(y>675-p))||((x-p==975)&&(y<375+p)&&(y>375-p)));
                else x-=1;
            }
            break;
        case Qt::Key_S:
            for(int i = 0 ; i < (player->sp+mdata->ad_sp); i++) {
                if((y+1>1275)||((x>1)&&(x<150)&&(y+p==150))||((x>225-p)&&(x<225+p)&&(y+p==450))||((x>1)&&(x<150)&&(y+p==750))||((x<600+p)&&(x>600-p)&&(y+p==675))||((x>975-p)&&(x<975+p)&&(y+p==375)));
                else y+=1;
            }
            break;
        case Qt::Key_D:
            for(int i = 0 ; i < (player->sp+mdata->ad_sp); i++) {
                if((x+1>1725)||((x+p==p)&&(y>150-p)&&(y<150+p))||((x+p==225)&&(y<450+p)&&(y>450-p))||((x+p==p)&&(y<750+p)&&(y>750-p))||((x+p==600)&&(y<675+p)&&(y>675-p))||((x+p==975)&&(y<375+p)&&(y>375-p)));
                else x+=1;
            }
            break;
        case Qt::Key_Space:
            restop();
            msave_pause->show();
            break;
        default:
            break;
        }
        ui->label->move(x,y);
        if(is_end==false)
            ui->HP_bar->move(x,y-15);
        this->update();
    }
}

void scene::restop() {
    keys.clear();
    bTimer->stop();
    qTimer->stop();
    mTimer->stop();
}

void scene::restart() {
    bTimer->start();
    qTimer->start();
    mTimer->start();
}

scene::~scene() {
    delete ui;
    delete keyRespondTimer;
}
