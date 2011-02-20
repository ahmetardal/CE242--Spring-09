#ifndef QUEUE_H_
#define QUEUE_H_

#include "List.h"

struct Queue
{
    List *pList;
};

Queue *QueueCreate();

Node  *QueueEnqueue(Queue *pQueue, const void *pData);

void  *QueueDequeue(Queue *pQueue);

void  *QueuePeek(Queue *pQueue);

int    QueueGetSize(Queue *pQueue);

bool   QueueIsEmpty(Queue *pQueue);

void   QueueDestroy(Queue *pQueue);

#endif  /* QUEUE_H_ */
