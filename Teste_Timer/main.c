#include <stdio.h>
#include <stdint.h>

#define F_CPU       16000000ULL
#define INC_CONT    0.25
#define CS10        0x01
#define CS11        0x02
#define CS12        0x04
#define TOIE1       0x01
#define CS20        0x01
#define CS21        0x02
#define CS22        0x04
#define TOIE2       0x01

uint16_t TCCR1B, TCNT1, TIMSK1, TCCR2B, TIMSK2, TCNT2;

static const uint16_t preescaleValues[5] =
{
    1,
    8,
    64,
    256,
    1024
};

static const uint16_t timer_2_preescaleValues[7] =
{
    1,
    8,
    32,
    64,
    128,
    256,
    1024
};


void timer_1_init(uint16_t tempo_ms)
{
    //reg = (uint16_t) ((F_CPU * ms / 1000) - 1) * 2;
    //reg = 65535 - reg;
    //reg = 0;
    float t = 0.0;
    float ms = (float) tempo_ms / 1000;
    uint8_t prescale = 0;
    uint16_t reg = 0;
    //    uint16_t inc = 0;
    //    uint16_t resolucao = 10000;

    //    inc = (uint16_t) ((float) 360.0 / INC_CONT * resolucao);
    //    uint32_t aux = inc;

    while (t < ms)
    {
        t = (float) 65535 * preescaleValues[prescale] / F_CPU;

        if (t < ms)
        {
            ++prescale;
            t = 0;

            if (prescale > 4)
            {
                prescale = 4;
                break;
            }
        }
    }

    TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12));

    switch(prescale)
    {
    case 0:
        TCCR1B |= (1 << CS10);
        break;
    case 1:
        TCCR1B |= (1 << CS11);
        break;
    case 2:
        TCCR1B |= ((1 << CS11) | (1 << CS10));
        break;
    case 3:
        TCCR1B |= (1 << CS12);
        break;
    case 4:
        TCCR1B |= ((1 << CS12) | (1 << CS10));
        break;
    }


    //    reg = (uint16_t) (((float) ms / t * 65535) - 1);
    float f1 = ms / t;
    float f2 = f1 * 65535;
    float f3 = f2 - 1;

    if (f3 < 65535)
        reg = (uint16_t) f3;
    else
        reg = 65535;

    TCNT1 = reg;
    TIMSK1 |= (1 << TOIE1);
}

void timer_2_init(uint16_t tempo_ms, uint32_t f_cpu)
{
    float ms = (float) tempo_ms / 1000;
    float t = 0.0;
    uint8_t prescale = 0;
    uint16_t reg_2 = 0;

    while (t < ms)
    {
        t = (float) 255 * timer_2_preescaleValues[prescale] / f_cpu;

        if (t < ms)
        {
            ++prescale;
            t = 0;

            if (prescale > 6)
            {
                prescale = 6;
                break;
            }
        }
    }

    TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));

    switch(prescale)
    {
    case 0:
        TCCR2B |= (1 << CS20);
        break;
    case 1:
        TCCR2B |= (1 << CS21);
        break;
    case 2:
        TCCR2B |= ((1 << CS21) | (1 << CS20));
        break;
    case 3:
        TCCR2B |= (1 << CS22);
        break;
    case 4:
        TCCR2B |= ((1 << CS22) | (1 << CS20));
        break;
    case 5:
        TCCR2B |= ((1 << CS22) | (1 << CS21));
        break;
    case 6:
        TCCR2B |= ((1 << CS22) | (1 << CS21) | (1 << CS20));
        break;
    }


    reg_2 = (uint16_t) (ms / t * 255);

    if (reg_2 < 255)
    {
        reg_2 = 255 - reg_2;
    }
    else
    {
        reg_2 = 0;
    }

    TCNT2 = reg_2;
    TIMSK2 |= (1 << TOIE2);
}

int main()
{
    timer_2_init(200, 16000000);
    return 0;
}
