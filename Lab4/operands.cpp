#include "operands.hpp"
#include "tools.hpp"

std::istream& operator >> (std::istream& in, Operator_Register& a) {
    std::cout << "Enter the label: " << std::endl;
    getInput(a.m_Label);
    std::cout << "Enter the code of operation: " << std::endl;
    getInput(a.m_Code);
    std::cout << "Enter the L register: " << std::endl;
    getInput(a.m_LRegister);
    std::cout << "Enter the H register: " << std::endl;
    getInput(a.m_HRegister);
    return in;   
}

std::ostream& operator << (std::ostream& out, Operator_Register& a) {
    std::cout << "Your register operand: " << std::endl;
    std::cout << a.m_Label << std::endl << a.m_Code << std::endl
                << a.m_LRegister << std::endl << a.m_HRegister << std::endl;
    return out;
}

std::istream& operator >> (std::istream& in, Operator_RegisterMemory& a) {
    std::cout << "Enter the label: " << std::endl;
    getInput(a.m_Label);
    std::cout << "Enter the code of operation: " << std::endl;
    getInput(a.m_Code);
    std::cout << "Enter the register: " << std::endl;
    getInput(a.m_Register);
    std::cout << "Enter the memory ID: " << std::endl;
    getInput(a.m_MemoryId); 
    return in;      
}

std::ostream& operator << (std::ostream& out, Operator_RegisterMemory& a) {
    std::cout << "Your memory register operand: " << std::endl;
    std::cout << a.m_Label << std::endl << a.m_Code << std::endl
                << a.m_Register << std::endl
                        << a.m_MemoryId << std::endl;
    return out;
}

std::istream& operator >> (std::istream& in, Operator_Transition& a) {
    std::cout << "Enter the code of operation: " << std::endl;
    getInput(a.m_Code);
    std::cout << "Enter the transition label: " << std::endl;
    getInput(a.m_TranslLabel);
    return in;  
}

std::ostream& operator << (std::ostream& out, Operator_Transition& a) {
    std::cout << "Your transition operand: " << std::endl;
    std::cout << a.m_Code << std::endl
                << a.m_TranslLabel << std::endl;
    return out;    
}

std::istream& operator >> (std::istream& in, Operator_Typedef& a) {
    std::cout << "Enter the label: " << std::endl;
    getInput(a.m_Label);
    std::cout << "Enter the code of operation: " << std::endl;
    getInput(a.m_Code);
    std::cout << "Enter the operand: " << std::endl;
    getInput(a.m_Operand);
    return in;  
}

std::ostream& operator << (std::ostream& out, Operator_Typedef& a) {
    std::cout << "Your typedef operand: " << std::endl;
    std::cout << a.m_Label << std::endl
            << a.m_Code << std::endl
                << a.m_Operand << std::endl;
    return out;      
}