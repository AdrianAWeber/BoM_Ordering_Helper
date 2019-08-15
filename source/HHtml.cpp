#include "HHtml.h"
#include "HPart.h"
#include "HBom.h"
#include <fstream>


void printBOM(HBom &b){

}


const void HHtml::makeHTML(HBom b, std::string opt){
    if (b.GetNofParts() == 0) return;

    std::cout<<"Creating HMTL File...";

    std::string htmlOut = "";

    htmlOut += this->header("BoM - KiCad");
    htmlOut += this->beginBody("background-color: 252c30;color: white;");//#424242
    htmlOut += "<table>\n";
    htmlOut += "<tr style=\"background-color:3b4749\"><th>Part No.</th><th>Name</th><th>Value</th><th>Package</th><th>Quantity</th><th>In Cart</th></tr>\n";
    for (int k=0;k<b.GetNofParts();++k){
        HPart p  = b.GetPart(k);
        if (k%2){
            htmlOut += "<tr class=\"trbg1\">\n";
        } else {
            htmlOut += "<tr class=\"trbg0\">\n";
        }
        htmlOut += "    <td id=\""+ std::to_string(k) +"\" onclick=\"collapse(this)\">" + std::to_string(k+1) + "</td>\n";
        htmlOut += "    <td id=\""+ std::to_string(k) +"\" onclick=\"collapse(this)\">" + p.GetName() + "</td>\n";
        htmlOut += "    <td id=\""+ std::to_string(k) +"\" onclick=\"              \">" + p.GetValue() + "</td>\n";
        htmlOut += "    <td id=\""+ std::to_string(k) +"\" onclick=\"              \">" + p.GetPackage() + "</td>\n";
        htmlOut += "    <td id=\""+ std::to_string(k) +"\" onclick=\"collapse(this)\">" + std::to_string(p.GetAmount()) + "</td>\n";
        htmlOut += "    <td><input type=\"checkbox\"></td>\n";
        htmlOut += "</tr>\n";
        
        htmlOut += "<tr name=\""+ std::to_string(k) +"\" style=\"border: 0;visibility:collapse\">";
        htmlOut += "<th style=\"background-color:3b4749\">Ref.:</th> <td colspan=\"5\" style=\"background-color:3b4749\">";
        for (int l=0;l<p.GetRefs().size();++l){
            htmlOut += p.GetRefs().at(l);
            if (l != p.GetRefs().size()-1) htmlOut += ", ";
        }
        htmlOut += "</td></tr>\n";
    }
    htmlOut += "</table>\n\n";

    htmlOut += "<script>\n";
    htmlOut += "function collapse(dom) {\n";
    htmlOut += "    var x = document.getElementsByName(dom.id);\n";
    htmlOut += "    for (i = 0; i < x.length; i++) {\n";
    htmlOut += "        var vis = x[i].style.visibility;\n";
    htmlOut += "        if (vis == \"collapse\"){";
    htmlOut += "            x[i].style.visibility=\"visible\";";
    htmlOut += "        } else {";
    htmlOut += "            x[i].style.visibility=\"collapse\";";
    htmlOut += "        };\n";
    htmlOut += "    }\n";
    htmlOut += "}\n";
    htmlOut += "</script>\n\n";

    htmlOut += this->endBody();

    //this->print(htmlOut);
    this->writeToFile(htmlOut);

    std::cout<<"DONE!"<<std::endl;
}



const void HHtml::writeToFile(std::string & s, std::string file){
    std::ofstream fileout;
    fileout.open(file);
    fileout<<s;
    fileout.close();
}

const void HHtml::print(std::string& s){
    std::cout<< s <<std::endl;
}


const std::string HHtml::header( const std::string & title){
    std::string head;
    
    head  = "<html>\n<head>\n";
    head += "<title>" + title + "</title>\n";
    head += "<style>\n";
    head += "table {\n";
    head += "   font-family: arial, sans-serif;\n";
    head += "   border-collapse: collapse;\n";
    head += "   width: 100%;\n";
    head += "}\n";
    head += "td, th {\n";
    head += "   border: 1px solid #777777;\n";
    head += "   text-align: left;\n";
    head += "   padding: 8px;\n";
    head += "}\n";
    head += ".trbg0:hover, .trbg1:hover {\n";
    head += "   background-color: #226022;\n";
    head += "}\n";
    head += ".trbg0 {\n";
    head += "   background-color: #313b40;\n";
    head += "}\n";
    head += ".trbg1 {\n";
    head += "   background-color: #252c30;\n";
    head += "}\n";
    head += "</style>\n";
    head += "</head>\n";

    return head;
}

const std::string HHtml::beginBody( const std::string & style){
    std::string body;
    
    body  = "<body style=\"" + style +"\">\n";

    return body;
}