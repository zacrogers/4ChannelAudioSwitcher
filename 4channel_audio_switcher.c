/*
 * Attiny85_audio_switcher.c
 * 
 * Version not using any arduino elements
 *
 * Created: 15-Jan-20 11:31:53 AM
 * Author : Zac
 */ 

#define F_CPU 1000000

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define NUM_CHANNELS 4

/* Function prototypes */
void gpio_init(void);
void poll_buttons(void);
void set_mux(void);

/* Pin defines*/
const uint8_t MUX_PIN[2] = {PINB3, PINB4};
const uint8_t BTN_PIN[2] = {PINB0, PINB2};
	
/* State variables */
uint8_t current_channel  = 0x00;
uint8_t previous_channel = 0x00;

int main(void)
{
	gpio_init();
	
    while (1) 
    {
		poll_buttons();
		
		if(previous_channel != current_channel)
		{
			set_mux();
		}
    }
}

void gpio_init(void)
{
	DDRB |= (1U << MUX_PIN[0]) | (1U << MUX_PIN[1]);  /* Set mux pins as output */
	DDRB &= ~(1U << BTN_PIN[0]) | (1U << BTN_PIN[1]); /* Set button pins as input */
}

void poll_buttons(void)
{
	/* Increment channel */
	if(PINB & (1U << BTN_PIN[0]))
	{
		previous_channel = current_channel;

		if(current_channel < (NUM_CHANNELS - 1))
		{
			current_channel++;
		}
		_delay_ms(250); /* debounce */
	}
	
	/* Decrement channel */
	if(PINB & (1U << BTN_PIN[1]))
	{
		previous_channel = current_channel;

        if(current_channel > 0)
        {
	        current_channel--;
        }
		_delay_ms(250); /* debounce */
	}
}

/* Set mux pins corresponding to bits of current channel variable */
void set_mux(void)
{
	for(uint8_t pin = 0; pin < 2; ++pin)
	{
		if(current_channel & (1U << pin))
		{
			PORTB |= (1U << MUX_PIN[pin]);  /* Set pin */
		}
		else
		{
			PORTB &= ~(1U << MUX_PIN[pin]);  /* Clear pin*/
		}
	}
}
