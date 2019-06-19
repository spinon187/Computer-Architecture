#include "cpu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */

unsigned char cpu_ram_read(struct cpu *cpu, unsigned char index){
  return cpu->ram[index];
};

void cpu_ram_write(struct cpu *cpu, unsigned char index, unsigned char value){
  cpu->ram[index] = value;
}

void cpu_load(char *filename, struct cpu *cpu){
	FILE *fp;
	char line[1024];

  int address = 0;

	if ((fp = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "Cannot open file %s\n", filename);
		exit(2);
	}

	while (fgets(line, sizeof(line), fp) != NULL) {
		char *endchar;
		unsigned char byte = strtoul(line, &endchar, 2);
		if (endchar == line) {
			continue;
		}
		cpu_ram_write(cpu, byte, address++);
	}
}


/**
 * ALU
 */
// void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
// {
//   switch (op) {
//     case ALU_MUL:
//       // TODO
//       break;

//     // TODO: implement more ALU ops
//   }
// }

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction


  while (running) {
    unsigned char operandA = 0;
    unsigned char operandB = 0;
    unsigned char IR = cpu_ram_read(cpu, cpu->PC);
    unsigned int num_operands = IR >> 6;
    if(num_operands == 2){
      operandA = cpu_ram_read(cpu, (cpu->PC +1) & 0xff);
      operandB = cpu_ram_read(cpu, (cpu->PC +2) & 0xff);
    }
    else if(num_operands == 1){
      operandA = cpu_ram_read(cpu, (cpu->PC +1) & 0xff);
    }
    else{}

    int instruction_set_pc = (IR >> 4) & 1;
    switch(IR){
      case HLT:
        running = 0;
        break;
      case LDI:
        cpu->registers[operandA] = operandB;
        break;
      case PRN:
        printf("%d\n", cpu->registers[operandA]);
        break;
      case MUL:
        cpu->registers[operandA] = cpu->registers[operandA] * cpu->registers[operandB];
        break;
      default:
        fprintf(stderr, "PC %02x: unknown instruction %02x\n", cpu->PC, IR);
        exit(3);
    }

    if(!instruction_set_pc) {
      cpu->PC += num_operands + 1;
    }
  }
}

 
/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  cpu->PC = 0;
  cpu->FL = 0;
  memset(cpu->registers, 0, sizeof(cpu->registers));
  memset(cpu->ram, 0, sizeof(cpu->ram));
  // cpu->registers[7] = 0xF4;
}
