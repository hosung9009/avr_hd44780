#include "lcd_conf.h"
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
		lcd_set_ddram_address(61);
		lcd_set_cursor(1);
		_delay_ms(500);
		for (uint8_t i = 0; i < sizeof(msg)-1; i++) {
			_delay_ms(150);
			lcd_putchar(msg[i]);
		}
		_delay_ms(500);
		lcd_set_cursor(0);
		lcd_clear();
		_delay_ms(500);
	}
}
