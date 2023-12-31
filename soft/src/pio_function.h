/*****************************************************************************************
 * HEIG-VD
 * Haute Ecole d'Ingenerie et de Gestion du Canton de Vaud
 * School of Business and Engineering in Canton de Vaud
 *****************************************************************************************
 * REDS Institute
 * Reconfigurable Embedded Digital Systems
 *****************************************************************************************
 *
 * File                 : pio_function.h
 * Author               : Anthony Convers
 * Date                 : 27.07.2022
 *
 * Context              : ARE lab
 *
 *****************************************************************************************
 * Brief: Header file for pio function
 *
 *****************************************************************************************
 * Modifications :
 * Ver    Date        Student      Comments
 * 0.0    27.07.2022  ACS           Initial version.
 * 0.1    12.10.2023  MJ           
 * 0.2    24.11.2023  MJ           Timer init added
*****************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "axi_lw.h"

//#define DEBUG_PIO 1

// Base address
#define PIO_CORE0_BASE_ADD         0x100 + AXI_LW_HPS_FPGA_BASE_ADD   //To be complete
#define PIO_CORE1_BASE_ADD         0x120 + AXI_LW_HPS_FPGA_BASE_ADD    //To be complete
#define OSC1_0_BASE_ADD            0xFFD00000

// ACCESS MACROS
#define PIO0_REG(_x_)       *(volatile uint32_t *)(PIO_CORE0_BASE_ADD + _x_) // _x_ is an offset with respect to the base address
#define PIO1_REG(_x_)       *(volatile uint32_t *)(PIO_CORE1_BASE_ADD + _x_)
#define OSC1_0_REG(_x_)     *(volatile uint32_t *)(OSC1_0_BASE_ADD + _x_)

// PIO Registers
#define	DATA                0x0
#define DIRECTION           0x4
#define INTERRUPTMASK       0x8
#define EDGECAPTURE         0xc
#define OUTSET              0x10
#define OUTCLEAR            0x14


// Define PIO bits usage
#define SWITCHS_BITS        0x000003FF
#define LEDS_BITS           0x000FFC00
#define KEYS_BITS           0x00F00000
#define SEG7_BITS           0x0FFFFFFF
#define SEG7_BITS_HEX       0x7F

// PIO0 Offsets
#define SWITCHS_OFFSET      0
#define LEDS_OFFSET         10
#define KEY_OFFSET          20
#define INT_MASK_OFFSET     2
#define EDGE_CAPT_OFFSET    3

// PIO1 Offsets
#define HEX0_OFFSET         0
#define HEX1_OFFSET         7
#define HEX2_OFFSET         14
#define HEX3_OFFSET         28

// Timer offsets
#define OSC1_LOAD_OFFSET    0x0
#define OSC1_VAL_OFFSET     0x4   
#define OSC1_CTLREG_OFFSET  0x8
#define OSC1_CLEAR_OFFSET   0xc
#define OSC1_ISTAT_OFFSET   0x10

//***************************//
//****** Init function ******//

// Timer_init function : Initialize the timer
void Timer_init(uint32_t load_value);

// Swicths_init function : Initialize all Switchs in PIO core (SW9 to SW0)
void Switchs_init(void);

// Leds_init function : Initialize all Leds in PIO core (LED9 to LED0)
void Leds_init(void);

// Keys_init function : Initialize all Keys in PIO core (KEY3 to KEY0)
void Keys_init(void);

// Segs7_init function : Initialize all 7-segments display in PIO core (HEX3 to HEX0)
void Segs7_init(void);

//***********************************//
//****** Global usage function ******//

// Timer_start function : Start the timer
// Parameter : None
// Return : timer value in cycles
uint32_t Timer_get_value(void);

// Timer_start function : Start the timer
// Parameter : None
// Return : None
void Timer_start(void);

// Timer_stop function : Stop the timer
// Parameter : None
// Return : None
void Timer_stop(void);

// Switchs_read function : Read the switchs value
// Parameter : None
// Return : Value of all Switchs (SW9 to SW0)
uint32_t Switchs_read(void);

// Leds_write function : Write a value to all Leds (LED9 to LED0)
// Parameter : "value"= data to be applied to all Leds
// Return : None
void Leds_write(uint32_t value);

// Leds_set function : Set to ON some or all Leds (LED9 to LED0)
// Parameter : "maskleds"= Leds selected to apply a set (maximum 0x3FF)
// Return : None
void Leds_set(uint32_t maskleds);

// Leds_clear function : Clear to OFF some or all Leds (LED9 to LED0)
// Parameter : "maskleds"= Leds selected to apply a clear (maximum 0x3FF)
// Return : None
void Leds_clear(uint32_t maskleds);

// Leds_toggle function : Toggle the curent value of some or all Leds (LED9 to LED0)
// Parameter : "maskleds"= Leds selected to apply a toggle (maximum 0x3FF)
// Return : None
void Leds_toggle(uint32_t maskleds);

// Key_read function : Read one Key status, pressed or not (KEY0 or KEY1 or KEY2 or KEY3)
// Parameter : "key_number"= select the key number to read, from 0 to 3
// Return : True(1) if key is pressed, and False(0) if key is not pressed
bool Key_read(int key_number);

// Seg7_write function : Write digit segment value to one 7-segments display (HEX0 or HEX1 or HEX2 or HEX3)
// Parameter : "seg7_number"= select the 7-segments number, from 0 to 3
// Parameter : "value"= digit segment value to be applied on the selected 7-segments (maximum 0x7F to switch ON all segments)
// Return : None
void Seg7_write(int seg7_number, uint32_t value);

// Seg7_write_hex function : Write an Hexadecimal value to one 7-segments display (HEX0 or HEX1 or HEX2 or HEX3)
// Parameter : "seg7_number"= select the 7-segments number, from 0 to 3
// Parameter : "value"= Hexadecimal value to be display on the selected 7-segments, form 0x0 to 0xF
// Return : None
void Seg7_write_hex(int seg7_number, uint32_t value);
