int generate_load_instruction(int width, int destination, int address, int offset) {
    int instruction = 0;

    instruction |= (offset & 0xFFF) << 20;
    instruction |= (address & 0x1F) << 15;
    instruction |= (width & 0x7) << 12;
    instruction |= (destination & 0x1F) << 7;
    instruction |= 0x03;

    return instruction;
}

int generate_store_instruction(int width, int address, int source, int offset) {
    int instruction = 0;

    instruction |= ((offset >> 5) & 0x7F) << 25;
    instruction |= (source & 0x1F) << 20;
    instruction |= (address & 0x1F) << 15;
    instruction |= (width & 0x7) << 12;
    instruction |= (offset & 0x1F) << 7;
    instruction |= 0x23;

    return instruction;
}

int generate_math_instruction(int function, int a, int b, int destination) {
    int instruction = 0;

    instruction |= (b & 0x1F) << 20;
    instruction |= (a & 0x1F) << 15;
    instruction |= (function & 0x7) << 12;
    instruction |= (destination & 0x1F) << 7;
    instruction |= 0x33;

    return instruction;
}

int generate_constant_instruction(int value, int destination) {
    int instruction = 0;

    instruction |= (value & 0xFFFFF) << 12;
    instruction |= (destination & 0x1F) << 7;
    instruction |= 0x37;

    return instruction;
}