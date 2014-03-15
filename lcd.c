/*
 * For LCD with hd44780 controller.
 *
 * by tommyo 20130119
 */

/*
 * TODO:
 *
 * Header.
 * Timings are preliminary (although from data sheet).
 * Few-pin-mode using shift register.
 */

#include "settings.h"
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

#define LCD_BARE_MIN (0)

#define LCD_COLS				(16)
#define LCD_ROWS				(2)
#define LCD_DATA_PORT			(PORTB)
#define LCD_DATA_DDR			(DDRB)
#define LCD_CLK_PORT			(PORTD)
#define LCD_CLK_DDR				(DDRD)
#define LCD_CLK_PIN				(6)
#define LCD_REG_SEL_PORT		(PORTD)
#define LCD_REG_SEL_DDR			(DDRD)
#define LCD_REG_SEL_PIN			(4)
#define LCD_PUT_DELAY			(1)			/* ms, 255 us did not work well. */

void lcd_putdata(uint8_t d)
{
	LCD_REG_SEL_PORT &= ~(1 << LCD_REG_SEL_PIN);
	LCD_DATA_PORT = d;
	LCD_CLK_PORT |= (1 << LCD_CLK_PIN);
	_delay_ms(LCD_PUT_DELAY);
	LCD_CLK_PORT &= ~(1 << LCD_CLK_PIN);
	_delay_ms(LCD_PUT_DELAY);
}

void lcd_putchar(char c)
{
	LCD_REG_SEL_PORT |= (1 << LCD_REG_SEL_PIN);
	LCD_DATA_PORT = c;
	LCD_CLK_PORT |= (1 << LCD_CLK_PIN);
	_delay_ms(LCD_PUT_DELAY);
	LCD_CLK_PORT &= ~(1 << LCD_CLK_PIN);
	_delay_ms(LCD_PUT_DELAY);
}

void lcd_init(void)
{
	unsigned char cmds[] = {0x0C, 0x38, 0x06, 0x80};

	_delay_ms(100);
	LCD_DATA_DDR    |= 0xFF;
	LCD_REG_SEL_DDR |= (1 << LCD_REG_SEL_PIN);
	LCD_CLK_DDR     |= (1 << LCD_CLK_PIN);
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

void lcd_set_ddram_address(unsigned char add)
{
	lcd_putdata((1 << 7) | (0x7F & add));
	_delay_us(37);
}

void lcd_try(void)
{
	_delay_ms(100);
	lcd_init();
	for (;;) {
		/* lcd_set_ddram_address(0); */
		for (int i = 0; i < 16; i++)
			lcd_putchar('a' + i);
		lcd_set_ddram_address(61);
		for (int i = 0; i < 16; i++)
			lcd_putchar('A' + i);
		_delay_ms(1000);
		lcd_clear_display();
	}
}
