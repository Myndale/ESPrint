#include	"gcode_parse.h"
#include	"config.h"

#include "petit_fatfs.h"

#ifdef SD_PRINTING

uint8_t rx()
{
	/*
  SPDR = 0xFF;
  loop_until_bit_is_set(SPSR, SPIF);
  return SPDR;
  */
	return 0;
}

void tx(uint8_t d)
{
	/*
  SPDR = d;
  loop_until_bit_is_set(SPSR, SPIF);
  */
}

void spi_init()
{
	/*
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
  
  SPCR = _BV(MSTR) | _BV(SPE);      // Master mode, SPI enable, clock speed MCU_XTAL/4
  */
}

void list_sd_card()
{
	serial_writestr_P(PSTR("list_sd_card!"));
}

void init_sd_card()
{
	spi_init();
	//pFFS.begin(4, rx, tx);
}

void select_sd_file()
{
	serial_writestr_P(PSTR("select_sd_file!"));
}

void start_sd_print()
{
	serial_writestr_P(PSTR("start_sd_print!"));
}

void pause_sd_print()
{
	serial_writestr_P(PSTR("pause_sd_print!"));
}

void report_sd_status()
{
	serial_writestr_P(PSTR("report_sd_status!"));
}

void select_and_start_sd_print()
{
	serial_writestr_P(PSTR("select_and_start_sd_print!"));
}


#endif SD_PRINTING