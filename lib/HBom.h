#ifndef HBOMH
#define HBOMH

#include <iostream>
#include <vector>
#include "HPart.h"
#include "HModule.h"

class HBom {
public:
    HBom() {Init();};
    ~HBom(){};

    const void Fill(std::vector<HModule>* mod);
    const std::string FindPackage(std::string s);

    const int GetNofParts() {return this->fPart.size();};
    const HPart &GetPart(int idx){return this->fPart[idx];}

private:
    std::vector<HPart> fPart;
    std::vector<std::string> fBlackList;
    bool checkBlackList(std::string const lib, std::string const pack);
    void Init();

};

#endif