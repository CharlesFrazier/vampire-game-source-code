#ifndef CHATACOR_SHORT_H
#define CHATACOR_SHORT_H
#include <QProgressBar>
#include <QLabel>
class chatacor_short
{
public:
    chatacor_short(){}
    chatacor_short(int mx, int my);
    int X;
    int Y;
    int hp=30;
    QLabel *label;
    QProgressBar * progressBar;
    ~chatacor_short(){}
};

#endif // CHATACOR_SHORT_H
