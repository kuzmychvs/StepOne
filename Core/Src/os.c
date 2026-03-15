#include <main.h>
#include <os.h>

void delay_ms(uint32_t ms)
{
    uint32_t start = HAL_GetTick();
    while (HAL_GetTick() - start < ms)
        ;
}

void delay_start(delay_t *d, uint32_t ms)
{
    d->start = HAL_GetTick();
    d->delay = ms;
    d->active = 1;
}

uint8_t delay_expired(delay_t *d)
{
    if (!d->active)
        return 0;

    if (HAL_GetTick() - d->start >= d->delay)
    {
        d->active = 0;
        return 1;
    }

    return 0;
}

/*how to use
delay_t led_delay;

int main(void)
{
    HAL_Init();

    delay_start(&led_delay, 1000);

    while (1)
    {
        if (delay_expired(&led_delay))
        {
            toggle_led();
            delay_start(&led_delay, 1000);
        }

        // інший код виконується тут
    }
}
*/
