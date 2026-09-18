#include <stdio.h>
#include <string.h>

unsigned int binaryToDecimal(char *str)
{
    unsigned int value = 0;

    for (int i = 2; str[i] != '\0'; i++)
    {
        value = value * 2 + (str[i] - '0');
    }

    return value;
}

unsigned int hexToDecimal(char *str)
{
    unsigned int value = 0;
    unsigned int digit;

    for (int i = 2; str[i] != '\0'; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            digit = str[i] - '0';
        }
        else
        {
            digit = str[i] - 'a' + 10;
        }

        value = value * 16 + digit;
    }

    return value;
}

unsigned int decimalToDecimal(char *str)
{
    unsigned int value = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        value = value * 10 + (str[i] - '0');
    }

    return value;
}

unsigned int convertNumber(char *str)
{
    if (str[0] == '0' && str[1] == 'b')
    {
        return binaryToDecimal(str);
    }

    if (str[0] == '0' && str[1] == 'x')
    {
        return hexToDecimal(str);
    }

    return decimalToDecimal(str);
}

int main(int argc, char *argv[])
{
    int stack[10];
    int top = -1;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "add") == 0 ||
            strcmp(argv[i], "sub") == 0 ||
            strcmp(argv[i], "mult") == 0 ||
            strcmp(argv[i], "div") == 0)
        {
            int b = stack[top--];
            int a = stack[top--];
            int result;

            if (strcmp(argv[i], "add") == 0)
            {
                result = a + b;
            }
            else if (strcmp(argv[i], "sub") == 0)
            {
                result = a - b;
            }
            else if (strcmp(argv[i], "mult") == 0)
            {
                result = a * b;
            }
            else
            {
                result = a / b;
            }

            stack[++top] = result;
        }
        else
        {
            stack[++top] = (int)convertNumber(argv[i]);
        }
    }

    printf("%d\n", stack[top]);

    return 0;
}