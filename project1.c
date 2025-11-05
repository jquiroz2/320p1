#include "project1.h"


void IF_stage(Simple_Pipe* cpu) {
    // program is over
    if(cpu->program_ended || cpu->pull_no_more_instr) {
        return;
    }
    
    // need to stall
    if(cpu->if_to_id_reg.valid) {
        printf("IF STALL\n");
        return; 
    }

    // else: fetch next instruction
    unsigned char opcode = cpu->memory[cpu->pc];
    unsigned char byte1 = cpu->memory[cpu->pc + 1];
    unsigned char byte2 = cpu->memory[cpu->pc + 2];
    unsigned char byte3 = cpu->memory[cpu->pc + 3];

    cpu->if_to_id_reg.opcode = opcode;
    cpu->if_to_id_reg.byte1 = byte1;
    cpu->if_to_id_reg.byte2 = byte2;
    cpu->if_to_id_reg.byte3 = byte3;
    cpu->if_to_id_reg.valid = 1;
    cpu->inst_count++;

    

    printf("current instruction in IF stage: ");
    printf("0x%02X %d %d %d\n", cpu->if_to_id_reg.opcode, cpu->if_to_id_reg.byte1, cpu->if_to_id_reg.byte2, cpu->if_to_id_reg.byte3);
    if(opcode == 0x70) {
        cpu->pull_no_more_instr = 1;
        return;
    }
    
    // printf("current instruction opcode: 0x%02X \n", opcode);
    // printf("current instruction byte1: 0x%02X \n", byte1);
    // printf("current instruction byte2: 0x%02X \n", byte2);
    // printf("current instruction byte3: 0x%02X \n", byte3);

    cpu->pc += 4;
    printf("new pc: %d", cpu->pc);
}

void ID_stage(Simple_Pipe* cpu) {
    if(!cpu->if_to_id_reg.valid) {
        //printf("ID stall - no instruction to process\n");
        return;
    }
    if(cpu->id_to_ia_reg.valid) {
        //printf("ID stall - id_to_ia alr in use\n");
        //cpu->data_hazard_count++;
        return;
    }

    cpu->id_to_ia_reg.opcode = cpu->if_to_id_reg.opcode;
    unsigned char opcode = cpu->id_to_ia_reg.opcode;
    switch(opcode) {
        case 0x00:
            cpu->id_to_ia_reg.destination_reg = cpu->if_to_id_reg.byte1;
            cpu->id_to_ia_reg.immediate_val = (cpu->if_to_id_reg.byte2 << 8) | cpu->if_to_id_reg.byte3;
            cpu->id_to_ia_reg.reg_operand1 = -1;
            cpu->id_to_ia_reg.reg_operand2 = -1;
            cpu->id_to_ia_reg.valid = 1;
            break;
        case 0x10:
            cpu->id_to_ia_reg.destination_reg = cpu->if_to_id_reg.byte1;
            cpu->id_to_ia_reg.reg_operand1 = cpu->if_to_id_reg.byte2;
            cpu->id_to_ia_reg.reg_operand2 = cpu->if_to_id_reg.byte3;
            cpu->id_to_ia_reg.immediate_val = -1;
            cpu->id_to_ia_reg.valid = 1;
            break;
        case 0x11:
            cpu->id_to_ia_reg.destination_reg = cpu->if_to_id_reg.byte1;
            cpu->id_to_ia_reg.reg_operand1 = cpu->if_to_id_reg.byte2;
            cpu->id_to_ia_reg.immediate_val = cpu->if_to_id_reg.byte3;
            cpu->id_to_ia_reg.reg_operand2 = -1;
            cpu->id_to_ia_reg.valid = 1;
            break;
        case 0x20:
            cpu->id_to_ia_reg.destination_reg = cpu->if_to_id_reg.byte1;
            cpu->id_to_ia_reg.reg_operand1 = cpu->if_to_id_reg.byte2;
            cpu->id_to_ia_reg.reg_operand2 = cpu->if_to_id_reg.byte3;
            cpu->id_to_ia_reg.immediate_val = -1;
            cpu->id_to_ia_reg.valid = 1;
            break;
        case 0x21:
            cpu->id_to_ia_reg.destination_reg = cpu->if_to_id_reg.byte1;
            cpu->id_to_ia_reg.reg_operand1 = cpu->if_to_id_reg.byte2;
            cpu->id_to_ia_reg.immediate_val = cpu->if_to_id_reg.byte3;
            cpu->id_to_ia_reg.reg_operand2 = -1;
            cpu->id_to_ia_reg.valid = 1;
            break;
        case 0x30:
            cpu->id_to_ia_reg.destination_reg = cpu->if_to_id_reg.byte1;
            cpu->id_to_ia_reg.reg_operand1 = cpu->if_to_id_reg.byte2;
            cpu->id_to_ia_reg.reg_operand2 = cpu->if_to_id_reg.byte3;
            cpu->id_to_ia_reg.immediate_val = -1;
            cpu->id_to_ia_reg.valid = 1;
            break;
        case 0x31:
            cpu->id_to_ia_reg.destination_reg = cpu->if_to_id_reg.byte1;
            cpu->id_to_ia_reg.reg_operand1 = cpu->if_to_id_reg.byte2;
            cpu->id_to_ia_reg.immediate_val = cpu->if_to_id_reg.byte3;
            cpu->id_to_ia_reg.reg_operand2 = -1;
            cpu->id_to_ia_reg.valid = 1;
            break;
        case 0x40:
            cpu->id_to_ia_reg.destination_reg = cpu->if_to_id_reg.byte1;
            cpu->id_to_ia_reg.reg_operand1 = cpu->if_to_id_reg.byte2;
            cpu->id_to_ia_reg.reg_operand2 = cpu->if_to_id_reg.byte3;
            cpu->id_to_ia_reg.immediate_val = -1;
            cpu->id_to_ia_reg.valid = 1;
            break;
        case 0x41:
            cpu->id_to_ia_reg.destination_reg = cpu->if_to_id_reg.byte1;
            cpu->id_to_ia_reg.reg_operand1 = cpu->if_to_id_reg.byte2;
            cpu->id_to_ia_reg.immediate_val = cpu->if_to_id_reg.byte3;
            cpu->id_to_ia_reg.reg_operand2 = -1;
            cpu->id_to_ia_reg.valid = 1;
            break;
        case 0x50:
            cpu->id_to_ia_reg.destination_reg = cpu->if_to_id_reg.byte1;
            cpu->id_to_ia_reg.immediate_val = (cpu->if_to_id_reg.byte2 << 8) | cpu->if_to_id_reg.byte3;
            cpu->id_to_ia_reg.reg_operand1 = -1;
            cpu->id_to_ia_reg.reg_operand2 = -1;
            cpu->id_to_ia_reg.valid = 1;
            break;
        case 0x51:
            cpu->id_to_ia_reg.destination_reg = cpu->if_to_id_reg.byte1;
            cpu->id_to_ia_reg.reg_operand1 = cpu->if_to_id_reg.byte2;
            cpu->id_to_ia_reg.reg_operand2 = cpu->if_to_id_reg.byte3;
            cpu->id_to_ia_reg.immediate_val = -1;
            cpu->id_to_ia_reg.valid = 1;
            break;
        case 0x60:
            cpu->id_to_ia_reg.destination_reg = cpu->if_to_id_reg.byte1;
            cpu->id_to_ia_reg.immediate_val = (cpu->if_to_id_reg.byte2 << 8) | cpu->if_to_id_reg.byte3;
            cpu->id_to_ia_reg.reg_operand1 = -1;
            cpu->id_to_ia_reg.reg_operand2 = -1;
            cpu->id_to_ia_reg.valid = 1;
            break;
        case 0x61:
            cpu->id_to_ia_reg.destination_reg = cpu->if_to_id_reg.byte1;
            cpu->id_to_ia_reg.reg_operand1 = cpu->if_to_id_reg.byte2;
            cpu->id_to_ia_reg.reg_operand2 = cpu->if_to_id_reg.byte3;
            cpu->id_to_ia_reg.immediate_val = -1;
            cpu->id_to_ia_reg.valid = 1;
            break;
        case 0x70:
            cpu->id_to_ia_reg.destination_reg = -1;
            cpu->id_to_ia_reg.reg_operand1 = -1;
            cpu->id_to_ia_reg.reg_operand2 = -1;
            cpu->id_to_ia_reg.immediate_val = -1;
            cpu->id_to_ia_reg.valid = 1;
            break;
    }

    printf("current instruction in ID stage: ");
    printf("0x%02X %d %d %d %d\n", cpu->id_to_ia_reg.opcode, cpu->id_to_ia_reg.destination_reg, cpu->id_to_ia_reg.reg_operand1, cpu->id_to_ia_reg.reg_operand2, cpu->id_to_ia_reg.immediate_val);
    
    // cpu->id_to_ia_reg.valid = 1;

    cpu->if_to_id_reg.valid = 0;
}


void IA_stage(Simple_Pipe* cpu) {
    
    if(!cpu->id_to_ia_reg.valid) {
        if(cpu->cycles > 2 && !cpu->pull_no_more_instr) {
            //printf("IA stall lmapppp\n");
        }
        return;
    }

    if(cpu->ia_to_ex1_reg.valid) {
        //printf("IA stall b/c ex1 not open for next instr\n");
        return;
    }

    unsigned char opcode = cpu->id_to_ia_reg.opcode;
    printf("current instruction in IA stage:--------------------");
    // printf("opcode: %d\n", cpu->id_to_ia_reg.opcode);

    printf("0x%02X %d %d %d %d\n", cpu->id_to_ia_reg.opcode, cpu->id_to_ia_reg.destination_reg, cpu->id_to_ia_reg.reg_operand1, cpu->id_to_ia_reg.reg_operand2, cpu->id_to_ia_reg.immediate_val);
    // printf("register operand 1: %d\n", cpu->id_to_ia_reg.reg_operand1);
    // printf("register operand 2: %d\n", cpu->id_to_ia_reg.reg_operand2);
    // printf("immediate value: %d\n", cpu->id_to_ia_reg.immediate_val);


    // int ex1_is_next_stage = (opcode == 0x00 || opcode == 0x10 || opcode == 0x11 || opcode == 0x20 || opcode == 0x21);
    // int ex2_is_next_stage = (opcode == 0x30 || opcode == 0x31 || opcode == 0x40 || opcode == 0x41); 
    // int is_a_memory_instr = (opcode == 0x50 || opcode == 0x51 || opcode == 0x60 || opcode == 0x61);

    // if(ex1_is_next_stage && cpu->ia_to_ex1_reg.valid) {
    //     printf("stalling\n");
    //     return; // we need to stall
    // }
    // if(ex2_is_next_stage && cpu->ia_to_ex2_reg.valid) {
    //     printf("stalling\n");
    //     return; // we need to stall
    // }
    // if(is_a_memory_instr && cpu->ia_to_ex1_reg.valid) {
    //     printf("stalling\n");
    //     return; // stalling
    // }

    // check for data dependencies
    int register_operand1 = cpu->id_to_ia_reg.reg_operand1;
    int register_operand2 = cpu->id_to_ia_reg.reg_operand2;

    // checking ex1 stage
    if(cpu->ia_to_ex1_reg.valid && cpu->ia_to_ex1_reg.destination_reg != -1) {
        if((register_operand1 == cpu->ia_to_ex1_reg.destination_reg) || (register_operand2 == cpu->ia_to_ex1_reg.destination_reg)) {
            printf("IA STALL\n");
            cpu->data_hazard_count++;
            return; // needs a stall
        }
    }

    if(cpu->ex1_to_ex2_reg.valid && cpu->ex1_to_ex2_reg.destination_reg != -1) {
        if((register_operand1 == cpu->ex1_to_ex2_reg.destination_reg) || (register_operand2 == cpu->ex1_to_ex2_reg.destination_reg)) {
            printf("IA STALL\n");
            cpu->data_hazard_count++;
            return; // needs a stall
        }
    }
    if(cpu->ex2_to_mem1_reg.valid && cpu->ex2_to_mem1_reg.destination_reg != -1) {
        if((register_operand1 == cpu->ex2_to_mem1_reg.destination_reg) || (register_operand2 == cpu->ex2_to_mem1_reg.destination_reg)) {
            printf("IA STALL\n");
            cpu->data_hazard_count++;
            return; // needs a stall
        }
    }
    if(cpu->mem1_to_mem2_reg.valid && cpu->mem1_to_mem2_reg.destination_reg != -1) {
        if((register_operand1 == cpu->mem1_to_mem2_reg.destination_reg) || (register_operand2 == cpu->mem1_to_mem2_reg.destination_reg)) {
            printf("IA STALL\n");
            cpu->data_hazard_count++;
            return; // needs a stall
        }
    }
    if(cpu->mem2_to_wb_reg.valid && cpu->mem2_to_wb_reg.destination_reg != -1) {
        if((register_operand1 == cpu->mem2_to_wb_reg.destination_reg) || (register_operand2 == cpu->mem2_to_wb_reg.destination_reg)) {
            printf("IA STALL\n");
            cpu->data_hazard_count++;
            return; // needs a stall
        }
    }

    // if it hasn't returned by here, no dependencies
    
    

    
    cpu->ia_to_ex1_reg.opcode = cpu->id_to_ia_reg.opcode;
    cpu->ia_to_ex1_reg.destination_reg = cpu->id_to_ia_reg.destination_reg;
    cpu->ia_to_ex1_reg.reg_operand1 = cpu->id_to_ia_reg.reg_operand1;
    cpu->ia_to_ex1_reg.reg_operand2 = cpu->id_to_ia_reg.reg_operand2;
    cpu->ia_to_ex1_reg.immediate_val = cpu->id_to_ia_reg.immediate_val;

    cpu->id_to_ia_reg.valid = 0;
    cpu->ia_to_ex1_reg.valid = 1;
    
    
}


void EX1_stage(Simple_Pipe* cpu) {
    if(!cpu->ia_to_ex1_reg.valid) {
        if(cpu->cycles > 3 && !cpu->pull_no_more_instr) {
            //cpu->data_hazard_count++;
        }
        return;
    }

    if(cpu->ex1_to_ex2_reg.valid) {
        printf("EX1 stall b/c ex2 not empty\n");
        return;
    }
    
    unsigned char opcode = cpu->ia_to_ex1_reg.opcode;


    
    //unsigned int result;
    printf("now we in EX1 stage:\n");
    printf("current instruction in EX1 stage: 0x%02X %d %d %d %d\n", cpu->ia_to_ex1_reg.opcode, cpu->ia_to_ex1_reg.destination_reg, cpu->ia_to_ex1_reg.reg_operand1, cpu->ia_to_ex1_reg.reg_operand2, cpu->ia_to_ex1_reg.immediate_val);

    // // need to check for data hazards here!!
    int register_operand1 = cpu->ia_to_ex1_reg.reg_operand1;
    int register_operand2 = cpu->ia_to_ex1_reg.reg_operand2;


    // // checking ex1
    // if(cpu->ex1_to_ex2_reg.valid && cpu->ia_to_ex1_reg.destination_reg != -1) {
    //     if((register_operand1 == cpu->ex1_to_ex2_reg.destination_reg) || (register_operand2 == cpu->ex1_to_ex2_reg.destination_reg)) {
    //         printf("EX1 STALL b/c data hazard\n");
    //         cpu->data_hazard_count++;
    //         return; // needs a stall
    //     }
    // }
    // // checking ex2
    // if(cpu->ex2_to_mem1_reg.valid && cpu->ia_to_ex1_reg.destination_reg != -1) {
    //     if((register_operand1 == cpu->ex2_to_mem1_reg.destination_reg) || (register_operand2 == cpu->ex2_to_mem1_reg.destination_reg)) {
    //         printf("EX1 STALL b/c data hazard\n");
    //         cpu->data_hazard_count++;
    //         return; // needs a stall
    //     }
    // }
    // // checking mem1
    // if(cpu->mem1_to_mem2_reg.valid && cpu->ia_to_ex1_reg.destination_reg != -1) {
    //     if((register_operand1 == cpu->mem1_to_mem2_reg.destination_reg) || (register_operand2 == cpu->mem1_to_mem2_reg.destination_reg)) {
    //         printf("EX1 STALL b/c data hazard\n");
    //         cpu->data_hazard_count++;
    //         return; // needs a stall
    //     }
    // }
    // //  checking mem2
    // if(cpu->mem2_to_wb_reg.valid && cpu->ia_to_ex1_reg.destination_reg != -1) {
    //     if((register_operand1 == cpu->mem2_to_wb_reg.destination_reg) || (register_operand2 == cpu->mem2_to_wb_reg.destination_reg)) {
    //         printf("EX1 STALL b/c data hazard\n");
    //         cpu->data_hazard_count++;
    //         return; // needs a stall
    //     }
    // }
    

    if(cpu->ia_to_ex1_reg.reg_operand1 != -1) {
        cpu->ex1_to_ex2_reg.value_in_reg1 = cpu->registers[register_operand1];
    }

    if(cpu->ia_to_ex1_reg.reg_operand2 != -1) {
        cpu->ex1_to_ex2_reg.value_in_reg2 = cpu->registers[register_operand2];
    }


    switch(opcode) {
        case 0x00:
            cpu->ia_to_ex1_reg.result = cpu->ia_to_ex1_reg.immediate_val;
            break;
        case 0x10:
            cpu->ia_to_ex1_reg.result = cpu->ex1_to_ex2_reg.value_in_reg1 + cpu->ex1_to_ex2_reg.value_in_reg2;
            break;
        case 0x11:
            cpu->ia_to_ex1_reg.result = cpu->ex1_to_ex2_reg.value_in_reg1 + cpu->ia_to_ex1_reg.immediate_val;
            printf("value in reg operand 1: %d\n", cpu->ex1_to_ex2_reg.value_in_reg1);
            break;
        case 0x20:
            cpu->ia_to_ex1_reg.result = cpu->ex1_to_ex2_reg.value_in_reg1 - cpu->ex1_to_ex2_reg.value_in_reg2;
            break;
        case 0x21:
            cpu->ia_to_ex1_reg.result = cpu->ex1_to_ex2_reg.value_in_reg1 - cpu->ia_to_ex1_reg.immediate_val;
            break;
        case 0x50:
            cpu->ia_to_ex1_reg.result = cpu->ia_to_ex1_reg.immediate_val;
            break;
        case 0x51:
            cpu->ia_to_ex1_reg.result = cpu->ex1_to_ex2_reg.value_in_reg1 + cpu->ex1_to_ex2_reg.value_in_reg2;
            break;
        case 0x60:
            cpu->ia_to_ex1_reg.result = cpu->ia_to_ex1_reg.immediate_val;
            break;
        case 0x61:
            cpu->ia_to_ex1_reg.result = cpu->ex1_to_ex2_reg.value_in_reg1 + cpu->ex1_to_ex2_reg.value_in_reg2;
            break;
        case 0x70:
            break;
    }
    //cpu->ia_to_ex1_reg.result = result;

        
    cpu->ex1_to_ex2_reg.destination_reg = cpu->ia_to_ex1_reg.destination_reg;
    cpu->ex1_to_ex2_reg.reg_operand1 = cpu->ia_to_ex1_reg.reg_operand1;
    cpu->ex1_to_ex2_reg.reg_operand2 = cpu->ia_to_ex1_reg.reg_operand2;
    // cpu->ex1_to_ex2_reg.value_in_reg1 = cpu->ia_to_ex1_reg.value_in_reg1;
    // cpu->ex1_to_ex2_reg.value_in_reg2 = cpu->ia_to_ex1_reg.value_in_reg2;
    cpu->ex1_to_ex2_reg.immediate_val = cpu->ia_to_ex1_reg.immediate_val;
    cpu->ex1_to_ex2_reg.opcode = cpu->ia_to_ex1_reg.opcode;
    cpu->ex1_to_ex2_reg.result = cpu->ia_to_ex1_reg.result;
    cpu->ex1_to_ex2_reg.valid = 1;

    cpu->ia_to_ex1_reg.valid = 0;
    
    
}

void EX2_stage(Simple_Pipe* cpu) {
    if(!cpu->ex1_to_ex2_reg.valid) {
        return;
    }
    if(cpu->ex2_to_mem1_reg.valid) {
        printf("EX2 stall b/c mem1 not ready for new instr\n");
        return;
    }
    printf("current instruction in EX2 stage: 0x%02X %d %d %d %d %d\n", cpu->ex1_to_ex2_reg.opcode, cpu->ex1_to_ex2_reg.destination_reg, cpu->ex1_to_ex2_reg.reg_operand1, cpu->ex1_to_ex2_reg.reg_operand2, cpu->ex1_to_ex2_reg.immediate_val, cpu->ex1_to_ex2_reg.result);

    unsigned char opcode = cpu->ex1_to_ex2_reg.opcode;
    //unsigned int result = 0;
    switch(opcode) {
        case 0x30:
            cpu->ex1_to_ex2_reg.result = cpu->ex1_to_ex2_reg.reg_operand1 * cpu->ex1_to_ex2_reg.reg_operand2;
            break;
        case 0x31:
            cpu->ex1_to_ex2_reg.result = cpu->ex1_to_ex2_reg.reg_operand1 * cpu->ex1_to_ex2_reg.immediate_val;
            break;
        case 0x40:
            if(cpu->ex1_to_ex2_reg.reg_operand2 != 0) {
                cpu->ex1_to_ex2_reg.result = cpu->ex1_to_ex2_reg.reg_operand1 / cpu->ex1_to_ex2_reg.reg_operand2;
            }
            else {
                cpu->ex1_to_ex2_reg.result = 0;
            }
            break;
        case 0x41:
            if(cpu->ex1_to_ex2_reg.immediate_val != 0) {
                cpu->ex1_to_ex2_reg.result = cpu->ex1_to_ex2_reg.reg_operand1 / cpu->ex1_to_ex2_reg.immediate_val;
            }
            else {
                cpu->ex1_to_ex2_reg.result = 0;
            }
            break;
    }
    //cpu->ex1_to_ex2_reg.result = result;
    
    cpu->ex2_to_mem1_reg.destination_reg = cpu->ex1_to_ex2_reg.destination_reg;
    cpu->ex2_to_mem1_reg.reg_operand1 = cpu->ex1_to_ex2_reg.reg_operand1;
    cpu->ex2_to_mem1_reg.reg_operand2 = cpu->ex1_to_ex2_reg.reg_operand2;
    cpu->ex2_to_mem1_reg.opcode = cpu->ex1_to_ex2_reg.opcode;
    cpu->ex2_to_mem1_reg.immediate_val = cpu->ex1_to_ex2_reg.immediate_val;
    cpu->ex2_to_mem1_reg.result = cpu->ex1_to_ex2_reg.result;

    cpu->ex2_to_mem1_reg.valid = 1;

    cpu->ex1_to_ex2_reg.valid = 0;
}

void MEM1_stage(Simple_Pipe* cpu) {
    if(!cpu->ex2_to_mem1_reg.valid) {
        return;
    }
    if(cpu->mem1_to_mem2_reg.valid) {
        printf("MEM1 STALL\n");
        return;
    }
    printf("current instruction in MEM1 stage: 0x%02X %d %d %d %d %d\n", cpu->ex2_to_mem1_reg.opcode, cpu->ex2_to_mem1_reg.destination_reg, cpu->ex2_to_mem1_reg.reg_operand1, cpu->ex2_to_mem1_reg.reg_operand2, cpu->ex2_to_mem1_reg.immediate_val, cpu->ex2_to_mem1_reg.result);

    cpu->mem1_to_mem2_reg.destination_reg = cpu->ex2_to_mem1_reg.destination_reg;
    cpu->mem1_to_mem2_reg.reg_operand1 = cpu->ex2_to_mem1_reg.reg_operand1;
    cpu->mem1_to_mem2_reg.reg_operand2 = cpu->ex2_to_mem1_reg.reg_operand2;
    cpu->mem1_to_mem2_reg.opcode = cpu->ex2_to_mem1_reg.opcode;
    cpu->mem1_to_mem2_reg.immediate_val = cpu->ex2_to_mem1_reg.immediate_val;
    cpu->mem1_to_mem2_reg.result = cpu->ex2_to_mem1_reg.result;

    cpu->mem1_to_mem2_reg.valid = 1;
    cpu->ex2_to_mem1_reg.valid = 0;
}


void MEM2_stage(Simple_Pipe* cpu) {
    if(!cpu->mem1_to_mem2_reg.valid) {
        return;
    }
    printf("current instruction in MEM2 stage: 0x%02X %d %d %d %d %d\n", cpu->mem1_to_mem2_reg.opcode, cpu->mem1_to_mem2_reg.destination_reg, cpu->mem1_to_mem2_reg.reg_operand1, cpu->mem1_to_mem2_reg.reg_operand2, cpu->mem1_to_mem2_reg.immediate_val, cpu->mem1_to_mem2_reg.result);

    unsigned char opcode = cpu->mem1_to_mem2_reg.opcode;

    if(opcode == 0x50 || opcode == 0x51) {
        unsigned int address = cpu->mem1_to_mem2_reg.result;

        unsigned int value = (cpu->memory[address]) | (cpu->memory[address + 1] << 8) | (cpu->memory[address + 2] << 16) | (cpu->memory[address + 3] << 24);
        cpu->mem1_to_mem2_reg.result = value;
    }
    else if(opcode == 0x60 || opcode == 0x61) {
        unsigned int address = cpu->mem1_to_mem2_reg.result;
        unsigned int value = cpu->mem1_to_mem2_reg.reg_operand1;

        cpu->memory[address] = value & 0xFF;
        cpu->memory[address + 1] = (value >> 8) & 0xFF;
        cpu->memory[address + 2] = (value >> 16) & 0xFF;
        cpu->memory[address + 3] = (value >> 24) & 0xFF;
    }

    if(cpu->mem2_to_wb_reg.valid) {
        return;
    }
    cpu->mem2_to_wb_reg.destination_reg = cpu->mem1_to_mem2_reg.destination_reg;
    cpu->mem2_to_wb_reg.opcode = cpu->mem1_to_mem2_reg.opcode;
    cpu->mem2_to_wb_reg.reg_operand1 = cpu->mem1_to_mem2_reg.reg_operand1;
    cpu->mem2_to_wb_reg.reg_operand2 = cpu->mem1_to_mem2_reg.reg_operand2;
    cpu->mem2_to_wb_reg.immediate_val = cpu->mem1_to_mem2_reg.immediate_val;
    cpu->mem2_to_wb_reg.result = cpu->mem1_to_mem2_reg.result;

    cpu->mem2_to_wb_reg.valid = 1;
    cpu->mem1_to_mem2_reg.valid = 0;
}

void WB_stage(Simple_Pipe* cpu) {
    // if(!cpu->ia_to_ex1_reg.valid) {
    //     if(cpu->cycles > 3) {
    //         printf("EX1 STALL\n");
    //     }
    //     return;
    // }

    if(!cpu->mem2_to_wb_reg.valid) {
        return;
    }

    if(cpu->cycles > 4 && !cpu->pull_no_more_instr) {
        cpu->data_hazard_count++;
        printf("WB STALL\n");
    }
    printf("current instruction in WB stage: 0x%02X %d %d %d %d %d\n", cpu->mem2_to_wb_reg.opcode, cpu->mem2_to_wb_reg.destination_reg, cpu->mem2_to_wb_reg.reg_operand1, cpu->mem2_to_wb_reg.reg_operand2, cpu->mem2_to_wb_reg.immediate_val, cpu->mem2_to_wb_reg.result);

    unsigned char opcode = cpu->mem2_to_wb_reg.opcode;
    if(!cpu->mem2_to_wb_reg.counted) {
        if (opcode == 0x00) {
            cpu->set_count++; 
            //printf("set count updated");
        }
        else if (opcode == 0x10 || opcode == 0x11) cpu->add_count++;
        else if (opcode == 0x20 || opcode == 0x21) cpu->sub_count++;
        else if (opcode == 0x30 || opcode == 0x31) cpu->mul_count++;
        else if (opcode == 0x40 || opcode == 0x41) cpu->div_count++;
        else if (opcode == 0x50 || opcode == 0x51) cpu->ld_count++;
        else if (opcode == 0x60 || opcode == 0x61) cpu->sd_count++;   
        else if(opcode ==0x70) cpu->program_ended = 1;
        cpu->mem2_to_wb_reg.counted = 1;    
    }
    if(cpu->mem2_to_wb_reg.destination_reg != -1) {
        cpu->registers[cpu->mem2_to_wb_reg.destination_reg] = cpu->mem2_to_wb_reg.result;
        printf("new value in register: %d\n", cpu->registers[cpu->mem2_to_wb_reg.destination_reg]);
    }
    if(cpu->mem2_to_wb_reg.opcode == 0x70) {
       cpu->program_ended = 1;
    }
    cpu->mem2_to_wb_reg.valid = 0;
    cpu->mem2_to_wb_reg.counted = 0;   
    
    
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

    printf("Number of instruction SET: %d\n", simple_pipe.set_count);
    printf("Number of instruction ADD: %d\n", simple_pipe.add_count);
    printf("Number of instruction SUB: %d\n", simple_pipe.sub_count);
    printf("Number of instruction MUL: %d\n", simple_pipe.mul_count);
    printf("Number of instruction DIV: %d\n", simple_pipe.div_count);
    printf("Number of instruction LD: %d\n", simple_pipe.ld_count);
    printf("Number of instruction SD: %d\n", simple_pipe.sd_count);
    printf("Number of instruction RET: 1\n");
    printf("\n");
    
    printf("Total execution cycles: %d\n", simple_pipe.execution_time);
    printf("IPC: %f\n", ((double)simple_pipe.inst_count / simple_pipe.execution_time) );
}

unsigned char bits_to_byte(char bits[8]) {
    unsigned char value = 0;
    for (int i = 0; i < 8; i++) {
        value <<= 1;
        if (bits[i] == '1') {
            value |= 1;
        }
    }
    return value;
}
int pipeline_has_instructions(Simple_Pipe* cpu) {
    return cpu->if_to_id_reg.valid || 
           cpu->id_to_ia_reg.valid || 
           cpu->ia_to_ex1_reg.valid || 
           cpu->ex1_to_ex2_reg.valid || 
           cpu->ex2_to_mem1_reg.valid ||
           cpu->mem1_to_mem2_reg.valid ||
           cpu->mem2_to_wb_reg.valid;
}
int main(int argc, char *argv[]) {
    Simple_Pipe my_cpu;
    my_cpu.data_hazard_count = 0;
    my_cpu.execution_time = 0;
    my_cpu.inst_count = 0;
    my_cpu.pc = 0;
    my_cpu.program_ended = 0;
    my_cpu.pull_no_more_instr = 0;
    my_cpu.cycles = 0;

    my_cpu.set_count = 0;
	my_cpu.add_count = 0;
	my_cpu.sub_count = 0;
	my_cpu.mul_count = 0;
	my_cpu.div_count = 0;
	my_cpu.ld_count = 0;
	my_cpu.sd_count = 0;
    
    for (int i = 0; i < REG_COUNT; i++) {
        my_cpu.registers[i] = 0;
    }

    my_cpu.if_to_id_reg.opcode = 0;
    my_cpu.if_to_id_reg.byte1 = 0;
    my_cpu.if_to_id_reg.byte2 = 0;
    my_cpu.if_to_id_reg.byte3 = 0;
    my_cpu.if_to_id_reg.valid = 0;

    my_cpu.id_to_ia_reg.opcode = 0;
    my_cpu.id_to_ia_reg.destination_reg = 0;
    my_cpu.id_to_ia_reg.reg_operand1 = 0;
    my_cpu.id_to_ia_reg.reg_operand2 = 0;
    my_cpu.id_to_ia_reg.immediate_val = 0;
    my_cpu.id_to_ia_reg.valid = 0;
    // my_cpu.id_to_ia_reg.value_in_reg1 = 0;
    // my_cpu.id_to_ia_reg.value_in_reg2 = 0;

    my_cpu.ia_to_ex1_reg.opcode = 0;
    my_cpu.ia_to_ex1_reg.destination_reg = 0;
    my_cpu.ia_to_ex1_reg.reg_operand1 = 0;
    my_cpu.ia_to_ex1_reg.reg_operand2 = 0;
    my_cpu.ia_to_ex1_reg.immediate_val = 0;
    my_cpu.ia_to_ex1_reg.valid = 0;
    my_cpu.ia_to_ex1_reg.result = 0;
    // my_cpu.ia_to_ex1_reg.value_in_reg1 = 0;
    // my_cpu.ia_to_ex1_reg.value_in_reg2 = 0;

    my_cpu.ex1_to_ex2_reg.opcode = 0;
    my_cpu.ex1_to_ex2_reg.destination_reg = 0;
    my_cpu.ex1_to_ex2_reg.reg_operand1 = 0;
    my_cpu.ex1_to_ex2_reg.reg_operand2 = 0;
    my_cpu.ex1_to_ex2_reg.immediate_val = 0;
    my_cpu.ex1_to_ex2_reg.valid = 0;
    my_cpu.ex1_to_ex2_reg.result = 0;

    my_cpu.ex2_to_mem1_reg.opcode = 0;
    my_cpu.ex2_to_mem1_reg.destination_reg = 0;
    my_cpu.ex2_to_mem1_reg.reg_operand1 = 0;
    my_cpu.ex2_to_mem1_reg.reg_operand2 = 0;
    my_cpu.ex2_to_mem1_reg.value_in_reg1 = 0;
    my_cpu.ex2_to_mem1_reg.value_in_reg2 = 0;
    my_cpu.ex2_to_mem1_reg.immediate_val = 0;
    my_cpu.ex2_to_mem1_reg.valid = 0;
    my_cpu.ex2_to_mem1_reg.result = 0;

    my_cpu.mem1_to_mem2_reg.opcode = 0;
    my_cpu.mem1_to_mem2_reg.destination_reg = 0;
    my_cpu.mem1_to_mem2_reg.reg_operand1 = 0;
    my_cpu.mem1_to_mem2_reg.reg_operand2 = 0;
    my_cpu.mem1_to_mem2_reg.immediate_val = 0;
    my_cpu.mem1_to_mem2_reg.valid = 0;
    my_cpu.mem1_to_mem2_reg.result = 0;

    my_cpu.mem2_to_wb_reg.opcode = 0;
    my_cpu.mem2_to_wb_reg.destination_reg = 0;
    my_cpu.mem2_to_wb_reg.reg_operand1 = 0;
    my_cpu.mem2_to_wb_reg.reg_operand2 = 0;
    my_cpu.mem2_to_wb_reg.immediate_val = 0;
    my_cpu.mem2_to_wb_reg.valid = 0;
    my_cpu.mem2_to_wb_reg.result = 0;
    my_cpu.mem2_to_wb_reg.counted = 0;

    
    int current_memory_index = 0;
    // need to open and read from input file 
    FILE *fp = fopen(argv[1], "r");
    // check if the file opened successfully
    if(fp == NULL) {
        perror("file open failed");
        return 1;
    }

    char line[34];
    
    while (fgets(line, sizeof(line), fp)) {
        char byte_bits[8];

        // break down each 32-bit instruction into 4 bytes
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                byte_bits[j] = line[(i * 8) + j];
            }

            unsigned char byte_val = bits_to_byte(byte_bits);
            my_cpu.memory[current_memory_index++] = byte_val;
        }
    }

    // for(int i =0; i<20; i++) {
    //     printf("btye: 0x%02X \n", my_cpu.memory[i]);
    // }

    fclose(fp);

    // printf("%02X", my_cpu.memory[0]);
    // printf("%02X", my_cpu.memory[1]);
    // printf("%02X", my_cpu.memory[2]);
    // printf("%02X", my_cpu.memory[3]);
    // printf("\n");
    // printf("%02X", my_cpu.memory[4]);
    // printf("%02X", my_cpu.memory[5]);
    // printf("%02X", my_cpu.memory[6]);
    // printf("%02X", my_cpu.memory[7]);
    // printf("\n");
    // printf("%02X", my_cpu.memory[8]);
    // printf("%02X", my_cpu.memory[9]);
    // printf("%02X", my_cpu.memory[10]);
    // printf("%02X", my_cpu.memory[11]);


    //int cycle = 0;
    while(pipeline_has_instructions(&my_cpu) || my_cpu.cycles == 0) {
        my_cpu.cycles++;
        printf("cycle number: %d----------\n", my_cpu.cycles);
        WB_stage(&my_cpu);
        MEM2_stage(&my_cpu);
        MEM1_stage(&my_cpu);
        EX2_stage(&my_cpu);
        EX1_stage(&my_cpu);
        IA_stage(&my_cpu);
        ID_stage(&my_cpu);
        IF_stage(&my_cpu);
        printf("\n\n");
    }
    my_cpu.execution_time = my_cpu.cycles;
    print_regs(my_cpu);


    // for(int i=0; i<5; i++) {
    //     printf("cycle %d ------------\n", i);
    //     IA_stage(&my_cpu);
    //     ID_stage(&my_cpu);
    //     IF_stage(&my_cpu);
    // }
   
    return 0;
}
