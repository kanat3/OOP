#pragma once
#include <string>

class Operator_Container {
protected:
    std::string m_Label; // label
    std::string m_Code; // The numerical value of the op code
public:
    std::string GetLabel (void) const { return m_Label; };
    std::string GetCode (void) const { return m_Code; };
    void SetLabel (const std::string& Label) { m_Label = Label; };
    void SetCode (const std::string& Code) { m_Code = Code; };
    virtual const std::string getTypeofClass (void) { return "Operator_Container"; };
};

class Operator_Register : public Operator_Container {
protected:
    short int m_LRegister; // The numerical value of the op register
    short int m_HRegister;
public:

    friend std::istream& operator >> (std::istream& in, Operator_Register& a);
    friend std::ostream& operator << (std::ostream& out, Operator_Register& a);
    void SetLR (const short int L_Reg) { m_LRegister = L_Reg; };
    void SetHR (const short int H_Reg) { m_HRegister = H_Reg; };
    short int GetLR (void) const { return m_LRegister; };
    short int GetHR (void) const { return m_HRegister; };
    virtual const std::string getTypeofClass (void) { return "Operator_Register"; };
};

class Operator_RegisterMemory : public Operator_Container {
private:
    std::string m_MemoryId;
    short int m_Register;
public:

    enum MEMORY_TYPE { //with '%'
        DATA_SEGMENT,
        CODE_SEGMENT,
        STACK
    };

    friend std::istream& operator >> (std::istream& in, Operator_RegisterMemory& a);
    friend std::ostream& operator << (std::ostream& out, const Operator_RegisterMemory& a);
    void SetMemoryID (const std::string ID) { m_MemoryId = ID; };
    void SetRegister (const short int Register) { m_Register = Register; };
    std::string GetMemoryID (void) const { return m_MemoryId; };
    short int GetRegister (void) const { return m_Register; };
    virtual const std::string getTypeofClass (void) { return "Operator_RegisterMemory"; };
};

class Operator_Transition : public Operator_Container {
private:
    std::string m_TransLabel; // id of transition label
public:

    friend std::istream& operator >> (std::istream& in, Operator_Transition& a);
    friend std::ostream& operator << (std::ostream& out, Operator_Transition& a);
    void SetTransLabel (const std::string& TLabel) { m_TransLabel = TLabel; };
    std::string GetTransLabel (void) const { return m_TransLabel; };
    virtual const std::string getTypeofClass (void) { return "Operator_Transition"; };
};

class Operator_Typedef : public Operator_Container {
private:
    std::string m_Operand; // must be
public:

    enum DATA_TYPE { // with ':'
        m_INT,
        m_FLOAT,
        m_STRING
    };

    friend std::istream& operator >> (std::istream& in, Operator_Typedef& a);
    friend std::ostream& operator << (std::ostream& out, Operator_Typedef& a);
    std::string GetOperand (void) const { return m_Operand; };
    void SetOperand (const std::string& Operand) { m_Operand = Operand; };
    virtual const std::string getTypeofClass (void) { return "Operator_Typedef"; };
};