#include "assembler.hpp"

void Assembler::WriteInstruction (void) {
    std::string parse_string;
    std::string result;
    std::string label = "";
    int address = 0;
    do {
        if (address >= MAX_MEMORY) {
            std::cout << "Overflow!!" << std::endl;
            return;
        }
        result = ParseInstruction(parse_string);
        if (parse_string[0] == '#') {
            label = parse_string;
            result = ParseInstruction(parse_string);
        }
        CreateOperands(result, parse_string, label, address);
        label = "";  
    } while (result != "END");
}

void Assembler::CreateOperands (const std::string info, const std::string line, const std::string label, int& adr) {
    int count = 0;
    std::istringstream input(line);
    std::string ibuff;
    input >> ibuff;
    if (info == "Operator_Register") {
        Operator_Register* a =  new Operator_Register;
        if (label != "") { //metka
            a->SetLabel(label);
        }
        while (ibuff != "") {
            while(ibuff != ""){
                switch(count) {
                    case 0:
                        a->SetCode(ibuff);
                        break;
                    case 1:
                        a->SetLR(stoi(ibuff));
                        break;
                    case 2:
                        a->SetHR(stoi(ibuff));
                        break;                
                }
                ibuff = "";
                input >> ibuff;
                count++;
            }        
        }
        adr += 109;
        m_symtab.AddSymbol(adr, a);
        std::cout << "Operands information: " << *a << std::endl;
    }
    if (info == "Operator_RegisterMemory") {
        Operator_RegisterMemory* b = new Operator_RegisterMemory;
        if (label != "") { //metka
            b->SetLabel(label);
        }
        while (ibuff != "") {
            while(ibuff != ""){
                switch(count) {
                    case 0:
                        b->SetCode(ibuff);
                        break;
                    case 1:
                        b->SetRegister(stoi(ibuff));
                        break;
                    case 2:
                        b->SetMemoryID(ibuff);
                        break;                
                }
                ibuff = "";
                input >> ibuff;
                count++;
            }        
        }
        adr += 57;
        m_symtab.AddSymbol(adr, b);
        std::cout << "Operands information: " << *b << std::endl;
    }
    if (info == "Operator_Transition") {
        Operator_Transition* c = new Operator_Transition;
        while (ibuff != "") {
            while(ibuff != ""){
                switch(count) {
                    case 0:
                        c->SetCode(ibuff);
                        break;
                    case 1:
                        c->SetTransLabel(ibuff);
                        break;              
                }
                ibuff = "";
                input >> ibuff;
                count++;
            }        
        }
        adr += 39;
        m_symtab.AddSymbol(adr, c);
        std::cout << "Operands information: " << *c << std::endl;
    }
    if (info == "Operator_Typedef") {
        Operator_Typedef* d = new Operator_Typedef;
        while (ibuff != "") {
            while(ibuff != ""){
                switch(count) {
                    case 0:
                        if (ibuff == ":m_INT") {
                            d->SetLabel("m_INT");
                        } else if (ibuff == ":m_FLOAT") {
                            d->SetLabel("m_FLOAT");
                        } else {
                            d->SetLabel("m_STRING");
                        }
                        break;
                    case 1:
                        d->SetCode(ibuff);
                        break;
                    case 2:
                        d->SetOperand(ibuff);             
                }
                ibuff = "";
                input >> ibuff;
                count++;
            }        
        }
        adr += 44;
        m_symtab.AddSymbol(adr, d);
        std::cout << "Operands information: " << *d << std::endl;
    }
}

std::string Assembler::ParseInstruction (std::string& my_str) {
    int count = 0;
    bool check_register = true;
    m_facc.GetNextLine(my_str);
    std::istringstream input(my_str);
	std::string ibuff;
	input >> ibuff;
    if (ibuff.empty()) { //empty line
        return "END";
    }
    if (ibuff.at(0) == ';') { //first symbol is comment
        return "COMMENT";
    }
    if (ibuff.at(0) == '#') { //metka
        count++;
        return "METKA";
    }
    while (ibuff != "") {
        bool hasComment = false;
        while(ibuff != ""){
            int findComment = ibuff.find(';');
            if ( findComment >= 0) {
                hasComment = true;
                if (ibuff.at(0) == ';') break;
                ibuff = ibuff.substr(0, ibuff.find(';'));
            }
            switch(count) {
                case 0: // CODE OF OPERATION?
                    if (ibuff.at(0) == ':') { //metka
                        if ((ibuff == ":m_INT" || ibuff == ":m_FLOAT" || ibuff == ":m_STRING") == 0) {
                            return "ERROR";
                        }
                        return "Operator_Typedef";
                    }
                    //std::cout << "to label: " << ibuff << std::endl;
                    break;
                case 1:
                    if (ibuff.at(0) == '#') { //metka
                        return "Operator_Transition";
                    }
                    try {
                        stoi(ibuff);
                    }
                    catch (std::invalid_argument&) {
                        check_register = false;
                    }
                    if (check_register == false) {
                        return "ERROR";
                    }
                    //std::cout << "to label: " << ibuff << std::endl;
                    break;
                case 2:
                    if (ibuff.at(0) == '%') { //metka
                        if ((ibuff == "%DATA_SEGMENT" || ibuff == "%CODE_SEGMENT" || ibuff == "%STACK") == 0) {
                            return "ERROR";
                        }
                        return "Operator_RegisterMemory";
                    }
                    try {
                        stoi(ibuff);
                    }
                    catch (std::invalid_argument&) {
                        check_register = false;
                    }
                    if (check_register == false) {
                        return "ERROR";
                    }
                    //std::cout << "to label: " << ibuff << std::endl;
                    break;
            }
            ibuff = "";
            input >> ibuff;
            count++;
            if (hasComment) break;
        }
    }
     return "Operator_Register";
}