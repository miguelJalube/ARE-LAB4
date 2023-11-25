/*****************************************************************************************
 * HEIG-VD
 * Haute Ecole d'Ingenerie et de Gestion du Canton de Vaud
 * School of Business and Engineering in Canton de Vaud
 *****************************************************************************************
 * REDS Institute
 * Reconfigurable Embedded Digital Systems
 *****************************************************************************************
 *
 * File                 : int_defines.h
 * Author               : Anthony Convers
 * Date                 : 27.10.2022
 *
 * Context              : ARE lab
 *
 *****************************************************************************************
 * Brief: Some definitions for the interrupt
 *
 *****************************************************************************************
 * Modifications :
 * Ver    Date        Engineer      Comments
 * 0.0    27.10.2022  ACS           Initial version.
 *
*****************************************************************************************/
#define		CPU0					0x01	// bit-mask; bit 0 represents cpu0
#define		ENABLE					0x1

#define		USER_MODE				0b10000
#define		FIQ_MODE				0b10001
#define		IRQ_MODE				0b10010
#define		SVC_MODE				0b10011
#define		ABORT_MODE				0b10111
#define		UNDEF_MODE				0b11011
#define		SYS_MODE				0b11111

#define		INT_ENABLE				0b01000000
#define		INT_DISABLE				0b11000000

#define     TIMER_IRQ               201
#define     ICCICR                  0xFFFEC100
#define     ICCPMR                  0xFFFEC104
#define     ICCIAR                  0xFFFEC10C
#define     ICCEOIR                 0xFFFEC110
#define     ICDDCR                  0xFFFED000
#define     ICDISER                 0xFFFED100
#define     ICDICER                 0xFFFED180
#define     ICDIPR                  0xFFFED400
#define     ICDIPTR                 0xFFFED800

