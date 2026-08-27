#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int stack[10];
    int top = -1;
    int i;

    for (i = 1; i < argc; i++)
    {
        char *endptr;
        long value = strtol(argv[i], &endptr, 10);

        if (*endptr == '\0')
        {
            stack[++top] = (int)value;
        }
        else
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
    }

    printf("%d\n", stack[top]);

    return 0;
}