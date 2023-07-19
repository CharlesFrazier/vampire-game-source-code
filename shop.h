#ifndef SHOP_H
#define SHOP_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QMessageBox>
#include "data.h"

namespace Ui {
class shop;
}

class shop : public QWidget
{
    Q_OBJECT

public:
    explicit shop(QWidget *parent = nullptr);
    void set(class data *d);
    void load();
    class data * mdata;
    QTableWidgetItem *atk;
    QTableWidgetItem *hp;
    QTableWidgetItem *ar;
    QTableWidgetItem *dt;
    QTableWidgetItem *cd;
    QTableWidgetItem *sp;
    QTableWidgetItem *pk;
    QTableWidgetItem *rec;
    QTableWidgetItem *rate;
    int choice = 0;
    ~shop();
    void box();
private:
    Ui::shop *ui;
signals:
    void EmitS();
public slots:
    void exits();
private slots:
    void on_player1_clicked();
    void on_player2_clicked();
    void on_atk_clicked();
    void on_hp_clicked();
    void on_sp_clicked();
    void on_cd_clicked();
    void on_dt_clicked();
    void on_pk_clicked();
    void on_ar_clicked();
    void on_rec_clicked();
    void on_rate_clicked();
    void on_coin_clicked();
};

#endif // SHOP_H
