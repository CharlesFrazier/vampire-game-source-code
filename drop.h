#ifndef DROP_H
#define DROP_H


class Drop
{
public:
    enum Type{coin=0, exp=1, add_hp=2} mtype;
    Drop(){};
    Drop(enum Type type, int x, int y);
    ~Drop(){};
    int mX, mY;
};

#endif // DROP_H
