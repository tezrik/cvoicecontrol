/***************************************************************************
                          queue.h  -  simple thread safe queue
                             -------------------
    begin                : Sat Feb 12 2000
    copyright            : (C) 2000 by Daniel Kiecza
    email                : daniel@kiecza.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef CVC_QUEUE_H
#define CVC_QUEUE_H

#include "semaphore.h"

/*****
  states a queue item can have
  *****/
enum QStatus {Q_invalid, Q_start, Q_data, Q_end, Q_abort, Q_exit};

/*****
  one item of the queue consists of
  a chunk of data, a status flag and
  a pointer to the next queue item
  *****/
struct _QueueItem
{
    void              *data;
    struct _QueueItem *next;
    enum QStatus       status;
};
typedef struct _QueueItem QueueItem;

/*****
  a queue knows the 'number_of_elements' it contains.
  It has a pointer to the 'head' item and the 'tail' item
  type indicates the type of data stored in the queue
  (needed for proper memory allocation etc.)
  *****/
typedef struct
{
    int number_of_elements;
    QueueItem *head;
    QueueItem *tail;
    enum {T_invalid, T_char, T_float} type;

    Semaphore semaphore;     /***** needed to block reader thread if queue is empty */
    pthread_mutex_t access;  /***** ensure thread-safe access to queue */
} Queue;

void initQueue(Queue *queue, char *type);
void resetQueue(Queue *queue);
void enqueue(Queue *queue, void *data, int size, int _status);
void *dequeue(Queue *queue, enum QStatus *status);
int numberOfElements(Queue *queue);

#endif //CVC_QUEUE_H//

