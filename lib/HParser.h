#ifndef HPARSERH
#define HPARSERH

#include <iostream>
#include <vector>
#include "HModule.h"

class HParser {
public:
    HParser(std::string file);
    ~HParser(){};

    void run(std::vector<HModule> *modul);
    

private:
    std::vector<std::string> fFiles;
    void getTag(HModule& SingleMod,
                const std::vector<std::string>& wspVec,
                const unsigned int j,
                const std::string name,
                bool& modOpen
                );
};


#endif