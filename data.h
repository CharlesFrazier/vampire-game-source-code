#ifndef DATA_H
#define DATA_H
#include "charactor.h"
#include <fstream>
using namespace std;
class data
{
public:
    const int short_hp=30, short_atk=5;
    const int boss_hp=100, boss_atk=10;
    data();
    charactor player1, player2;
    int choice;
    int coin, rec, exp, level, time;
    double coin_rate;
    int ad_hp,ad_atk,ad_sp,ad_dt,ad_ar,ad_pk,ad_cd;
};

#endif // DATA_H
