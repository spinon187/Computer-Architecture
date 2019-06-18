#ifndef _CPU_H_
#define _CPU_H_

// Holds all information about the CPU
struct cpu {
  // TODO
  // PC
  unsigned int PC;
  // registers (array)
  unsigned char registers[8];
  // ram (array)
  unsigned char ram[256];
  unsigned char FL;
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
// TODO: more instructions here. These can be used in cpu_run().
#define ADD  10100000 
#define SUB  10100001 
#define MUL  10100010 
#define DIV  10100011 
#define MOD  10100100 
#define INC  01100101 
#define DEC  01100110 
#define CMP  10100111 
#define AND  10101000 
#define NOT  01101001 
#define OR   10101010 
#define XOR  10101011 
#define SHL  10101100 
#define SHR  10101101
#define HLT  00000001

// Function declarations

extern void cpu_load(struct cpu *cpu);
extern void cpu_init(struct cpu *cpu);
extern void cpu_run(struct cpu *cpu);

#endif
