#ifndef HMODULEH
#define HMODULEH

#include <iostream>
#include <vector>
#include "./HTag.h"


class HModule {
public:
    HModule() = default;
    ~HModule(){};

    const std::string GetValue(){ return this->fval;};
    const int GetNofTags(){return this->ftag.size();};
    HTag GetTagAt(int i){ return this->ftag[i];};

    const void SetValue(std::string val){ this->fval = val;};
    const void AddTag(HTag tag){ this->ftag.push_back(tag);};
    const void ClearTags(){ this->ftag.clear();};

private:
    std::string fval;
    std::vector<HTag> ftag;
};


#endif