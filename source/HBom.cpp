#include "HBom.h"

const std::string HBom::FindPackage(std::string s){
    size_t idx = idx =  s.find(":");
    if (idx == std::string::npos) return "";

    //idx = s.find("_",idx + 1);
    //if (idx == std::string::npos) return "";
    std::string pack = s.substr(idx+1);
    size_t startLetter = pack.find("_");
    //std::cout<<startLetter<<"#"<<pack.substr(0,startLetter)<<"#"<<std::endl;
    if ( pack.substr(0,startLetter) == "R" ||
         pack.substr(0,startLetter) == "C"
       ){
        pack = pack.substr(startLetter+1);
    }

    return pack;
}

const void HBom::Fill(std::vector<HModule>* mod){
    
    for (int i=0;i< mod->size();++i){
        HPart p;

        std::string ref  = "";
        std::string val  = "";
        size_t libPos = mod->operator[](i).GetValue().find(":");
        std::string lib = (libPos!=std::string::npos)?mod->operator[](i).GetValue().substr(0,libPos) : "";

        std::string pack = FindPackage(mod->operator[](i).GetValue());

        if (!checkBlackList(lib,pack)) continue;

        for (int l=0;l<mod->operator[](i).GetNofTags();l++) {
            if ( mod->operator[](i).GetTagAt(l).GetName() == "reference" ) ref = mod->operator[](i).GetTagAt(l).GetValue();
            if ( mod->operator[](i).GetTagAt(l).GetName() == "value" )     val = mod->operator[](i).GetTagAt(l).GetValue();
        }
        bool found = false;
        int foundIndx = -1;
        for (int k=0; k < fPart.size() ;++k){
            if (fPart[k].GetName() == mod->operator[](i).GetValue()  && fPart[k].GetValue().compare(val) == 0 && fPart[k].GetPackage().compare(pack) == 0){
                // already there
                found = true;
                foundIndx = k; 
                fPart[k].IncAmount();
                fPart[k].AddRef(ref);
                break;   
            }
        }

        if ( found == false) {
            p.SetName(mod->operator[](i).GetValue());
            p.SetPackage(pack);
            p.SetValue(val);
            p.SetKiCadLib(lib);
            p.IncAmount();
            p.AddRef(ref);
            fPart.push_back(p);
        }

    }    
}

bool HBom::checkBlackList(std::string const lib, std::string const pack){
    for (auto item : this->fBlackList){
        //ckeck Black List
        if (item.compare(lib)  == 0) return false;
        if (item.compare(pack) == 0) return false;
    }

    return true;
}

void HBom::Init(){
    this->fBlackList.emplace_back("logo");
    this->fBlackList.emplace_back("holder");
    this->fBlackList.emplace_back("JTAG");
    this->fBlackList.emplace_back("TestPoint");
    this->fBlackList.emplace_back("Grid_1_7");
}