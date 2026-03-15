// uint32_t millis(void);

typedef struct
{
    uint32_t start;
    uint32_t delay;
    uint8_t active;
} delay_t;

void delay_ms(uint32_t ms);

void delay_start(delay_t *d, uint32_t ms);

uint8_t delay_expired(delay_t *d);
