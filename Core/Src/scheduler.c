#include "scheduler.h"
#include "main.h"

static task_t tasks[MAX_TASKS];

void scheduler_init(void)
{
    for (int i = 0; i < MAX_TASKS; i++)
        tasks[i].active = 0;
}

int scheduler_add(task_func_t task, uint32_t period_ms)
{
    for (int i = 0; i < MAX_TASKS; i++)
    {
        if (!tasks[i].active)
        {
            tasks[i].task = task;
            tasks[i].period = period_ms;
            tasks[i].next_run = HAL_GetTick() + period_ms;
            tasks[i].active = 1;
            return i;
        }
    }
    return -1; // немає місця
}

void scheduler_run(void)
{
    uint32_t now = HAL_GetTick();

    for (int i = 0; i < MAX_TASKS; i++)
    {
        if (tasks[i].active &&
            (int32_t)(now - tasks[i].next_run) >= 0)
        {
            tasks[i].task();
            tasks[i].next_run += tasks[i].period;
        }
    }
}

/*how to use
#include "scheduler.h"

void led_task(void)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

void uart_task(void)
{
    // перевірка прийому, відправка і т.д.
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    scheduler_init();

    scheduler_add(led_task, 500);   // кожні 500 мс
    scheduler_add(uart_task, 10);   // кожні 10 мс

    while (1)
    {
        scheduler_run();
    }
}
*/