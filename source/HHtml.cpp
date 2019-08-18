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
    htmlOut += "<tr style=\"background-color:3b4749\">\n";
    htmlOut += "    <th name=\"head\">Part No.\n";
    htmlOut += "        <div onclick=\"sort(this,0,0,'num')\" style=\"display: inline-box; float: right;cursor: pointer;\">&#9650;</div>\n";
    htmlOut += "        <div onclick=\"sort(this,0,1,'num')\" style=\"display: inline-box; float: right;cursor: pointer;\">&#9661;</div></th>\n";
    htmlOut += "    <th name=\"head\">Name\n";
    htmlOut += "        <div onclick=\"sort(this,1,0,)\" style=\"display: inline-box; float: right;cursor: pointer;\">&#9650;</div>\n";
    htmlOut += "        <div onclick=\"sort(this,1,1,)\" style=\"display: inline-box; float: right;cursor: pointer;\">&#9660;</div></th>\n";
    htmlOut += "    <th name=\"head\">Value\n";
    htmlOut += "        <div onclick=\"sort(this,2,0,)\" style=\"display: inline-box; float: right;cursor: pointer;\">&#9650;</div>\n";
    htmlOut += "        <div onclick=\"sort(this,2,1,)\" style=\"display: inline-box; float: right;cursor: pointer;\">&#9660;</div></th>\n";
    htmlOut += "    <th name=\"head\">Package\n";
    htmlOut += "        <div onclick=\"sort(this,3,0,)\" style=\"display: inline-box; float: right;cursor: pointer;\">&#9650;</div>\n";
    htmlOut += "        <div onclick=\"sort(this,3,1,)\" style=\"display: inline-box; float: right;cursor: pointer;\">&#9660;</div></th>\n";
    htmlOut += "    <th name=\"head\">Quantity\n";
    htmlOut += "        <div onclick=\"sort(this,4,0,'num')\" style=\"display: inline-box; float: right;cursor: pointer;\">&#9650;</div>\n";
    htmlOut += "        <div onclick=\"sort(this,4,1,'num')\" style=\"display: inline-box; float: right;cursor: pointer;\">&#9660;</div></th>\n";
    htmlOut += "    <th name=\"head\">In Cart\n";
    htmlOut += "        <div onclick=\"sort(this,5,0,'checkbox')\" style=\"display: inline-box; float: right;cursor: pointer;\">&#9650;</div>\n";
    htmlOut += "        <div onclick=\"sort(this,5,1,'checkbox')\" style=\"display: inline-box; float: right;cursor: pointer;\">&#9660;</div></th>\n";;
    htmlOut += "</tr>\n";
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
        htmlOut += "    <td><input type=\"checkbox\" onclick=\"              \"></td>\n";
        htmlOut += "</tr>\n";
        
        htmlOut += "<tr name=\""+ std::to_string(k) +"\" style=\"border: 0;visibility:collapse\">";
        htmlOut += "    <th style=\"background-color:3b4749\">Ref.:</th>\n  <td colspan=\"5\" style=\"background-color:3b4749\">";
        for (int l=0;l<p.GetRefs().size();++l){
            htmlOut += p.GetRefs().at(l);
            if (l != p.GetRefs().size()-1) htmlOut += ", ";
        }
        htmlOut += "</td>\n</tr>\n";
    }
    htmlOut += "</table>\n\n";

    htmlOut += "<script>\n";
    htmlOut += "    function collapse(dom) {\n";
    htmlOut += "        var x = document.getElementsByName(dom.id);\n";
    htmlOut += "        for (i = 0; i < x.length; i++) {\n";
    htmlOut += "            var vis = x[i].style.visibility;\n";
    htmlOut += "            if (vis == \"collapse\"){";
    htmlOut += "                x[i].style.visibility=\"visible\";";
    htmlOut += "            } else {";
    htmlOut += "                x[i].style.visibility=\"collapse\";";
    htmlOut += "            };\n";
    htmlOut += "        }\n";
    htmlOut += "    }\n\n";
    htmlOut += "   function sort(dom,field,dir,opt){\n";
    htmlOut += "      var table, rows, switching, i, x, y, shouldSwitch, node, switchEqual;\n";
    htmlOut += "      table = document.getElementsByTagName(\"TABLE\")[0];\n";
    htmlOut += "      switching = true;\n";
    htmlOut += "      node = field;\n";
    htmlOut += "      /* Make a loop that will continue until\n";
    htmlOut += "          no switching has been done: */\n";
    htmlOut += "          \n";
    htmlOut += "      while (switching) {\n";
    htmlOut += "          // Start by saying: no switching is done:\n";
    htmlOut += "         switching = false;\n";
    htmlOut += "         rows = table.rows;\n";
    htmlOut += "         /* Loop through all table rows (except the\n";
    htmlOut += "         first, which contains table headers): */\n";
    htmlOut += "         for (i = 1; i < (rows.length - 2); i=i+2) {\n";
    htmlOut += "            // Start by saying there should be no switching:\n";
    htmlOut += "            shouldSwitch = false;\n";
    htmlOut += "            switchEqual  = false;\n";
    htmlOut += "            /* Get the two elements you want to compare,\n";
    htmlOut += "               one from current row and one from the next: */\n";
    htmlOut += "            x = rows[i].getElementsByTagName(\"TD\")[node];\n";
    htmlOut += "            y = rows[i + 2].getElementsByTagName(\"TD\")[node]; // +2 for Refs\n";
    htmlOut += "            //alert(\"TEST \" + x.innerHTML.toLowerCase() +\"  \"+ y.innerHTML.toLowerCase());\n";
    htmlOut += "            // Check if the two rows should switch place:\n";
    htmlOut += "            var checkx = x.innerHTML.toLowerCase();\n";
    htmlOut += "            var checky = y.innerHTML.toLowerCase();\n";
    htmlOut += "            if (opt == 'num') {\n";
    htmlOut += "                checkx = parseFloat(checkx);\n";
    htmlOut += "                checky = parseFloat(checky);\n";
    htmlOut += "            } else if (opt == 'checkbox') {\n";
    htmlOut += "                x = x.childNodes[0];\n";   
    htmlOut += "                if (x.checked) {checkx = 'z';} else { checkx = 'a';}\n";   
    htmlOut += "                y = y.childNodes[0];\n";   
    htmlOut += "                if (y.checked) {checky = 'z';} else { checky = 'a';}\n";      
    htmlOut += "            }\n";
    htmlOut += "            var doCheck;\n";
    htmlOut += "            if (dir === 0) doCheck = checkx < checky;\n";
    htmlOut += "            if (dir === 1) doCheck = checkx > checky;\n";
    htmlOut += "            if (doCheck) {\n";
    htmlOut += "                // If so, mark as a switch and break the loop:\n";
    htmlOut += "                shouldSwitch = true;\n";
    htmlOut += "                break;\n";
    htmlOut += "            } else if (checkx === checky) {\n";
    htmlOut += "                switchEqual = true;\n";
//    htmlOut += "                break;\n";
    htmlOut += "            }\n";
    htmlOut += "         }\n";
    htmlOut += "         if (shouldSwitch) {\n";
    htmlOut += "         /* If a switch has been marked, make the switch\n";
    htmlOut += "            and mark that a switch has been done: */\n";
    htmlOut += "            rows[i].parentNode.insertBefore(rows[i + 2], rows[i]);\n";
    htmlOut += "            rows[i+1].parentNode.insertBefore(rows[i + 3], rows[i+1]);\n";
    htmlOut += "            \n";
    htmlOut += "            switching = true;\n";
    htmlOut += "         }\n";
    // htmlOut += "         if (switchEqual) {\n";
    // htmlOut += "            rows[i].parentNode.insertBefore(rows[i + 2], rows[i]);\n";
    // htmlOut += "            rows[i+1].parentNode.insertBefore(rows[i + 3], rows[i+1]);\n";
    // htmlOut += "            \n";
    // htmlOut += "            switching = true;\n";
    // htmlOut += "         }\n";    
    htmlOut += "      }\n";
    htmlOut += "  colorizeRows(table);\n";
    htmlOut += "  changeButtons(node,dir);\n";
    htmlOut += " }\n\n";
    htmlOut += "function colorizeRows(dom){\n";
    htmlOut += "   var rows = document.getElementsByTagName(\"TR\");\n";
    htmlOut += "   var cnt = 0;\n";
    htmlOut += "   for (var i=1;i<rows.length;i++){\n";
    htmlOut += "      if (rows[i].className == \"\" ) continue;\n";
    htmlOut += "      if (cnt%2 == 0) {\n";
    htmlOut += "         rows[i].className = \"trbg0\";\n";
    htmlOut += "      } else {\n";
    htmlOut += "         rows[i].className = \"trbg1\";\n";
    htmlOut += "      }\n\n";
    htmlOut += "      cnt++;\n";
    htmlOut += "   }\n\n";
    htmlOut += "}\n\n";

    htmlOut += "function changeButtons(node,dir){\n";
    htmlOut += "   var fields = document.getElementsByName(\"head\");\n";
    htmlOut += "   \n";
    htmlOut += "   for (var i=0;i<fields.length;i++){\n";
    htmlOut += "      var childs = fields[i].childNodes;\n";
    htmlOut += "      for (var j=0;j<childs.length;j++){\n";
    htmlOut += "         if (typeof childs[j].innerHTML !== 'undefined'){\n";
    htmlOut += "            if (childs[j].innerHTML === '▽') childs[j].innerHTML = '&#9660;';\n";
    htmlOut += "            if (childs[j].innerHTML === '△') childs[j].innerHTML = '&#9650;';\n";
    htmlOut += "            if (i === node) {\n";
    htmlOut += "                if (childs[j].innerHTML === '▼' && dir == 1) childs[j].innerHTML = '&#9661;';";
    htmlOut += "                if (childs[j].innerHTML === '▲' && dir == 0) childs[j].innerHTML = '&#9651;';";    
    htmlOut += "            }\n"; 
    htmlOut += "         }\n";
    htmlOut += "      }\n\n";
    htmlOut += "   }\n\n";
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
    
    head  = "<html>\n<meta charset=\"UTF-8\">\n<head>\n";
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