#ifndef HBOMH
#define HBOMH

#include <iostream>
#include <vector>
#include "HPart.h"
#include "HModule.h"

class HBom {
public:
    HBom():fPart(),fBlackList() {Init();};
    ~HBom(){};

    void Fill(std::vector<HModule>* mod);
    const std::string FindPackage(std::string s);

    int GetNofParts() const {return static_cast<int>(this->fPart.size());};
    HPart &GetPart(int idx){return this->fPart[idx];}

private:
    std::vector<HPart> fPart;
    std::vector<std::string> fBlackList;
    bool checkBlackList(std::string const lib, std::string const pack);
    void Init();

};

#endif