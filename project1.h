#include <stdio.h>

#define REG_COUNT 32

void IF_stage(Simple_Pipe* cpu);
void ID_stage(Simple_Pipe* cpu);
void IA_stage(Simple_Pipe* cpu);
void EX1_stage(Simple_Pipe* cpu);
void EX2_stage(Simple_Pipe* cpu);
void MEM1_stage(Simple_Pipe* cpu);
void MEM2_stage(Simple_Pipe* cpu);
void WB_stage(Simple_Pipe* cpu); 

typedef struct
{
    int registers[REG_COUNT];

	int data_hazard_count;
	int inst_count;
	int execution_time;
    int pc;

} Simple_Pipe;
