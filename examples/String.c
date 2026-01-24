#include <stdio.h>

#include "Core/StringLib.h"

int main() {
    char string[] = "testing";

    reverseString(string);

    printf("%s\n", string);

    return 0;
}