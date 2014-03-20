#include "lcd_conf.h"
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"


int main(void)
{
	lcd_init();
	for (;;) {
		const char msg[] = "by tommyo";
		lcd_set_ddram_address(0);
		lcd_puts("avr_hd44780");
		_delay_ms(500);
		lcd_set_position(1, 6);
		lcd_on_off_control(1, 1, 0);
		_delay_ms(500);
		for (uint8_t i = 0; i < sizeof(msg)-1; i++) {
			_delay_ms(150);
			lcd_putchar(msg[i]);
		}
		_delay_ms(300);
		lcd_on_off_control(1, 1, 1);
		_delay_ms(3000);
		lcd_on_off_control(1, 0, 0);
		for (uint8_t i = 0; i < 2; i++) {
			for (uint8_t  k = 0; k < 16; k++) {
				for (uint8_t j = 0; j < 2; j++) {
					lcd_set_position(j, k);
					lcd_putchar((i % 2) ? ' ' : 0xFF);
				}
				_delay_ms(25);
			}
		}
		lcd_clear();
		_delay_ms(500);
	}
}
