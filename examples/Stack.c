#include <stdio.h>

#include "Core/Stack/StackArray.h"
#include "Core/Stack/StackLinked.h"

int main()
{
    StackArray* st = staCreate(20);

    staPush(st, 10);
    staPush(st, 20);
    staPush(st, 30);
    staPush(st, 40);
    staPush(st, 50);

    printf("%d\n", *staTop(st));

    staDisplay(st);

    return 0;
}
