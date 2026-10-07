int get_opcode(int instruction) {
    return (instruction & 0x7F) >> 2;
}

/*  Returns an integer representing the type of instruction
 *    0 - Load     (opcode == 0x0)
 *    1 - Store    (opcode == 0x8)
 *    2 - Math     (opcode == 0xC)
 *    3 - Constant (opcode == 0xD)
 */
int get_instruction_type(int instruction) {
    switch (get_opcode(instruction)) {
        case 0x0:
            return 0;
        case 0x8:
            return 1;
        case 0xC:
            return 2;
        case 0xD:
            return 3;
        default:
            return -1;
    }
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
    int upper = (instruction >> 25) & 0x7F;
    int lower = (instruction >> 7) & 0x1F;

    return (upper << 5) | lower;
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