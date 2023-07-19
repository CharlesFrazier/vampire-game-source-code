#ifndef SAVE_PAUSE_H
#define SAVE_PAUSE_H

#include <QWidget>

namespace Ui {
class save_pause;
}

class save_pause : public QWidget
{
    Q_OBJECT

public:
    explicit save_pause(QWidget *parent = nullptr);
    ~save_pause();

private slots:
    void on_btn_save_clicked();
    void on_btn_pause_clicked();

private:
    Ui::save_pause *ui;
signals:
    void ExitS();
    void StartS();
};

#endif // SAVE_PAUSE_H
