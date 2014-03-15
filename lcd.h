#ifndef LCD_H
#define LCD_H

/*
 * TODO:
 * Check java impl. for additional notes.
 * Add serial (4-pin) mode.
 */

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
void lcd_clear_display(void);

/* Returns the cursor to position zero. */
void lcd_return_home(void);

/* Sets the cursor position. (See layout above.) */
void lcd_set_ddram_address(uint8_t add);

/* Prints a string. */
void lcd_puts(const char *s);

void lcd_try(void);

#endif
