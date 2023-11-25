/*****************************************************************************************
 * HEIG-VD
 * Haute Ecole d'Ingenerie et de Gestion du Canton de Vaud
 * School of Business and Engineering in Canton de Vaud
 *****************************************************************************************
 * REDS Institute
 * Reconfigurable Embedded Digital Systems
 *****************************************************************************************
 *
 * File                 : execptions.h
 * Author               : Miguel Jalube
 * Date                 : 24.11.2023
 *
 * Context              : ARE lab
 *
 *****************************************************************************************
 * Brief: defines prototypes for the IRQ exception handlers
 *
 *****************************************************************************************
 * Modifications :
 * Ver    Date        Engineer      Comments
 * 0.0    24.11.2023  MJ           Initial version.
 *
*****************************************************************************************/

// Timer count
// used to notify the main programe that the timer has expired
extern volatile int interrupt_catched;

// Define the IRQ exception handler
void __attribute__ ((interrupt)) __cs3_isr_irq (void);

// Define the remaining exception handlers
void __attribute__ ((interrupt)) __cs3_reset (void);

void __attribute__ ((interrupt)) __cs3_isr_undef (void);

void __attribute__ ((interrupt)) __cs3_isr_swi (void);

void __attribute__ ((interrupt)) __cs3_isr_pabort (void);

void __attribute__ ((interrupt)) __cs3_isr_dabort (void);

void __attribute__ ((interrupt)) __cs3_isr_fiq (void);

/* 
 * Initialize the banked stack pointer register for IRQ mode
*/
void set_A9_IRQ_stack(void);

/* 
 * Turn on interrupts in the ARM processor
*/
void enable_A9_interrupts(void);

/* 
 * Configure the Generic Interrupt Controller (GIC)
*/
void config_GIC(void);

void config_interrupt(int N, int CPU_target);

void hps_timer_ISR(void);