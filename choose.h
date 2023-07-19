#ifndef CHOOSE_H
#define CHOOSE_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "data.h"
#include "scene.h"
namespace Ui {
class choose;
}

class choose : public QWidget
{
    Q_OBJECT

public:
    explicit choose(QWidget *parent = nullptr);
    void set(class data* d, scene *s);
    void load();
    class data* mdata;
    scene * mscene;
    QTreeWidgetItem * hp1;
    QTreeWidgetItem * atk1;
    QTreeWidgetItem * sp1;
    QTreeWidgetItem * cd1;
    QTreeWidgetItem * dt1;
    QTreeWidgetItem * pk1;
    QTreeWidgetItem * ae1;

    QTreeWidgetItem * hp2;
    QTreeWidgetItem * atk2;
    QTreeWidgetItem * sp2;
    QTreeWidgetItem * cd2;
    QTreeWidgetItem * dt2;
    QTreeWidgetItem * pk2;
    QTreeWidgetItem * ae2;
    ~choose();

private slots:
    void on_btn_chs1_clicked();

    void on_btn_chs2_clicked();

    void on_btn_back_clicked();

private:
    Ui::choose *ui;
signals:
    void ExitC();
};

#endif // CHOOSE_H
