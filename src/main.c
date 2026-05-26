#include <MKL25Z4.h>


int main(void)
{
    // Ativar clock da porta B
    SIM->SCGC5 |= (1 << 10);

    // Fazer pin config
    PORTB->PCR[0] = (1 << 8);

    // Ativar clock para ADC
    SIM->SCGC6 |= (1 << 27);

    // Configurar trigger do ADC pra software trigger
    ADC0->SC2 &= ~(1 << 6); 

    // Selecionar clock para bus
    ADC0->CFG1 &= ~(0b11);

    // Definir modo em 12 bits
    ADC0->CFG1 = (ADC0->CFG1 & ~0b11) | 0b01;

    // Selecionar canal de entrada

    // Loop infinito
    for (;;)
    {



    }

    return 0;
}