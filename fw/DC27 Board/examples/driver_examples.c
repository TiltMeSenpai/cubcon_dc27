/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/**
 * Example of using RAND_0 to generate waveform.
 */
void RAND_0_example(void)
{
	uint32_t random_n[4];
	rand_sync_enable(&RAND_0);
	random_n[0] = rand_sync_read32(&RAND_0);
	random_n[1] = rand_sync_read32(&RAND_0);
	rand_sync_read_buf32(&RAND_0, &random_n[2], 2);
	if (random_n[0] == random_n[1]) {
		/* halt */
		while (1)
			;
	}
	if (random_n[2] == random_n[3]) {
		/* halt */
		while (1)
			;
	}
}

#ifndef NVMCTRL_ROW_SIZE
#define NVMCTRL_ROW_SIZE (NVMCTRL_PAGE_SIZE * NVMCTRL_ROW_PAGES)
#endif
static uint8_t flash_src_data[FLASH_PAGE_SIZE];
static uint8_t flash_chk_data[FLASH_PAGE_SIZE];

/**
 * Example of using FLASH_0 to read and write buffer.
 */
void FLASH_0_example(void)
{
	uint32_t i;

	/* Target address.
	 * Make sure the address is reasonable to your application.
	 * It might a address in NVM memory of FLASH, DATAFLASH, AUX FLASH.
	 */
	uint32_t target_addr = FLASH_ADDR + FLASH_SIZE - NVMCTRL_ROW_SIZE;

	/* Initialize source data */
	for (i = 0; i < FLASH_PAGE_SIZE; i++) {
		flash_src_data[i] = i;
	}

	/* Erase row in flash */
	FLASH_0_erase_row(target_addr);

	/* Write data to flash */
	FLASH_0_write_page(target_addr, flash_src_data, FLASH_PAGE_SIZE);

	/* Read data from flash */
	FLASH_0_read(target_addr, flash_chk_data, FLASH_PAGE_SIZE);

	/* Check data */
	for (i = 0; i < FLASH_PAGE_SIZE; i++) {
		if (flash_src_data[i] != flash_chk_data[i]) {
			while (1)
				; /* Error happen */
		}
	}
}

static struct timer_task TIMER_0_task1, TIMER_0_task2;

/**
 * Example of using TIMER_0.
 */
static void TIMER_0_task1_cb(const struct timer_task *const timer_task)
{
}

static void TIMER_0_task2_cb(const struct timer_task *const timer_task)
{
}

void TIMER_0_example(void)
{
	TIMER_0_task1.interval = 100;
	TIMER_0_task1.cb       = TIMER_0_task1_cb;
	TIMER_0_task1.mode     = TIMER_TASK_REPEAT;
	TIMER_0_task2.interval = 200;
	TIMER_0_task2.cb       = TIMER_0_task2_cb;
	TIMER_0_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_0, &TIMER_0_task1);
	timer_add_task(&TIMER_0, &TIMER_0_task2);
	timer_start(&TIMER_0);
}

void I2C_0_example(void)
{
	struct io_descriptor *I2C_0_io;

	i2c_m_sync_get_io_descriptor(&I2C_0, &I2C_0_io);
	i2c_m_sync_enable(&I2C_0);
	i2c_m_sync_set_slaveaddr(&I2C_0, 0x12, I2C_M_SEVEN);
	io_write(I2C_0_io, (uint8_t *)"Hello World!", 12);
}

void delay_example(void)
{
	delay_ms(5000);
}

static void button_on_PA02_pressed(void)
{
}

static void button_on_PA03_pressed(void)
{
}

static void button_on_PA04_pressed(void)
{
}

/**
 * Example of using EXTERNAL_IRQ_0
 */
void EXTERNAL_IRQ_0_example(void)
{

	ext_irq_register(PIN_PA02, button_on_PA02_pressed);
	ext_irq_register(PIN_PA03, button_on_PA03_pressed);
	ext_irq_register(PIN_PA04, button_on_PA04_pressed);
}
