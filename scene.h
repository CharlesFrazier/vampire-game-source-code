#ifndef SCENE_H
#define SCENE_H

#include <QMainWindow>
#include "data.h"
#include "save_pause.h"
#include "mwid.h"
#include "deadlist.h"
#include "drop.h"
#include "charactor.h"
#include "chatacor_short.h"
#include "charactor_boss.h"
#include <QKeyEvent>
#include <QPaintEvent>
#include <QLabel>
#include <QList>
#include <QMessageBox>
#include <QPainter>
#include <QTransform>
#include <QTimer>
#include <QTime>
#include <QThread>
#include <QMovie>
#include <cmath>
#include <iostream>
namespace Ui {
class scene;
}

class scene : public QMainWindow
{
    Q_OBJECT

public:
    explicit scene(QWidget *parent = nullptr);
    void set(class data * d,save_pause * s);
    void load();
    void restop();
    void slotTimeOut();
    void paintEvent(QPaintEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void keyPressEvent(QKeyEvent *);
    QList<int> keys;
    QTimer* keyRespondTimer;
    QPixmap *p_1;
    QPixmap *p_1_hit;
    QPixmap *p_1_HP;
    QPixmap *p_2;
    QPixmap *p_2_hit;
    QPixmap *p_2_HP;
    QPixmap *p_boss;
    QPixmap *p_boss_hit;
    QPixmap *p_short;
    QPixmap *p_short_hit;
    QMovie *bang_movie;
    charactor_boss boss;
    QTimer *bTimer;
    QTimer *qTimer;
    QTimer *mTimer;
    class data * mdata;
    save_pause * msave_pause;
    mwid * mwids;
    bool is_win, is_end;
    int time_HP=0;
    int restr_exp = 0;
    int mresurrection;
    const int p = 75;
    charactor * player;
    const int min = 30;
    QList<chatacor_short> list;
    QList<Deadlist> qlist;
    QList<Deadlist> stonlist;
    QList<Drop> droplist;
    QList<chatacor_short> bang;
    ~scene();
private:
    Ui::scene *ui;
signals:
    void ExitM();
    void enhance3();
public slots:
    void restart();
    void mboss();
    void mbuild();
    void mmove();
    void update_time();//1s
    void mkill();
    void mpick();
    void mjudge();
    void end_pro();
};

#endif // SCENE_H
