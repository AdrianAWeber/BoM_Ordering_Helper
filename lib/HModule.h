#ifndef HMODULEH
#define HMODULEH

#include <iostream>
#include <vector>
#include "./HTag.h"


class HModule {
public:
    HModule():fVal(""),fTag(){};
    ~HModule(){};

    const std::string GetValue(){ return this->fVal;};
    unsigned int GetNofTags(){return static_cast<int>(this->fTag.size());};
    HTag GetTagAt(unsigned int i){ return this->fTag[i];};

    void SetValue(std::string val){ this->fVal = val;};
    void AddTag(HTag tag){ this->fTag.push_back(tag);};
    void ClearTags(){ this->fTag.clear();};

private:
    std::string fVal;
    std::vector<HTag> fTag;
};


#endif