#include <stdio.h>

#include "Core/Queue/QueueArray.h"
#include "Core/Queue/QueueLinked.h"

int main()
{
    QueueArray* q = aqCreate(10);

    aqEnqueue(q, 10);
    aqEnqueue(q, 20);
    aqEnqueue(q, 30);
    aqEnqueue(q, 40);
    aqEnqueue(q, 50);

    aqDequeue(q);
    aqDequeue(q);

    aqPrint(q);

    printf("front: %d\n", *aqFront(q));

    aqDequeue(q);

    return 0;
}