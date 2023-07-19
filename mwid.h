#ifndef MWID_H
#define MWID_H

#include <QMainWindow>
#include <QMainWindow>
#include <vector>
#include <random>
#include <algorithm>
#include <QVBoxLayout>
#include <QPushButton>
#include "data.h"
class mwid : public QMainWindow
{
    Q_OBJECT
public:
    explicit mwid(QWidget *parent = nullptr);
    void set(class data * d);
    class data *mdata;
    std::vector<QPushButton*> vectors;
    QVBoxLayout *layout;
    QPushButton *addhp;
    QPushButton *addatk;
    QPushButton *addae;
    QPushButton *adddt;
    QPushButton *addcd;
    QPushButton *addpk;
    QPushButton *addsp;
    int numbers[7] = {0, 1, 2, 3, 4, 5, 6};
    int index[3];
protected:
    void moveEvent(QMoveEvent *) override {
        QPoint pos = QPoint(1000,500);
        move(pos);
    }
signals:
    void StartM();
public slots:
    void redom();
};

#endif // MWID_H
