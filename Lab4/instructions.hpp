// Class to parse and provide information about instructions
#pragma once
#include <string>

enum InstructionType {
    I_AssemblerInstr,  // Assembler Language instruction.
    I_Comment,          // Comment or blank line
    I_End,                    // end instruction
    I_ILLEGAL		// Illegal instruction type
};

enum OperandType {
    O_Register,
    O_RegisterMemory,
    O_Typedef,
    O_Transition
};

class Instruction {
private:
	// The elemements of a instruction
	std::string m_Label;            // The label
	std::string m_OpCode;       // The numerical value of the op code
	std::string m_Operand;      // The operand
	std::string m_instruction;    // The original instruction
	// Derived values
	InstructionType m_Type; // The type of instruction
    OperandType m_OpType;
	void clearValues();
public:
	Instruction();
	~Instruction() {};
};