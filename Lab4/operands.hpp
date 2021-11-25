#pragma once
#include <string>

class Operator_Container {
protected:
    std::string m_Label; // label
    std::string m_Code; // The numerical value of the op code
public:
    std::string GetLabel (void) const { return m_Label; };
    std::string GetCode (void) const { return m_Code; };
};

class Operator_Register : public Operator_Container {
protected:
    short int m_LRegister; // The numerical value of the op register
    short int m_HRegister; // The numerical value of the op register
public:
    ~Operator_Register() { return; };

    friend std::istream& operator >> (std::istream& in, Operator_Register& a);
    friend std::ostream& operator << (std::ostream& out, Operator_Register& a);
};

class Operator_RegisterMemory : public Operator_Container {
private:
    std::string m_MemoryId;
    std::string m_Register;
public:
    ~Operator_RegisterMemory () { return; };

    friend std::istream& operator >> (std::istream& in, Operator_RegisterMemory& a);
    friend std::ostream& operator << (std::ostream& out, Operator_RegisterMemory& a);
};

class Operator_Transition : public Operator_Container {
private:
    std::string m_TranslLabel; // id of transition label
public:
    ~Operator_Transition () { return; };

    friend std::istream& operator >> (std::istream& in, Operator_Transition& a);
    friend std::ostream& operator << (std::ostream& out, Operator_Transition& a);
};

class Operator_Typedef : public Operator_Container {
private:
    std::string m_Operand; // must be
public:
    ~Operator_Typedef () { return; };

    friend std::istream& operator >> (std::istream& in, Operator_Typedef& a);
    friend std::ostream& operator << (std::ostream& out, Operator_Typedef& a);
};