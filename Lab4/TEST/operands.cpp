#include "operands.hpp"
#include "tools.hpp"

std::istream& operator >> (std::istream& in, Operator_Register& a) {
    std::cout << "Do you want to enter a label? y/n: ";
    std::string answer;
    while (1) {
        getInput(answer);
        if (answer == "y" || answer == "n") {
            break;
        }
    }
    if (answer == "y") {
        std::cout << "Enter the label of <register operator>: " << std::endl;
        getInput(a.m_Label);
    } else {
        a.m_Label.clear();
    }
    std::cout << "Enter the code of operation: " << std::endl;
    getInput(a.m_Code);
    std::cout << "Enter the L register: " << std::endl;
    getInput(a.m_LRegister);
    std::cout << "Enter the H register: " << std::endl;
    getInput(a.m_HRegister);
    return in;   
}

std::ostream& operator << (std::ostream& out, Operator_Register& a) {
    std::cout << std::endl << "This is register operand: " << std::endl;
    std::cout << a.m_Label << std::endl << a.m_Code << std::endl
                << a.m_LRegister << std::endl << a.m_HRegister << std::endl;
                //"\n"
    return out;
}

std::istream& operator >> (std::istream& in, Operator_RegisterMemory& a) {
    std::cout << "Do you want to enter a label? y/n: ";
    std::string answer = "";
    while (1) {
        getInput(answer);
        if (answer == "y" || answer == "n") {
            break;
        }
    }
    if (answer == "y") {
        std::cout << "Enter the label of <register memory operator>: " << std::endl;
        getInput(a.m_Label);
    } else {
        a.m_Label = "";
    }
    std::cout << "Enter the code of operation: " << std::endl;
    getInput(a.m_Code);
    std::cout << "Enter the register: " << std::endl;
    getInput(a.m_Register);
    std::cout << "Enter the memory ID: " << std::endl;
    getInput(a.m_MemoryId); 
    return in;      
}

std::ostream& operator << (std::ostream& out, const Operator_RegisterMemory& a) {
    std::cout << std::endl << "This is memory register operand: " << std::endl;
    std::cout << a.m_Label << std::endl << a.m_Code << std::endl
                << a.m_Register << std::endl
                        << a.m_MemoryId << std::endl;
    return out;
}

std::istream& operator >> (std::istream& in, Operator_Transition& a) {
    std::cout << "Enter the code of operation of <transition operator>: " << std::endl;
    getInput(a.m_Code);
    std::cout << "Enter the transition label: " << std::endl;
    getInput(a.m_TransLabel);
    return in;  
}

std::ostream& operator << (std::ostream& out, Operator_Transition& a) {
    std::cout << std::endl << "This is transition operand: " << std::endl;
    std::cout << a.m_Code << std::endl
                << a.m_TransLabel << std::endl;
    return out;    
}

std::istream& operator >> (std::istream& in, Operator_Typedef& a) {
    std::cout << "Do you want to enter a label? y/n: ";
    std::string answer = "";
    while (1) {
        getInput(answer);
        if (answer == "y" || answer == "n") {
            break;
        }
    }
    if (answer == "y") {
        std::cout << "Enter the label of <typedef operator>: " << std::endl;
        getInput(a.m_Label);
    } else {
        a.m_Label = "";
    }
    std::cout << "Enter the code of operation: " << std::endl;
    getInput(a.m_Code);
    std::cout << "Enter the operand: " << std::endl;
    getInput(a.m_Operand);
    return in;  
}

std::ostream& operator << (std::ostream& out, Operator_Typedef& a) {
    std::cout << std::endl << "This is typedef operand: " << std::endl;
    std::cout << a.m_Label << std::endl
            << a.m_Code << std::endl
                << a.m_Operand << std::endl;
    return out;      
}