#ifndef HTAGH
#define HTAGH

#include <iostream>
#include <vector>

class HTag {
public:
    HTag():fName(""),fVal(""){};
    ~HTag(){};

    std::string GetName() const { return this->fName;};
    std::string GetValue() const { return this->fVal;};

    void SetValue(std::string val){ this->fVal = val;};
    void SetName(std::string name){ this->fName = name;};

private:
    std::string fName;
    std::string fVal;
};


#endif