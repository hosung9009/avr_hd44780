#ifndef LCD_H
#define LCD_H

#include "lcd_conf.h"
#include <inttypes.h>


/*
 * DDRAM address layout (2x16):
 *
 * |  0 |  1 |  2 | ... |  60 |
 * | 61 | 62 | 63 | ... | 121(?) |
 *
 */

/* Used to init the hd44780 controller. */
void lcd_init(void);

/* Puts a char and advances the cursor. */
void lcd_putchar(char c);

/* Clears the display and puts the cursor at position zero. */
void lcd_clear(void);

/* Sets the cursor position. (See layout above.) */
void lcd_set_ddram_address(uint8_t add);

#if !LCD_BARE_MIN

/* Prints a string. Handles newline.*/
void lcd_puts(const char *s);

/* Returns the cursor to position zero. */
void lcd_home(void);

/* Lower level functions */
void lcd_entry_mode_set(uint8_t id, uint8_t s);
void lcd_on_off_control(uint8_t d, uint8_t c, uint8_t b);
void lcd_cursor_or_display_shift(uint8_t sc, uint8_t rl);
void lcd_function_set(uint8_t dl, uint8_t n, uint8_t f);
void lcd_set_cgram_address(unsigned char add);

/* Simpler interfaces for some of the functions above. */
void lcd_set_cursor(uint8_t on);
void lcd_set_position(uint8_t line, uint8_t col);

/* Prints a short message on the display. */
void lcd_try(void);

#endif

#endif
