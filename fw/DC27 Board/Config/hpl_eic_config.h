/* Auto-generated config file hpl_eic_config.h */
#ifndef HPL_EIC_CONFIG_H
#define HPL_EIC_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Basic Settings

// <o> CKSEL: Clock Selection
// <0x0=> Clocked by GCLK
// <0x1=> Clocked by ULPOSC32K
// <id> ctrla_cksel
#ifndef CONF_EIC_CKSEL
#define CONF_EIC_CKSEL 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> CTRLA <doc-hint.field> CKSEL
#endif

// <o> TICKON: Pin Sampler frequency selection
// <0x0=> Using GCLK_EIC
// <0x1=> Using the low frequency clock
// <id> dprescaler_tickon
#ifndef CONF_EIC_TICKON
#define CONF_EIC_TICKON 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> DPRESCALER <doc-hint.field> TICKON
#endif

// </h>

// <h> Debouncer Settings
// <o> PRESCALER: Debouncer Prescaler
// <0x0=>Divided by 2
// <0x1=>Divided by 4
// <0x2=>Divided by 8
// <0x3=>Divided by 16
// <0x4=>Divided by 32
// <0x5=>Divided by 64
// <0x6=>Divided by 128
// <0x7=>Divided by 256
// <id> dprescaler_prescaler
#ifndef CONF_EIC_DPRESCALER
#define CONF_EIC_DPRESCALER 0x0
// <doc-hint.module> EIC_U2804 <doc-hint.register> DPRESCALER <doc-hint.field> PRESCALER
#endif

// <o>  STATES: Debouncer Number of States
// <0x0=>3
// <0x1=>7
// <id> dprescaler_states
#ifndef CONF_EIC_STATES
#define CONF_EIC_STATES 0x0
// <doc-hint.module> EIC_U2804 <doc-hint.register> DPRESCALER <doc-hint.field> STATES
#endif
// </h>

// <h> Non-secure Interrupt Settings for NMI and External Pin

// <q> NMI: Non-Secure Non-Maskable Interrupt
// <id> nonsec_nmi
#ifndef CONF_EIC_NMI
#define CONF_EIC_NMI 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> NONSEC <doc-hint.field> NMIFILTEN
#endif

// <q> EXTINT0: Non-Secure EXTINT Enable0
// <id> config_nonsecure_extint0
#ifndef CONF_EIC_NONSECURE_EXTINT0
#define CONF_EIC_NONSECURE_EXTINT0 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> NONSEC <doc-hint.field> EXTINT0
#endif

// <q> EXTINT1: Non-Secure EXTINT Enable1
// <id> config_nonsecure_extint1
#ifndef CONF_EIC_NONSECURE_EXTINT1
#define CONF_EIC_NONSECURE_EXTINT1 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> NONSEC <doc-hint.field> EXTINT1
#endif

// <q> EXTINT2: Non-Secure EXTINT Enable2
// <id> config_nonsecure_extint2
#ifndef CONF_EIC_NONSECURE_EXTINT2
#define CONF_EIC_NONSECURE_EXTINT2 1
// <doc-hint.module> EIC_U2804 <doc-hint.register> NONSEC <doc-hint.field> EXTINT2
#endif

// <q> EXTINT3: Non-Secure EXTINT Enable3
// <id> config_nonsecure_extint3
#ifndef CONF_EIC_NONSECURE_EXTINT3
#define CONF_EIC_NONSECURE_EXTINT3 1
// <doc-hint.module> EIC_U2804 <doc-hint.register> NONSEC <doc-hint.field> EXTINT3
#endif

// <q> EXTINT4: Non-Secure EXTINT Enable4
// <id> config_nonsecure_extint4
#ifndef CONF_EIC_NONSECURE_EXTINT4
#define CONF_EIC_NONSECURE_EXTINT4 1
// <doc-hint.module> EIC_U2804 <doc-hint.register> NONSEC <doc-hint.field> EXTINT4
#endif

// <q> EXTINT5: Non-Secure EXTINT Enable5
// <id> config_nonsecure_extint5
#ifndef CONF_EIC_NONSECURE_EXTINT5
#define CONF_EIC_NONSECURE_EXTINT5 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> NONSEC <doc-hint.field> EXTINT5
#endif

// <q> EXTINT6: Non-Secure EXTINT Enable6
// <id> config_nonsecure_extint6
#ifndef CONF_EIC_NONSECURE_EXTINT6
#define CONF_EIC_NONSECURE_EXTINT6 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> NONSEC <doc-hint.field> EXTINT6
#endif

// <q> EXTINT7: Non-Secure EXTINT Enable7
// <id> config_nonsecure_extint7
#ifndef CONF_EIC_NONSECURE_EXTINT7
#define CONF_EIC_NONSECURE_EXTINT7 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> NONSEC <doc-hint.field> EXTINT7
#endif

// </h>

// <e> Non-Maskable Interrupt Control
// <id> nmictrl_configure
#ifndef CONF_EIC_NMICTRL_ENABLE
#define CONF_EIC_NMICTRL_ENABLE 0
#endif

// <q> NMIFILTEN: Non-Maskable Interrupt Filter Enable
// <id> nmictrl_nmifilten
#ifndef CONF_EIC_NMIFILTEN
#define CONF_EIC_NMIFILTEN 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> NMICTRL <doc-hint.field> NMIFILTEN
#endif

// <o> NMISENSE: Non-Maskable Interrupt Sense Configuration
// <0x0=>NONE
// <0x1=>RISE
// <0x2=>FALL
// <0x3=>BOTH
// <0x4=>HIGH
// <0x5=>LOW
// <id> nmictrl_nmisense
#ifndef CONF_EIC_NMISENSE
#define CONF_EIC_NMISENSE 0x0
// <doc-hint.module> EIC_U2804 <doc-hint.register> NMICTRL <doc-hint.field> NMISENSE
#endif

// <q> NMIASYNCH: Non-Maskable Interrupt Asynchronous Edge Detection Mode
// <id> nmictrl_nmiasynch
#ifndef CONF_EIC_NMIASYNCH
#define CONF_EIC_NMIASYNCH 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> NMICTRL <doc-hint.field> NMIASYNCH
#endif
// </e>

// <e> Interrupt 0 Settings
// <id> eic_irq_setting_enable0
#ifndef CONF_EIC_IRQ_SETTING_ENABLE0
#define CONF_EIC_IRQ_SETTING_ENABLE0 0
#endif

// <q> FILTEN0: Filter Enable 0
// <id> config_filten0
#ifndef CONF_EIC_FILTEN0
#define CONF_EIC_FILTEN0 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> CONFIG <doc-hint.field> FILTEN0
#endif

// <q> DEBOUNCEN0: Debouncer Enable 0
// <id> debouncen_debouncen0
#ifndef CONF_EIC_DEBOUNCE_ENABLE0
#define CONF_EIC_DEBOUNCE_ENABLE0 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> DEBOUNCEN <doc-hint.field> DEBOUNCEN
#endif

// <q> EXTINTEO0: External Interrupt Event Output Enable 0
// <id> evctrl_extinteo0
#ifndef CONF_EIC_EXTINTEO0
#define CONF_EIC_EXTINTEO0 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> EVCTRL <doc-hint.field> EXTINTEO
#endif

// <o> SENSE0: Input Sense Configuration 0
// <0x0=>NONE
// <0x1=>RISE
// <0x2=>FALL
// <0x3=>BOTH
// <0x4=>HIGH
// <0x5=>LOW
// <id> config_sense0
#ifndef CONF_EIC_SENSE0
#define CONF_EIC_SENSE0 0x0
// <doc-hint.module> EIC_U2804 <doc-hint.register> CONFIG <doc-hint.field> SENSE0
#endif

// <q> ASYNCH0: Asynchronous Edge Detection Mode 0
// <id> asynch_asynch0
#ifndef CONF_EIC_ASYNCH0
#define CONF_EIC_ASYNCH0 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> ASYNCH <doc-hint.field> ASYNCH
#endif
// </e>

// <e> Interrupt 1 Settings
// <id> eic_irq_setting_enable1
#ifndef CONF_EIC_IRQ_SETTING_ENABLE1
#define CONF_EIC_IRQ_SETTING_ENABLE1 0
#endif

// <q> FILTEN1: Filter Enable 1
// <id> config_filten1
#ifndef CONF_EIC_FILTEN1
#define CONF_EIC_FILTEN1 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> CONFIG <doc-hint.field> FILTEN1
#endif

// <q> DEBOUNCEN1: Debouncer Enable 1
// <id> debouncen_debouncen1
#ifndef CONF_EIC_DEBOUNCE_ENABLE1
#define CONF_EIC_DEBOUNCE_ENABLE1 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> DEBOUNCEN <doc-hint.field> DEBOUNCEN
#endif

// <q> EXTINTEO1: External Interrupt Event Output Enable 1
// <id> evctrl_extinteo1
#ifndef CONF_EIC_EXTINTEO1
#define CONF_EIC_EXTINTEO1 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> EVCTRL <doc-hint.field> EXTINTEO
#endif

// <o> SENSE1: Input Sense Configuration 1
// <0x0=>NONE
// <0x1=>RISE
// <0x2=>FALL
// <0x3=>BOTH
// <0x4=>HIGH
// <0x5=>LOW
// <id> config_sense1
#ifndef CONF_EIC_SENSE1
#define CONF_EIC_SENSE1 0x0
// <doc-hint.module> EIC_U2804 <doc-hint.register> CONFIG <doc-hint.field> SENSE1
#endif

// <q> ASYNCH1: Asynchronous Edge Detection Mode 1
// <id> asynch_asynch1
#ifndef CONF_EIC_ASYNCH1
#define CONF_EIC_ASYNCH1 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> ASYNCH <doc-hint.field> ASYNCH
#endif
// </e>

// <e> Interrupt 2 Settings
// <id> eic_irq_setting_enable2
#ifndef CONF_EIC_IRQ_SETTING_ENABLE2
#define CONF_EIC_IRQ_SETTING_ENABLE2 1
#endif

// <q> FILTEN2: Filter Enable 2
// <id> config_filten2
#ifndef CONF_EIC_FILTEN2
#define CONF_EIC_FILTEN2 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> CONFIG <doc-hint.field> FILTEN2
#endif

// <q> DEBOUNCEN2: Debouncer Enable 2
// <id> debouncen_debouncen2
#ifndef CONF_EIC_DEBOUNCE_ENABLE2
#define CONF_EIC_DEBOUNCE_ENABLE2 1
// <doc-hint.module> EIC_U2804 <doc-hint.register> DEBOUNCEN <doc-hint.field> DEBOUNCEN
#endif

// <q> EXTINTEO2: External Interrupt Event Output Enable 2
// <id> evctrl_extinteo2
#ifndef CONF_EIC_EXTINTEO2
#define CONF_EIC_EXTINTEO2 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> EVCTRL <doc-hint.field> EXTINTEO
#endif

// <o> SENSE2: Input Sense Configuration 2
// <0x0=>NONE
// <0x1=>RISE
// <0x2=>FALL
// <0x3=>BOTH
// <0x4=>HIGH
// <0x5=>LOW
// <id> config_sense2
#ifndef CONF_EIC_SENSE2
#define CONF_EIC_SENSE2 0x2
// <doc-hint.module> EIC_U2804 <doc-hint.register> CONFIG <doc-hint.field> SENSE2
#endif

// <q> ASYNCH2: Asynchronous Edge Detection Mode 2
// <id> asynch_asynch2
#ifndef CONF_EIC_ASYNCH2
#define CONF_EIC_ASYNCH2 1
// <doc-hint.module> EIC_U2804 <doc-hint.register> ASYNCH <doc-hint.field> ASYNCH
#endif
// </e>

// <e> Interrupt 3 Settings
// <id> eic_irq_setting_enable3
#ifndef CONF_EIC_IRQ_SETTING_ENABLE3
#define CONF_EIC_IRQ_SETTING_ENABLE3 1
#endif

// <q> FILTEN3: Filter Enable 3
// <id> config_filten3
#ifndef CONF_EIC_FILTEN3
#define CONF_EIC_FILTEN3 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> CONFIG <doc-hint.field> FILTEN3
#endif

// <q> DEBOUNCEN3: Debouncer Enable 3
// <id> debouncen_debouncen3
#ifndef CONF_EIC_DEBOUNCE_ENABLE3
#define CONF_EIC_DEBOUNCE_ENABLE3 1
// <doc-hint.module> EIC_U2804 <doc-hint.register> DEBOUNCEN <doc-hint.field> DEBOUNCEN
#endif

// <q> EXTINTEO3: External Interrupt Event Output Enable 3
// <id> evctrl_extinteo3
#ifndef CONF_EIC_EXTINTEO3
#define CONF_EIC_EXTINTEO3 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> EVCTRL <doc-hint.field> EXTINTEO
#endif

// <o> SENSE3: Input Sense Configuration 3
// <0x0=>NONE
// <0x1=>RISE
// <0x2=>FALL
// <0x3=>BOTH
// <0x4=>HIGH
// <0x5=>LOW
// <id> config_sense3
#ifndef CONF_EIC_SENSE3
#define CONF_EIC_SENSE3 0x2
// <doc-hint.module> EIC_U2804 <doc-hint.register> CONFIG <doc-hint.field> SENSE3
#endif

// <q> ASYNCH3: Asynchronous Edge Detection Mode 3
// <id> asynch_asynch3
#ifndef CONF_EIC_ASYNCH3
#define CONF_EIC_ASYNCH3 1
// <doc-hint.module> EIC_U2804 <doc-hint.register> ASYNCH <doc-hint.field> ASYNCH
#endif
// </e>

// <e> Interrupt 4 Settings
// <id> eic_irq_setting_enable4
#ifndef CONF_EIC_IRQ_SETTING_ENABLE4
#define CONF_EIC_IRQ_SETTING_ENABLE4 1
#endif

// <q> FILTEN4: Filter Enable 4
// <id> config_filten4
#ifndef CONF_EIC_FILTEN4
#define CONF_EIC_FILTEN4 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> CONFIG <doc-hint.field> FILTEN4
#endif

// <q> DEBOUNCEN4: Debouncer Enable 4
// <id> debouncen_debouncen4
#ifndef CONF_EIC_DEBOUNCE_ENABLE4
#define CONF_EIC_DEBOUNCE_ENABLE4 1
// <doc-hint.module> EIC_U2804 <doc-hint.register> DEBOUNCEN <doc-hint.field> DEBOUNCEN
#endif

// <q> EXTINTEO4: External Interrupt Event Output Enable 4
// <id> evctrl_extinteo4
#ifndef CONF_EIC_EXTINTEO4
#define CONF_EIC_EXTINTEO4 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> EVCTRL <doc-hint.field> EXTINTEO
#endif

// <o> SENSE4: Input Sense Configuration 4
// <0x0=>NONE
// <0x1=>RISE
// <0x2=>FALL
// <0x3=>BOTH
// <0x4=>HIGH
// <0x5=>LOW
// <id> config_sense4
#ifndef CONF_EIC_SENSE4
#define CONF_EIC_SENSE4 0x2
// <doc-hint.module> EIC_U2804 <doc-hint.register> CONFIG <doc-hint.field> SENSE4
#endif

// <q> ASYNCH4: Asynchronous Edge Detection Mode 4
// <id> asynch_asynch4
#ifndef CONF_EIC_ASYNCH4
#define CONF_EIC_ASYNCH4 1
// <doc-hint.module> EIC_U2804 <doc-hint.register> ASYNCH <doc-hint.field> ASYNCH
#endif
// </e>

// <e> Interrupt 5 Settings
// <id> eic_irq_setting_enable5
#ifndef CONF_EIC_IRQ_SETTING_ENABLE5
#define CONF_EIC_IRQ_SETTING_ENABLE5 0
#endif

// <q> FILTEN5: Filter Enable 5
// <id> config_filten5
#ifndef CONF_EIC_FILTEN5
#define CONF_EIC_FILTEN5 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> CONFIG <doc-hint.field> FILTEN5
#endif

// <q> DEBOUNCEN5: Debouncer Enable 5
// <id> debouncen_debouncen5
#ifndef CONF_EIC_DEBOUNCE_ENABLE5
#define CONF_EIC_DEBOUNCE_ENABLE5 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> DEBOUNCEN <doc-hint.field> DEBOUNCEN
#endif

// <q> EXTINTEO5: External Interrupt Event Output Enable 5
// <id> evctrl_extinteo5
#ifndef CONF_EIC_EXTINTEO5
#define CONF_EIC_EXTINTEO5 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> EVCTRL <doc-hint.field> EXTINTEO
#endif

// <o> SENSE5: Input Sense Configuration 5
// <0x0=>NONE
// <0x1=>RISE
// <0x2=>FALL
// <0x3=>BOTH
// <0x4=>HIGH
// <0x5=>LOW
// <id> config_sense5
#ifndef CONF_EIC_SENSE5
#define CONF_EIC_SENSE5 0x0
// <doc-hint.module> EIC_U2804 <doc-hint.register> CONFIG <doc-hint.field> SENSE5
#endif

// <q> ASYNCH5: Asynchronous Edge Detection Mode 5
// <id> asynch_asynch5
#ifndef CONF_EIC_ASYNCH5
#define CONF_EIC_ASYNCH5 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> ASYNCH <doc-hint.field> ASYNCH
#endif
// </e>

// <e> Interrupt 6 Settings
// <id> eic_irq_setting_enable6
#ifndef CONF_EIC_IRQ_SETTING_ENABLE6
#define CONF_EIC_IRQ_SETTING_ENABLE6 0
#endif

// <q> FILTEN6: Filter Enable 6
// <id> config_filten6
#ifndef CONF_EIC_FILTEN6
#define CONF_EIC_FILTEN6 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> CONFIG <doc-hint.field> FILTEN6
#endif

// <q> DEBOUNCEN6: Debouncer Enable 6
// <id> debouncen_debouncen6
#ifndef CONF_EIC_DEBOUNCE_ENABLE6
#define CONF_EIC_DEBOUNCE_ENABLE6 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> DEBOUNCEN <doc-hint.field> DEBOUNCEN
#endif

// <q> EXTINTEO6: External Interrupt Event Output Enable 6
// <id> evctrl_extinteo6
#ifndef CONF_EIC_EXTINTEO6
#define CONF_EIC_EXTINTEO6 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> EVCTRL <doc-hint.field> EXTINTEO
#endif

// <o> SENSE6: Input Sense Configuration 6
// <0x0=>NONE
// <0x1=>RISE
// <0x2=>FALL
// <0x3=>BOTH
// <0x4=>HIGH
// <0x5=>LOW
// <id> config_sense6
#ifndef CONF_EIC_SENSE6
#define CONF_EIC_SENSE6 0x0
// <doc-hint.module> EIC_U2804 <doc-hint.register> CONFIG <doc-hint.field> SENSE6
#endif

// <q> ASYNCH6: Asynchronous Edge Detection Mode 6
// <id> asynch_asynch6
#ifndef CONF_EIC_ASYNCH6
#define CONF_EIC_ASYNCH6 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> ASYNCH <doc-hint.field> ASYNCH
#endif
// </e>

// <e> Interrupt 7 Settings
// <id> eic_irq_setting_enable7
#ifndef CONF_EIC_IRQ_SETTING_ENABLE7
#define CONF_EIC_IRQ_SETTING_ENABLE7 0
#endif

// <q> FILTEN7: Filter Enable 7
// <id> config_filten7
#ifndef CONF_EIC_FILTEN7
#define CONF_EIC_FILTEN7 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> CONFIG <doc-hint.field> FILTEN7
#endif

// <q> DEBOUNCEN7: Debouncer Enable 7
// <id> debouncen_debouncen7
#ifndef CONF_EIC_DEBOUNCE_ENABLE7
#define CONF_EIC_DEBOUNCE_ENABLE7 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> DEBOUNCEN <doc-hint.field> DEBOUNCEN
#endif

// <q> EXTINTEO7: External Interrupt Event Output Enable 7
// <id> evctrl_extinteo7
#ifndef CONF_EIC_EXTINTEO7
#define CONF_EIC_EXTINTEO7 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> EVCTRL <doc-hint.field> EXTINTEO
#endif

// <o> SENSE7: Input Sense Configuration 7
// <0x0=>NONE
// <0x1=>RISE
// <0x2=>FALL
// <0x3=>BOTH
// <0x4=>HIGH
// <0x5=>LOW
// <id> config_sense7
#ifndef CONF_EIC_SENSE7
#define CONF_EIC_SENSE7 0x0
// <doc-hint.module> EIC_U2804 <doc-hint.register> CONFIG <doc-hint.field> SENSE7
#endif

// <q> ASYNCH7: Asynchronous Edge Detection Mode 7
// <id> asynch_asynch7
#ifndef CONF_EIC_ASYNCH7
#define CONF_EIC_ASYNCH7 0
// <doc-hint.module> EIC_U2804 <doc-hint.register> ASYNCH <doc-hint.field> ASYNCH
#endif
// </e>

#define CONFIG_EIC_EXTINT_MAP {2, PIN_PA02}, {3, PIN_PA03}, {4, PIN_PA04},

// <<< end of configuration section >>>

#endif // HPL_EIC_CONFIG_H
