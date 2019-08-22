#ifndef HBORDERH
#define HBORDERH

#include <iostream>
#include <vector>


class HBorder {
public:
    HBorder() = default;
    ~HBorder(){};

    uint GetPos() const { return this->fpos;};
    bool GetOpenBrack() const { return this->fopenBrack;};

    void SetPos(uint pos){ this->fpos = pos;};
    void SetOpenBrack(bool oB){ this->fopenBrack = oB;};

private:
    uint fpos;
    bool fopenBrack;
};


#endif