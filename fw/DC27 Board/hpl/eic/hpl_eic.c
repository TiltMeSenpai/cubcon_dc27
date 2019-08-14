
/**
 * \file
 *
 * \brief EIC related functionality implementation.
 *
 * Copyright (c) 2017-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#include <compiler.h>
#include <hpl_eic_config.h>
#include <hpl_ext_irq.h>
#include <string.h>
#include <utils.h>
#include <utils_assert.h>

#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE != 3U))
/* Weak Non-secure callable function. Real one should be in secure gateway library. */
struct ext_irq_setting {
	uint32_t evctrl;    /* EIC.EVCTRL register value */
	uint32_t config[1]; /* EIC.CONFIG register value */
	uint32_t asynch;    /* EIC.ASYNCH register value */
	uint32_t debouncen; /* EIC.DEBOUNCEN register value */
};

WEAK int32_t nsc_ext_irq_init(struct ext_irq_setting irq_setting)
{
	(void)irq_setting;
	return 0;
}
#endif

#ifdef __MINGW32__
#define ffs __builtin_ffs
#endif
#if defined(__CC_ARM) || defined(__ICCARM__) || (__ARMCOMPILER_VERSION > 6000000)
/* Find the first bit set */
static int ffs(int v)
{
	int i, bit = 1;
	for (i = 0; i < sizeof(int) * 8; i++) {
		if (v & bit) {
			return i + 1;
		}
		bit <<= 1;
	}
	return 0;
}
#endif

/**
 * \brief Invalid external interrupt and pin numbers
 */
#define INVALID_EXTINT_NUMBER 0xFF
#define INVALID_PIN_NUMBER 0xFFFFFFFF

#ifndef CONFIG_EIC_EXTINT_MAP
/** Dummy mapping to pass compiling. */
#define CONFIG_EIC_EXTINT_MAP                                                                                          \
	{                                                                                                                  \
		INVALID_EXTINT_NUMBER, INVALID_PIN_NUMBER                                                                      \
	}
#endif

#define EXT_IRQ_AMOUNT 3

/**
 * \brief EXTINTx and pin number map
 */
struct _eic_map {
	uint8_t  extint;
	uint32_t pin;
};

/**
 * \brief PIN and EXTINT map for enabled external interrupts
 */
static const struct _eic_map _map[] = {CONFIG_EIC_EXTINT_MAP};

/**
 * \brief The callback to upper layer's interrupt processing routine
 */
static void (*callback)(const uint32_t pin);

static void _ext_irq_handler(void);

/**
 * \brief Initialize external interrupt module
 */
int32_t _ext_irq_init(void (*cb)(const uint32_t pin))
{

#define REG_EVCTRL_VAL                                                                                                 \
	((CONF_EIC_EXTINTEO0 << 0) | (CONF_EIC_EXTINTEO1 << 1) | (CONF_EIC_EXTINTEO2 << 2) | (CONF_EIC_EXTINTEO3 << 3)     \
	 | (CONF_EIC_EXTINTEO4 << 4) | (CONF_EIC_EXTINTEO5 << 5) | (CONF_EIC_EXTINTEO6 << 6) | (CONF_EIC_EXTINTEO7 << 7)   \
	 | 0)

#define REG_ASYNCH_VAL                                                                                                 \
	((CONF_EIC_ASYNCH0 << 0) | (CONF_EIC_ASYNCH1 << 1) | (CONF_EIC_ASYNCH2 << 2) | (CONF_EIC_ASYNCH3 << 3)             \
	 | (CONF_EIC_ASYNCH4 << 4) | (CONF_EIC_ASYNCH5 << 5) | (CONF_EIC_ASYNCH6 << 6) | (CONF_EIC_ASYNCH7 << 7) | 0)

#define REG_DEBOUNCEN_VAL                                                                                              \
	((CONF_EIC_DEBOUNCE_ENABLE0 << 0) | (CONF_EIC_DEBOUNCE_ENABLE1 << 1) | (CONF_EIC_DEBOUNCE_ENABLE2 << 2)            \
	 | (CONF_EIC_DEBOUNCE_ENABLE3 << 3) | (CONF_EIC_DEBOUNCE_ENABLE4 << 4) | (CONF_EIC_DEBOUNCE_ENABLE5 << 5)          \
	 | (CONF_EIC_DEBOUNCE_ENABLE6 << 6) | (CONF_EIC_DEBOUNCE_ENABLE7 << 7) | 0)

#define REG_CONFIG0_VAL                                                                                                \
	((CONF_EIC_FILTEN0 << EIC_CONFIG_FILTEN0_Pos) | EIC_CONFIG_SENSE0(CONF_EIC_SENSE0)                                 \
	 | (CONF_EIC_FILTEN1 << EIC_CONFIG_FILTEN1_Pos) | EIC_CONFIG_SENSE1(CONF_EIC_SENSE1)                               \
	 | (CONF_EIC_FILTEN2 << EIC_CONFIG_FILTEN2_Pos) | EIC_CONFIG_SENSE2(CONF_EIC_SENSE2)                               \
	 | (CONF_EIC_FILTEN3 << EIC_CONFIG_FILTEN3_Pos) | EIC_CONFIG_SENSE3(CONF_EIC_SENSE3)                               \
	 | (CONF_EIC_FILTEN4 << EIC_CONFIG_FILTEN4_Pos) | EIC_CONFIG_SENSE4(CONF_EIC_SENSE4)                               \
	 | (CONF_EIC_FILTEN5 << EIC_CONFIG_FILTEN5_Pos) | EIC_CONFIG_SENSE5(CONF_EIC_SENSE5)                               \
	 | (CONF_EIC_FILTEN6 << EIC_CONFIG_FILTEN6_Pos) | EIC_CONFIG_SENSE6(CONF_EIC_SENSE6)                               \
	 | (CONF_EIC_FILTEN7 << EIC_CONFIG_FILTEN7_Pos) | EIC_CONFIG_SENSE7(CONF_EIC_SENSE7) | 0)

	if (!hri_eic_is_syncing(EIC_SEC, EIC_SYNCBUSY_SWRST)) {
		if (hri_eic_get_CTRLA_reg(EIC_SEC, EIC_CTRLA_ENABLE)) {
			hri_eic_clear_CTRLA_ENABLE_bit(EIC_SEC);
			hri_eic_wait_for_sync(EIC_SEC, EIC_SYNCBUSY_ENABLE);
		}
		hri_eic_write_CTRLA_reg(EIC_SEC, EIC_CTRLA_SWRST);
	}
	hri_eic_wait_for_sync(EIC_SEC, EIC_SYNCBUSY_SWRST);

	hri_eic_write_CTRLA_CKSEL_bit(EIC_SEC, CONF_EIC_CKSEL);

	hri_eic_write_NONSEC_reg(
	    EIC_SEC,
	    (CONF_EIC_NMI << EIC_NONSEC_NMI_Pos) | (CONF_EIC_NONSECURE_EXTINT7 << 7) | (CONF_EIC_NONSECURE_EXTINT6 << 6)
	        | (CONF_EIC_NONSECURE_EXTINT5 << 5) | (CONF_EIC_NONSECURE_EXTINT4 << 4) | (CONF_EIC_NONSECURE_EXTINT3 << 3)
	        | (CONF_EIC_NONSECURE_EXTINT2 << 2) | (CONF_EIC_NONSECURE_EXTINT1 << 1) | CONF_EIC_NONSECURE_EXTINT0);

	hri_eic_write_DPRESCALER_reg(EIC_SEC,
	                             (EIC_DPRESCALER_PRESCALER0(CONF_EIC_DPRESCALER))
	                                 | (CONF_EIC_STATES << EIC_DPRESCALER_STATES0_Pos)
	                                 | CONF_EIC_TICKON << EIC_DPRESCALER_TICKON_Pos | 0);

#if (CONF_EIC_NMICTRL_ENABLE == 1)
	hri_eic_write_NMICTRL_reg(EIC_SEC,
	                          (CONF_EIC_NMIFILTEN << EIC_NMICTRL_NMIFILTEN_Pos)
	                              | EIC_NMICTRL_NMISENSE(CONF_EIC_NMISENSE) | EIC_ASYNCH_ASYNCH(CONF_EIC_NMIASYNCH)
	                              | 0);
#endif

	hri_eic_write_EVCTRL_reg(EIC_SEC, REG_EVCTRL_VAL);
	hri_eic_write_ASYNCH_reg(EIC_SEC, REG_ASYNCH_VAL);
	hri_eic_write_DEBOUNCEN_reg(EIC_SEC, REG_DEBOUNCEN_VAL);
	hri_eic_write_CONFIG_reg(EIC_SEC, 0, REG_CONFIG0_VAL);

	hri_eic_set_CTRLA_ENABLE_bit(EIC_SEC);

	NVIC_DisableIRQ(EIC_2_IRQn);
	NVIC_ClearPendingIRQ(EIC_2_IRQn);
	NVIC_EnableIRQ(EIC_2_IRQn);
	NVIC_DisableIRQ(EIC_3_IRQn);
	NVIC_ClearPendingIRQ(EIC_3_IRQn);
	NVIC_EnableIRQ(EIC_3_IRQn);
	NVIC_DisableIRQ(EIC_OTHER_IRQn);
	NVIC_ClearPendingIRQ(EIC_OTHER_IRQn);
	NVIC_EnableIRQ(EIC_OTHER_IRQn);

	callback = cb;

	return ERR_NONE;
}

/**
 * \brief De-initialize external interrupt module
 */
int32_t _ext_irq_deinit(void)
{

	NVIC_DisableIRQ(EIC_2_IRQn);
	NVIC_DisableIRQ(EIC_3_IRQn);
	NVIC_DisableIRQ(EIC_OTHER_IRQn);

	callback = NULL;

	hri_eic_clear_CTRLA_ENABLE_bit(EIC_SEC);
	hri_eic_set_CTRLA_SWRST_bit(EIC_SEC);

	return ERR_NONE;
}

/**
 * \brief Enable / disable external irq
 */
int32_t _ext_irq_enable(const uint32_t pin, const bool enable)
{
	uint8_t extint = INVALID_EXTINT_NUMBER;
	uint8_t i      = 0;

	for (; i < ARRAY_SIZE(_map); i++) {
		if (_map[i].pin == pin) {
			extint = _map[i].extint;
			break;
		}
	}
	if (INVALID_EXTINT_NUMBER == extint) {
		return -1;
	}

	if (enable) {
		hri_eic_set_INTEN_reg(EIC_SEC, 1ul << extint);
	} else {
		hri_eic_clear_INTEN_reg(EIC_SEC, 1ul << extint);
		hri_eic_clear_INTFLAG_reg(EIC_SEC, 1ul << extint);
	}

	return ERR_NONE;
}

/**
 * \brief Inter EIC interrupt handler
 */
static void _ext_irq_handler(void)
{
	volatile uint32_t flags = hri_eic_read_INTFLAG_reg(EIC_SEC);
	int8_t            pos;
	uint32_t          pin = INVALID_PIN_NUMBER;

	hri_eic_clear_INTFLAG_reg(EIC_SEC, flags);

	ASSERT(callback);

	while (flags) {
		pos = ffs(flags) - 1;
		while (-1 != pos) {
			uint8_t lower = 0, middle, upper = EXT_IRQ_AMOUNT;

			while (upper >= lower) {
				middle = (upper + lower) >> 1;
				if (_map[middle].extint == pos) {
					pin = _map[middle].pin;
					break;
				}
				if (_map[middle].extint < pos) {
					lower = middle + 1;
				} else {
					upper = middle - 1;
				}
			}

			if (INVALID_PIN_NUMBER != pin) {
				callback(pin);
			}
			flags &= ~(1ul << pos);
			pos = ffs(flags) - 1;
		}
		flags = hri_eic_read_INTFLAG_reg(EIC_SEC);
		hri_eic_clear_INTFLAG_reg(EIC_SEC, flags);
	}
}

/**
 * \brief EIC interrupt handler
 */
void EIC_2_Handler(void)
{
	_ext_irq_handler();
} /**
   * \brief EIC interrupt handler
   */
void EIC_3_Handler(void)
{
	_ext_irq_handler();
} /**
   * \brief EIC interrupt handler
   */
void EIC_OTHER_Handler(void)
{
	_ext_irq_handler();
}
