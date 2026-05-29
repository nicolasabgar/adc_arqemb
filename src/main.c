#include <MKL25Z4.h>


int main(void)
{

    //------------------------------------
    // Configuracoes do ADC
    //------------------------------------

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

    //------------------------------------
    // Configuracoes do GPIO
    //------------------------------------

    PORTD->PCR[1] |= (1 << 8); // Configurar MUX do GPIO

    FGPIOD->PDDR |= (1 << 1); // Definir direcao de saida

    PORTB->PCR[19] |= (1 << 8); // Configurar MUX do GPIO

    FGPIOB->PDDR |= (1 << 19); // Definir direcao de saida
    

    // Loop infinito
    for (;;)
    {

        // Selecionar canal de entrada (pino utilizado PTB0 -> ADC0_SE8 -> Canal: AD8)
        ADC0->SC1[0] = (ADC0->SC1[0] & ~0b11111) | 0b01000;

        // Esperar ate fim de conversao
        while ( !(ADC0->SC1[0] & 0b10000000) ) {}

        // Salvar resultado em 12 bits
        uint16_t result = ADC0->R[0] & 0x0FFF;

        if (result > 512) {
            GPIOD->PCOR |= (1 << 1);
            GPIOB->PSOR |= (1 << 19);
        } else {
            GPIOD->PSOR |= (1 << 1);
            GPIOB->PCOR |= (1 << 19);
        }

        printk("Valor: %d \n", result);

    }

    return 0;
}