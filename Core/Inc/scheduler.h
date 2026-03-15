#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "stdint.h"

#define MAX_TASKS 10

typedef void (*task_func_t)(void);

typedef struct
{
    task_func_t task;
    uint32_t period;
    uint32_t next_run;
    uint8_t active;
} task_t;

void scheduler_init(void);
int scheduler_add(task_func_t task, uint32_t period_ms);
void scheduler_run(void);

#endif