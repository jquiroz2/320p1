#include "project1.h"


void IF_stage(Simple_Pipe* cpu) {
    // program is over
    if(cpu->program_ended) {
        return;
    }
    
    // need to stall
    if(if_to_id_reg.valid) {
        return; 
    }

    // else: fetch next instruction
    unsigned char opcode = cpu->memory[cpu->pc];
    unsigned char byte1 = cpu->memory[cpu->pc + 1];
    unsigned char byte2 = cpu->memory[cpu->pc + 2];
    unsigned char byte3 = cpu->memory[cpu->pc + 3];

    if_to_id_reg.opcode = opcode;
    if_to_id_reg.byte1 = byte1;
    if_to_id_reg.byte2 = byte2;
    if_to_id_reg.byte3 = byte3;
    if_to_id_reg.valid = 1;
    printf("current instruction opcode: 0x%02X \n", opcode);
    printf("current instruction byte1: 0x%02X \n", byte1);
    printf("current instruction byte2: 0x%02X \n", byte2);
    printf("current instruction byte3: 0x%02X \n", byte3);

    cpu->pc += 4;
}

void ID_stage(Simple_Pipe* cpu) {
    if(!if_to_id_reg.valid) {
        return;
    }
    if(id_to_ia_reg.valid) {
        return;
    }

    id_to_ia_reg.opcode = if_to_id_reg.opcode;
    unsigned char opcode = id_to_ia_reg.opcode;
    switch(opcode) {
        case 0x00:
            id_to_ia_reg.destination_reg = if_to_id_reg.byte1;
            id_to_ia_reg.immediate_val = (if_to_id_reg.byte2 << 8) | if_to_id_reg.byte3;
            id_to_ia_reg.reg_operand1 = -1;
            id_to_ia_reg.reg_operand2 = -1;
            break;
        case 0x10:
            id_to_ia_reg.destination_reg = if_to_id_reg.byte1;
            id_to_ia_reg.reg_operand1 = if_to_id_reg.byte2;
            id_to_ia_reg.reg_operand2 = if_to_id_reg.byte3;
            id_to_ia_reg.immediate_val = -1;
            break;
        case 0x11:
            id_to_ia_reg.destination_reg = if_to_id_reg.byte1;
            id_to_ia_reg.reg_operand1 = if_to_id_reg.byte2;
            id_to_ia_reg.immediate_val = if_to_id_reg.byte3;
            id_to_ia_reg.reg_operand2 = -1;
            break;
        case 0x20:
            id_to_ia_reg.destination_reg = if_to_id_reg.byte1;
            id_to_ia_reg.reg_operand1 = if_to_id_reg.byte2;
            id_to_ia_reg.reg_operand2 = if_to_id_reg.byte3;
            id_to_ia_reg.immediate_val = -1;
            break;
        case 0x21:
            id_to_ia_reg.destination_reg = if_to_id_reg.byte1;
            id_to_ia_reg.reg_operand1 = if_to_id_reg.byte2;
            id_to_ia_reg.immediate_val = if_to_id_reg.byte3;
            id_to_ia_reg.reg_operand2 = -1;
            break;
        case 0x30:
            id_to_ia_reg.destination_reg = if_to_id_reg.byte1;
            id_to_ia_reg.reg_operand1 = if_to_id_reg.byte2;
            id_to_ia_reg.reg_operand2 = if_to_id_reg.byte3;
            id_to_ia_reg.immediate_val = -1;
            break;
        case 0x31:
            id_to_ia_reg.destination_reg = if_to_id_reg.byte1;
            id_to_ia_reg.reg_operand1 = if_to_id_reg.byte2;
            id_to_ia_reg.immediate_val = if_to_id_reg.byte3;
            id_to_ia_reg.reg_operand2 = -1;
            break;
        case 0x40:
            id_to_ia_reg.destination_reg = if_to_id_reg.byte1;
            id_to_ia_reg.reg_operand1 = if_to_id_reg.byte2;
            id_to_ia_reg.reg_operand2 = if_to_id_reg.byte3;
            id_to_ia_reg.immediate_val = -1;
            break;
        case 0x41:
            id_to_ia_reg.destination_reg = if_to_id_reg.byte1;
            id_to_ia_reg.reg_operand1 = if_to_id_reg.byte2;
            id_to_ia_reg.immediate_val = if_to_id_reg.byte3;
            id_to_ia_reg.reg_operand2 = -1;
            break;
        case 0x50:
            id_to_ia_reg.destination_reg = if_to_id_reg.byte1;
            id_to_ia_reg.immediate_val = (if_to_id_reg.byte2 << 8) | if_to_id_reg.byte3;
            id_to_ia_reg.reg_operand1 = -1;
            id_to_ia_reg.reg_operand2 = -1;
            break;
        case 0x51:
            id_to_ia_reg.destination_reg = if_to_id_reg.byte1;
            id_to_ia_reg.reg_operand1 = if_to_id_reg.byte2;
            id_to_ia_reg.reg_operand2 = if_to_id_reg.byte3;
            id_to_ia_reg.immediate_val = -1;
            break;
        case 0x60:
            id_to_ia_reg.destination_reg = if_to_id_reg.byte1;
            id_to_ia_reg.immediate_val = (if_to_id_reg.byte2 << 8) | if_to_id_reg.byte3;
            id_to_ia_reg.reg_operand1 = -1;
            id_to_ia_reg.reg_operand2 = -1;
            break;
        case 0x61:
            id_to_ia_reg.destination_reg = if_to_id_reg.byte1;
            id_to_ia_reg.reg_operand1 = if_to_id_reg.byte2;
            id_to_ia_reg.reg_operand2 = if_to_id_reg.byte3;
            id_to_ia_reg.immediate_val = -1;
            break;
        case 0x70:
            id_to_ia_reg.destination_reg = -1;
            id_to_ia_reg.reg_operand1 = -1;
            id_to_ia_reg.reg_operand2 = -1;
            id_to_ia_reg.immediate_val = -1;
            break;
    }

    id_to_ia_reg.valid = 1;

    if_to_id_reg.valid = 0;
}


void IA_stage(Simple_Pipe* cpu) {
    printf("opcode: %d\n", id_to_ia_reg.opcode);

    printf("destination register: %d\n", id_to_ia_reg.destination_reg);
    printf("register operand 1: %d\n", id_to_ia_reg.reg_operand1);
    printf("register operand 2: %d\n", id_to_ia_reg.reg_operand2);
    printf("immediate value: %d\n", id_to_ia_reg.immediate_val);

    if(!id_to_ia_reg.valid) {
        return;
    }

    unsigned char opcode = id_to_ia_reg.opcode;

    int ex1_is_next_stage = (opcode == 0x00 || opcode == 0x10 || opcode == 0x11 || opcode == 0x20 || opcode == 0x21);
    int ex2_is_next_stage = (opcode == 0x30 || opcode == 0x31 || opcode == 0x40 || opcode == 0x41); 
    int is_a_memory_instr = (opcode == 0x50 || opcode == 0x51 || opcode == 0x60 || opcode == 0x61);

    if(ex1_is_next_stage && ia_to_ex1_reg.valid) {
        return; // we need to stall
    }
    if(ex2_is_next_stage && ia_to_ex2_reg.valid) {
        return; // we need to stall
    }
    if(is_a_memory_instr && ia_to_ex1_reg.valid) {
        return; // stalling
    }

    // check for data dependencies
    int register_operand1 = id_to_ia_reg.reg_operand1;
    int register_operand2 = id_to_ia_reg.reg_operand2;

    // checking ex1 stage
    if(ia_to_ex1_reg.valid && ia_to_ex1_reg.destination_reg != -1) {
        if((register_operand1 == ia_to_ex1_reg.destination_reg) || (register_operand2 == ia_to_ex1_reg.destination_reg)) {
            return; // needs a stall
        }
    }

    // checking ex2 stage
    if(ia_to_ex2_reg.valid && ia_to_ex2_reg.destination_reg != -1) {
        if((register_operand1 == ia_to_ex2_reg.destination_reg) || (register_operand2 == ia_to_ex2_reg.destination_reg)) {
            return; // needs a stall
        }
    }

    // check mem1 stage
    if(ex1_to_mem1_reg.valid && ex1_to_mem1_reg.destination_reg != -1) {
        if((register_operand1 == ex1_to_mem1_reg.destination_reg) || (register_operand2 == ex1_to_mem1_reg.destination_reg)) {
            return;
        }
    }

    // check mem2 stage
    if(mem1_to_mem2_reg.valid && mem1_to_mem2_reg.destination_reg != -1) {
        if((register_operand1 == mem1_to_mem2_reg.destination_reg) || (register_operand2 == mem1_to_mem2_reg.destination_reg)) {
            return;
        }
    }

    // if it hasn't returned by here, no dependencies
    if(id_to_ia_reg.reg_operand1 != -1) {
        id_to_ia_reg.reg_operand1 = cpu->registers[id_to_ia_reg.reg_operand1];
    }

    if(id_to_ia_reg.reg_operand2 != -1) {
        id_to_ia_reg.reg_operand2 = cpu->registers[id_to_ia_reg.reg_operand2];
    }

    if(ex1_is_next_stage || is_a_memory_instr) {
        ia_to_ex1_reg.opcode = id_to_ia_reg.opcode;
        ia_to_ex1_reg.destination_reg = id_to_ia_reg.destination_reg;
        ia_to_ex1_reg.reg_operand1 = id_to_ia_reg.reg_operand1;
        ia_to_ex1_reg.reg_operand2 = id_to_ia_reg.reg_operand2;
        ia_to_ex1_reg.immediate_val = id_to_ia_reg.immediate_val;

        ia_to_ex1_reg.valid = 1;
    }
    else if(ex2_is_next_stage) {
        ia_to_ex2_reg.opcode = id_to_ia_reg.opcode;
        ia_to_ex2_reg.destination_reg = id_to_ia_reg.destination_reg;
        ia_to_ex2_reg.reg_operand1 = id_to_ia_reg.reg_operand1;
        ia_to_ex2_reg.reg_operand2 = id_to_ia_reg.reg_operand2;
        ia_to_ex2_reg.immediate_val = id_to_ia_reg.immediate_val;

        ia_to_ex2_reg.valid = 1;
    }
    else {
        // ret instruction
        ia_to_ex1_reg.opcode = id_to_ia_reg.opcode;
        ia_to_ex1_reg.destination_reg = id_to_ia_reg.destination_reg;
        ia_to_ex1_reg.reg_operand1 = id_to_ia_reg.reg_operand1;
        ia_to_ex1_reg.reg_operand2 = id_to_ia_reg.reg_operand2;
        ia_to_ex1_reg.immediate_val = id_to_ia_reg.immediate_val;

        ia_to_ex1_reg.valid = 1;
    }
    id_to_ia_reg.valid = 0;
}


void EX1_stage(Simple_Pipe* cpu) {
    if(!ia_to_ex1_reg.valid) {
        return;
    }
    unsigned char opcode = ia_to_ex1_reg.opcode;
    unsigned int result;

    switch(opcode) {
        case 0x00:
            result = ia_to_ex1_reg.immediate_val;
            break;
        case 0x10:
            result = ia_to_ex1_reg.reg_operand1 + ia_to_ex1_reg.reg_operand2;
            break;
        case 0x11:
            result = ia_to_ex1_reg.reg_operand1 + ia_to_ex1_reg.immediate_val;
            break;
        case 0x20:
            result = ia_to_ex1_reg.reg_operand1 - ia_to_ex1_reg.reg_operand2;
            break;
        case 0x21:
            result = ia_to_ex1_reg.reg_operand1 - ia_to_ex1_reg.immediate_val;
            break;
        case 0x50:
            result = ia_to_ex1_reg.immediate_val;
            break;
        case 0x51:
            result = ia_to_ex1_reg.reg_operand1 + ia_to_ex2_reg.reg_operand2;
            break;
        case 0x60:
            result = ia_to_ex1_reg.immediate_val;
            break;
        case 0x61:
            result = ia_to_ex1_reg.reg_operand1 + ia_to_ex1_reg.reg_operand2;
            break;
        case 0x70:
            break;
    }
    ia_to_ex1_reg.result = result;

    int is_memory_instr = (opcode == 0x50 || opcode == 0x51 || opcode == 0x60 || opcode == 0x61);
    if(is_memory_instr) {
        if(ex1_to_mem1_reg.valid) {
            return;
        }
        ex1_to_mem1_reg.destination_reg = ia_to_ex1_reg.destination_reg;
        ex1_to_mem1_reg.reg_operand1 = ia_to_ex1_reg.reg_operand1;
        ex1_to_mem1_reg.reg_operand2 = ia_to_ex1_reg.reg_operand2;
        ex1_to_mem1_reg.immediate_val = ia_to_ex1_reg.immediate_val;
        ex1_to_mem1_reg.opcode = ia_to_ex1_reg.opcode;
        ex1_to_mem1_reg.result = ia_to_ex1_reg.result;
        ex1_to_mem1_reg.valid = 1;
    }
    else {
        if(ex1_to_wb_reg.valid) {
            return;
        }
        ex1_to_wb_reg.destination_reg = ia_to_ex1_reg.destination_reg;
        ex1_to_wb_reg.reg_operand1 = ia_to_ex1_reg.reg_operand1;
        ex1_to_wb_reg.reg_operand2 = ia_to_ex1_reg.reg_operand2;
        ex1_to_wb_reg.immediate_val = ia_to_ex1_reg.immediate_val;
        ex1_to_wb_reg.opcode = ia_to_ex1_reg.opcode;
        ex1_to_wb_reg.result = ia_to_ex1_reg.result;
        ex1_to_wb_reg.valid = 1;
    }
    ia_to_ex1_reg.valid = 0;
}

void EX2_stage(Simple_Pipe* cpu) {
    if(!ia_to_ex2_reg.valid) {
        return;
    }
    unsigned char opcode = ia_to_ex2_reg.opcode;
    unsigned int result = 0;
    switch(opcode) {
        case 0x30:
            result = ia_to_ex2_reg.reg_operand1 * ia_to_ex2_reg.reg_operand2;
            break;
        case 0x31:
            result = ia_to_ex2_reg.reg_operand1 * ia_to_ex2_reg.immediate_val;
            break;
        case 0x40:
            if(ia_to_ex2_reg.reg_operand2 != 0) {
                result = ia_to_ex2_reg.reg_operand1 / ia_to_ex2_reg.reg_operand2;
            }
            else {
                result = 0;
            }
            break;
        case 0x41:
            if(ia_to_ex2_reg.immediate_val != 0) {
                result = ia_to_ex2_reg.reg_operand1 / ia_to_ex2_reg.immediate_val;
            }
            else {
                result = 0;
            }
            break;
    }
    ia_to_ex2_reg.result = result;
    if(ex2_to_wb_reg.valid) {
        return;
    }
    ex2_to_wb_reg.destination_reg = ia_to_ex2_reg.destination_reg;
    ex2_to_wb_reg.reg_operand1 = ia_to_ex2_reg.reg_operand1;
    ex2_to_wb_reg.reg_operand2 = ia_to_ex2_reg.reg_operand2;
    ex2_to_wb_reg.opcode = ia_to_ex2_reg.opcode;
    ex2_to_wb_reg.immediate_val = ia_to_ex2_reg.immediate_val;
    ex2_to_wb_reg.result = ia_to_ex2_reg.result;

    ex2_to_wb_reg.valid = 1;

    ia_to_ex2_reg.valid = 0;
}

void MEM1_stage(Simple_Pipe* cpu) {
    if(!ex1_to_mem1_reg.valid) {
        return;
    }
    if(mem1_to_mem2_reg.valid) {
        return;
    }
    mem1_to_mem2_reg.destination_reg = ex1_to_mem1_reg.destination_reg;
    mem1_to_mem2_reg.reg_operand1 = ex1_to_mem1_reg.reg_operand1;
    mem1_to_mem2_reg.reg_operand2 = ex1_to_mem1_reg.reg_operand2;
    mem1_to_mem2_reg.opcode = ex1_to_mem1_reg.opcode;
    mem1_to_mem2_reg.immediate_val = ex1_to_mem1_reg.immediate_val;
    mem1_to_mem2_reg.result = ex1_to_mem1_reg.result;

    mem1_to_mem2_reg.valid = 1;
    ex1_to_mem1_reg.valid = 0;
}


void MEM2_stage(Simple_Pipe* cpu) {
    if(!mem1_to_mem2_reg.valid) {
        return;
    }
    unsigned char opcode = mem1_to_mem2_reg.opcode;

    if(opcode == 0x50 || opcode == 0x51) {
        unsigned int address = mem1_to_mem2_reg.result;

        unsigned int value = (cpu->memory[address]) | (cpu->memory[address + 1] << 8) | (cpu->memory[address + 2] << 16) | (cpu->memory[address + 3] << 24);
        mem1_to_mem2_reg.result = value;
    }
    else if(opcode == 0x60 || opcode == 0x61) {
        unsigned int address = mem1_to_mem2_reg.result;
        unsigned int value = mem1_to_mem2_reg.reg_operand1;

        cpu->memory[address] = value & 0xFF;
        cpu->memory[address + 1] = (value >> 8) & 0xFF;
        cpu->memory[address + 2] = (value >> 16) & 0xFF;
        cpu->memory[address + 3] = (value >> 24) & 0xFF;
    }

    if(mem2_to_wb_reg.valid) {
        return;
    }
    mem2_to_wb_reg.destination_reg = mem1_to_mem2_reg.destination_reg;
    mem2_to_wb_reg.opcode = mem1_to_mem2_reg.opcode;
    mem2_to_wb_reg.reg_operand1 = mem1_to_mem2_reg.reg_operand1;
    mem2_to_wb_reg.reg_operand2 = mem1_to_mem2_reg.reg_operand2;
    mem2_to_wb_reg.immediate_val = mem1_to_mem2_reg.immediate_val;
    mem2_to_wb_reg.result = mem1_to_mem2_reg.result;

    mem2_to_wb_reg.valid = 1;
    mem1_to_mem2_reg.valid = 0;
}

void  WB_stage(Simple_Pipe* cpu) {
    if(ex1_to_wb_reg.valid) {
        switch(ex1_to_wb_reg.opcode) {
            case 0x00: 
                cpu->set_count++;
                break;
            case 0x10: case 0x11:
                cpu->add_count++;
                break;
            case 0x20: case 0x21:
                cpu->sub_count++;
                break;
            case 0x50: case 0x51:
                cpu->ld_count++;
                break;
            case 0x60: case 0x61:
                cpu->sd_count++;
                break;
            case 0x70:
                break;
        }


        if(ex1_to_wb_reg.destination_reg != -1) {
            cpu->registers[ex1_to_wb_reg.destination_reg] = ex1_to_wb_reg.result;
        }
        if(ex1_to_wb_reg.opcode == 0x70) {
            cpu->program_ended = 1;
        }
        ex1_to_wb_reg.valid = 0;
    }
    if(ex2_to_wb_reg.valid) {
        if(ex2_to_wb_reg.destination_reg != -1) {
            cpu->registers[ex2_to_wb_reg.destination_reg] = ex2_to_wb_reg.result;
        }
        ex2_to_wb_reg.valid = 0;
    }
    if(mem2_to_wb_reg.valid) {
        if(mem2_to_wb_reg.destination_reg != -1) {
            cpu->registers[mem2_to_wb_reg.destination_reg] = mem2_to_wb_reg.result;
        }
        mem2_to_wb_reg.valid = 0;
    }
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

int main(int argc, char *argv[]) {
    Simple_Pipe my_cpu;
    my_cpu.data_hazard_count = 0;
    my_cpu.execution_time = 0;
    my_cpu.inst_count = 0;
    my_cpu.pc = 0;
    my_cpu.program_ended = 0;

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

    if_to_id_reg.opcode = 0;
    if_to_id_reg.byte1 = 0;
    if_to_id_reg.byte2 = 0;
    if_to_id_reg.byte3 = 0;
    if_to_id_reg.valid = 0;
    
    int current_memory_index = 0;
    // need to open and read from input file 
    FILE *fp = fopen(argv[1], "r");
    // check if the file opened successfully
    if(fp == NULL) {
        perror("file open failed");
        return 1;
    }

    char line[33];
    
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

    int cycle = 0;
    while(!my_cpu.program_ended) {
        cycle++;
        WB_stage(&my_cpu);
        MEM2_stage(&my_cpu);
        MEM1_stage(&my_cpu);
        EX2_stage(&my_cpu);
        EX1_stage(&my_cpu);
        IA_stage(&my_cpu);
        ID_stage(&my_cpu);
        IF_stage(&my_cpu);
    }

    print_regs(my_cpu);


    // for(int i=0; i<5; i++) {
    //     printf("cycle %d ------------\n", i);
    //     IA_stage(&my_cpu);
    //     ID_stage(&my_cpu);
    //     IF_stage(&my_cpu);
    // }
   
    return 0;
}
