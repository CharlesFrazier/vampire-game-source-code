#ifndef CHARACTOR_BOSS_H
#define CHARACTOR_BOSS_H
#include<QProgressBar>

class charactor_boss
{
public:
    charactor_boss()
        :X(1725)
        ,Y(0)
        ,hp(100){}
    int X;
    int Y;
    int hp;
};

#endif // CHARACTOR_BOSS_H
