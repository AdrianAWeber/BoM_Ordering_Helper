#ifndef HHTMLH
#define HHTMLH

#include <iostream>
#include <vector>
#include "HBom.h"

class HHtml {
    public:
        HHtml(std::string file) : fFile(file){};
        HHtml() = default;
        ~HHtml(){};

        const std::string GetFile() const {return this->fFile;};

        void SetFile(std::string file){this->fFile = file;};
        void makeHTML(HBom b, std::string opt);

    private:
        void writeToFile(std::string &s){
                    writeToFile(s,this->fFile);
                };
        void writeToFile(std::string &s, std::string file);
        const std::string header(const std::string & title);
        const std::string beginBody( const std::string & style);
        const std::string endBody(){ return "</body></html>";};
        void print(std::string &s);
        std::string fFile = "bod_order.htm";
};

#endif