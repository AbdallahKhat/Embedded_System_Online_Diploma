/*
 * WDT.c
 *
 * Created: 6/30/2023 5:23:52 PM
 * Author : Abdallah Khater
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SET_BIT(REG,BIT)       (REG |= (1 << BIT))
#define RESET_BIT(REG,BIT)     (REG &= ~(1 << BIT))
#define TOGGLE_BIT(REG,BIT)    (REG ^= (1 << BIT))
#define READ_BIT(REG,BIT)      ((REG >> BIT) & 0x01)

#define LED_DDR                 DDRD
#define LED_PORT                PORTD
#define LED_PIN                 6

void WDT_OFF()
{
    // In the same operation, write a logic one to WDTOE and WDE.
    // A logic one must be written to WDE even though it is set to one before the disable operation starts.
    WDTCR |= ((1 << WDE) | (1 << WDTOE));

    // Within the next four clock cycles, write a logic 0 to WDE. This disables the Watchdog.
    WDTCR = 0x0; // Reset register to initial values
}

void WDT_ON()
{
    // When the WDE is written to logic one, the Watchdog Timer is enabled
    WDTCR |= (1 << WDE) | (1 << WDP1) | (1 << WDP2); // // Prescalers WDP1..2 are set , WDP0 is reset for typical timeout at (Vcc = 5.0v) = 1.0s
    RESET_BIT(WDTCR,WDP0);
}



int main(void)
{
    SET_BIT(LED_DDR, LED_PIN); //SET LED PIN as output
    _delay_ms(500);
    while (1) 
    {
        WDT_ON();
        TOGGLE_BIT(LED_PORT, LED_PIN); //Toggle LED PIN
        _delay_ms(2000);
        WDT_OFF();
    }
}

