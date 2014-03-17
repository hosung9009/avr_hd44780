#ifndef LCD_CONF_H
#define LCD_CONF_H

#define F_CPU 8000000L
#define LCD_DATA_SER			/* One of LCD_DATA_[PAR, SER]. */

#define LCD_BARE_MIN			(0) /* Turn on for smaller binary. */

#define LCD_COLS				(16) /* Number of cols on display. */
#define LCD_ROWS				(2)	 /* Number of rows on display. */


#if defined(LCD_DATA_PAR)		/* Example settings, parallel data. */

#define LCD_DATA_PORT			(PORTB)
#define LCD_DATA_DDR			(DDRB)
#define LCD_EN_PORT				(PORTD)
#define LCD_EN_DDR				(DDRD)
#define LCD_EN_PIN				(6)
#define LCD_RS_PORT				(PORTD)
#define LCD_RS_DDR				(DDRD)
#define LCD_RS_PIN				(4)

#elif defined(LCD_DATA_SER)		/* Example setting, data via SR. */

#define LCD_DATA_SREG_CP_DDR	(DDRC)
#define LCD_DATA_SREG_CP_PORT	(PORTC)
#define LCD_DATA_SREG_CP_PIN	(3)

#define LCD_DATA_SREG_DS_DDR	(DDRC)
#define LCD_DATA_SREG_DS_PORT	(PORTC)
#define LCD_DATA_SREG_DS_PIN	(2)

#define LCD_EN_DDR				(DDRC)
#define LCD_EN_PORT				(PORTC)
#define LCD_EN_PIN				(1)

#define LCD_RS_DDR				(DDRC)
#define LCD_RS_PORT				(PORTC)
#define LCD_RS_PIN				(0)

#else
	#error "LCD mode not specified"
#endif


#endif
