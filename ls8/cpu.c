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


void cpu_ram_write(struct cpu *cpu, unsigned char value, unsigned char index){
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
    unsigned char num, val;
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
      case ADD:
        cpu->registers[operandA] = cpu->registers[operandA] + cpu->registers[operandB];
        break;
      case PUSH:
        cpu->SP--;
        num = cpu->ram[cpu->PC + 1];
        val = cpu->registers[num];
        cpu->ram[cpu->SP] = val;
        break;
      case POP:
        num = cpu->ram[cpu->PC + 1];
        cpu->registers[num] = cpu->ram[cpu->SP];
        cpu->SP++;
        break;
      case CALL:
        cpu->SP--;
        cpu->ram[cpu->SP] = cpu->PC + 2;
        num = cpu->ram[cpu->PC + 1];
        cpu->PC = cpu->registers[num];
        break;
      case RET:
        num = cpu->ram[cpu->SP];
        cpu->SP++;
        cpu->PC = num;
        break;
      case CMP:
        // printf("CMP\n");
        if(cpu->registers[operandA] < cpu->registers[operandB]){
          cpu->FL[7] = 0;
          cpu->FL[6] = 0;
          cpu->FL[5] = 1;
        }
        else if(cpu->registers[operandA] > cpu->registers[operandB]){
          cpu->FL[7] = 0;
          cpu->FL[6] = 1;
          cpu->FL[5] = 0;
        }
        else if(cpu->registers[operandA] == cpu->registers[operandB]) {
          cpu->FL[7] = 1;
          cpu->FL[6] = 0;
          cpu->FL[5] = 0;
        }
        break;
      case JMP:
        cpu->PC = cpu->registers[operandA];
        // printf("JMP\n");
        break;
      case JEQ:
        if(cpu->FL[7] == 1){
          cpu->PC = cpu->registers[operandA];
          // printf("JEQ\n");
        }
        else{
          cpu->PC +=2;
        }
        break;
      case JNE:
        if(cpu->FL[7] == 0){
          cpu->PC = cpu->registers[operandA];
          // printf("JNE\n");
        }
        else{
          cpu->PC +=2;
        }
        break;
      default:
        fprintf(stderr, "PC %02x: unknown instruction %02x\n", cpu->PC, IR);
        exit(3);
    }

    // printf("TRACE: cpu-PC: %d: cpu-IR: %02X  %d  operand0: %02x operand1: %02x\n", cpu->PC, IR, cpu->FL, operandA, operandB);

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
  memset(cpu->FL, 0, sizeof(cpu->FL));
  memset(cpu->registers, 0, sizeof(cpu->registers));
  memset(cpu->ram, 0, sizeof(cpu->ram));
  cpu->registers[7] = 0xF4;
  cpu->SP = cpu->registers[7];
}
