/*****************************************************************************************
 * HEIG-VD
 * Haute Ecole d'Ingenerie et de Gestion du Canton de Vaud
 * School of Business and Engineering in Canton de Vaud
 *****************************************************************************************
 * REDS Institute
 * Reconfigurable Embedded Digital Systems
 *****************************************************************************************
 *
 * File                 : app_timer_irq.c
 * Author               : Anthony Convers
 * Date                 : 27.10.2022
 *
 * Context              : ARE lab
 *
 *****************************************************************************************
 * Brief: Using timer IRQ on DE1-SoC board
 *
 *****************************************************************************************
 * Modifications :
 * Ver    Date        Student      Comments
 * 0.0    27.10.2022  ACS           Initial version.
 *
*****************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "axi_lw.h"
#include "exceptions.h"
#include "pio_function.h"

int __auto_semihosting;

//#define DEBUG           1

#define ID_ADDR         AXI_LW_REG(0)

#define SW98_MASK       0x300
#define SW71_MASK       0x0FF

#define N_KEYS          4
#define N_HEX           4

#define CLOCK_FREQ      25000000

// Update pressed keys
void update_pressed(bool *pressed, size_t size){
    int i;
    for(i = 0; i< size; i++){
        pressed[i] = Key_read(i);
    }
}

// Display timer value
void display_timer(uint32_t timer_value_tenths){
    #ifdef DEBUG
        printf("[display_timer] Timer value : %u\n", timer_value_tenths);
    #endif

    // Convert the value into tenths of a second, seconds, tens of seconds, and hundreds of seconds
    uint32_t tenths = timer_value_tenths % 10;
    uint32_t seconds = (timer_value_tenths / 10) % 10;
    uint32_t tens_seconds = (timer_value_tenths / 100) % 10;
    uint32_t hundreds_seconds = (timer_value_tenths / 1000) % 10;

    // Display the values on the 7-segment displays
    Seg7_write_hex(0, tenths);
    Seg7_write_hex(1, seconds);
    Seg7_write_hex(2, tens_seconds);
    Seg7_write_hex(3, hundreds_seconds);
}

volatile int interrupt_catched = 0;

int main(void){

    // Timer load value
    uint32_t timer_value = 0;

    // Timer on/off
    bool timer_on = false;

    // Which key is pressed
    bool pressed[N_KEYS] = {false, false, false, false};

    // Edge detection for keys
    bool pressed_edge[N_KEYS] = {false, false, false, false};

    
	set_A9_IRQ_stack();

    // Config gic
    config_GIC();

    enable_A9_interrupts();

    // Initialize leds, switches, keys and 7-segments
    Leds_init();
    Switchs_init();
    Keys_init();
    Segs7_init();

    // Turn off al leds
    Leds_clear(0x3ff);

    // Seg7 0 to 3 display 0
    for (size_t i = 0; i < N_HEX; i++)
    {
        Seg7_write_hex(i, 0);
    }

    // Display ID constant
    printf("[main] ID : %#X\n", (unsigned)ID_ADDR);

    
    // Timer init
    // period set to 0.1s
    uint32_t count = 2500000;

    // Load timer period
    Timer_init(count);

    // Main program loop
    while(1){
        // Update key pressed state 2
        update_pressed(pressed_edge, N_KEYS);

        if(!pressed[0] && pressed_edge[0]){
            #ifdef DEBUG
                printf("[main] KEY0 pressed\n");
            #endif

            // Key 0 pressed
            // timer start
            Timer_start();
            
            // Timer on
            timer_on = true;

            // Turn on led 8
            Leds_set(0x100);
        }
        pressed[0] = pressed_edge[0];

        if(!pressed[1] && pressed_edge[1]){
            #ifdef DEBUG
                printf("[main] KEY1 pressed\n");
            #endif

            // Key 1 pressed
            // timer stop
            Timer_stop();

            // Timer off
            timer_on = false;
        }
        pressed[1] = pressed_edge[1];

        if(!pressed[2] && pressed_edge[2]){
            #ifdef DEBUG
                printf("[main] KEY2 pressed\n");
            #endif

            // Key 2 pressed

            // Update led values
            uint32_t sw_value = Switchs_read() & SW71_MASK;
            Leds_write(sw_value);

            timer_value = sw_value * 10;

            // Display timer value
            display_timer(timer_value);
        }
        pressed[2] = pressed_edge[2];

        if(!pressed[3] && pressed_edge[3]){
            #ifdef DEBUG
                printf("[main] KEY3 pressed\n");
            #endif
            // Key 3 pressed
            // used for debug

            #ifdef DEBUG
                display_timer(timer_value);
            #endif
        }
        pressed[3] = pressed_edge[3];

        // Timer interrupt
        if(interrupt_catched && timer_on){
            // Clear interrupt
            interrupt_catched = 0;

            // Toggle led 9
            Leds_toggle(0x200);

            // décrement timer value
            timer_value--;

            // stops the timer when it reaches 0
            if (timer_value == 0)
            {
                // Timer stop
                Timer_stop();
                timer_on = false;
            }
            
            // Refresh display
            display_timer(timer_value);
        }

        // Turn off led 8 if timer is off
        if(!timer_on){
            Leds_clear(0x100);
        }
    }

    return 0;
}
