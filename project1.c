#include "project1.h"


void IF_stage(Simple_Pipe* cpu)
{
}


void ID_stage(Simple_Pipe* cpu);
{
}


void IA_stage(Simple_Pipe* cpu);
{
}


void EX1_stage(Simple_Pipe* cpu);
{
}


void EX2_stage(Simple_Pipe* cpu);
{
}


void MEM1_stage(Simple_Pipe* cpu);
{
}


void MEM2_stage(Simple_Pipe* cpu);
{
}


void  WB_stage(Simple_Pipe* cpu); 
{
}


void print_regs(Simple_Pipe simple_pipe)
{
    printf("\nRegisters: \n");
    printf("----------------------------------------\n");
    for (int i = 0; i < REG_COUNT; i += 2)
    {
        if (i + 1 < REG_COUNT)
        {
            printf("  R%-3d: %-10d |   R%-3d: %-10d\n", i, simple_pipe.registers[i], i + 1, simple_pipe.registers[i + 1]);
            printf("----------------------------------------\n");
        }
        else
        {
            printf("  R%-3d: %-10d |   \n", i, simple_pipe.registers[i]);
            printf("----------------------------------------\n");
        }
    }
    printf("\n");
    printf("Stalled cycles due to data hazard: %d \n", simple_pipe.data_hazard_count);
    printf("\n");

    printf("Number of instruction SET: \n");
    printf("Number of instruction ADD: \n");
    printf("Number of instruction SUB: \n");
    printf("Number of instruction MUL: \n");
    printf("Number of instruction DIV: \n");
    printf("Number of instruction LD: \n");
    printf("Number of instruction SD: \n");
    printf("Number of instruction RET: 1\n");
    printf("\n");
    
    printf("Total execution cycles: %d\n", simple_pipe.execution_time);
    printf("IPC: %f\n", ((double)simple_pipe.inst_count / simple_pipe.execution_time) );
}


int main(int argc, char *argv[])
{

    return 0;
}
