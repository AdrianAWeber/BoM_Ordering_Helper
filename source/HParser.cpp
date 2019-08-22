#include "HParser.h"
#include "HBorder.h"
#include <fstream>

HParser::HParser(std::string file):fFiles(){

    if (file.size() == 0) std::cout<< "No input File Specified!" <<std::endl;

    while(true){
        std::size_t indx = file.find(";");
        
        if (indx == std::string::npos){
            if (file.size() != 0) this->fFiles.push_back(file);
            break;
        } else {
            this->fFiles.push_back(file.substr(0,indx));
            file = file.substr(indx+1);
        }
    }
}

void HParser::getTag(HModule& SingleMod ,const std::vector<std::string>& wspVec, const unsigned int j, const std::string name, bool& modOpen)
{ 
    HTag t;
    if (wspVec[j].compare(name) == 0) {
        t.SetName(name);
        if (j+1 < wspVec.size()) {
            t.SetValue(wspVec[j+1]);
        }
        if (name == "module" ) {
            if (modOpen == false) {
                //newMOdule
                SingleMod.SetValue(t.GetValue());
                SingleMod.ClearTags();
            }
            modOpen = true;
        } else {
            SingleMod.AddTag(t);
        }
    }
}

void HParser::run(std::vector<HModule> *modul){
    
    for (auto fFile: this->fFiles){
        std::cout<<"Parsing file: "<< fFile;
        std::string line;
        std::ifstream myfile (fFile);
        if (myfile.is_open())
        {
            uint tag_open = 0;
            bool modOpen = false;
            HModule SingleMod;
            while ( getline (myfile,line) )
            {   
                std::vector<HBorder> b;
                for (uint c = 0; c< line.size();++c){
                    //std::cout<<line[c];
                    if (line.substr(c,1).compare("(") == 0) {
                        HBorder b_tmp;
                        b_tmp.SetPos(c);
                        b_tmp.SetOpenBrack(true);
                        b.push_back(b_tmp);
                    }
                    if (line.substr(c,1).compare(")") == 0) {
                        HBorder b_tmp;
                        b_tmp.SetPos(c);
                        b_tmp.SetOpenBrack(false);
                        b.push_back(b_tmp);
                    }
                }

                for (unsigned int i = 0; i < b.size(); ++i){
                    HBorder borders = b[i];
                    uint tag_open_old = tag_open;
                    if (borders.GetOpenBrack() == true) {
                        tag_open++;
                        if ((i+1)<b.size()){
                            //check if in vector
                            std::vector<std::string> wspVec;
                            size_t wsp = borders.GetPos();
                            while (true){
                                size_t wsp_old = wsp;
                                wsp = line.find(" ", wsp+1);
                                if (wsp < static_cast<size_t>(b[i+1].GetPos()) && wsp != std::string::npos){
                                    wspVec.emplace_back(line.substr(wsp_old+1,wsp - wsp_old -1));
                                } else {
                                    //no whitespace between "(" and ")"                                
                                    break;
                                }
                            }

                            for (unsigned int j=0;j<wspVec.size();++j){   
                                  getTag(SingleMod, wspVec, j, "module"   , modOpen);
                                  getTag(SingleMod, wspVec, j, "reference", modOpen);
                                  getTag(SingleMod, wspVec, j, "value"    , modOpen);

                            }

                        }

                    } else if (borders.GetOpenBrack() == false) {
                        tag_open--;
                    } else {
                        // for security         
                    }

                    if (tag_open_old == tag_open+1 && tag_open == 1 && modOpen) {
                        //std::cout<<"END OF MODULE"<<std::endl;
                        modul->push_back(SingleMod);
                        modOpen = false;
                    }
                }

            }
            myfile.close();
            std::cout<<" ...DONE!"<<std::endl;

        } else {
            std::cout<<" ...FAILED!"<<std::endl;
            std::cout << "Unable to open file "<< fFile <<"."<<std::endl;
        }
    } //for loop
}   