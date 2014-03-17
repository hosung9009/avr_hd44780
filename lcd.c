/*
 * For LCD with hd44780 controller.
 *
 * by tommyo 20130119
 */

/*
 * TODO:
 *
 * Timings are preliminary.
 */

#include "lcd_conf.h"
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"


#define LCD_PUT_DELAY			(1)			/* ms, 255 us did not work well. */


static void lcd_put(uint8_t d)
{
#if defined(LCD_DATA_PAR)
	LCD_DATA_PORT = d;
#elif defined(LCD_DATA_SER)
	uint8_t i;

	for (i = 0; i < 8; i++) {
		uint8_t tmp;

		tmp = 0x01 & (d >> i);
		if (tmp)
			LCD_DATA_SREG_DS_PORT |= (1 << LCD_DATA_SREG_DS_PIN);
		else
			LCD_DATA_SREG_DS_PORT &= ~(1 << LCD_DATA_SREG_DS_PIN);

		/*
		 * Worst case scenario (at 4.5V) gives an f_max for the
		 * 74HC164 at 20MHz. This means that no delay is neccessary
		 * even at maximum frequency.
		 */
		LCD_DATA_SREG_CP_PORT |= (1 << LCD_DATA_SREG_CP_PIN);
		LCD_DATA_SREG_CP_PORT &= ~(1 << LCD_DATA_SREG_CP_PIN);
	}
#endif

	LCD_EN_PORT |= (1 << LCD_EN_PIN);
	_delay_us(1);				/* 450 ns */
	LCD_EN_PORT &= ~(1 << LCD_EN_PIN);
	_delay_us(37);				/* 37 us */
}

void lcd_putdata(uint8_t d)
{
	LCD_RS_PORT &= ~(1 << LCD_RS_PIN);
	lcd_put(d);
}

void lcd_putchar(char c)
{
	LCD_RS_PORT |= (1 << LCD_RS_PIN);
	lcd_put(c);
}

void lcd_init(void)
{
	unsigned char cmds[] = {0x0C, 0x38, 0x06, 0x80};

	_delay_ms(100);
#if defined(LCD_DATA_PAR)
	LCD_DATA_DDR    |= 0xFF;
#elif defined(LCD_DATA_SER)
	LCD_DATA_SREG_CP_DDR |= (1 << LCD_DATA_SREG_CP_PIN);
	LCD_DATA_SREG_DS_DDR |= (1 << LCD_DATA_SREG_DS_PIN);
	LCD_DATA_SREG_CP_PORT &= ~(1 << LCD_DATA_SREG_CP_PIN);
	LCD_DATA_SREG_DS_PORT &= ~(1 << LCD_DATA_SREG_DS_PIN);
#endif
	LCD_EN_DDR |= (1 << LCD_EN_PIN);
	LCD_RS_DDR |= (1 << LCD_RS_PIN);
	LCD_EN_PORT &= ~(1 << LCD_EN_PIN);
	LCD_RS_PORT &= ~(1 << LCD_RS_PIN);
	for (int i = 0; i < sizeof(cmds); i++)
		lcd_putdata(cmds[i]);
	lcd_clear_display();
}

void lcd_clear_display(void)
{
	lcd_putdata(1);
}

void lcd_return_home(void)
{
	lcd_putdata(1 << 1);
	_delay_us(1520);
}

#if !LCD_BARE_MIN

void lcd_entry_mode_set(int id, int s)
{
	lcd_putdata((1 << 2) | (id << 1) | (s << 0));
	_delay_us(37);
}

void lcd_display_on_off_control(int d, int c, int b)
{
	lcd_putdata((1 << 3) | (d << 2) | (c << 1) | (b << 0));
	_delay_us(37);
}

void lcd_cursor_or_display_shift(int sc, int rl)
{
	lcd_putdata((1 << 4) | (sc << 3) | (rl << 2));
	_delay_us(37);
}

void lcd_function_set(int dl, int n, int f)
{
	lcd_putdata((1 << 5) | (dl << 4) | (n << 3) | (f << 2));
	_delay_us(37);
}

void lcd_set_cgram_address(unsigned char add)
{
	lcd_putdata((1 << 6) | (0x3F & add));
	_delay_us(37);
}

void lcd_puts(const char *s)
{
	while (*s != '\0') {
		if (*s == '\n')
			lcd_set_ddram_address(61);
		else
			lcd_putchar(*s);
		s++;
	}
}

#endif

void lcd_set_ddram_address(uint8_t add)
{
	lcd_putdata((1 << 7) | (0x7F & add));
	_delay_us(37);
}

void lcd_try(void)
{
	_delay_ms(100);
	lcd_init();
	for (;;) {
		lcd_set_ddram_address(0);
		for (int i = 0; i < 16; i++)
			lcd_putchar('a' + i);
		lcd_set_ddram_address(61);
		_delay_ms(500);
		for (int i = 0; i < 16; i++)
			lcd_putchar('A' + i);
		_delay_ms(500);
		lcd_clear_display();
		_delay_ms(500);
	}
}
