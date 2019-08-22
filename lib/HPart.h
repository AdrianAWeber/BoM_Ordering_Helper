#ifndef HPARTH
#define HPARTH

#include <iostream>
#include <vector>

class HPart {
public:
    HPart():fName(""),fRefs(),fVal(""),fPackage(""),fKiCadLib(""),fAmount(0){};
    ~HPart(){};

    std::string GetName() const { return this->fName;};
    std::string GetValue() const { return this->fVal;};
    std::string GetPackage() const { return this->fPackage;};
    std::string GetKiCadLib() const { return this->fKiCadLib;};
    int GetAmount() const { return this->fAmount;};
    std::vector<std::string> &GetRefs() { return this->fRefs;};
    //int GetRefSize() { return this->fRefs.size();};

    void SetValue(std::string val){ this->fVal = val;};
    void SetName(std::string name){ this->fName = name;};
    void SetPackage(std::string package){ this->fPackage = package;};
    void SetKiCadLib(std::string Lib){ this->fKiCadLib = Lib;};
    void IncAmount(){ this->fAmount++;};
    void AddRef(std::string ref){ this->fRefs.push_back(ref);};

private:
    std::string fName;
    std::vector<std::string> fRefs;
    std::string fVal;
    std::string fPackage;
    std::string fKiCadLib;
    int fAmount;

};

#endif