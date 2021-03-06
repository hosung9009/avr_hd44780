/*
 * For LCD with hd44780 controller.
 *
 * by tommyo 20130119
 */

#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>


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
	_delay_us(0.45);
	LCD_EN_PORT &= ~(1 << LCD_EN_PIN);
	_delay_us(37.0);
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

#if LCD_BARE_MIN
	/* Just output the commands, some functions are unavailable. */
	_delay_ms(40.0);
	lcd_putdata(0x38);			/* fs */
	_delay_ms(4.1);
	lcd_putdata(0x38);			/* fs */
	_delay_us(100.0);
	lcd_putdata(0x38);			/* fs */
	lcd_putdata(0x38);			/* fs */
	lcd_putdata(0x08);			/* ooc */
	lcd_clear();
	lcd_putdata(0x06);			/* ems */
	lcd_putdata(0x0C);			/* ooc */
	lcd_putdata(0x80);			/* ddram */
#else
	/* Do it properly. */
	_delay_ms(40.0);
	lcd_function_set(1, 1, 0);
	_delay_ms(4.1);
	lcd_function_set(1, 1, 0);
	_delay_us(100.0);
	lcd_function_set(1, 1, 0);
	lcd_function_set(1, 1, 0);
	lcd_on_off_control(0, 0, 0);
	lcd_clear();
	lcd_entry_mode_set(1, 0);
	lcd_on_off_control(1, 0, 0);
	lcd_set_ddram_address(0);
#endif
	_delay_ms(10.0);
}

void lcd_clear(void)
{
	lcd_putdata(1);
}

void lcd_set_ddram_address(uint8_t add)
{
	lcd_putdata((1 << 7) | (0x7F & add));
	_delay_us(37);
}

#if !LCD_BARE_MIN

void lcd_on_off_control(uint8_t disp, uint8_t cursor, uint8_t blink)
{
	lcd_putdata((1 << 3) | (disp << 2) | (cursor << 1) | (blink << 0));
	_delay_us(37);
}

void lcd_set_cursor(uint8_t on)
{
	lcd_on_off_control(1, on, 0);
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

void lcd_home(void)
{
	lcd_putdata(2);
	_delay_ms(1.52);
}

void lcd_entry_mode_set(uint8_t inc_one, uint8_t shift)
{
	lcd_putdata((1 << 2) | (inc_one << 1) | (shift << 0));
	_delay_us(37);
}

void lcd_cursor_or_display_shift(uint8_t sc, uint8_t rl)
{
	lcd_putdata((1 << 4) | (sc << 3) | (rl << 2));
	_delay_us(37);
}

void lcd_function_set(uint8_t full_itf, uint8_t multi_line, uint8_t f)
{
	lcd_putdata((1 << 5) | (full_itf << 4) | (multi_line << 3) | (f << 2));
	_delay_us(37);
}

void lcd_set_cgram_address(uint8_t add)
{
	lcd_putdata((1 << 6) | (0x3F & add));
	_delay_us(37);
}

void lcd_set_position(uint8_t line, uint8_t col)
{
	lcd_set_ddram_address(line * 0x40 + col);
}

#endif
