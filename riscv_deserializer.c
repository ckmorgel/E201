int get_opcode(int instruction) {
    instruction &= 0x7F;
    return instruction >> 2;
}

int get_instruction_type(int instruction) {
    int opcode = get_opcode(instruction);

    if (opcode == 0x0)
        return 0;
    if (opcode == 0x8)
        return 1;
    if (opcode == 0xC)
        return 2;
    if (opcode == 0xD)
        return 3;

    return -1;
}

int get_width(int instruction) {
    return (instruction >> 12) & 0x7;
}

int get_destination(int instruction) {
    return (instruction >> 7) & 0x1F;
}

int get_load_address(int instruction) {
    return (instruction >> 15) & 0x1F;
}

int get_load_offset(int instruction) {
    return (instruction >> 20) & 0xFFF;
}

int get_store_offset(int instruction) {
    int low = (instruction >> 7) & 0x1F;
    int high = (instruction >> 25) & 0x7F;

    return (high << 5) | low;
}

int get_store_source(int instruction) {
    return (instruction >> 20) & 0x1F;
}

int get_store_address(int instruction) {
    return (instruction >> 15) & 0x1F;
}

int get_math_function(int instruction) {
    return (instruction >> 12) & 0x7;
}

int get_math_operand_a(int instruction) {
    return (instruction >> 15) & 0x1F;
}

int get_math_operand_b(int instruction) {
    return (instruction >> 20) & 0x1F;
}

int get_constant_value(int instruction) {
    return (instruction >> 12) & 0xFFFFF;
}
``