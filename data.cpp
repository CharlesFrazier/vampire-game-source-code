#include "data.h"

data::data() {
    ifstream fin;
    fin.open("D:/source.txt",ios::in);
    fin>>player1.atk>>player1.hp>>player1.sp>>player1.cd>>player1.dt>>player1.pk>>player1.ar>>player1.x>>player1.y;
    fin>>player2.atk>>player2.hp>>player2.sp>>player2.cd>>player2.dt>>player2.pk>>player2.ar>>player2.x>>player2.y;
    fin>>choice>>coin>>rec>>exp>>level>>time>>coin_rate;
    fin>>ad_atk>>ad_hp>>ad_sp>>ad_cd>>ad_dt>>ad_pk>>ad_ar;
    fin.close();
}
