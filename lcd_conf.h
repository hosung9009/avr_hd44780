#ifndef LCD_CONF_H
#define LCD_CONF_H

#if 0							/* Defined in Makefile. */
#define LCD_DATA_PAR			/* One of LCD_DATA_[PAR, SER]. */
#endif

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

#elif defined(LCD_DATA_SER)		/* Example settings, data via SR. */

#define LCD_DATA_SREG_CP_DDR	(DDRB)
#define LCD_DATA_SREG_CP_PORT	(PORTB)
#define LCD_DATA_SREG_CP_PIN	(3)

#define LCD_DATA_SREG_DS_DDR	(DDRB)
#define LCD_DATA_SREG_DS_PORT	(PORTB)
#define LCD_DATA_SREG_DS_PIN	(2)

#define LCD_EN_DDR				(DDRB)
#define LCD_EN_PORT				(PORTB)
#define LCD_EN_PIN				(1)

#define LCD_RS_DDR				(DDRB)
#define LCD_RS_PORT				(PORTB)
#define LCD_RS_PIN				(0)

#else
	#error "LCD mode not specified"
#endif


#endif
