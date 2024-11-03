#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "nrf_gpio.h"


#define FIRST_LED_PIN      NRF_GPIO_PIN_MAP(0, 6)
#define SECOND_RED_LED_PIN NRF_GPIO_PIN_MAP(0, 8)
#define SECOND_GREEN_LED_PIN NRF_GPIO_PIN_MAP(1, 9)
#define SECOND_BLUE_LED_PIN NRF_GPIO_PIN_MAP(0, 12)
#define BUTTON_PIN         NRF_GPIO_PIN_MAP(1, 6)

#define LED_DELAY_MS 500

uint8_t led_sequence[] = {FIRST_LED_PIN, SECOND_RED_LED_PIN, SECOND_GREEN_LED_PIN, SECOND_BLUE_LED_PIN};
uint8_t device_id[] = {6, 5, 7, 9}; 

void gpio_init(void)
{
    nrf_gpio_cfg_output(FIRST_LED_PIN);
    nrf_gpio_cfg_output(SECOND_RED_LED_PIN);
    nrf_gpio_cfg_output(SECOND_GREEN_LED_PIN);
    nrf_gpio_cfg_output(SECOND_BLUE_LED_PIN);
    nrf_gpio_cfg_input(BUTTON_PIN, NRF_GPIO_PIN_PULLUP);
}

void leds_off(void)
{
    nrf_gpio_pin_write(FIRST_LED_PIN, 1);
    nrf_gpio_pin_write(SECOND_RED_LED_PIN, 1);
    nrf_gpio_pin_write(SECOND_GREEN_LED_PIN, 1);
    nrf_gpio_pin_write(SECOND_BLUE_LED_PIN, 1);
}

int main(void)
{
    gpio_init();
    leds_off(); 

    int current_led = 0; 
    int blink_index = 0; 
    bool led_on = false; 

    while (true)
    {
    
        if (!nrf_gpio_pin_read(BUTTON_PIN)) 
        {
        
            if (blink_index < device_id[current_led])
            {
                nrf_gpio_pin_write(led_sequence[current_led], 0); 
                nrf_delay_ms(LED_DELAY_MS);
                leds_off(); 
                nrf_delay_ms(LED_DELAY_MS);

                blink_index++; 
            }
            else {

                blink_index = 0; 
                current_led = (current_led + 1) % (sizeof(device_id) / sizeof(device_id[0])); 
            }

            led_on = true; 
        }
        else 
        {
            if (led_on) 
            {
                nrf_gpio_pin_write(led_sequence[current_led], 0); 
            }
            else 
            {
                leds_off();
            }
        }

        nrf_delay_ms(LED_DELAY_MS); 
    }
}
