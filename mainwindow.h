#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "shop.h"
#include "choose.h"
#include "data.h"
#include "scene.h"
#include "save_pause.h"
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void save_game();
    shop *mshop;
    choose * mchoose;
    class data * mdata;
    scene * mscene;
    save_pause * msave_pause;
    void paintEvent(QPaintEvent*);
private:
    Ui::MainWindow *ui;

public slots:
    void quit();
    void which_show();
private slots:
    void on_btn_shop_clicked();
    void on_btn_start_clicked();
};
#endif // MAINWINDOW_H
