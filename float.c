#include <stdio.h>
#include <stdlib.h>

union FloatBits {
    float f;
    unsigned int u;
};

unsigned int binaryToInt(char *str) {
    unsigned int result = 0;

    for (int i = 0; i < 32; i++) {
        result <<= 1;

        if (str[i] == '1') {
            result |= 1;
        }
    }

    return result;
}

void printBinary(unsigned int bits) {
    printf("Binary: ");

    for (int i = 31; i >= 0; i--) {
        printf("%u", (bits >> i) & 1);
    }

    printf("\n");
}

float getMantissa(unsigned int fraction, unsigned int exponentBits) {
    float mantissa;

    if (exponentBits == 0) {
        mantissa = 0.0f;
    }
    else {
        mantissa = 1.0f;
    }

    float value = 0.5f;

    for (int i = 22; i >= 0; i--) {
        if ((fraction >> i) & 1) {
            mantissa += value;
        }

        value /= 2.0f;
    }

    return mantissa;
}

void printInfo(union FloatBits num) {
    unsigned int bits = num.u;

    int sign = (bits >> 31) & 1;
    unsigned int exponentBits = (bits >> 23) & 0xFF;
    unsigned int fraction = bits & 0x7FFFFF;

    int exponent;

    if (exponentBits == 0) {
        exponent = -126;
    }
    else if (exponentBits == 255) {
        exponent = 128;
    }
    else {
        exponent = (int)exponentBits - 127;
    }

    float mantissa = getMantissa(fraction, exponentBits);

    printBinary(bits);

    printf("Sign: %d\n", sign);
    printf("Exponent: %d\n", exponent);
    printf("Mantissa: %.7g\n", mantissa);
    printf("Value: %.7g\n", num.f);
}

int main(int argc, char *argv[]) {
    union FloatBits num;

    if (argc != 3) {
        return 1;
    }

    if (argv[1][0] == '-' &&
        argv[1][1] == 'f' &&
        argv[1][2] == '\0') {

        num.f = strtof(argv[2], NULL);
        printInfo(num);
    }
    else if (argv[1][0] == '-' &&
             argv[1][1] == 'b' &&
             argv[1][2] == '\0') {

        num.u = binaryToInt(argv[2]);
        printInfo(num);
    }

    return 0;
}