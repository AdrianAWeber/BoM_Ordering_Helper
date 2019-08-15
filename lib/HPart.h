#ifndef HPARTH
#define HPARTH

#include <iostream>
#include <vector>

class HPart {
public:
    HPart() = default;
    ~HPart(){};

    const std::string GetName(){ return this->fName;};
    const std::string GetValue(){ return this->fVal;};
    const std::string GetPackage(){ return this->fPackage;};
    const std::string GetKiCadLib(){ return this->fKiCadLib;};
    const int GetAmount(){ return this->fAmount;};
    const std::vector<std::string> &GetRefs() { return this->fRefs;};
    //int GetRefSize() { return this->fRefs.size();};

    const void SetValue(std::string val){ this->fVal = val;};
    const void SetName(std::string name){ this->fName = name;};
    const void SetPackage(std::string package){ this->fPackage = package;};
    const void SetKiCadLib(std::string Lib){ this->fKiCadLib = Lib;};
    const void IncAmount(){ this->fAmount++;};
    const void AddRef(std::string ref){ this->fRefs.push_back(ref);};

private:
    std::string fName;
    std::vector<std::string> fRefs;
    std::string fVal;
    std::string fPackage;
    std::string fKiCadLib;
    int fAmount = 0;

};

#endif