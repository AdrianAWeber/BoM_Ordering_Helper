#ifndef HTAGH
#define HTAGH

#include <iostream>
#include <vector>

class HTag {
public:
    HTag() = default;
    ~HTag(){};

    const std::string GetName(){ return this->fname;};
    const std::string GetValue(){ return this->fval;};

    const void SetValue(std::string val){ this->fval = val;};
    const void SetName(std::string name){ this->fname = name;};

private:
    std::string fname;
    std::string fval;
};


#endif