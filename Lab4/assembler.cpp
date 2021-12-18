#include "assembler.hpp"

void Assembler::RunAssembler (void) {
    bool result = WriteInstruction();
    if (result == true) {
        DisplayInfo();
        std::cout << "\n=================    Memory information    =================\n" << std::endl;
        DisplayMemory();
    }
}

bool Assembler::WriteInstruction (void) {
    std::string parse_string;
    std::string result;
    std::string label = "";
    int address = 0;
    int numb_str = 0;
    do {
        if (m_facc.isEOF()) {
            result = "END";
            break;
        }
        if (address >= MAX_MEMORY) {
            std::cout << "Overflow!!" << std::endl;
            return true;
        }
        numb_str++;
        result = ParseInstruction(parse_string, numb_str);
        if (parse_string[0] == '#') {
            label = parse_string;
            result = ParseInstruction(parse_string, numb_str);
        }
        if (result == "ERROR") {
            std::cout << "Invalid arguments in the string " << numb_str << std::endl;
            std::cout << "\t " << numb_str << ": " << parse_string << std::endl;
            return false;
        }
        CreateOperands(result, parse_string, label, address);
        label = "";
    } while (result != "END");
    return true;
}

void Assembler::CreateOperands (const std::string& info, const std::string& line, const std::string& label, int& adr) {
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
                        AssignMemory(ibuff);
                        break;
                    case 2:
                        a->SetHR(stoi(ibuff));
                        AssignMemory(ibuff);
                        break;                
                }
                ibuff = "";
                input >> ibuff;
                count++;
            }        
        }
        adr += 109;
        m_symtab.AddSymbol(adr, a);
        //std::cout << "Operands information: " << *a << std::endl;
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
                        AssignMemory(ibuff);
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
        //std::cout << "Operands information: " << *b << std::endl;
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
                        AssignMemory(ibuff);
                        break;              
                }
                ibuff = "";
                input >> ibuff;
                count++;
            }        
        }
        adr += 39;
        m_symtab.AddSymbol(adr, c);
        //std::cout << "Operands information: " << *c << std::endl;
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
                        AssignMemory(ibuff);             
                }
                ibuff = "";
                input >> ibuff;
                count++;
            }        
        }
        adr += 44;
        m_symtab.AddSymbol(adr, d);
        //std::cout << "Operands information: " << *d << std::endl;
    }
}

std::string Assembler::ParseInstruction (std::string& my_str, const int numb_str) {
    int count = 0;
    int word_count = 0;
    bool check_register = true;
    m_facc.GetNextLine(my_str);
    std::istringstream input(my_str);
	std::string ibuff;
	input >> ibuff;
    if (ibuff.empty()) {
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
        while (ibuff != "") {
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
                    word_count++;
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
                    word_count++;
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
                    word_count++;
                    //std::cout << "to label: " << ibuff << std::endl;
                    break;
            }
            ibuff = "";
            input >> ibuff;
            count++;
            if (hasComment) break;
        }
    }
    if (word_count == 1) {
        return "ERROR";
    }
    return "Operator_Register";
}

bool Assembler::AssignMemory (const std::string& info) {
    int i = 0;
    std::string result;
    result = GetRegister(i);
    while (result != " ") {
        i++;
        result = GetRegister(i);
    }
    if (i > REGISTERS_COUNT) {
        std::cout << "\nStack overflow!!!" << std::endl;
        return false;
    }
    m_registers.at(i) = info;
    return true;
}