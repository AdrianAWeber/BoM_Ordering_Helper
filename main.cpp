#include <string.h>
#include "HModule.h"
#include "HParser.h"
#include "HPart.h"
#include "HBom.h"
#include "HHtml.h"

void print(std::vector<HModule>* modul){
    for (int k=0;k<modul->size();++k){
        std::cout <<"Modul "<<k<<": "<< modul->operator[](k).GetValue() <<"  "<<modul->operator[](k).GetNofTags() <<std::endl;
        for (int m=0;m<modul->operator[](k).GetNofTags();++m){
            std::cout <<"\t\t"<<modul->operator[](k).GetTagAt(m).GetName() <<"  "<<modul->operator[](k).GetTagAt(m).GetValue() <<std::endl;
        }
    }
}



int main() {

    std::cout<<"**BOM Ordering Helper**"<<std::endl;
    
    std::vector<HModule>* modul = new std::vector<HModule>;

    const std::string files = "/home/adrian/kicad_bom_orderer/EtherFPGA.kicad_pcb;/home/adrian/kicad_bom_orderer/EthernetAddOn.kicad_pcb;/home/adrian/kicad_bom_orderer/breakoutAddOn.kicad_pcb;";
    HParser parser(files);
    parser.run(modul);

    //Create BOM
    //print(modul);

    HBom b;
    b.Fill(modul);
    delete modul;
    //printBOM(b);

    HHtml html;
    html.makeHTML(b, "");

    return 0;
}
