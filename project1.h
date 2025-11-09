#include <stdio.h>
#include <stdint.h>

#define REG_COUNT 32

typedef struct {
	unsigned char opcode; // byte 0
	unsigned char byte1;
	unsigned char byte2;
	unsigned char byte3;
	int valid; // 1 = there is a real instruction to process, 0 = empty/bubble
} IF_TO_ID_reg;

typedef struct {
	unsigned char opcode;
	int destination_reg;
	int reg_operand1;
	int reg_operand2;
	int immediate_val;
	int valid; // 1 = there is a real instruction to process, 0 = empty/bubble
} ID_TO_IA_reg;

typedef struct {
	unsigned char opcode;
	int destination_reg;
	int reg_operand1;
	int reg_operand2;
	int value_in_reg1;
	int value_in_reg2;
	int immediate_val;
	int valid; // 1 = there is a real instruction to process, 0 = empty/bubble
	int result;
	int store_value;
} IA_TO_EX1_reg;

typedef struct {
	unsigned char opcode;
	int destination_reg;
	int reg_operand1;
	int reg_operand2;
	int value_in_reg1;
	int value_in_reg2;
	int immediate_val;
	int valid; // 1 = there is a real instruction to process, 0 = empty/bubble
	int result;
	int store_value;
} EX1_TO_EX2_reg;

typedef struct {
	unsigned char opcode;
	int destination_reg;
	int reg_operand1;
	int reg_operand2;
	int value_in_reg1;
	int value_in_reg2;
	int immediate_val;
	int valid; // 1 = there is a real instruction to process, 0 = empty/bubble
	int result;
	int store_value;
} EX2_TO_MEM1_reg;

typedef struct {
	unsigned char opcode;
	int destination_reg;
	int reg_operand1;
	int reg_operand2;
	int value_in_reg1;
	int value_in_reg2;
	int immediate_val;
	int valid; // 1 = there is a real instruction to process, 0 = empty/bubble
	int result;
	int store_value;
} MEM1_TO_MEM2_reg;

typedef struct {
	unsigned char opcode;
	int destination_reg;
	int reg_operand1;
	int reg_operand2;
	int value_in_reg1;
	int value_in_reg2;
	int immediate_val;
	int valid; // 1 = there is a real instruction to process, 0 = empty/bubble
	int result;
	int store_value;
	int counted;
} MEM2_TO_WB_reg;

typedef struct
{
    int registers[REG_COUNT];

	int data_hazard_count;
	int inst_count;
	int execution_time;
    int pc;
	int cycles;
	int pull_no_more_instr;

	int set_count;
	int add_count;
	int sub_count;
	int mul_count;
	int div_count;
	int ld_count;
	int sd_count;

	IF_TO_ID_reg if_to_id_reg;
	ID_TO_IA_reg id_to_ia_reg;
	IA_TO_EX1_reg ia_to_ex1_reg;
	EX1_TO_EX2_reg ex1_to_ex2_reg;
	EX2_TO_MEM1_reg ex2_to_mem1_reg;
	// IA_TO_EX2_reg ia_to_ex2_reg;
	// EX1_TO_MEM1_reg ex1_to_mem1_reg;
	// EX1_TO_WB_reg ex1_to_wb_reg;
	// EX2_TO_WB_reg ex2_to_wb_reg;
	MEM1_TO_MEM2_reg mem1_to_mem2_reg;
	MEM2_TO_WB_reg mem2_to_wb_reg;

	// 64KB = 65536 bytes of data
    unsigned char memory[65536];
	int program_ended;

} Simple_Pipe;



void IF_stage(Simple_Pipe* cpu);
void ID_stage(Simple_Pipe* cpu);
void IA_stage(Simple_Pipe* cpu);
void EX1_stage(Simple_Pipe* cpu);
void EX2_stage(Simple_Pipe* cpu);
void MEM1_stage(Simple_Pipe* cpu);
void MEM2_stage(Simple_Pipe* cpu);
void WB_stage(Simple_Pipe* cpu); 