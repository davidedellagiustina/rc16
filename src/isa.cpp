/**
 * ===================
 * RCC - RC16 COMPILER
 * ===================
 * 
 * ISA DEFINITION
 * Della Giustina Davide
 * 05/10/2019
 */

#ifndef ISA
#define ISA

// SET <reg> <val>: save immediate value to register.
// @param reg       Destination register.
// @param val       Immediate value.
// @param cond      Conditional. Defualt: AL.
// @return          Hexadecimal string representation of command.
inline string set(const int &reg, const int &val, const int &cond = AL) {
    oss os;
    try {
        os << SET(reg, val, cond);
    } catch (...) { throw "The given value is too big. Maximum is 63."; }
    return os.str();
}

// MOV <reg> <reg>: move a value from a register to another.
// @param reg1      Source register.
// @param reg2      Destination register.
// @param cond      Conditional. Defualt: AL.
// @return          Hexadecimal string representation of command.
inline string mov(const int &reg1, const int &reg2, const int &cond = AL) {
    return MOVREG(reg1, reg2, cond);
}

// LDR <reg> <reg_addr>: load value from memory to register.
// @param reg       Destination register.
// @param reg_addr  Register containing memory address.
// @param cond      Conditional. Defualt: AL.
// @return          Hexadecimal string representation of command.
inline string ldr(const int &reg, const int &reg_addr, const int &cond = AL) {
    oss os;
    os << MOVREG(reg_addr, MAR, cond);
    os << MOVMEM(false, reg, cond);
    return os.str();
}

// STR <reg> <reg_addr>: store value in memory from register.
// @param reg       Source register.
// @param reg_addr  Register containing memory address.
// @param cond      Conditional. Defualt: AL.
// @return          Hexadecimal string representation of command.
inline string str(const int &reg, const int &reg_addr, const int &cond = AL) {
    oss os;
    os << MOVREG(reg_addr, MAR, cond);
    os << MOVMEM(true, reg, cond);
    return os.str();
}

// ADD <reg> <reg> <reg>: add two values into a register.
// @param reg1      Register containing operand 1.
// @param reg2      Register containing operand 2.
// @param reg3      Destination register.
// @param s         Update flags if 1, do not otherwise.
// @param cond      Conditional. Defualt: AL.
// @return          Hexadecimal string representation of command.
inline string add(const int &reg1, const int &reg2, const int &reg3, const bool &s, const int &cond = AL) {
    oss os;
    if (s && cond != AL) { // If flags need to get updated and condition is not AL, we need to copy reg3 to OUT to avoid errors
        os << MOVREG(reg3, A);
        os << SET(B, 0);
        os << EXC(ADD, false, false);
    }
    os << MOVREG(reg1, A, cond);
    os << MOVREG(reg2, B, cond);
    os << EXC(ADD, false, s, cond);
    os << MOVREG(OUT, reg3);
    return os.str();
}

// SUB <reg> <reg> <reg>: subtract two values into a register.
// @param reg1      Register containing operand 1.
// @param reg2      Register containing operand 2.
// @param reg3      Destination register.
// @param s         Update flags if 1, do not otherwise.
// @param cond      Conditional. Defualt: AL.
// @return          Hexadecimal string representation of command.
inline string sub(const int &reg1, const int &reg2, const int &reg3, const bool &s, const int &cond = AL) {
    oss os;
    if (s && cond != AL) { // If flags need to get updated and condition is not AL, we need to copy reg3 to OUT to avoid errors
        os << MOVREG(reg3, A);
        os << SET(B, 0);
        os << EXC(ADD, false, false);
    }
    os << MOVREG(reg1, A, cond);
    os << MOVREG(reg2, B, cond);
    os << EXC(ADD, true, s, cond);
    os << MOVREG(OUT, reg3);
    return os.str();
}

// AND <reg> <reg> <reg>: perform bitwise and of two values into a register.
// @param reg1      Register containing operand 1.
// @param reg2      Register containing operand 2.
// @param reg3      Destination register.
// @param s         Update flags if 1, do not otherwise.
// @param cond      Conditional. Defualt: AL.
// @return          Hexadecimal string representation of command.
inline string and(const int &reg1, const int &reg2, const int &reg3, const bool &s, const int &cond = AL) {
    oss os;
    if (s && cond != AL) { // If flags need to get updated and condition is not AL, we need to copy reg3 to OUT to avoid errors
        os << MOVREG(reg3, A);
        os << SET(B, 0);
        os << EXC(ADD, false, false);
    }
    os << MOVREG(reg1, A, cond);
    os << MOVREG(reg2, B, cond);
    os << EXC(AND, false, s, cond);
    os << MOVREG(OUT, reg3);
    return os.str();
}

// ORR <reg> <reg> <reg>: perform bitwise or of two values into a register.
// @param reg1      Register containing operand 1.
// @param reg2      Register containing operand 2.
// @param reg3      Destination register.
// @param s         Update flags if 1, do not otherwise.
// @param cond      Conditional. Defualt: AL.
// @return          Hexadecimal string representation of command.
inline string orr(const int &reg1, const int &reg2, const int &reg3, const bool &s, const int &cond = AL) {
    oss os;
    if (s && cond != AL) { // If flags need to get updated and condition is not AL, we need to copy reg3 to OUT to avoid errors
        os << MOVREG(reg3, A);
        os << SET(B, 0);
        os << EXC(ADD, false, false);
    }
    os << MOVREG(reg1, A, cond);
    os << MOVREG(reg2, B, cond);
    os << EXC(ORR, false, s, cond);
    os << MOVREG(OUT, reg3);
    return os.str();
}

// XOR <reg> <reg> <reg>: perform bitwise xor of two values into a register.
// @param reg1      Register containing operand 1.
// @param reg2      Register containing operand 2.
// @param reg3      Destination register.
// @param s         Update flags if 1, do not otherwise.
// @param cond      Conditional. Defualt: AL.
// @return          Hexadecimal string representation of command.
inline string xor(const int &reg1, const int &reg2, const int &reg3, const bool &s, const int &cond = AL) {
    oss os;
    if (s && cond != AL) { // If flags need to get updated and condition is not AL, we need to copy reg3 to OUT to avoid errors
        os << MOVREG(reg3, A);
        os << SET(B, 0);
        os << EXC(ADD, false, false);
    }
    os << MOVREG(reg1, A, cond);
    os << MOVREG(reg2, B, cond);
    os << EXC(XOR, false, s, cond);
    os << MOVREG(OUT, reg3);
    return os.str();
}

// PRT <reg>: print value contained in register.
// @param reg       Source register.
// @param cond      Conditional. Defualt: AL.
// @return          Hexadecimal string representation of command.
inline string prt(const int &reg, const int &cond = AL) {
    return MOVREG(reg, OR, cond);
}

// CMP <reg> <reg>: update flags basing on subtraction.
// @param reg1      Register 1.
// @param reg2      Register 2.
// @param cond      Conditional. Defualt: AL.
// @return          Hexadecimal string representation of command.
inline string cmp(const int &reg1, const int &reg2, const int &cond = AL) {
    oss os;
    // Flags do get updated, but result remains in OUT register
    os << MOVREG(reg1, A, cond);
    os << MOVREG(reg2, B, cond);
    os << EXC(ADD, true, true, cond);
    return os.str();
}

// JMP <rel_addr>: jump to a certain address.
// @param reladdr   Address to jump to. RELATIVE ADDRESS: this value is added to the current one (at the moment of this operation start). MAX: 63.
// @param cond      Conditional. Defualt: AL.
// @return          Hexadecimal string representation of command.
inline string jmp(const int &reladdr, const int &cond = AL) {
    oss os;
    // Since flags are not being updated, this version is fine
    os << MOVREG(PC, A, cond);
    try {
        os << SET(B, reladdr, cond);
    } catch (...) { throw "Cannot jump this long!"; }
    os << EXC(ADD, false, false, cond);
    os << MOVREG(OUT, PC, cond);
    return os.str();
}

// NOP: do nothing.
// @param cond      Conditional. Defualt: AL.
// @return          Hexadecimal string representation of command.
inline string nop(const int &cond = AL) {
    return NOP(cond);
}

// HLT: halt program execution.
// @param cond      Conditional. Defualt: AL.
// @return          Hexadecimal string representation of command.
inline string hlt(const int &cond = AL) {
    return HLT(cond);
}

#endif