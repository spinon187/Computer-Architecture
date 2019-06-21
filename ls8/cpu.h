#ifndef _CPU_H_
#define _CPU_H_

// Holds all information about the CPU
struct cpu {
  // TODO
  // PC
  unsigned int PC;
  unsigned char FL[8];
  // registers (array)
  unsigned char registers[8];
  // ram (array)
  unsigned char ram[256];
  unsigned int SP;
};

// ALU operations
enum alu_op {
	ALU_MUL,
  // ALU_ADD,
  // ALU_AND,
  // ALU_CMP,
  // ALU_DEC,
  // ALU_DIV,
  // ALU_INC,
  // ALU_MOD,
  // ALU_NOT,
  // ALU_OR,
  // ALU_SUB,
  // ALU_XOR
};

// Instructions

// These use binary literals. If these aren't available with your compiler, hex
// literals should be used.

#define LDI  0b10000010
#define PRN  0b01000111
#define ADD  0b10100000 
// #define SUB  0b10100001 
#define MUL  0b10100010 
// #define DIV  0b10100011 
// #define MOD  0b10100100 
// #define INC  0b01100101 
// #define DEC  0b01100110 
#define CMP  0b10100111 
// #define AND  0b10101000 
// #define NOT  0b01101001 
// #define OR   0b10101010 
// #define XOR  0b10101011 
// #define SHL  0b10101100 
// #define SHR  0b10101101
#define PUSH 0b01000101
#define POP  0b01000110
#define CALL 0b01010000
#define RET  0b00010001
#define JMP  0b01010100
#define JEQ  0b01010101
#define JNE  0b01010110
#define HLT  0b00000001

// Function declarations

extern void cpu_load(char *filename, struct cpu *cpu);
extern void cpu_init(struct cpu *cpu);
extern void cpu_run(struct cpu *cpu);

#endif
