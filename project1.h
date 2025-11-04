#include <stdio.h>

#define REG_COUNT 32

typedef struct
{
    int registers[REG_COUNT];

	int data_hazard_count;
	int inst_count;
	int execution_time;
    int pc;

	int set_count;
	int add_count;
	int sub_count;
	int mul_count;
	int div_count;
	int ld_count;
	int sd_count;

	// 64KB = 65536 bytes of data
    unsigned char memory[65536];
	int program_ended;

} Simple_Pipe;

struct {
	unsigned char opcode; // byte 0
	unsigned char byte1;
	unsigned char byte2;
	unsigned char byte3;
	int valid; // 1 = there is a real instruction to process, 0 = empty/bubble
} if_to_id_reg;

struct {
	unsigned char opcode;
	int destination_reg;
	int reg_operand1;
	int reg_operand2;
	int immediate_val;
	int valid; // 1 = there is a real instruction to process, 0 = empty/bubble
} id_to_ia_reg;

struct {
	unsigned char opcode;
	int destination_reg;
	int reg_operand1;
	int reg_operand2;
	int immediate_val;
	int valid; // 1 = there is a real instruction to process, 0 = empty/bubble
	int result;
} ia_to_ex1_reg;

struct {
	unsigned char opcode;
	int destination_reg;
	int reg_operand1;
	int reg_operand2;
	int immediate_val;
	int valid; // 1 = there is a real instruction to process, 0 = empty/bubble
	int result;
} ia_to_ex2_reg;

struct {
	unsigned char opcode;
	int destination_reg;
	int reg_operand1;
	int reg_operand2;
	int immediate_val;
	int valid; // 1 = there is a real instruction to process, 0 = empty/bubble
	int result;
} ex1_to_mem1_reg;

struct {
	unsigned char opcode;
	int destination_reg;
	int reg_operand1;
	int reg_operand2;
	int immediate_val;
	int valid; // 1 = there is a real instruction to process, 0 = empty/bubble
	int result;
} ex1_to_wb_reg;

struct {
	unsigned char opcode;
	int destination_reg;
	int reg_operand1;
	int reg_operand2;
	int immediate_val;
	int valid; // 1 = there is a real instruction to process, 0 = empty/bubble
	int result;
} ex2_to_wb_reg;

struct {
	unsigned char opcode;
	int destination_reg;
	int reg_operand1;
	int reg_operand2;
	int immediate_val;
	int valid; // 1 = there is a real instruction to process, 0 = empty/bubble
	int result;
} mem1_to_mem2_reg;

struct {
	unsigned char opcode;
	int destination_reg;
	int reg_operand1;
	int reg_operand2;
	int immediate_val;
	int valid; // 1 = there is a real instruction to process, 0 = empty/bubble
	int result;
} mem2_to_wb_reg;

void IF_stage(Simple_Pipe* cpu);
void ID_stage(Simple_Pipe* cpu);
void IA_stage(Simple_Pipe* cpu);
void EX1_stage(Simple_Pipe* cpu);
void EX2_stage(Simple_Pipe* cpu);
void MEM1_stage(Simple_Pipe* cpu);
void MEM2_stage(Simple_Pipe* cpu);
void WB_stage(Simple_Pipe* cpu); 