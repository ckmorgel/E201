int get_opcode(int instruction) {
    instruction &= 0x7F;
    return instruction >> 2;
}

int get_instruction_type(int instruction) {
    int opcode = get_opcode(instruction);

    switch(opcode) {
        case 0x0: return 0;
        case 0x8: return 1;
        case 0xC: return 2;
        case 0xD: return 3;
    }

    return -1;
}

int get_width(int instruction) {
    instruction &= 0x00007000;
    return instruction >> 12;
}

int get_destination(int instruction) {
    instruction &= 0x00000F80;
    return instruction >> 7;
}

int get_load_address(int instruction) {
    instruction &= 0x000F8000;
    return instruction >> 15;
}

int get_load_offset(int instruction) {
    instruction &= 0xFFF00000;
    return instruction >> 20;
}

int get_store_offset(int instruction) {
    int low = (instruction & 0x00000F80) >> 7;
    int high = (instruction & 0xFE000000) >> 25;

    return (high << 5) | low;
}

int get_store_source(int instruction) {
    instruction &= 0x01F00000;
    return instruction >> 20;
}

int get_store_address(int instruction) {
    instruction &= 0x000F8000;
    return instruction >> 15;
}

int get_math_function(int instruction) {
    instruction &= 0x00007000;
    return instruction >> 12;
}

int get_math_operand_a(int instruction) {
    instruction &= 0x000F8000;
    return instruction >> 15;
}

int get_math_operand_b(int instruction) {
    instruction &= 0x01F00000;
    return instruction >> 20;
}

int get_constant_value(int instruction) {
    instruction &= 0xFFFFF000;
    return instruction >> 12;
}