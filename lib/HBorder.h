#ifndef HBORDERH
#define HBORDERH

#include <iostream>
#include <vector>


class HBorder {
public:
    HBorder() = default;
    ~HBorder(){};

    const uint GetPos(){ return this->fpos;};
    const bool GetOpenBrack(){ return this->fopenBrack;};

    const void SetPos(uint pos){ this->fpos = pos;};
    const void SetOpenBrack(bool oB){ this->fopenBrack = oB;};

private:
    uint fpos;
    bool fopenBrack;
};


#endif