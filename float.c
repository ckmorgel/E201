#include <stdio.h>
#include <stdlib.h>

union FloatBits {
    float f;
    unsigned int u;
};

void printBinary(unsigned int bits) {
    for (int i = 31; i >= 0; i--) {
        printf("%u", (bits >> i) & 1);
    }
    printf("\n");
}

float getMantissa(unsigned int fraction, unsigned int exponentBits) {
    float mantissa;

    if (exponentBits == 0) {
        mantissa = 0.0f;
    } else {
        mantissa = 1.0f;
    }

    for (int i = 22; i >= 0; i--) {
        if ((fraction >> i) & 1) {
            mantissa += 1.0f / (1u << (23 - i));
        }
    }

    return mantissa;
}

void printInfo(union FloatBits value) {
    unsigned int bits = value.u;

    int sign = (bits >> 31) & 1;
    unsigned int exponentBits = (bits >> 23) & 0xFF;
    unsigned int fraction = bits & 0x7FFFFF;

    int exponentValue;
    float mantissa;

    printBinary(bits);

    printf("Sign: %d\n", sign);

    if (exponentBits == 255) {
        printf("Exponent: 128\n");
    }
    else if (exponentBits == 0) {
        printf("Exponent: -126\n");
    }
    else {
        exponentValue = (int)exponentBits - 127;
        printf("Exponent: %d\n", exponentValue);
    }

    mantissa = getMantissa(fraction, exponentBits);

    printf("Mantissa: %.7g\n", mantissa);
    printf("Value: %.7g\n", value.f);
}

unsigned int binaryToInt(char *str) {
    unsigned int bits = 0;

    for (int i = 0; i < 32; i++) {
        bits <<= 1;

        if (str[i] == '1') {
            bits |= 1;
        }
    }

    return bits;
}

int main(int argc, char *argv[]) {
    union FloatBits value;

    if (argc != 3) {
        return 1;
    }

    if (argv[1][0] == '-' && argv[1][1] == 'f' && argv[1][2] == '\0') {
        value.f = strtof(argv[2], NULL);
        printInfo(value);
    }
    else if (argv[1][0] == '-' && argv[1][1] == 'b' && argv[1][2] == '\0') {
        value.u = binaryToInt(argv[2]);
        printInfo(value);
    }

    return 0;
}