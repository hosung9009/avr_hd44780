#include "lcd_conf.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"


int main(void)
{
	lcd_try();
	for(;;) ;
}
