#pragma once
#include <string>

class Operand_Register {
protected:
    std::string m_ORLabel; // label
    bool m_IsLabel; // is label
    std::string m_ORCode; // The numerical value of the op code
    short int m_ORRegister1; // The numerical value of the op register
    short int m_ORRegister2; // The numerical value of the op register
public:
    virtual const DisplayInfo (void);
    std::string RegisterValue (int n); // first or second ?
    Operand_Register& SetORRegister (const std::string& a, int n); // 1 or 2
}

class Operand_RegisterMemory : public Operand_Register {
private:
    std::string m_MemoryId;
public:
    virtual const DisplayInfo (void);  
    std::string GetOPMRegister (void) const { return m_ORRegister1; };
    void SetOPMRegister (const std::string& a);
    std::string GetOPM_MemoryId (void) const { return m_MemoryId; };
    void SetOPM_MemoryId (const std::string& a);
}

class Operand_Transition {
private:
    std::string m_OTCode; // The numerical value of the op code
    std::string m_TranslLabel; // id of transition label
public:
    void DisplayInfo (void) const;
    std::string GetTranslLabel (void) const { return m_TranslLabel; };
    void SetTranslLabel (const std::string& a);
}

class Operand_Typedef {
private:
    std::string m_ORLabel; // must be
    std::string m_Type; // type of data
    std::string m_OTypeCode; // code of operator
    std::string m_Operand; // string or integer
    bool m_IsInt; // is m_Operand int
public:
    void DisplayInfo (void) const;
    std::string GetORLabel (void) const { return m_ORLabel; };
    void SetORLabel (const std::string& a);
}