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
	bool m_IsNumericOperand;// == true if the operand is numeric
	void clearValues();
public:
	Instruction();
	~Instruction() {};

	// Parse the Instruction
	InstructionType ParseInstruction(std::string &a_buff);
	// Compute the location of the next instruction
	int LocationNextInstruction(int a_loc);
	// To access the label
	inline std::string &GetLabel() {
		return m_Label;
	};
	// To determine if a label is blank
	inline bool isLabel() {
		return !m_Label.empty();
	};
	inline std::string &GetInstruction() {
		return m_instruction;
	}
	inline std::string getOperand() {
		return m_Operand;
	}
	inline bool isNumericOperand() {
		return m_IsNumericOperand;
	}
	inline std::string getOpCode() {
		return m_OpCode;
	}
	inline void setOpCode(std::string str) {
		m_OpCode = str;
	}
	inline void setLabel(std::string str) {
		m_Label = str;
	}
	inline void setOperand(std::string str) {
		m_Operand = str;
	}
};